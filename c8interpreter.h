#pragma once

#include <efi.h>
#include <efilib.h>

#include "c8fs.h"
#include "c8input.h"
#include "c8display.h"
#include "c8sound.h"
#include "c8opcodes.h"

#include "debug.h"

#define CLOCK_RATE 2000 /* Delay for CPU clock in microseconds. */
#define TIMER_RATE 10 /* CPU clocks per timer tick. */

typedef enum
{
	INT_OK = 0,
	INT_INIT_FAILED,
	INT_EXEC_FAILED,
	INT_UNKNOWN_OP
} interpreter_status_t;

typedef enum
{
	EX_NORMAL = 0,
	EX_AWAITS_KEY,
	EX_STOP
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
	key_event_t last_key;
	UINT8 X;
	UINT8 SP;
	UINTN cycle;
	UINTN timer_rate;
};

interpreter_status_t interpreter_init(CHAR16 *rom_file, CHAR16 *image_file, struct interpreter_state *state);
interpreter_status_t interpreter_loop(struct interpreter_state *state);