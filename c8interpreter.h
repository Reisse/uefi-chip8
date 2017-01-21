#pragma once

#include "c8fs.h"
#include "c8input.h"
#include "c8display.h"

#include "debug.h"

typedef enum
{
	INT_OK = 0,
	INT_EXEC_FAILED
} interpreter_status_t;

struct interpreter_state;

struct interpreter_state* interpreter_init(CHAR16 *rom_file, CHAR16 *image_file);
interpreter_status_t interpreter_loop(struct interpreter_state *state);