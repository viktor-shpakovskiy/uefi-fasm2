EFI_FILE_SYSTEM_INFO_GUID fix 0x09576e93,0x6d3f,0x11d2,0x8e39,0x00,0xa0,0xc9,0x69,0x72,0x3b

efi_struct EFI_FILE_SYSTEM_INFO
    Size        UINT64
    ReadOnly    BOOL
    VolumeSize  UINT64
    FreeSpace   UINT64
    BlockSize   UINT32
    VolumeLabel PTR CHAR16
end efi_struct

macro EFI_FILE_SYSTEM_INFO_init self*
namespace self
    macro bind
        mov r15, [self]
    end macro

    macro getter8 value_name
        macro get#value_name
            mov ax, byte [r15 + EFI_FILE_SYSTEM_INFO.#value_name]
        end macro
    end macro

    macro getter32 value_name
        macro get#value_name
            mov eax, dword [r15 + EFI_FILE_SYSTEM_INFO.#value_name]
        end macro
    end macro

    macro getter64 value_name
        macro get#value_name
            mov rax, qword [r15 + EFI_FILE_SYSTEM_INFO.#value_name]
        end macro
    end macro

    getter64 Size
    gettet8  ReadOnly
    getter64 VolumeSize
    getter64 FreeSpace
    getter32 BlockSize
    getter64 VolumeLabel

    purge getter8
    purge getter32
    purge getter64
end namespace
end macro
