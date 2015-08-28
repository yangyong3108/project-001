#include "conn.h"
#include <unistd.h>
#include "dbhelper.h"
#include <string.h>
//#include "user.pb.h"
//#include "proto/logininfoprotos.pb.h"
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/io/coded_stream.h>
#include "global.h"
#include "proto/commonprotocol.pb.h"
#include "proto/logininfoprotos.pb.h"
#include "proto/responseprotos.pb.h"
#include "proto/protobufresponse.pb.h"
#include "proto/requestprotocol.pb.h"
#include <time.h>
#include <errno.h>
#include "json/json.h"
#include "NetMessageNo.h"

using namespace google::protobuf::io;
using namespace google::protobuf;
using namespace card_protobuf;

static pthread_mutex_t conn_lock = PTHREAD_MUTEX_INITIALIZER;
static int freecurr;
static int freetotal;
static conn **freeconns;

extern Global G;

void conn_init()
{
	freetotal = 200;
	freecurr = 0;
	if ((freeconns = (conn**)calloc(freetotal, sizeof(conn*))) == NULL)
	  printf("Failed to allocate connection structures\n");

	return;
}

conn* conn_new(const int sfd, enum conn_states init_state, const int event_flags 
			, enum network_transport transport, struct event_base *base)
{
	conn *c = conn_from_freelist();
	if (NULL == c)
	{
		if ((c = (conn*)calloc(1, sizeof(conn))) == NULL)
		{
			printf("Failed to allocate conn");
			return NULL;
		}
	}	

	//int nCurCount(0);
	//if (c->redisHelp.addServerCounter(nCurCount))
	//  printf("cur count:%d\n", nCurCount);

	//c->nUserId = 0;
	c->bAuth = false;

	c->sfd = sfd;
	event_set(&c->read_event, sfd, event_flags, do_read, (void*)c);
	event_set(&c->write_event, sfd, EV_WRITE|EV_PERSIST, do_write, (void*)c);
	event_base_set(base, &c->read_event);
	event_base_set(base, &c->write_event);
	c->ev_flags = event_flags;
	if (-1 == event_add(&c->read_event, 0))
	{
		if (conn_add_to_freelist(c))
		  conn_free(c);
		printf("event_add error");

		return NULL;
	}
	return c;
}

conn *conn_from_freelist()
{
	conn *c;
	pthread_mutex_lock(&conn_lock);

	if (freecurr > 0)
	  c = freeconns[--freecurr];
	else
	  c = NULL;

	pthread_mutex_unlock(&conn_lock);

	return c;
}

void do_read(const int fd, const short which, void *arg)
{
	conn *c = (conn*)arg;
	char buff[65535];
	ssize_t result = recv(fd, buff, sizeof(buff), 0);
	if (result == 0) // client close
	{
		cleanconn(c);
	}
	else if (result < 0)
	{
		if (errno == EAGAIN) // socker buff has no data
		{
			return;
		}
		perror("recv error");
		cleanconn(c);
	}
	else
	{
		c->read_dataqueue.push(buff, result);
		process_data(&c->read_dataqueue, c);
	}


	//send(fd, "copy data", 9, 0);
	//CodedInputStream* coded_input = new CodedInputStream((uint8_t*)(c->read_buffer + c->had_read_size), result);
	//uint32_t datalen;
	//coded_input->ReadVarint32(&datalen);
	//printf("datalen:%d\n", datalen);
	//User u;
	//	LoginInfo loginInfo;

	//send(fd, r[0][1].c_str(), strlen(r[0][1].c_str()), 0);
}

bool conn_add_to_freelist(conn *c)
{
	bool ret(true);
	pthread_mutex_lock(&conn_lock);
	if (freecurr < freetotal)
	{
		freeconns[freecurr++] = c;
		ret = false;
	}
	else
	{
		size_t newsize = freetotal * 2;
		conn **new_freeconns = (conn**)realloc(freeconns, sizeof(conn*) * newsize);
		if (new_freeconns)
		{
			freetotal = newsize;
			freeconns = new_freeconns;
			freeconns[freecurr++] = c;
			ret = false;
		}
	}
	pthread_mutex_unlock(&conn_lock);

	return ret;
}

void conn_free(conn *c)
{
	if (c)
	{
		free(c);
	}
}

void cleanconn(conn *c)
{
	c->redisHelp.disconnect();
	map<string, user_data*>::iterator it = G.m_userdata.find(c->strUserId);
	if (it != G.m_userdata.end())
	{
		delete it->second;
		G.m_userdata.erase(it);
	}
	printf("client close\n");
	event_del(&c->read_event);
	event_del(&c->write_event);
	//	event_free(&c->read_event);
	//	event_free(&c->write_event);
	if (conn_add_to_freelist(c))
	  conn_free(c);
}

bool process_data(DataQueue *dq, conn *c)
{
	int nPos(0);
	int nPackage = dq->getPos();

	while (1)
	{
		if (nPackage <= 0)
		  break;

		CodedInputStream* coded_input = new CodedInputStream((uint8_t*)(dq->getBuf()+nPos), dq->getPos()-nPos);
		autoptr<CodedInputStream> inputguard(coded_input);

		int nOldPos = coded_input->CurrentPosition();

		uint32_t datalen;
		if (!coded_input->ReadVarint32(&datalen))
		{
			dq->pop(nPos);	
			break;
		}

		int nNewPos = coded_input->CurrentPosition();
		if (nNewPos+datalen > nPackage)
		{
			//一个包没有收整
			if (nPos > 0)
			{
				dq->pop(nPos);
			}

			break;
		}
		else if (nNewPos + datalen == nPackage)
		{
			char* data = new char[datalen];
			autoptr_arr<char> arrdata(data);
			if (coded_input->ReadRaw(data, datalen))
			{
				parse_package(data,datalen, c);
			}

			dq->setPos(0);
			break;
		}
		else
		{
			char* data = new char[datalen];
			autoptr_arr<char> arrdata(data);

			if (coded_input->ReadRaw(data, datalen))
			{
				parse_package(data, datalen, c);
			}

			nPackage -= datalen+nNewPos-nOldPos;
			nPos += datalen+nNewPos-nOldPos;
		}
	}

	return true;
}

void parse_package(const char *buff, size_t len, conn *c)
{
	if (buff == NULL || len <= 0)
	  return;

	TopMessage msg;
	if (!msg.ParseFromArray(buff, len))
	  return;
	const int64 &nSeq = msg.seq();
	switch (msg.msg_type())
	{
		default:
			break;
		case REQUEST:
			{
				switch (msg.sub_msg_type())
				{
					default:
						break;
					case LOGIN:
						{
							LoginInfo loginInfo;
							if (!loginInfo.ParseFromString(msg.data()))
							{
								perror("parse logininfo error!\n");
								return;
							}
							string strSql("select userid, username from t_user where username='");
							strSql.append(loginInfo.username());
							strSql.append("' and password='");
							strSql.append(loginInfo.password());
							strSql.append("' ");
							pqxx::result r = query(strSql.c_str());
							if (!r.empty())
							{

								c->bAuth = true;
								c->strUserId = r[0][0].c_str();
								user_data *pUserData = new user_data;
								pUserData->fd = c->sfd;
								c->redisHelp.connect();

								G.m_userdata.insert(map<string, user_data*>::value_type(c->strUserId, pUserData));
								//msg.set_data(&rsp, rsp.ByteSize());
								printf("auth success ready send data\n");								
								ProtobufResponseData prData;
								ProtobufColumnInfo *colInfo = prData.add_columninfo();
								RowValue *rValue = prData.add_rowvalue();
								colInfo->set_name("money");
								colInfo->set_type(ProtobufColumnInfo::INT32);
								colInfo = prData.add_columninfo();
								colInfo->set_name("username");
								colInfo->set_type(ProtobufColumnInfo::STRING);
								colInfo = prData.add_columninfo();
								colInfo->set_name("userid");
								colInfo->set_type(ProtobufColumnInfo::STRING);
								RowValue_ColumnValue *cValue = rValue->add_columnvalue();
								cValue->set_int32value(1000);
								cValue = rValue->add_columnvalue();
								cValue->set_stringvalue(r[0][1].c_str());
								cValue = rValue->add_columnvalue();
								cValue->set_stringvalue(r[0][0].c_str());
								int nPrDataSize(prData.ByteSize());
								char *szPrData = new char[nPrDataSize];
								autoptr_arr<char> arrGuard(szPrData);
								if (!prData.SerializeToArray(szPrData, nPrDataSize))
								{
									printf("serialize error!\n");
									return;
								}

								Response rsp;
								rsp.set_response_code(OK);
								Data *loginData = rsp.add_data();
								loginData->set_type(PROTOBUF);
								loginData->set_value(szPrData, nPrDataSize);


								int nRspSize(rsp.ByteSize());
								char *szRsp = new char[nRspSize];
								autoptr_arr<char> guardRsp(szRsp);
								if (!rsp.SerializeToArray(szRsp, nRspSize))
								{
									printf("serialize error!\n");
									return;
								}

								TopMessage msg;
								msg.set_protocol_version("1.0");
								msg.set_msg_type(RESPONSE);
								msg.set_sub_msg_type(LOGIN);
								msg.set_seq(nSeq);
								msg.set_session_id("0");
								time_t t;
								time(&t);
								msg.set_timestamp(t);
								msg.set_data(szRsp, nRspSize);
								int nDataSize(msg.ByteSize());
								int nHeadSize(CodedOutputStream::VarintSize32(nDataSize));
								char *szData = new char[nDataSize];
								autoptr_arr<char> guardData(szData);
								if (!msg.SerializeToArray(szData, nDataSize))
								{
									printf("serialize error!\n");
									return;
								}
								char *szTemp = new char[nDataSize + nHeadSize];
								autoptr_arr<char> guardTemp(szTemp);
								ZeroCopyOutputStream *raw_output = new ArrayOutputStream(szTemp, nDataSize + nHeadSize);
								autoptr<ZeroCopyOutputStream> guardRawOutput(raw_output);
								CodedOutputStream *code_output = new CodedOutputStream(raw_output);
								autoptr<CodedOutputStream> guardCodedOutput(code_output);
								code_output->WriteVarint32(nDataSize);
								code_output->WriteRaw(szData, nDataSize);

								c->write_dataqueue.push(szTemp, nDataSize + nHeadSize);
								if (-1 == event_add(&c->write_event, NULL))
								{
									perror("event add error");
									return;
								}
							}
							else
							{
								Response rsp;
								rsp.set_response_code(NOT_FOUND);

								int nRspSize(rsp.ByteSize());
								char *szRsp = new char[nRspSize];
								autoptr_arr<char> guardRsp(szRsp);
								if (!rsp.SerializeToArray(szRsp, nRspSize))
								{
									perror("serialize error!");
									return;
								}
								TopMessage msg;
								msg.set_protocol_version("1.0");
								msg.set_msg_type(RESPONSE);
								msg.set_sub_msg_type(LOGIN);
								msg.set_seq(nSeq);
								msg.set_session_id("0");
								time_t t;
								time(&t);
								msg.set_timestamp(t);
								msg.set_data(szRsp, nRspSize);
								int nDataSize(msg.ByteSize());
								int nHeadSize(CodedOutputStream::VarintSize32(nDataSize));
								char *szData = new char[nDataSize];
								autoptr_arr<char> guardData(szData);
								if (!msg.SerializeToArray(szData, nDataSize))
								{
									perror("serialize error");
									return;
								}
								char *szTemp = new char[nDataSize + nHeadSize];
								autoptr_arr<char> guardTemp(szTemp);
								ZeroCopyOutputStream *raw_output = new ArrayOutputStream(szTemp, nDataSize + nHeadSize);
								autoptr<ZeroCopyOutputStream> guardRawOutput(raw_output);
								CodedOutputStream *code_output = new CodedOutputStream(raw_output);
								autoptr<CodedOutputStream> guardCodeOutput(code_output);
								code_output->WriteVarint32(nDataSize);
								code_output->WriteRaw(szData, nDataSize);
								c->write_dataqueue.push(szTemp, nDataSize + nHeadSize);
								if (-1 == event_add(&c->write_event, NULL))
								{
									perror("event add error");
									return;
								}
							}

						}
						break;  // end Login
					case POST:
						{
							Request req;
							if (!req.ParseFromString(msg.data()))
							{
								perror("parse post data error!\n");
								return;
							}
							case (req.msgid)
							{
								default:
									break;
								case MSG_TABLESINFO:
									{
										
									}
									break;
							}
						}
						break; // end post
				}
			}
			break;
	}

}


void do_write(const int fd, const short which, void *arg)
{
	conn *c = (conn*)arg;
	ssize_t result = send(fd, c->write_dataqueue.getBuf(), c->write_dataqueue.getPos(), 0);
	if (result > 0)
	  c->write_dataqueue.pop(result);
	if (c->write_dataqueue.getPos() == 0)
	{
		printf("send data:%d\n", result);
		event_del(&c->write_event);
	}
}
