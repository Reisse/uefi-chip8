ARCH	=$(shell uname -m | sed s,i[3-9]86,ia32,)

EFIINC	=/usr/local/include/efi
EFIINCS	=-I$(EFIINC) -I$(EFIINC)/$(ARCH) -I$(EFIINC)/protocol
EFILIB	=/usr/local/lib
EFICRT	=$(EFILIB)/crt0-efi-$(ARCH).o
EFILDS	=$(EFILIB)/elf_$(ARCH)_efi.lds

CC	=gcc
CFLAGS	=-Wall $(EFIINCS) -fno-stack-protector -fPIC -fshort-wchar -mno-red-zone -c
ifeq ($(ARCH),x86_64)
	CFLAGS += -DEFI_FUNCTION_WRAPPER
endif

LDFLAGS	=-nostdlib -znocombreloc -T $(EFILDS) -shared -Bsymbolic -L $(EFILIB) $(EFICRT)

TARGET	=uc8

SRC=$(wildcard *.c)
OBJ=$(SRC:%.c=%.o)

all: $(TARGET).efi 

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

%.so: $(OBJ)
	ld $(LDFLAGS) $(OBJ) -o $(TARGET).so -lefi -lgnuefi

%.efi: %.so
	objcopy -j .text -j .sdata -j .data -j .dynamic -j .dynsym -j .rel -j .rela -j .reloc --target=efi-app-$(ARCH) $^ $@

clean:
	rm -f *.o *.so *.efi
