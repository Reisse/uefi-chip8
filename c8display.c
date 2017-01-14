#include "c8display.h"

SIMPLE_TEXT_OUTPUT_INTERFACE *CO = NULL;
EFI_GRAPHICS_OUTPUT_PROTOCOL *GO = NULL;

EFI_GRAPHICS_OUTPUT_BLT_PIXEL PX_WHITE = {255, 255, 255, 0};
EFI_GRAPHICS_OUTPUT_BLT_PIXEL PX_BLACK = {0, 0, 0, 0};

CHAR8 display[DISPLAY_WIDTH * DISPLAY_HEIGHT] = {0};

display_status_t display_init(SIMPLE_TEXT_OUTPUT_INTERFACE *ConOut, EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphOut)
{
	if (!ConOut || !GraphOut)
		return DS_ERROR;

	CO = ConOut;
	GO = GraphOut;

	if (EFI_ERROR(uefi_call_wrapper(CO->Reset, 2, CO, FALSE)))
		return DS_ERROR;

	if (EFI_ERROR(uefi_call_wrapper(CO->EnableCursor, 2, CO, FALSE)))
		return DS_ERROR;

	return DS_OK;
}

display_status_t display_clear()
{
	if (!CO)
		return DS_ERROR;

	if (EFI_ERROR(uefi_call_wrapper(CO->ClearScreen, 1, CO)))
		return DS_ERROR;

	return DS_OK;
}

px_status_t display_px_set(unsigned const int x, unsigned const int y, const px_content_t value)
{
	if (x > DISPLAY_WIDTH - 1 || y > DISPLAY_HEIGHT - 1 || !GO)
		return PX_ERROR;

	if (display[x + y * DISPLAY_WIDTH] == value)
		return PX_CLEAN;
	else
	{
		switch (value)
		{
			case PX_BLANK:
			if (EFI_ERROR(uefi_call_wrapper(GO->Blt, 10, GO, &PX_BLACK, EfiBltVideoFill, 0, 0, 
					x * PX_SCALE_FACTOR, y * PX_SCALE_FACTOR, PX_SCALE_FACTOR, PX_SCALE_FACTOR, 0)))
			{
				return PX_ERROR;
			}
			break;

			case PX_FILLED:
			if (EFI_ERROR(uefi_call_wrapper(GO->Blt, 10, GO, &PX_WHITE, EfiBltVideoFill, 0, 0, 
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
	if (x > DISPLAY_WIDTH - 1 || y > DISPLAY_HEIGHT - 1 || !GO)
		return PX_ERROR;

	switch (display[x + y * DISPLAY_WIDTH])
	{
		case PX_BLANK:
		if (EFI_ERROR(uefi_call_wrapper(GO->Blt, 10, GO, &PX_WHITE, EfiBltVideoFill, 0, 0, 
				x * PX_SCALE_FACTOR, y * PX_SCALE_FACTOR, PX_SCALE_FACTOR, PX_SCALE_FACTOR, 0)))
		{
			return PX_ERROR;
		}
		display[x + y * DISPLAY_WIDTH] = PX_FILLED;
		return PX_DIRTY;

		case PX_FILLED:
		if (EFI_ERROR(uefi_call_wrapper(GO->Blt, 10, GO, &PX_BLACK, EfiBltVideoFill, 0, 0, 
				x * PX_SCALE_FACTOR, y * PX_SCALE_FACTOR, PX_SCALE_FACTOR, PX_SCALE_FACTOR, 0)))
		{
			return PX_ERROR;
		}
		display[x + y * DISPLAY_WIDTH] = PX_BLANK;
		return PX_DIRTY;
	}

	return PX_CLEAN;
}