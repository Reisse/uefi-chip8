#include <efi.h>
#include <efilib.h>

#include "c8display.h"

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
	EFI_GUID EfiGraphicsOutputProtocolGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;

	EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphOut = NULL;

	EFI_HANDLE *HandleBuffer = NULL;
	UINTN HandleCount;

	InitializeLib(ImageHandle, SystemTable);

	uefi_call_wrapper(BS->LocateHandleBuffer, 5, ByProtocol, &EfiGraphicsOutputProtocolGuid, NULL, &HandleCount, &HandleBuffer);
	uefi_call_wrapper(BS->HandleProtocol, 3, HandleBuffer[0], &EfiGraphicsOutputProtocolGuid, (VOID **) &GraphOut);

	display_init(ST->ConOut, GraphOut);
	display_px_flip(0, 0);
	display_px_set(10, 10, 1);
	display_px_flip(10, 10);
	display_px_flip(11, 11);
	display_px_flip(12, 12);
	display_px_set(13, 13, 1);
	display_px_flip(10, 10);
	display_px_flip(11, 11);
	display_px_set(12, 12, 1);
	display_px_set(63, 31, 1);
	display_px_set(63, 0, 1);
	display_px_set(0, 31, 1);

	while (1) {}

	return EFI_SUCCESS;
}
