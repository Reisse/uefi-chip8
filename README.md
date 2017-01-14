# uefi-chip8
CHIP-8/SCHIP emulator as an UEFI application
## Building
You'll have to install `gnu-efi` library. If it is not present in your distro's repos, you can get it [here](https://sourceforge.net/projects/gnu-efi/).

Debian:
```
sudo apt install gnu-efi
```
Then you should clone this repo and run `make`:
```
git clone https://github.com/Reisse/uefi-chip8.git && cd uefi-chip8 && make
```
This builds `uc8.efi` file, which is an UEFI application that you could run either in QEMU or on any UEFI device with secure boot switched off.
## Testing in QEMU
Make sure you have QEMU installed. Then, build as explained in previous section and run `qemu-start.sh`. Wait for EFI Shell prompt and run:
```
fs0:\uc8.efi
```
## License
* The "qemu-env" directory contains its own LICENSE file with licensing information, please read it.
* For everything else, see LICENSE.md

