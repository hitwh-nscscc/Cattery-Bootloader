# Cattery Bootloader - First Stage Bootloader
most recently [![Build status](https://ci.appveyor.com/api/projects/status/dc7urowjl0nnnb0k?svg=true)](https://ci.appveyor.com/project/ArHShRn/cattery-bootloader) <br>
branch/master [![Build status](https://ci.appveyor.com/api/projects/status/dc7urowjl0nnnb0k/branch/master?svg=true)](https://ci.appveyor.com/project/ArHShRn/cattery-bootloader/branch/master) <br>
branch/rdev [![Build status](https://ci.appveyor.com/api/projects/status/dc7urowjl0nnnb0k/branch/rdev?svg=true)](https://ci.appveyor.com/project/ArHShRn/cattery-bootloader/branch/rdev) <br>
----
Cattery Bootloader is a first-stage bootloader targeting RagdollSoC, MIPS32EL, used for board-level initializing and have an exception vector that catches magic error.

For now, Cattery Bootloader has two booting modes(all of them are configured at coding time using #define DEBUG or not):

- Full Mode: Full functionality, contains several testing methods to test the board.
![Full](./doc/pics/Full.jpg)
- Reduced Mode: Reduced functionality, used only for booting(u-boot or else).
![Reduced](./doc/pics/Reduced.jpg)

# Copyright and Reference Notice

## Barebone
Cattery Bootloader's first prototype is based on barebone by Jun Sun, 10/16/2001.
Please refer to [Linux/MIPS Porting Guide](https://www.linux-mips.org/wiki/Linux/MIPS_Porting_Guide), section "Hello, world!".

## Baremetal softwares for TrivialMIPS platform @ THU
### Features below are derived from TrivialMIPS FSB
- Toggle KSEG0 Cachability
- Xilinx UART 16550 IP Core lowlevel initialization <br>
### Authorized usage by Harry-Chen @ THU. <br>
- If you want to redistribute FSB which includes these features, please contact Harry-Chen @ https://github.com/Harry-Chen <br>
- TrivialMIPS Software https://github.com/trivialmips/TrivialMIPS_Software <br>
