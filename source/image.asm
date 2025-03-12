format pe64 dll efi
entry main

macro delay cycles
    mov rcx, cycles
    local delay
    delay: loop delay
end macro

DEFAULT_DELAY equ 0xFFFFFFFF

include 'efi/efi.inc'
include 'efi/efi_graphics_output.inc'

efi_struct FrameBuffer base, width, height
    Base    EFI_PHYSICAL_ADDRESS base
    Width   UINT32 width
    Height  UINT32 height
end efi_struct

efi_struct FramePoint _x, _y
    x UINT32 _x
    y UINT32 _y
end efi_struct

efi_struct FrameRegion x1, y1, x2, y2
    TopLeft     FramePoint x1, y1
    BotRight    FramePoint x2, y2
end efi_struct

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

    EfiGraphicsOutput.Mode.getFrameBufferBase
    mov qword [screen_frame + FrameBuffer.Base], rax

    EfiGraphicsOutput.Mode.Info.bind

    EfiGraphicsOutput.Mode.Info.getHorisontalResolution
    mov dword [screen_frame + FrameBuffer.Width], eax
    sub eax, IMAGE_W
    sar eax, 1
    mov dword [screen_point + FramePoint.x], eax
    EfiGraphicsOutput.Mode.Info.getVerticalResolution
    mov dword [screen_frame + FrameBuffer.Height], eax
    sub eax, IMAGE_H
    sar eax, 1
    mov dword [screen_point + FramePoint.y], eax

    mov qword [image_frame + FrameBuffer.Base], image
    mov dword [image_frame + FrameBuffer.Width], IMAGE_W
    mov dword [image_frame + FrameBuffer.Height], IMAGE_H

    EfiConsoleOut.OutputString gop_draw_start
    ; EfiGraphicsOutput.Blt image, EFI_GRAPHICS_OUTPUT_BLT_OPERATION.BUFFER_TO_VIDEO, \
    ;                       0, 0, [pos_x], [pos_y], IMAGE_W, IMAGE_H, 0

    fastcall blk_tr, image_frame, image_region, screen_frame, screen_point
    
    EfiConsoleOut.OutputString gop_draw_end

    delay DEFAULT_DELAY
    mov rax, 0
    ret

on_gop_init_error:
    EfiConsoleOut.OutputString gop_error
    delay DEFAULT_DELAY
    mov rax, 0
    ret

; rcx - source frame
; rdx - source region
; r8  - destination frame
; r9  - destination point
blk_tr:
    push rsi
    push rdi

    macro load_start_pos reg, frame, point
        xor rax, rax
        mov eax, dword [point + FramePoint.y]
        imul eax, dword [frame + FrameBuffer.Width]
        add eax, dword [point + FramePoint.x]
        sal rax, 2
        mov reg, qword [frame + FrameBuffer.Base]
        add reg, rax
    end macro

    load_start_pos rsi, rcx, rdx
    load_start_pos rdi, r8, r9

    ; eax - lines count
    mov eax, dword [rdx + FrameRegion.BotRight + FramePoint.y]
    sub eax, dword [rdx + FrameRegion.TopLeft  + FramePoint.y]

    ; r9d - pixels per line
    mov r9d, dword [rdx + FrameRegion.BotRight + FramePoint.x]
    sub r9d, dword [rdx + FrameRegion.TopLeft  + FramePoint.x]

    ; edx - source offset in bytes
    mov edx, dword [rcx + FrameBuffer.Width]
    sub edx, r9d
    sal edx, 2

    ; r8d - destiantion offset in bytes
    mov r8d, dword [r8 + FrameBuffer.Width]
    sub r8d, r9d
    sal r8d, 2

    xor rcx, rcx
.copy_line:
    ; copy line
    mov ecx, r9d
    rep movsd
    ; pass source offset
    add rsi, rdx
    ; pass destination offset
    add rdi, r8
    ; copy next line
    dec eax
    test eax, eax
    jnz .copy_line

    purge load_start_pos

    pop rdi
    pop rsi
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

image_frame     FrameBuffer
image_region    FrameRegion IMAGE_W / 3, IMAGE_H / 3, IMAGE_W / 3 * 2, IMAGE_H / 3 * 2

screen_frame    FrameBuffer
screen_point    FramePoint

pos_x   UINT32
pos_y   UINT32

section '.reloc' data readable discardable fixups
