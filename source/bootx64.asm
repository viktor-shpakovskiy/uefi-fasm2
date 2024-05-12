format pe64 dll efi
entry main

include 'efi/efi.inc'

section '.text' code readable executable

main:
    EfiInitializeLib

    EfiConsoleOut.ClearScreen
    EfiConsoleOut.OutputString hello_string

    mov rax, 0
    retn

section '.data' data readable writeable

hello_string EFI_STRING_NL 'Hello, World!!!'

section '.reloc' data readable discardable fixups
