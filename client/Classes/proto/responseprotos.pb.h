// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: responseprotos.proto

#ifndef PROTOBUF_responseprotos_2eproto__INCLUDED
#define PROTOBUF_responseprotos_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
#include "commonprotocol.pb.h"
// @@protoc_insertion_point(includes)

namespace card_protobuf {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_responseprotos_2eproto();
void protobuf_AssignDesc_responseprotos_2eproto();
void protobuf_ShutdownFile_responseprotos_2eproto();

class Response;

enum ResponseCode {
  OK = 200,
  ACCEPT = 202,
  PARTIAL_CONTENT = 203,
  SERVER_BUSY = 250,
  BAD_REQUEST = 400,
  UNAUTHORIZED = 401,
  FORBIDDEN = 403,
  NOT_FOUND = 404,
  REQUEST_TIMEOUT = 408,
  INTERVAL_TOO_SHORT = 440,
  OFF_LINE = 600,
  SEND_ERROR = 601,
  SERVER_INTERNAL_ERROR = 500,
  NOT_IMPLEMENT = 501,
  SERVICE_UNAVAILABLE = 503,
  GATEWAY_TIMEOUT = 504,
  UNSUPPORTED_VERSION = 997,
  PROTOCOL_ERROR = 998,
  UNKNOWN = 999
};
bool ResponseCode_IsValid(int value);
const ResponseCode ResponseCode_MIN = OK;
const ResponseCode ResponseCode_MAX = UNKNOWN;
const int ResponseCode_ARRAYSIZE = ResponseCode_MAX + 1;

const ::google::protobuf::EnumDescriptor* ResponseCode_descriptor();
inline const ::std::string& ResponseCode_Name(ResponseCode value) {
  return ::google::protobuf::internal::NameOfEnum(
    ResponseCode_descriptor(), value);
}
inline bool ResponseCode_Parse(
    const ::std::string& name, ResponseCode* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ResponseCode>(
    ResponseCode_descriptor(), name, value);
}
// ===================================================================

class Response : public ::google::protobuf::Message {
 public:
  Response();
  virtual ~Response();

  Response(const Response& from);

  inline Response& operator=(const Response& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Response& default_instance();

  void Swap(Response* other);

  // implements Message ----------------------------------------------

  Response* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Response& from);
  void MergeFrom(const Response& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required .card_protobuf.ResponseCode response_code = 1;
  inline bool has_response_code() const;
  inline void clear_response_code();
  static const int kResponseCodeFieldNumber = 1;
  inline ::card_protobuf::ResponseCode response_code() const;
  inline void set_response_code(::card_protobuf::ResponseCode value);

  // optional string error_description = 2;
  inline bool has_error_description() const;
  inline void clear_error_description();
  static const int kErrorDescriptionFieldNumber = 2;
  inline const ::std::string& error_description() const;
  inline void set_error_description(const ::std::string& value);
  inline void set_error_description(const char* value);
  inline void set_error_description(const char* value, size_t size);
  inline ::std::string* mutable_error_description();
  inline ::std::string* release_error_description();
  inline void set_allocated_error_description(::std::string* error_description);

  // repeated .card_protobuf.Data data = 3;
  inline int data_size() const;
  inline void clear_data();
  static const int kDataFieldNumber = 3;
  inline const ::card_protobuf::Data& data(int index) const;
  inline ::card_protobuf::Data* mutable_data(int index);
  inline ::card_protobuf::Data* add_data();
  inline const ::google::protobuf::RepeatedPtrField< ::card_protobuf::Data >&
      data() const;
  inline ::google::protobuf::RepeatedPtrField< ::card_protobuf::Data >*
      mutable_data();

  // @@protoc_insertion_point(class_scope:card_protobuf.Response)
 private:
  inline void set_has_response_code();
  inline void clear_has_response_code();
  inline void set_has_error_description();
  inline void clear_has_error_description();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* error_description_;
  ::google::protobuf::RepeatedPtrField< ::card_protobuf::Data > data_;
  int response_code_;
  friend void  protobuf_AddDesc_responseprotos_2eproto();
  friend void protobuf_AssignDesc_responseprotos_2eproto();
  friend void protobuf_ShutdownFile_responseprotos_2eproto();

  void InitAsDefaultInstance();
  static Response* default_instance_;
};
// ===================================================================


// ===================================================================

// Response

// required .card_protobuf.ResponseCode response_code = 1;
inline bool Response::has_response_code() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Response::set_has_response_code() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Response::clear_has_response_code() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Response::clear_response_code() {
  response_code_ = 200;
  clear_has_response_code();
}
inline ::card_protobuf::ResponseCode Response::response_code() const {
  // @@protoc_insertion_point(field_get:card_protobuf.Response.response_code)
  return static_cast< ::card_protobuf::ResponseCode >(response_code_);
}
inline void Response::set_response_code(::card_protobuf::ResponseCode value) {
  assert(::card_protobuf::ResponseCode_IsValid(value));
  set_has_response_code();
  response_code_ = value;
  // @@protoc_insertion_point(field_set:card_protobuf.Response.response_code)
}

// optional string error_description = 2;
inline bool Response::has_error_description() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Response::set_has_error_description() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Response::clear_has_error_description() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Response::clear_error_description() {
  if (error_description_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    error_description_->clear();
  }
  clear_has_error_description();
}
inline const ::std::string& Response::error_description() const {
  // @@protoc_insertion_point(field_get:card_protobuf.Response.error_description)
  return *error_description_;
}
inline void Response::set_error_description(const ::std::string& value) {
  set_has_error_description();
  if (error_description_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    error_description_ = new ::std::string;
  }
  error_description_->assign(value);
  // @@protoc_insertion_point(field_set:card_protobuf.Response.error_description)
}
inline void Response::set_error_description(const char* value) {
  set_has_error_description();
  if (error_description_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    error_description_ = new ::std::string;
  }
  error_description_->assign(value);
  // @@protoc_insertion_point(field_set_char:card_protobuf.Response.error_description)
}
inline void Response::set_error_description(const char* value, size_t size) {
  set_has_error_description();
  if (error_description_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    error_description_ = new ::std::string;
  }
  error_description_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:card_protobuf.Response.error_description)
}
inline ::std::string* Response::mutable_error_description() {
  set_has_error_description();
  if (error_description_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    error_description_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:card_protobuf.Response.error_description)
  return error_description_;
}
inline ::std::string* Response::release_error_description() {
  clear_has_error_description();
  if (error_description_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = error_description_;
    error_description_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void Response::set_allocated_error_description(::std::string* error_description) {
  if (error_description_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete error_description_;
  }
  if (error_description) {
    set_has_error_description();
    error_description_ = error_description;
  } else {
    clear_has_error_description();
    error_description_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:card_protobuf.Response.error_description)
}

// repeated .card_protobuf.Data data = 3;
inline int Response::data_size() const {
  return data_.size();
}
inline void Response::clear_data() {
  data_.Clear();
}
inline const ::card_protobuf::Data& Response::data(int index) const {
  // @@protoc_insertion_point(field_get:card_protobuf.Response.data)
  return data_.Get(index);
}
inline ::card_protobuf::Data* Response::mutable_data(int index) {
  // @@protoc_insertion_point(field_mutable:card_protobuf.Response.data)
  return data_.Mutable(index);
}
inline ::card_protobuf::Data* Response::add_data() {
  // @@protoc_insertion_point(field_add:card_protobuf.Response.data)
  return data_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::card_protobuf::Data >&
Response::data() const {
  // @@protoc_insertion_point(field_list:card_protobuf.Response.data)
  return data_;
}
inline ::google::protobuf::RepeatedPtrField< ::card_protobuf::Data >*
Response::mutable_data() {
  // @@protoc_insertion_point(field_mutable_list:card_protobuf.Response.data)
  return &data_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace card_protobuf

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::card_protobuf::ResponseCode> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::card_protobuf::ResponseCode>() {
  return ::card_protobuf::ResponseCode_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_responseprotos_2eproto__INCLUDED
