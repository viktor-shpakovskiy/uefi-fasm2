EFI_SIMPLE_TEXT_OUTPUT_GUID fix 0x387477c2,0x69c7,0x11d2,0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b

efi_struct EFI_SIMPLE_TEXT_OUTPUT
    Reset             FUNCTION
    OutputString      FUNCTION
    TestString        FUNCTION
    QueryMode         FUNCTION
    SetMode           FUNCTION
    SetAttribute      FUNCTION
    ClearScreen       FUNCTION
    SetCursorPosition FUNCTION
    EnableCursor      FUNCTION
    Mode              PTR EFI_SIMPLE_TEXT_OUTPUT_MODE
end efi_struct

macro EFI_SIMPLE_TEXT_OUTPUT_init self*
namespace self
    macro caller function, params&
        macro function params
            efi_call [self], EFI_SIMPLE_TEXT_OUTPUT, function, [self], params
        end macro
    end macro

    caller Reset,               extended_verification
    caller OutputString,        string
    caller TestString,          string
    caller QueryMode,           mode_number, columns, rows
    caller SetMode,             mode_number
    caller SetAttribute,        Attribute
    caller ClearScreen
    caller SetCursorPosition,   column, row
    caller EnableCursor,        visible

    purge caller

    macro bind
        mov r15, [self]
    end macro

    EFI_SIMPLE_TEXT_OUTPUT_MODE_init

end namespace
end macro

efi_struct EFI_SIMPLE_TEXT_OUTPUT_MODE
    MaxMode       INT32
    Mode          INT32
    Attribute     INT32
    CursorColumn  INT32
    CursorRow     INT32
    CursorVisible BOOL
end efi_struct

macro EFI_SIMPLE_TEXT_OUTPUT_MODE_init
namespace Mode
    macro bind
        mov r14, [r15 + EFI_SIMPLE_TEXT_OUTPUT.Mode]
    end macro

    macro getter value_name
        macro get#value_name
            mov rax, [r14 + EFI_SIMPLE_TEXT_OUTPUT_MODE.#value_name]
        end macro
    end macro

    getter MaxMode
    getter Mode
    getter Attribute
    getter CursorColumn
    getter CursorRow
    getter CursorVisible

    purge getter
end namespace
end macro
