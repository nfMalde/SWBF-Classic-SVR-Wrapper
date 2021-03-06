// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: swbf.proto

#include "swbf.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace swbf {
constexpr Interact::Interact(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : textmessages_(){}
struct InteractDefaultTypeInternal {
  constexpr InteractDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~InteractDefaultTypeInternal() {}
  union {
    Interact _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT InteractDefaultTypeInternal _Interact_default_instance_;
}  // namespace swbf
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_swbf_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_swbf_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_swbf_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_swbf_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::swbf::Interact, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::swbf::Interact, textmessages_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::swbf::Interact)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::swbf::_Interact_default_instance_),
};

const char descriptor_table_protodef_swbf_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\nswbf.proto\022\004swbf\" \n\010Interact\022\024\n\014textMe"
  "ssages\030\001 \003(\t"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_swbf_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_swbf_2eproto = {
  false, false, 52, descriptor_table_protodef_swbf_2eproto, "swbf.proto", 
  &descriptor_table_swbf_2eproto_once, nullptr, 0, 1,
  schemas, file_default_instances, TableStruct_swbf_2eproto::offsets,
  file_level_metadata_swbf_2eproto, file_level_enum_descriptors_swbf_2eproto, file_level_service_descriptors_swbf_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_swbf_2eproto_getter() {
  return &descriptor_table_swbf_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_swbf_2eproto(&descriptor_table_swbf_2eproto);
namespace swbf {

// ===================================================================

class Interact::_Internal {
 public:
};

Interact::Interact(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned),
  textmessages_(arena) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:swbf.Interact)
}
Interact::Interact(const Interact& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      textmessages_(from.textmessages_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:swbf.Interact)
}

inline void Interact::SharedCtor() {
}

Interact::~Interact() {
  // @@protoc_insertion_point(destructor:swbf.Interact)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Interact::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void Interact::ArenaDtor(void* object) {
  Interact* _this = reinterpret_cast< Interact* >(object);
  (void)_this;
}
void Interact::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Interact::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Interact::Clear() {
// @@protoc_insertion_point(message_clear_start:swbf.Interact)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  textmessages_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Interact::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // repeated string textMessages = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            auto str = _internal_add_textmessages();
            ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
            #ifndef NDEBUG
            ::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "swbf.Interact.textMessages");
            #endif  // !NDEBUG
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<10>(ptr));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Interact::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:swbf.Interact)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated string textMessages = 1;
  for (int i = 0, n = this->_internal_textmessages_size(); i < n; i++) {
    const auto& s = this->_internal_textmessages(i);
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
      s.data(), static_cast<int>(s.length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
      "swbf.Interact.textMessages");
    target = stream->WriteString(1, s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:swbf.Interact)
  return target;
}

size_t Interact::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:swbf.Interact)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated string textMessages = 1;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(textmessages_.size());
  for (int i = 0, n = textmessages_.size(); i < n; i++) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
      textmessages_.Get(i));
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Interact::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Interact::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Interact::GetClassData() const { return &_class_data_; }

void Interact::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Interact *>(to)->MergeFrom(
      static_cast<const Interact &>(from));
}


void Interact::MergeFrom(const Interact& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:swbf.Interact)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  textmessages_.MergeFrom(from.textmessages_);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Interact::CopyFrom(const Interact& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:swbf.Interact)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Interact::IsInitialized() const {
  return true;
}

void Interact::InternalSwap(Interact* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  textmessages_.InternalSwap(&other->textmessages_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Interact::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_swbf_2eproto_getter, &descriptor_table_swbf_2eproto_once,
      file_level_metadata_swbf_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace swbf
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::swbf::Interact* Arena::CreateMaybeMessage< ::swbf::Interact >(Arena* arena) {
  return Arena::CreateMessageInternal< ::swbf::Interact >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
