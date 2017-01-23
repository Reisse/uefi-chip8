#pragma once

/*  X-macro format: opcode, description, mask.
    Due to interpreter logic, operands MUST be sorted in "least (stricter) mask first" order. */
#define FOR_OPCODES(DO) \
	DO(00E0, L"Clears the screen.", 0x00E0) \
	DO(00EE, L"Returns from a subroutine.", 0x00EE) \
	DO(0NNN, L"Calls RCA 1802 program at address NNN.", 0x0FFF) \
	DO(1NNN, L"Jumps to address NNN.", 0x1FFF) \
	DO(2NNN, L"Calls subroutine at NNN.", 0x2FFF) \
	DO(3XNN, L"Skips the next instruction if VX equals NN.", 0x3FFF) \
	DO(4XNN, L"Skips the next instruction if VX doesn't equal NN.", 0x4FFF) \
	DO(5XY0, L"Skips the next instruction if VX equals VY.", 0x5FF0) \
	DO(6XNN, L"Sets VX to NN.", 0x6FFF) \
	DO(7XNN, L"Adds NN to VX.", 0x7FFF) \
	DO(8XY0, L"Sets VX to the value of VY.", 0x8FF0) \
	DO(8XY1, L"Sets VX to VX or VY (bitwise OR).", 0x8FF1) \
	DO(8XY2, L"Sets VX to VX and VY (bitwise AND).", 0x8FF2) \
	DO(8XY3, L"Sets VX to VX xor VY (bitwise XOR).", 0x8FF3) \
	DO(8XY4, L"Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.", 0x8FF4) \
	DO(8XY5, L"VY is subtracted from VX. VF is set to 0 when there's a borrow, and to 1 when there isn't.", 0x8FF5) \
	DO(8XY6, L"Shift VY right by one and store in VX. VF is set to the value of the least significant bit of VY before the shift.", 0x8FF6) \
	DO(8XY7, L"Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and to 1 when there isn't.", 0x8FF7) \
	DO(8XYE, L"Shifts VY left by one and store in VX. VF is set to the value of the most significant bit of VY before the shift.", 0x8FFE) \
	DO(9XY0, L"Skips the next instruction if VX doesn't equal VY.", 0x9FF0) \
	DO(ANNN, L"Sets I to the address NNN.", 0xAFFF) \
	DO(BNNN, L"Jumps to the address (NNN + V0).", 0xBFFF) \
	DO(CXNN, L"Sets VX to the result of a bitwise AND operation on a random number (0 to 255) and NN.", 0xCFFF) \
	DO(DXYN, L"Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels. Each row of 8 pixels is read as bit-coded starting from memory location I; I value doesn’t change after the execution of this instruction. VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, and to 0 if that doesn’t happen.", 0xDFFF) \
	DO(EX9E, L"Skips the next instruction if the key stored in VX is pressed.", 0xEF9E) \
	DO(EXA1, L"Skips the next instruction if the key stored in VX isn't pressed.", 0xEFA1) \
	DO(FX07, L"Sets VX to the value of the delay timer.", 0xFF07) \
	DO(FX0A, L"A key press is awaited, and then stored in VX (blocking operation, all instructions halted until next key event).", 0xFF0A) \
	DO(FX15, L"Sets the delay timer to VX.", 0xFF15) \
	DO(FX18, L"Sets the sound timer to VX.", 0xFF18) \
	DO(FX1E, L"Adds VX to I.", 0xFF1E) \
	DO(FX29, L"Sets I to the location of the sprite for the character in VX.", 0xFF29) \
	DO(FX33, L"Stores the binary-coded decimal representation of VX, with the most significant of three digits at the address in I, the middle digit at I plus 1, and the least significant digit at I plus 2.", 0xFF33) \
	DO(FX55, L"Stores V0 to VX (including VX) in memory starting at address I. I is set to I + X + 1 after operation.", 0xFF55) \
	DO(FX65, L"Fills V0 to VX (including VX) with values from memory starting at address I. I is set to I + X + 1 after operation.", 0xFF65)
