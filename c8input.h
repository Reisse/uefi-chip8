#pragma once

#include <efi.h>
#include <efilib.h>

typedef enum
{
	IN_OK = 0,
	IN_ERROR
} input_status_t;

typedef enum
{
	KB_0 = 0,
	KB_1,
	KB_2,
	KB_3,
	KB_4,
	KB_5,
	KB_6,
	KB_7,
	KB_8,
	KB_9,
	KB_A,
	KB_B,
	KB_C,
	KB_D,
	KB_E,
	KB_F,
	KB_PASS,
	KB_ERROR
} keyevent_t;

input_status_t input_init();
keyevent_t input_next();