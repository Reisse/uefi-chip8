#include "c8display.h"

EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphOut = NULL;

EFI_GRAPHICS_OUTPUT_BLT_PIXEL PX_WHITE = {255, 255, 255, 0};
EFI_GRAPHICS_OUTPUT_BLT_PIXEL PX_BLACK = {0, 0, 0, 0};

CHAR8 display[DISPLAY_WIDTH * DISPLAY_HEIGHT] = {0};

display_status_t display_init()
{
	EFI_STATUS status;

	EFI_HANDLE *HandleBuffer = NULL;
	UINTN HandleCount;

	if (GraphOut)
		return DS_BUSY;

	status = uefi_call_wrapper(BS->LocateHandleBuffer, 5, ByProtocol, &gEfiGraphicsOutputProtocolGuid, NULL, &HandleCount, &HandleBuffer);
	if (EFI_ERROR(status))
	{
		LOG(L"Failed while initializing display: BS->LocateHandleBuffer with gEfiGraphicsOutputProtocolGuid returned %r\n", status);
		return DS_ERROR;
	}

	/* First GOP will most probably be the visible one. */
	status = uefi_call_wrapper(BS->HandleProtocol, 3, HandleBuffer[0], &gEfiGraphicsOutputProtocolGuid, (VOID **) &GraphOut);
	if (EFI_ERROR(status))
	{
		LOG(L"Failed while initializing display: BS->HandleProtocol at 0 with gEfiGraphicsOutputProtocolGuid returned %r\n", status);
		return DS_ERROR;
	}

	if (EFI_ERROR(uefi_call_wrapper(ST->ConOut->Reset, 2, ST->ConOut, FALSE)))
		return DS_ERROR;

	if (EFI_ERROR(uefi_call_wrapper(ST->ConOut->EnableCursor, 2, ST->ConOut, FALSE)))
		return DS_ERROR;

	return DS_OK;
}

display_status_t display_clear()
{
	if (EFI_ERROR(uefi_call_wrapper(ST->ConOut->ClearScreen, 1, ST->ConOut)))
		return DS_ERROR;

	return DS_OK;
}

px_status_t display_px_set(unsigned const int x, unsigned const int y, const px_content_t value)
{
	if (x > DISPLAY_WIDTH - 1 || y > DISPLAY_HEIGHT - 1 || !GraphOut)
		return PX_ERROR;

	if (display[x + y * DISPLAY_WIDTH] == value)
		return PX_CLEAN;
	else
	{
		switch (value)
		{
			case PX_BLANK:
			if (EFI_ERROR(uefi_call_wrapper(GraphOut->Blt, 10, GraphOut, &PX_BLACK, EfiBltVideoFill, 0, 0, 
					x * PX_SCALE_FACTOR, y * PX_SCALE_FACTOR, PX_SCALE_FACTOR, PX_SCALE_FACTOR, 0)))
			{
				return PX_ERROR;
			}
			break;

			case PX_FILLED:
			if (EFI_ERROR(uefi_call_wrapper(GraphOut->Blt, 10, GraphOut, &PX_WHITE, EfiBltVideoFill, 0, 0, 
					x * PX_SCALE_FACTOR, y * PX_SCALE_FACTOR, PX_SCALE_FACTOR, PX_SCALE_FACTOR, 0)))
			{
				return PX_ERROR;
			}
			break;
		}

		display[x + y * DISPLAY_WIDTH] = value;

		return PX_DIRTY;
	}
}

px_status_t display_px_flip(unsigned const int x, unsigned const int y)
{
	if (x > DISPLAY_WIDTH - 1 || y > DISPLAY_HEIGHT - 1 || !GraphOut)
		return PX_ERROR;

	switch (display[x + y * DISPLAY_WIDTH])
	{
		case PX_BLANK:
		if (EFI_ERROR(uefi_call_wrapper(GraphOut->Blt, 10, GraphOut, &PX_WHITE, EfiBltVideoFill, 0, 0, 
				x * PX_SCALE_FACTOR, y * PX_SCALE_FACTOR, PX_SCALE_FACTOR, PX_SCALE_FACTOR, 0)))
		{
			return PX_ERROR;
		}
		display[x + y * DISPLAY_WIDTH] = PX_FILLED;
		return PX_DIRTY;

		case PX_FILLED:
		if (EFI_ERROR(uefi_call_wrapper(GraphOut->Blt, 10, GraphOut, &PX_BLACK, EfiBltVideoFill, 0, 0, 
				x * PX_SCALE_FACTOR, y * PX_SCALE_FACTOR, PX_SCALE_FACTOR, PX_SCALE_FACTOR, 0)))
		{
			return PX_ERROR;
		}
		display[x + y * DISPLAY_WIDTH] = PX_BLANK;
		return PX_DIRTY;
	}

	return PX_CLEAN;
}