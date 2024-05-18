EFI_GRAPHICS_OUTPUT_GUID fix 0x9042a9de,0x23dc,0x4a38,0x96,0xfb,0x7a,0xde,0xd0,0x80,0x51,0x6a

efi_struct EFI_GRAPHICS_OUTPUT
    QueryMode   FUNCTION
    SetMode     FUNCTION
    Blt         FUNCTION
    Mode        PTR EFI_GRAPHICS_OUTPUT_MODE
end efi_struct

macro EFI_GRAPHICS_OUTPUT_init self*
namespace self
    macro caller function, params&
        macro function params
            efi_call [self], EFI_GRAPHICS_OUTPUT, function, [self], params
        end macro
    end macro

    caller QueryMode, mode_number, size_of_info, info
    caller SetMode, mode_number
    caller Blt, blt_buffer, blt_operation, src_x, src_y, dest_x, dest_y, width, height, delta

    purge caller

    macro bind
        mov r15, [self]
    end macro

    EFI_GRAPHICS_OUTPUT_MODE_init
end namespace
end macro

efi_struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL blue, green, red
    Blue    UINT8 blue
    Green   UINT8 green
    Red     UINT8 red
    Reseved UINT8 0
end efi_struct

efi_enum EFI_GRAPHICS_OUTPUT_BLT_OPERATION
    item VIDEO_FILL
    item VIDEO_TO_BUFFER
    item BUFFER_TO_VIDEO
    item VIDEO_TO_VIDEO
end efi_enum

efi_struct EFI_GRAPHICS_OUTPUT_MODE
    MaxMode         UINT32
    Mode            UINT32
    Info            PTR EFI_GRAPHICS_OUTPUT_MODE_INFORMATION
    SizeOfInfo      UINTN
    FrameBufferBase EFI_PHYSICAL_ADDRESS
    FrameBufferSize UINTN
end efi_struct

macro EFI_GRAPHICS_OUTPUT_MODE_init
namespace Mode
    macro bind
        mov r14, [r15 + EFI_GRAPHICS_OUTPUT.Mode]
    end macro

    macro getter32 value_name
        macro get#value_name
            mov eax, [r14 + EFI_GRAPHICS_OUTPUT_MODE.#value_name]
        end macro
    end macro

    macro getter64 value_name
        macro get#value_name
            mov rax, [r14 + EFI_GRAPHICS_OUTPUT_MODE.#value_name]
        end macro
    end macro

    getter32 MaxMode
    getter32 Mode
    getter64 SizeOfInfo
    getter64 FrameBufferBase
    getter64 FrameBufferSize

    purge getter32
    purge getter64

    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION_init
end namespace
end macro

efi_struct EFI_GRAPHICS_OUTPUT_MODE_INFORMATION
    Version                 UINT32
    HorisontalResolution    UINT32
    VerticalResolution      UINT32
    PixelFormat             EFI_GRAPHICS_PIXEL_FORMAT
    PixelInformation        EFI_PIXEL_BITMASK
    PixelsPerScanLine       UINT32
end efi_struct

macro EFI_GRAPHICS_OUTPUT_MODE_INFORMATION_init
namespace Info
    macro bind
        mov r13, [r14 + EFI_GRAPHICS_OUTPUT_MODE.Info]
    end macro

    macro getter32 value_name
        macro get#value_name
            mov eax, [r13 + EFI_GRAPHICS_OUTPUT_MODE_INFORMATION.#value_name]
        end macro
    end macro

    getter32 Version
    getter32 HorisontalResolution
    getter32 VerticalResolution
    getter32 PixelFormat
    getter32 PixelsPerScanLine

    purge getter32

    EFI_PIXEL_BITMASK_init
end namespace
end macro

;RGB      - PixelRedGreenBlueReseved8BitPerColor
;BRG      - PixelBlueRedGreenReseved8BitPerColor
;BIT_MASK - PixelBitMask
;BLT_ONLY - PixelBltOnly
efi_enum EFI_GRAPHICS_PIXEL_FORMAT
    item RGB
    item BRG
    item BIT_MASK
    item BLT_ONLY
end efi_enum

efi_struct EFI_PIXEL_BITMASK
    RedMask        UINT32
    GreenMask      UINT32
    BlueMask       UINT32
    ResevedMask    UINT32
end efi_struct

macro EFI_PIXEL_BITMASK_init
    macro getter32 value_name
        macro get#value_name
            mov eax, [r13 + EFI_GRAPHICS_OUTPUT_MODE_INFORMATION.PixelInformation \
                          + EFI_PIXEL_BITMASK.#value_name]
        end macro
    end macro

    getter32 RedMask
    getter32 GreenMask
    getter32 BlueMask
    getter32 ResevedMask

    purge getter32
end macro
