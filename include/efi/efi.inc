include 'efi_call.inc'

include 'efi_type/efi_type.inc'
include 'efi_type/efi_enum.inc'
include 'efi_type/efi_struct.inc'

include 'efi_table_header.inc'

include 'efi_system/efi_system.inc'
include 'efi_system/efi_boot_services.inc'

include 'efi_console/efi_simple_text_input.inc'
include 'efi_console/efi_simple_text_output.inc'
include 'efi_console/efi_graphics_output.inc'

section '.data' data readable writeable
EfiSystem       PTR EFI_SYSTEM
EfiConsoleOut   PTR EFI_SIMPLE_TEXT_OUTPUT
EfiBootServices PTR EFI_BOOT_SERVICES

macro EfiInitializeLib
    mov [EfiSystem], rdx
    EFI_SYSTEM_init EfiSystem

    EfiSystem.bind

    EfiSystem.getConsoleOutTable
    mov [EfiConsoleOut], rax
    EFI_SIMPLE_TEXT_OUTPUT_init EfiConsoleOut

    EfiSystem.getBootServicesTable
    mov [EfiBootServices], rax
    EFI_BOOT_SERVICES_init EfiBootServices
end macro
