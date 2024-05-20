EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID fix 0x0964e5b22,0x6459,0x11d2,0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b

EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_REVISION fix 0x00010000

efi_struct EFI_SIMPLE_FILE_SYSTEM
    Revision    UINT64
    OpenVolume  FUNCTION
end efi_struct

macro EFI_SIMPLE_FILE_SYSTEM_init self*
namespace self
    macro caller function, params&
        macro function params
            efi_call [self], EFI_SIMPLE_FILE_SYSTEM, function, [self], params
        end macro
    end macro

    caller OpenVolume, root

    purge caller

    macro bind
        mov r15, [self]
    end macro

    macro getter64 value_name
        macro get#value_name
            mov rax, qword [r15 + EFI_SIMPLE_FILE_SYSTEM.#value_name]
        end macro
    end macro

    getter64 Revision

    purge getter64
end namespace
end macro
