EFI_FILE_PROTOCOL_REVISION fix 0x00010000

efi_struct EFI_FILE
    Revision    UINT64
    Open        FUNCTION
    Close       FUNCTION
    Delete      FUNCTION
    Read        FUNCTION
    Write       FUNCTION
    GetPosition FUNCTION
    SetPosition FUNCTION
    GetInfo     FUNCTION
    SetInfo     FUNCTION
    Flush       FUNCTION
end efi_struct

macro EFI_FILE_init self*
namespace self
    macro bind
        mov r15, [self]
    end macro

    macro getter64 value_name
        macro get#value_name
            mov rax, qword [r15 + EFI_FILE.#value_name]
        end macro
    end macro
    
    getter64 Revision

    purge getter64

    macro caller function, params&
        macro function params
            efi_call [self], EFI_FILE, function, [self], params
        end macro
    end macro

    caller Open,        new_handle, file_name, open_mode, attributes
    caller Close
    caller Delete
    caller Read,        buffer_size, buffer
    caller Write,       buffer_size, buffer
    caller GetPosition, position
    caller SetPosition, position
    caller GetInfo,     information_type, buffer_size, buffer
    caller SetInfo,     information_type, buffer_size, buffer
    caller Flush

    purge caller
end namespace
end macro
