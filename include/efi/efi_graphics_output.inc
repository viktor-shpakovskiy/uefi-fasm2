include 'efi_console/efi_graphics_output.inc'

section '.data' data readable writeable

EfiGraphicsOutput       PTR EFI_GRAPHICS_OUTPUT
EfiGraphicsOutputGuid   EFI_GUID EFI_GRAPHICS_OUTPUT_GUID

macro EfiInitializeGraphicsOutput on_error
    local error, ok

    EfiBootServices.LocateProtocol EfiGraphicsOutputGuid, 0, EfiGraphicsOutput
    test rax, rax
    jz ok
error:
    jmp on_error
ok:
    EFI_GRAPHICS_OUTPUT_init EfiGraphicsOutput
end macro
