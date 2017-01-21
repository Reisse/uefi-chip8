#pragma once

#include <efi.h>
#include <efilib.h>

#include "debug.h"

EFI_STATUS read_file(CHAR16 *path, UINTN *buf_sz, VOID *buf);