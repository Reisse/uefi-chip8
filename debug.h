#pragma once

#define DEBUG_MODE 0

#define LOG(fmt, ...) \
			do { if (DEBUG_MODE) Print(fmt, __VA_ARGS__); } while (0)
