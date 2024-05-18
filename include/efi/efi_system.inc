include 'efi_system/efi_system.inc'
include 'efi_console/efi_simple_text_input.inc'
include 'efi_console/efi_simple_text_output.inc'
include 'efi_system/efi_runtime_services.inc'
include 'efi_system/efi_boot_services.inc'

section '.data' data readable writeable
EfiSystem           PTR EFI_SYSTEM
EfiConsoleIn        PTR EFI_SIMPLE_TEXT_INPUT
EfiConsoleOut       PTR EFI_SIMPLE_TEXT_OUTPUT
EfiRuntimeServices  PTR EFI_RUNTIME_SERVICES
EfiBootServices     PTR EFI_BOOT_SERVICES

macro EfiInitializeSystem
    mov [EfiSystem], rdx
    EFI_SYSTEM_init EfiSystem

    EfiSystem.bind

    EfiSystem.getConsoleInTable
    mov [EfiConsoleIn], rax
    EFI_SIMPLE_TEXT_INPUT_init EfiConsoleIn

    EfiSystem.getConsoleOutTable
    mov [EfiConsoleOut], rax
    EFI_SIMPLE_TEXT_OUTPUT_init EfiConsoleOut

    EfiSystem.getRuntimeServicesTable
    mov [EfiRuntimeServices], rax
    EFI_RUNTIME_SERVICES_init EfiRuntimeServices

    EfiSystem.getBootServicesTable
    mov [EfiBootServices], rax
    EFI_BOOT_SERVICES_init EfiBootServices
end macro
