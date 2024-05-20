EFI_LOAD_FILE_PROTOCOL_GUID fix 0x56EC3091,0x954C,0x11d2,0x8E,0x3F,0x00,0xA0,0xC9,0x69,0x72,0x3B

efi_struct EFI_LOAD_FILE
    LoadFile    FUNCTION
end efi_struct

macro EFI_LOAD_FILE_init self*
namespace self
    macro caller function, params&
        macro function params
            efi_call [self], EFI_LOAD_FILE, function, [self], params
        end macro
    end macro

    caller LoadFile, file_path, boot_policy, buffer_size, buffer

    purge caller
end namespace
end macro
