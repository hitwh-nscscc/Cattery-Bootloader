OUTPUT_FORMAT("elf32-tradlittlemips")
OUTPUT_ARCH(mips)
ENTRY(_spi_start)

MEMORY
{
    BOOTROM     : ORIGIN = 0xBFC00000, LENGTH = 1M
    SPIROM      : ORIGIN = 0xBDA00000, LENGTH = 1M
    RAM         : ORIGIN = 0x80200000, LENGTH = 128M
}

SECTIONS
{
    .text : 
    {
        *(.text)
        *(.rodata)
        *(.rodata1)
        *(.rodata.str1.4)
    } > RAM

    .reginfo : 
    { 
        *(.reginfo) 
    } > RAM

    .date : 
    {
        *(.data)
    } > RAM

    .bss  : 
    {
        *(.dynbss)
        *(.bss)
    } > RAM
}
