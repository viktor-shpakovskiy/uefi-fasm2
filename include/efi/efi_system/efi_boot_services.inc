EFI_BOOT_SERVICES_SIGNATURE fix 0x56524553544f4f42

efi_struct EFI_BOOT_SERVICES
    Header                              EFI_TABLE_HEADER
        ; Task Priority Services
    RaiseTPL                            FUNCTION
    RestoreTPL                          FUNCTION
        ; Memory Services
    AllocatePages                       FUNCTION
    FreePages                           FUNCTION
    GetMemoryMap                        FUNCTION
    AllocatePool                        FUNCTION
    FreePool                            FUNCTION
        ; Event & Timer Services
    CreateEvent                         FUNCTION
    SetTimer                            FUNCTION
    WaitForEvent                        FUNCTION
    SignalEvent                         FUNCTION
    CloseEvent                          FUNCTION
    CheckEvent                          FUNCTION
        ; Protocol Handler Services
    InstallProtocolInterface            FUNCTION
    ReinstallProtocolInterface          FUNCTION
    UninstallProtocolInterface          FUNCTION
    HandleProtocol                      FUNCTION
    Reserved                            PTR VOID
    RegisterProtocolNotify              FUNCTION
    LocateHandle                        FUNCTION
    LocateDevicePath                    FUNCTION
    InstallConfigurationTable           FUNCTION
        ; Image Services
    LoadImage                           FUNCTION
    StartImage                          FUNCTION
    Exit                                FUNCTION
    UnloadImage                         FUNCTION
    ExitBootServices                    FUNCTION
        ; Miscellaneous Services
    GetNextMonotonicCount               FUNCTION
    Stall                               FUNCTION
    SetWatchdogTimer                    FUNCTION
        ; DriverSupport Services
    ConnectController                   FUNCTION
    DisconnectController                FUNCTION
        ; Open and Close Protocol Services
    OpenProtocol                        FUNCTION
    CloseProtocol                       FUNCTION
    OpenProtocolInformation             FUNCTION
        ; Library Services
    ProtocolsPerHandle                  FUNCTION
    LocateHandleBuffer                  FUNCTION
    LocateProtocol                      FUNCTION
    InstallMultipleProtocolInterfaces   FUNCTION
    UninstallMultipleProtocolInterfaces FUNCTION
        ; 32-bit CRC Services
    CalculateCrc32                      FUNCTION
        ; Miscellaneous Services
    CopyMem                             FUNCTION
    SetMem                              FUNCTION
    CreateEventEx                       FUNCTION
end efi_struct

macro EFI_BOOT_SERVICES_init self*
namespace self
    macro bind
        mov r15, [self]
    end macro

    EFI_TABLE_HEADER_init

    macro caller function, params&
        macro function params
            efi_call [self], EFI_BOOT_SERVICES, function, params
        end macro
    end macro

        ; Task Priority Services
    caller RaiseTPL,                            new_tpl
    caller RestoreTPL,                          old_tpl
        ; Memory Services
    caller AllocatePages,                       type, memory_type, pages, memory
    caller FreePages,                           memory, pages
    caller GetMemoryMap,                        memory_map_size, memory_map, map_key, descriptor_size, descriptor_version
    caller AllocatePool,                        pool_type, size, buffer
    caller FreePool,                            buffer
        ; Event & Timer Services
    caller CreateEvent,                         type, notify_tpl, notify_function, notify_context, event
    caller SetTimer,                            event, type, trigger_time
    caller WaitForEvent,                        number_of_events, event, index
    caller SignalEvent,                         event
    caller CloseEvent,                          event
    caller CheckEvent,                          event
        ; Protocol Handler Services
    caller InstallProtocolInterface,            handle, protocol, interface_type, interface
    caller ReinstallProtocolInterface,          handle, protocol, old_interface, new_interface
    caller UninstallProtocolInterface,          handle, protocol, interface
    caller HandleProtocol,                      handle, protocol, interface
    caller RegisterProtocolNotify,              protocol, event, registration
    caller LocateHandle,                        search_type, protocol, search_key, buffer_size, buffer
    caller LocateDevicePath,                    protocol, device_path, device
    caller InstallConfigurationTable,           guid, table
        ; Image Services
    caller LoadImage,                           boot_policy, parent_image_handle, file_path, source_buffer, source_size, image_handle
    caller StartImage,                          image_handle, exit_data_size, exit_data
    caller Exit,                                image_handle, exit_status, exit_data_size, exit_data
    caller UnloadImage,                         image_handle
    caller ExitBootServices,                    image_handle, map_key
        ; Miscellaneous Services
    caller GetNextMonotonicCount,               count
    caller Stall,                               microseconds
    caller SetWatchdogTimer,                    timeout, watchdog_code, data_size, watchdog_data
        ; DriverSupport Services
    caller ConnectController,                   controller_handle, driver_image_handle, remaining_device_path, recursive
    caller DisconnectController,                controller_handle, driver_image_handle, child_handle
        ; Open and Close Protocol Services
    caller OpenProtocol, handle,                protocol, interface, agent_handle, controller_handle, attributes
    caller CloseProtocol, handle,               protocol, agent_handle, controller_handle
    caller OpenProtocolInformation,             handle, protocol, entry_buffer, entry_count
        ; Library Services
    caller ProtocolsPerHandle,                  handle, protocol_buffer, protocol_buffer_count
    caller LocateHandleBuffer,                  search_type, protocol, search_key, no_handles, buffer
    caller LocateProtocol,                      protocol, registration, interface
    caller InstallMultipleProtocolInterfaces,   handle, protocol, interface, null_terminated&
    caller UninstallMultipleProtocolInterfaces, handle, protocol, interface, null_terminated&
        ; 32-bit CRC Services
    caller CalculateCrc32,                      data, data_size, crc32
        ; Miscellaneous Services
    caller CopyMem,                             destination, source, length
    caller SetMem,                              buffer, size, value
    caller CreateEventEx,                       type, notify_tpl, notify_function, notify_context, event_group, event

    purge caller
end namespace
end macro
