EFI_FILE_SYSTEM_VOLUME_LABEL_GUID fix 0xDB47D7D3,0xFE81,0x11d3,0x9A35,0x00,0x90,0x27,0x3F,0xC1,0x4D

efi_struct EFI_FILE_SYSTEM_VOLUME_LABEL
    VolumeLabel PTR CHAR16
end efi_struct

macro EFI_FILE_SYSTEM_VOLUME_LABEL_init self*
namespace self
    macro bind
        mov r15, [self]
    end macro

    macro getter64 value_name
        macro get#value_name
            mov rax, qword [r15 + EFI_FILE_SYSTEM_VOLUME_LABEL.#value_name]
        end macro
    end macro

    getter VolumeLabel

    purge getter64
end namespace
end macro
