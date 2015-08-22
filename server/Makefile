CC := g++
CFLAGS := -levent -pthread -lpqxx -lpq -lprotobuf -lhiredis
OBJECTS := main.cpp cq.o conn.o WorkerThreads.o dbhelper.o user.pb.o DataQueue.o commonprotocol.pb.o logininfoprotos.pb.o responseprotos.pb.o protobufresponse.pb.o jsoncpp.o
tmp:$(OBJECTS)
	$(CC) $(OBJECTS) -o tmp $(CFLAGS)
cq.o:cq.cpp cq.h
	$(CC) cq.cpp -c -g
conn.o:conn.cpp conn.h libevent_thread.h
	$(CC) conn.cpp -c -g
WorkerThreads.o:WorkerThreads.cpp WorkerThreads.h
	$(CC) WorkerThreads.cpp -c -g
dbhelper.o:dbhelper.cpp dbhelper.h
	$(CC) dbhelper.cpp -c -g
user.pb.o:user.pb.cc user.pb.h
	$(CC) user.pb.cc -c -g
DataQueue.o:DataQueue.cpp
	$(CC) DataQueue.cpp -c -g
commonprotocol.pb.o:proto/commonprotocol.pb.cc
	$(CC) proto/commonprotocol.pb.cc -c -g
logininfoprotos.pb.o:proto/logininfoprotos.pb.cc
	$(CC) proto/logininfoprotos.pb.cc -c -g
responseprotos.pb.o:proto/responseprotos.pb.cc
	$(CC) proto/responseprotos.pb.cc -c -g
protobufresponse.pb.o:proto/protobufresponse.pb.cc
	$(CC) proto/protobufresponse.pb.cc -c -g
jsoncpp.o:json/jsoncpp.cpp
	$(CC) json/jsoncpp.cpp -c -g
clean:
	rm tmp *.o
