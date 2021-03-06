// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: responseprotos.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "responseprotos.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace card_protobuf {

namespace {

const ::google::protobuf::Descriptor* Response_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Response_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* ResponseCode_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_responseprotos_2eproto() {
  protobuf_AddDesc_responseprotos_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "responseprotos.proto");
  GOOGLE_CHECK(file != NULL);
  Response_descriptor_ = file->message_type(0);
  static const int Response_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Response, response_code_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Response, error_description_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Response, data_),
  };
  Response_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Response_descriptor_,
      Response::default_instance_,
      Response_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Response, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Response, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Response));
  ResponseCode_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_responseprotos_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Response_descriptor_, &Response::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_responseprotos_2eproto() {
  delete Response::default_instance_;
  delete Response_reflection_;
}

void protobuf_AddDesc_responseprotos_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::card_protobuf::protobuf_AddDesc_commonprotocol_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\024responseprotos.proto\022\rcard_protobuf\032\024c"
    "ommonprotocol.proto\"|\n\010Response\0222\n\rrespo"
    "nse_code\030\001 \002(\0162\033.card_protobuf.ResponseC"
    "ode\022\031\n\021error_description\030\002 \001(\t\022!\n\004data\030\003"
    " \003(\0132\023.card_protobuf.Data*\375\002\n\014ResponseCo"
    "de\022\007\n\002OK\020\310\001\022\013\n\006ACCEPT\020\312\001\022\024\n\017PARTIAL_CONT"
    "ENT\020\313\001\022\020\n\013SERVER_BUSY\020\372\001\022\020\n\013BAD_REQUEST\020"
    "\220\003\022\021\n\014UNAUTHORIZED\020\221\003\022\016\n\tFORBIDDEN\020\223\003\022\016\n"
    "\tNOT_FOUND\020\224\003\022\024\n\017REQUEST_TIMEOUT\020\230\003\022\027\n\022I"
    "NTERVAL_TOO_SHORT\020\270\003\022\r\n\010OFF_LINE\020\330\004\022\017\n\nS"
    "END_ERROR\020\331\004\022\032\n\025SERVER_INTERNAL_ERROR\020\364\003"
    "\022\022\n\rNOT_IMPLEMENT\020\365\003\022\030\n\023SERVICE_UNAVAILA"
    "BLE\020\367\003\022\024\n\017GATEWAY_TIMEOUT\020\370\003\022\030\n\023UNSUPPOR"
    "TED_VERSION\020\345\007\022\023\n\016PROTOCOL_ERROR\020\346\007\022\014\n\007U"
    "NKNOWN\020\347\007B\002H\001", 573);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "responseprotos.proto", &protobuf_RegisterTypes);
  Response::default_instance_ = new Response();
  Response::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_responseprotos_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_responseprotos_2eproto {
  StaticDescriptorInitializer_responseprotos_2eproto() {
    protobuf_AddDesc_responseprotos_2eproto();
  }
} static_descriptor_initializer_responseprotos_2eproto_;
const ::google::protobuf::EnumDescriptor* ResponseCode_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ResponseCode_descriptor_;
}
bool ResponseCode_IsValid(int value) {
  switch(value) {
    case 200:
    case 202:
    case 203:
    case 250:
    case 400:
    case 401:
    case 403:
    case 404:
    case 408:
    case 440:
    case 500:
    case 501:
    case 503:
    case 504:
    case 600:
    case 601:
    case 997:
    case 998:
    case 999:
      return true;
    default:
      return false;
  }
}


// ===================================================================

#ifndef _MSC_VER
const int Response::kResponseCodeFieldNumber;
const int Response::kErrorDescriptionFieldNumber;
const int Response::kDataFieldNumber;
#endif  // !_MSC_VER

Response::Response()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:card_protobuf.Response)
}

void Response::InitAsDefaultInstance() {
}

Response::Response(const Response& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:card_protobuf.Response)
}

void Response::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  response_code_ = 200;
  error_description_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Response::~Response() {
  // @@protoc_insertion_point(destructor:card_protobuf.Response)
  SharedDtor();
}

void Response::SharedDtor() {
  if (error_description_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete error_description_;
  }
  if (this != default_instance_) {
  }
}

void Response::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Response::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Response_descriptor_;
}

const Response& Response::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_responseprotos_2eproto();
  return *default_instance_;
}

Response* Response::default_instance_ = NULL;

Response* Response::New() const {
  return new Response;
}

void Response::Clear() {
  if (_has_bits_[0 / 32] & 3) {
    response_code_ = 200;
    if (has_error_description()) {
      if (error_description_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        error_description_->clear();
      }
    }
  }
  data_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Response::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:card_protobuf.Response)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .card_protobuf.ResponseCode response_code = 1;
      case 1: {
        if (tag == 8) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::card_protobuf::ResponseCode_IsValid(value)) {
            set_response_code(static_cast< ::card_protobuf::ResponseCode >(value));
          } else {
            mutable_unknown_fields()->AddVarint(1, value);
          }
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_error_description;
        break;
      }

      // optional string error_description = 2;
      case 2: {
        if (tag == 18) {
         parse_error_description:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_error_description()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->error_description().data(), this->error_description().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "error_description");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_data;
        break;
      }

      // repeated .card_protobuf.Data data = 3;
      case 3: {
        if (tag == 26) {
         parse_data:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_data()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_data;
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:card_protobuf.Response)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:card_protobuf.Response)
  return false;
#undef DO_
}

void Response::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:card_protobuf.Response)
  // required .card_protobuf.ResponseCode response_code = 1;
  if (has_response_code()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->response_code(), output);
  }

  // optional string error_description = 2;
  if (has_error_description()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->error_description().data(), this->error_description().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "error_description");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->error_description(), output);
  }

  // repeated .card_protobuf.Data data = 3;
  for (int i = 0; i < this->data_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->data(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:card_protobuf.Response)
}

::google::protobuf::uint8* Response::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:card_protobuf.Response)
  // required .card_protobuf.ResponseCode response_code = 1;
  if (has_response_code()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->response_code(), target);
  }

  // optional string error_description = 2;
  if (has_error_description()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->error_description().data(), this->error_description().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "error_description");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->error_description(), target);
  }

  // repeated .card_protobuf.Data data = 3;
  for (int i = 0; i < this->data_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->data(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:card_protobuf.Response)
  return target;
}

int Response::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .card_protobuf.ResponseCode response_code = 1;
    if (has_response_code()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->response_code());
    }

    // optional string error_description = 2;
    if (has_error_description()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->error_description());
    }

  }
  // repeated .card_protobuf.Data data = 3;
  total_size += 1 * this->data_size();
  for (int i = 0; i < this->data_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->data(i));
  }

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Response::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Response* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Response*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Response::MergeFrom(const Response& from) {
  GOOGLE_CHECK_NE(&from, this);
  data_.MergeFrom(from.data_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_response_code()) {
      set_response_code(from.response_code());
    }
    if (from.has_error_description()) {
      set_error_description(from.error_description());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Response::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Response::CopyFrom(const Response& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Response::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  if (!::google::protobuf::internal::AllAreInitialized(this->data())) return false;
  return true;
}

void Response::Swap(Response* other) {
  if (other != this) {
    std::swap(response_code_, other->response_code_);
    std::swap(error_description_, other->error_description_);
    data_.Swap(&other->data_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Response::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Response_descriptor_;
  metadata.reflection = Response_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace card_protobuf

// @@protoc_insertion_point(global_scope)
