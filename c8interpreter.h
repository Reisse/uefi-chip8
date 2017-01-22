#pragma once

#include "c8fs.h"
#include "c8input.h"
#include "c8display.h"

#include "debug.h"

#define CLOCK_RATE 10000 /* CPU clocks per 1/60 of second. */

typedef enum
{
	INT_OK = 0,
	INT_INIT_FAILED,
	INT_EXEC_FAILED
} interpreter_status_t;

typedef enum
{
	EX_NORMAL = 0,
	EX_AWAITS_KEY
} execution_state_t;

struct interpreter_state
{
	UINT8 memory[4096];
	UINT16 stack[16];
	UINT8 V[16];
	UINT16 PC;
	UINT16 I;
	UINT8 delay_timer;
	UINT8 sound_timer;
	execution_state_t execution_state;
	UINTN cycle;
	UINTN clock_rate;
};

interpreter_status_t interpreter_init(CHAR16 *rom_file, CHAR16 *image_file, struct interpreter_state *state);
interpreter_status_t interpreter_loop(struct interpreter_state *state);