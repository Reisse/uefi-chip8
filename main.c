#include <efi.h>
#include <efilib.h>

#include "c8display.h"
#include "c8input.h"
#include "c8fs.h"

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
	CHAR16 **argv = NULL;
	INTN argc;

	InitializeLib(ImageHandle, SystemTable);
	argc = GetShellArgcArgv(ImageHandle, &argv);
	if (argc < 2) 
	{
		Print(L"CHIP-8 emulator.\nUsage: uc8 FILE\n");
		return EFI_SUCCESS;
	}

	display_init();
	input_init();
	
	return EFI_SUCCESS;
}
