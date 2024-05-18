format pe64 dll efi
entry main

macro delay cycles
    mov rcx, cycles
    local delay
    delay: loop delay
end macro

DEFAULT_DELAY equ 0xfffffff

include 'efi/efi.inc'
include 'efi/efi_graphics_output.inc'

section '.text' code readable executable

main:
    EfiInitializeSystem

    EfiConsoleOut.ClearScreen
    EfiConsoleOut.OutputString hello_string

    EfiConsoleOut.OutputString gop_init
    EfiInitializeGraphicsOutput on_gop_init_error
    EfiConsoleOut.OutputString gop_ok

    EfiGraphicsOutput.bind
    EfiGraphicsOutput.Mode.bind
    EfiGraphicsOutput.Mode.Info.bind

    EfiGraphicsOutput.Mode.Info.getHorisontalResolution
    mov [screen_width], eax
    sub eax, IMAGE_W
    sar eax, 1
    mov [pos_x], eax
    EfiGraphicsOutput.Mode.Info.getVerticalResolution
    mov [screen_height], eax
    sub eax, IMAGE_H
    sar eax, 1
    mov [pos_y], eax

    EfiConsoleOut.OutputString gop_draw_start
    EfiGraphicsOutput.Blt image, EFI_GRAPHICS_OUTPUT_BLT_OPERATION.BUFFER_TO_VIDEO, \
                          0, 0, [pos_x], [pos_y], IMAGE_W, IMAGE_H, 0
    EfiConsoleOut.OutputString gop_draw_end
    
    delay DEFAULT_DELAY
    mov rax, 0
    ret

on_gop_init_error:
    EfiConsoleOut.OutputString gop_error
    delay DEFAULT_DELAY
    mov rax, 0
    ret

section '.data' data readable writeable

hello_string    EFI_STRING_NL 'UEFI Program started'

gop_init        EFI_STRING_NL 'Trying to init Graphics Output Protocol'
gop_ok          EFI_STRING_NL 'Graphics Output Protocol inited'
gop_error       EFI_STRING_NL 'Graphics Output Protocol not supported'
gop_draw_start  EFI_STRING_NL 'Graphics Output Protocol draw started'
gop_draw_end    EFI_STRING_NL 'Graphics Output Protocol draw ended'

IMAGE_W         equ 512
IMAGE_H         equ 512
IMAGE_BPP       equ 4
image:          file 'assets/ring-image.data'

screen_base     EFI_PHYSICAL_ADDRESS
screen_width    UINT32
screen_height   UINT32

pos_x   UINT32
pos_y   UINT32

section '.reloc' data readable discardable fixups
