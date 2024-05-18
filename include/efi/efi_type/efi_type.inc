macro efi_decltype typename, data_mnemonic, _align
    struc typename value:?&
        align _align
        . data_mnemonic value
    end struc
end macro

efi_decltype BOOL,   db, 1
efi_decltype INT8,   db, 1
efi_decltype UINT8,  db, 1
efi_decltype CHAR8,  db, 1
efi_decltype CHAR16, du, 2
efi_decltype INT16,  dw, 2
efi_decltype UINT16, dw, 2
efi_decltype INT32,  dd, 4
efi_decltype UINT32, dd, 4
efi_decltype INT64,  dq, 8
efi_decltype UINT64, dq, 8
efi_decltype INTN,   dq, 8
efi_decltype UINTN,  dq, 8

struc PTR typename, value&
    . UINTN value
end struc

struc EFI_PHYSICAL_ADDRESS value&
    . UINTN value
end struc

struc FUNCTION value&
    . UINTN value
end struc

struc EFI_GUID a, b, c, d&
label . : .%top - .
namespace .
    data1 UINT32 a
    data2 UINT16 b
    data3 UINT16 c
    data4 UINT8  d
%top:
end namespace
end struc

struc EFI_STATUS value&
    . INTN value
end struc

struc EFI_HANDLE value&
    . PTR VOID, value
end struc

struc EFI_EVENT value&
    . PTR VOID, value
end struc

struc EFI_LBA value&
    . UINT64 value
end struc

struc EFI_TPL value&
    . UINTN value
end struc

struc EFI_MAC_ADDRESS value&
    . UINT8 value
end struc

struc EFI_IPV4_ADDRESS byte1, byte2, byte3, byte4
    . UINT8 byte1, byte2, byte3, byte4
end struc

struc EFI_IPV6_ADDRESS value&
    . UINT8 value
end struc

struc EFI_IP_ADDRESS value&
    . UINT32 value
end struc

struc EFI_SIGNATURE value&
    . UINT64 value
end struc

struc EFI_STRING value&
    . CHAR16 value, 0
end struc

struc EFI_STRING_NL value&
    . EFI_STRING value, 13, 10
end struc
