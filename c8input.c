#include "c8input.h"

SIMPLE_INPUT_INTERFACE *CI = NULL;

input_status_t input_init(SIMPLE_INPUT_INTERFACE *ConIn)
{
	if (!ConIn)
		return IN_ERROR;

	CI = ConIn;

	if (EFI_ERROR(uefi_call_wrapper(CI->Reset, 2, CI, FALSE)))
		return IN_ERROR;

	return IN_OK;
}

keyevent_t input_next()
{
	if (!CI)
		return KB_ERROR;

	EFI_STATUS st;
	EFI_INPUT_KEY *key_data = NULL;

	st = uefi_call_wrapper(CI->ReadKeyStroke, 2, CI, key_data);

	if (st == EFI_DEVICE_ERROR)
		return KB_ERROR;
	else if (st == EFI_NOT_READY)
		return KB_PASS;

	if (key_data->ScanCode == 0x00)
		switch (key_data->UnicodeChar)
		{
			case L'0':
			return KB_0;

			case L'1':
			return KB_1;

			case L'2':
			return KB_2;

			case L'3':
			return KB_3;

			case L'4':
			return KB_4;

			case L'5':
			return KB_5;

			case L'6':
			return KB_6;

			case L'7':
			return KB_7;

			case L'8':
			return KB_8;

			case L'9':
			return KB_9;

			case L'A':
			case L'a':
			return KB_A;

			case L'B':
			case L'b':
			return KB_B;

			case L'C':
			case L'c':
			return KB_C;

			case L'D':
			case L'd':
			return KB_D;

			case L'E':
			case L'e':
			return KB_E;

			case L'F':
			case L'f':
			return KB_F;
		}

	return KB_PASS;
}