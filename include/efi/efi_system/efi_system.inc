EFI_SYSTEM_SIGNATURE fix 0x5453595320494249

efi_struct EFI_SYSTEM
    Header               EFI_TABLE_HEADER
    FirmwareVendor       PTR CHAR16
    FirmwareRevision     UINT32
    ConsoleInHandle      EFI_HANDLE
    ConsoleInTable       PTR EFI_SIMPLE_TEXT_INPUT
    ConsoleOutHandle     EFI_HANDLE
    ConsoleOutTable      PTR EFI_SIMPLE_TEXT_OUTPUT
    StandardErrorHandle  EFI_HANDLE
    StandardErrorTable   PTR EFI_SIMPLE_TEXT_OUTPUT
    RuntimeServicesTable PTR EFI_RUNTIME_SERVICES
    BootServicesTable    PTR EFI_BOOT_SERVICES
    NumberOfTableEntries UINTN
    ConfigurationTable   PTR EFI_CONFIGURATION_TABLE
end efi_struct

macro EFI_SYSTEM_init self*
namespace self
    macro bind
        mov r15, [self]
    end macro

    EFI_TABLE_HEADER_init

    macro getter value_name
        macro get#value_name
            mov rax, [r15 + EFI_SYSTEM.#value_name]
        end macro
    end macro

    getter FirmwareVendor
    getter FirmwareRevision
    getter ConsoleInHandle
    getter ConsoleInTable
    getter ConsoleOutHandle
    getter ConsoleOutTable
    getter StandardErrorHandle
    getter StandardErrorTable
    getter RuntimeServicesTable
    getter BootServicesTable
    getter NumberOfTableEntries
    getter ConfigurationTable

    purge getter
end namespace
end macro
