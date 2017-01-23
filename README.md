# uefi-chip8
CHIP-8 emulator as an UEFI application
## Building
You'll have to build latest `gnu-efi` library. It is included as a submodule, so you should clone this repo:
```
git clone --recursive https://github.com/Reisse/uefi-chip8.git
```
Then, make and install `gnu-efi`:
```
cd ./uefi-chip8/gnu-efi-code/ && make && sudo make install
```
Finally, build uefi-chip8 itself:
```
cd .. && make
```
This builds `uc8.efi` file, which is an UEFI application that you could run either in QEMU or on any UEFI device with secure boot switched off.
## Testing in QEMU
Make sure you have QEMU installed. Then, build as explained in previous section and run `qemu-start.sh`. Wait for EFI Shell prompt and run:
```
fs0:\uc8.efi
```
Follow the instructions on your screen. In case of trouble, press `Z`.
## License
* The "qemu-env" directory contains its own LICENSE file with licensing information, please read it.
* "gnu-efi" submodule also contains its own license information in `gnu-efi-code/README` file
* For everything else, see LICENSE.md

