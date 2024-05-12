macro efi_struct? definition&
    macro end?.efi_struct!
                %top:
            end namespace
        esc end struc
        virtual at 0
            match a b, definition
                a a
            else
                definition definition
            end match
        end virtual
        purge end?.struct
    end macro

    esc struc definition
        label . : .%top - .
        namespace .
end macro
