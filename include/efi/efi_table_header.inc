efi_struct EFI_TABLE_HEADER
    Signature  UINT64
    Revision   UINT32
    HeaderSize UINT32
    Crc32Sum   UINT32
    Reserved   UINT32
end efi_struct

macro EFI_TABLE_HEADER_init
namespace Header
    macro getter value_name
        macro get#value_name
            mov rax, [r15 + EFI_TABLE_HEADER.#value_name]
        end macro
    end macro

    getter Signature
    getter Revision
    getter HeaderSize
    getter Crc32Sum
    getter Reserved

    purge getter
end namespace
end macro
