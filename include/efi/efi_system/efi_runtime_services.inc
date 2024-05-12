EFI_RUNTIME_SERVICES_SIGNATURE fix 0x56524553544e5552

efi_struct EFI_RUNTIME_SERVICES
    Header                      EFI_TABLE_HEADER
        ; Time services
    GetTime                     FUNCTION
    SetTime                     FUNCTION
    GetWakeupTime               FUNCTION
    SetWakeupTime               FUNCTION
        ; Virtual memory services
    SetVirtualAddressMap        FUNCTION
    ConvertPointer              FUNCTION
        ; Variable services
    GetVariable                 FUNCTION
    GetNextVariableName         FUNCTION
    SetVariable                 FUNCTION
        ; Miscellaneous Services
    GetNextHighMonotonicCount   FUNCTION
    ResetSystem                 FUNCTION
        ; UEFI 2.0 Capsule Services
    UpdateCapsule               FUNCTION
    QueryCapsuleCapabilities    FUNCTION
        ; Miscellaneous UEFI 2.0 Service
    QueryVariableInfo           FUNCTION
end efi_struct

macro EFI_RUNTIME_SERVICES_init self*
namespace self
    macro bind
        mov r15, [self]
    end macro

    EFI_TABLE_HEADER_init

    macro caller function, params&
        macro function params
            efi_call [self], EFI_BOOT_SERVICES, function, params
        end macro
    end macro

        ; Time services
    caller GetTime,                     time, capabilities
    caller SetTime,                     time
    caller GetWakeupTime,               enable, pending, time
    caller SetWakeupTime,               enable, time
        ; Virtual memory services
    caller SetVirtualAddressMap,        memory_map_size, descriptor_size, descriptor_version, virtual_map
    caller ConvertPointer,              debug_desposition, address_ptr
        ; Variable services
    caller GetVariable,                 variable_name, vendor_guid, attributes, data_size, data
    caller GetNextVariableName,         variable_name_size, variable_name, vendor_guid
    caller SetVariable,                 variable_name, vendor_guid, attributes, data_size, data
        ; Miscellaneous Services
    caller GetNextHighMonotonicCount,   high_count
    caller ResetSystem, reset_type,     reset_status, data_size, reset_data
        ; UEFI 2.0 Capsule Services
    caller UpdateCapsule,               capsule_header_array, capsule_count, scatter_gather_list
    caller QueryCapsuleCapabilities,    capsule_header_array, capsule_count, max_capsule_size, reset_type
        ; Miscellaneous UEFI 2.0 Service
    caller QueryVariableInfo,           attributes, max_variable_storage_size, remaining_variable_storage_size, max_variable_size

    purge caller
end namespace
end macro
