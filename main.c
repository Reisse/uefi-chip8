#include <efi.h>
#include <efilib.h>

#include "c8interpreter.h"

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
	CHAR16 **argv = NULL;
	INTN argc;

	interpreter_status_t i_status;
	struct interpreter_state i_state = {0};

	InitializeLib(ImageHandle, SystemTable);
	argc = GetShellArgcArgv(ImageHandle, &argv);
	if (argc < 2) 
	{
		Print(L"CHIP-8 emulator.\nUsage: uc8 FILE [ROM]\n");
		return EFI_SUCCESS;
	}
	else if (argc == 2)
		i_status = interpreter_init(L"rom.c8", argv[1], &i_state);
	else
		i_status = interpreter_init(argv[2], argv[1], &i_state);

	if (i_status != INT_OK)
	{
		Print(L"Failed to initialize interpreter.\n");
		return EFI_SUCCESS;
	}

	if (input_init() != IN_OK)
	{
		Print(L"Failed to initialize keyboard input.\n");
		return EFI_SUCCESS;
	}

	if (display_init() != DS_OK)
	{
		Print(L"Failed to initialize display.\n");
		return EFI_SUCCESS;
	}

	i_status = interpreter_loop(&i_state);
	if (i_status != INT_OK)
		Print(L"Failed in interpreter loop.\n");
	else
		display_clear();

	return EFI_SUCCESS;
}
