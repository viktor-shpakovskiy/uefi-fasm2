include 'macro/proc64.inc'

macro efi_call table*, protocol*, function*, args&
    mov rdi, table
    mov rdi, [rdi + protocol#.#function]
    fastcall rdi, args
end macro
