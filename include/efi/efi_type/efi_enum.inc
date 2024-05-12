macro efi_enum enum_name
    counter = 0
    macro item name, value
        if ~ `value eq ''
            enum_name#.#name := value
            counter = value + 1
        else
            enum_name#.#name := counter
            counter = counter + 1
        end if
    end macro
    struc enum_name value
        . UINT32 value
    end struc
end macro

macro end?.efi_enum!
    purge item
end macro
