#include <efi.h>
#include <efilib.h>

#include "c8display.h"
#include "c8input.h"

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
	EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphOut = NULL;

	EFI_HANDLE *HandleBuffer = NULL;
	UINTN HandleCount;

	InitializeLib(ImageHandle, SystemTable);

	uefi_call_wrapper(BS->LocateHandleBuffer, 5, ByProtocol, &gEfiGraphicsOutputProtocolGuid, NULL, &HandleCount, &HandleBuffer);
	uefi_call_wrapper(BS->HandleProtocol, 3, HandleBuffer[0], &gEfiGraphicsOutputProtocolGuid, (VOID **) &GraphOut);

	display_init(ST->ConOut, GraphOut);
	input_init(ST->ConIn);

	keyevent_t k;
	while (1)
	{
		k = input_next();
		if (k != KB_PASS && k != KB_ERROR)
		{
			display_px_flip(k, 0);
			display_px_flip(63, 31);
		}
	}

	return EFI_SUCCESS;
}
