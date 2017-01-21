#include <efi.h>
#include <efilib.h>

#include "c8interpreter.h"

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
	CHAR16 **argv = NULL;
	INTN argc;

	interpreter_status_t i_status;
	struct interpreter_state* i_state = NULL;

	InitializeLib(ImageHandle, SystemTable);
	argc = GetShellArgcArgv(ImageHandle, &argv);
	if (argc < 2) 
	{
		Print(L"CHIP-8 emulator.\nUsage: uc8 FILE [ROM]\n");
		return EFI_SUCCESS;
	}
	else if (argc == 2)
		i_state = interpreter_init(L"rom.c8", argv[1]);
	else
		i_state = interpreter_init(argv[2], argv[1]);

	if (!i_state) {
		Print(L"Failed to initialize interpreter: interpreter_init returned NULL\n");
		return EFI_SUCCESS;
	}

	i_status = interpreter_loop(i_state);
	if (i_status != INT_OK) {
		Print(L"Failed: interpreter_loop returned %r\n", i_status);
	}

	return EFI_SUCCESS;
}
