OUTPUT_FORMAT("elf32-tradlittlemips")
OUTPUT_ARCH(mips)
ENTRY(_start)

MEMORY
{
    BOOTROM     : ORIGIN = 0xBFC00000, LENGTH = 128K
    RAM         : ORIGIN = 0x80000000, LENGTH = 128M
}

SECTIONS
{
    .text : 
    {
        *(.text)
        *(.rodata)
        *(.rodata1)
        *(.rodata.str1.4)
    } > BOOTROM

    .reginfo : 
    { 
        *(.reginfo) 
    } > BOOTROM

    .date : 
    {
        *(.data)
    } > BOOTROM

    .bss  : 
    {
        *(.dynbss)
        *(.bss)
    } > BOOTROM
}
