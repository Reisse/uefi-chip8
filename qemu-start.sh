#!/bin/sh
mkdir -p qemu-fs && cp -f uc8.efi ./qemu-fs/ && qemu-system-x86_64 -drive if=pflash,format=raw,file=./qemu-env/OVMF-pure-efi.fd -drive file=fat:rw:./qemu-fs/,media=disk,if=virtio,format=raw -m 512 -M q35 -nodefaults -vga std 
