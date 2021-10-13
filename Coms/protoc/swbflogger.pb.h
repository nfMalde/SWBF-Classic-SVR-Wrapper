// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: swbflogger.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_swbflogger_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_swbflogger_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3017000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3017003 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_swbflogger_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_swbflogger_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_swbflogger_2eproto;
namespace swbf {
class LogMessage;
struct LogMessageDefaultTypeInternal;
extern LogMessageDefaultTypeInternal _LogMessage_default_instance_;
class Logger;
struct LoggerDefaultTypeInternal;
extern LoggerDefaultTypeInternal _Logger_default_instance_;
}  // namespace swbf
PROTOBUF_NAMESPACE_OPEN
template<> ::swbf::LogMessage* Arena::CreateMaybeMessage<::swbf::LogMessage>(Arena*);
template<> ::swbf::Logger* Arena::CreateMaybeMessage<::swbf::Logger>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace swbf {

// ===================================================================

class Logger final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:swbf.Logger) */ {
 public:
  inline Logger() : Logger(nullptr) {}
  ~Logger() override;
  explicit constexpr Logger(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Logger(const Logger& from);
  Logger(Logger&& from) noexcept
    : Logger() {
    *this = ::std::move(from);
  }

  inline Logger& operator=(const Logger& from) {
    CopyFrom(from);
    return *this;
  }
  inline Logger& operator=(Logger&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Logger& default_instance() {
    return *internal_default_instance();
  }
  static inline const Logger* internal_default_instance() {
    return reinterpret_cast<const Logger*>(
               &_Logger_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Logger& a, Logger& b) {
    a.Swap(&b);
  }
  inline void Swap(Logger* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Logger* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Logger* New() const final {
    return new Logger();
  }

  Logger* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Logger>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Logger& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const Logger& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Logger* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "swbf.Logger";
  }
  protected:
  explicit Logger(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kLogMessagesFieldNumber = 1,
  };
  // repeated .swbf.LogMessage LogMessages = 1;
  int logmessages_size() const;
  private:
  int _internal_logmessages_size() const;
  public:
  void clear_logmessages();
  ::swbf::LogMessage* mutable_logmessages(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::swbf::LogMessage >*
      mutable_logmessages();
  private:
  const ::swbf::LogMessage& _internal_logmessages(int index) const;
  ::swbf::LogMessage* _internal_add_logmessages();
  public:
  const ::swbf::LogMessage& logmessages(int index) const;
  ::swbf::LogMessage* add_logmessages();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::swbf::LogMessage >&
      logmessages() const;

  // @@protoc_insertion_point(class_scope:swbf.Logger)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::swbf::LogMessage > logmessages_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_swbflogger_2eproto;
};
// -------------------------------------------------------------------

class LogMessage final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:swbf.LogMessage) */ {
 public:
  inline LogMessage() : LogMessage(nullptr) {}
  ~LogMessage() override;
  explicit constexpr LogMessage(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  LogMessage(const LogMessage& from);
  LogMessage(LogMessage&& from) noexcept
    : LogMessage() {
    *this = ::std::move(from);
  }

  inline LogMessage& operator=(const LogMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline LogMessage& operator=(LogMessage&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const LogMessage& default_instance() {
    return *internal_default_instance();
  }
  static inline const LogMessage* internal_default_instance() {
    return reinterpret_cast<const LogMessage*>(
               &_LogMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(LogMessage& a, LogMessage& b) {
    a.Swap(&b);
  }
  inline void Swap(LogMessage* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(LogMessage* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline LogMessage* New() const final {
    return new LogMessage();
  }

  LogMessage* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<LogMessage>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const LogMessage& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const LogMessage& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(LogMessage* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "swbf.LogMessage";
  }
  protected:
  explicit LogMessage(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kDateFieldNumber = 1,
    kMessageFieldNumber = 3,
    kIdFieldNumber = 2,
  };
  // required string Date = 1;
  bool has_date() const;
  private:
  bool _internal_has_date() const;
  public:
  void clear_date();
  const std::string& date() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_date(ArgT0&& arg0, ArgT... args);
  std::string* mutable_date();
  PROTOBUF_MUST_USE_RESULT std::string* release_date();
  void set_allocated_date(std::string* date);
  private:
  const std::string& _internal_date() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_date(const std::string& value);
  std::string* _internal_mutable_date();
  public:

  // required string Message = 3;
  bool has_message() const;
  private:
  bool _internal_has_message() const;
  public:
  void clear_message();
  const std::string& message() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_message(ArgT0&& arg0, ArgT... args);
  std::string* mutable_message();
  PROTOBUF_MUST_USE_RESULT std::string* release_message();
  void set_allocated_message(std::string* message);
  private:
  const std::string& _internal_message() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_message(const std::string& value);
  std::string* _internal_mutable_message();
  public:

  // required int32 Id = 2;
  bool has_id() const;
  private:
  bool _internal_has_id() const;
  public:
  void clear_id();
  ::PROTOBUF_NAMESPACE_ID::int32 id() const;
  void set_id(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_id() const;
  void _internal_set_id(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:swbf.LogMessage)
 private:
  class _Internal;

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr date_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr message_;
  ::PROTOBUF_NAMESPACE_ID::int32 id_;
  friend struct ::TableStruct_swbflogger_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Logger

// repeated .swbf.LogMessage LogMessages = 1;
inline int Logger::_internal_logmessages_size() const {
  return logmessages_.size();
}
inline int Logger::logmessages_size() const {
  return _internal_logmessages_size();
}
inline void Logger::clear_logmessages() {
  logmessages_.Clear();
}
inline ::swbf::LogMessage* Logger::mutable_logmessages(int index) {
  // @@protoc_insertion_point(field_mutable:swbf.Logger.LogMessages)
  return logmessages_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::swbf::LogMessage >*
Logger::mutable_logmessages() {
  // @@protoc_insertion_point(field_mutable_list:swbf.Logger.LogMessages)
  return &logmessages_;
}
inline const ::swbf::LogMessage& Logger::_internal_logmessages(int index) const {
  return logmessages_.Get(index);
}
inline const ::swbf::LogMessage& Logger::logmessages(int index) const {
  // @@protoc_insertion_point(field_get:swbf.Logger.LogMessages)
  return _internal_logmessages(index);
}
inline ::swbf::LogMessage* Logger::_internal_add_logmessages() {
  return logmessages_.Add();
}
inline ::swbf::LogMessage* Logger::add_logmessages() {
  ::swbf::LogMessage* _add = _internal_add_logmessages();
  // @@protoc_insertion_point(field_add:swbf.Logger.LogMessages)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::swbf::LogMessage >&
Logger::logmessages() const {
  // @@protoc_insertion_point(field_list:swbf.Logger.LogMessages)
  return logmessages_;
}

// -------------------------------------------------------------------

// LogMessage

// required string Date = 1;
inline bool LogMessage::_internal_has_date() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool LogMessage::has_date() const {
  return _internal_has_date();
}
inline void LogMessage::clear_date() {
  date_.ClearToEmpty();
  _has_bits_[0] &= ~0x00000001u;
}
inline const std::string& LogMessage::date() const {
  // @@protoc_insertion_point(field_get:swbf.LogMessage.Date)
  return _internal_date();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void LogMessage::set_date(ArgT0&& arg0, ArgT... args) {
 _has_bits_[0] |= 0x00000001u;
 date_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:swbf.LogMessage.Date)
}
inline std::string* LogMessage::mutable_date() {
  std::string* _s = _internal_mutable_date();
  // @@protoc_insertion_point(field_mutable:swbf.LogMessage.Date)
  return _s;
}
inline const std::string& LogMessage::_internal_date() const {
  return date_.Get();
}
inline void LogMessage::_internal_set_date(const std::string& value) {
  _has_bits_[0] |= 0x00000001u;
  date_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* LogMessage::_internal_mutable_date() {
  _has_bits_[0] |= 0x00000001u;
  return date_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* LogMessage::release_date() {
  // @@protoc_insertion_point(field_release:swbf.LogMessage.Date)
  if (!_internal_has_date()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000001u;
  return date_.ReleaseNonDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void LogMessage::set_allocated_date(std::string* date) {
  if (date != nullptr) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  date_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), date,
      GetArenaForAllocation());
  // @@protoc_insertion_point(field_set_allocated:swbf.LogMessage.Date)
}

// required int32 Id = 2;
inline bool LogMessage::_internal_has_id() const {
  bool value = (_has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool LogMessage::has_id() const {
  return _internal_has_id();
}
inline void LogMessage::clear_id() {
  id_ = 0;
  _has_bits_[0] &= ~0x00000004u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 LogMessage::_internal_id() const {
  return id_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 LogMessage::id() const {
  // @@protoc_insertion_point(field_get:swbf.LogMessage.Id)
  return _internal_id();
}
inline void LogMessage::_internal_set_id(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000004u;
  id_ = value;
}
inline void LogMessage::set_id(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:swbf.LogMessage.Id)
}

// required string Message = 3;
inline bool LogMessage::_internal_has_message() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool LogMessage::has_message() const {
  return _internal_has_message();
}
inline void LogMessage::clear_message() {
  message_.ClearToEmpty();
  _has_bits_[0] &= ~0x00000002u;
}
inline const std::string& LogMessage::message() const {
  // @@protoc_insertion_point(field_get:swbf.LogMessage.Message)
  return _internal_message();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void LogMessage::set_message(ArgT0&& arg0, ArgT... args) {
 _has_bits_[0] |= 0x00000002u;
 message_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:swbf.LogMessage.Message)
}
inline std::string* LogMessage::mutable_message() {
  std::string* _s = _internal_mutable_message();
  // @@protoc_insertion_point(field_mutable:swbf.LogMessage.Message)
  return _s;
}
inline const std::string& LogMessage::_internal_message() const {
  return message_.Get();
}
inline void LogMessage::_internal_set_message(const std::string& value) {
  _has_bits_[0] |= 0x00000002u;
  message_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* LogMessage::_internal_mutable_message() {
  _has_bits_[0] |= 0x00000002u;
  return message_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* LogMessage::release_message() {
  // @@protoc_insertion_point(field_release:swbf.LogMessage.Message)
  if (!_internal_has_message()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000002u;
  return message_.ReleaseNonDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void LogMessage::set_allocated_message(std::string* message) {
  if (message != nullptr) {
    _has_bits_[0] |= 0x00000002u;
  } else {
    _has_bits_[0] &= ~0x00000002u;
  }
  message_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), message,
      GetArenaForAllocation());
  // @@protoc_insertion_point(field_set_allocated:swbf.LogMessage.Message)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace swbf

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_swbflogger_2eproto