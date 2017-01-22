#include "c8interpreter.h"

interpreter_status_t interpreter_init(CHAR16 *rom_file, CHAR16 *image_file, struct interpreter_state *state)
{
	state->PC = 512;
	state->I = 512;
	state->delay_timer = 0;
	state->sound_timer = 0;
	state->execution_state = EX_NORMAL;
	state->cycle = 0;
	state->clock_rate = CLOCK_RATE;

	UINTN rom_sz = 512;
	UINTN image_sz = 3584;

	if (EFI_ERROR(read_file(rom_file, &rom_sz, (VOID *) state->memory)))
		return INT_INIT_FAILED;

	if (EFI_ERROR(read_file(image_file, &image_sz, (VOID *) (state->memory + 512))))
		return INT_INIT_FAILED;

	return INT_OK;
}

interpreter_status_t interpreter_loop(struct interpreter_state *state)
{
	return INT_OK;
}