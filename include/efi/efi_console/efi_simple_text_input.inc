EFI_SIMPLE_TEXT_INPUT_GUID fix 0x387477c1,0x69c7,0x11d2,0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b

efi_struct EFI_SIMPLE_TEXT_INPUT
    Reset           FUNCTION
    ReadKeyStroke   FUNCTION
    WaitForKeyEvent EFI_EVENT
end efi_struct

macro EFI_SIMPLE_TEXT_INPUT_init self*
namespace self
    macro caller function, params&
        macro function params
            efi_call [self], EFI_SIMPLE_TEXT_INPUT, function, [self], params
        end macro
    end macro
    
    caller Reset,           extended_verification
    caller ReadKeyStroke,   key

    purge caller

    macro bind
        mov r15, [self]
    end macro

    macro getWaitForKeyEvent
        mov rax, [r15 + EFI_SIMPLE_TEXT_INPUT.WaitForKeyEvent]
    end macro
end namespace
end macro

efi_struct EFI_INPUT_KEY
    ScanCode    UINT16
    UnicodeChar CHAR16
end efi_struct

macro EFI_INPUT_KEY_init self*
namespace self
    macro bind
        mov r15, [self]
    end macro

    macro getter value_name
        macro get#value_name
            mov rax, [r15 + EFI_INPUT_KEY.#value_name]
        end macro
    end macro

    getter ScanCode
    getter UnicodeChar

    purge getter
end namespace
end macro
