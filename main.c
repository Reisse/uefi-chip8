#include <efi.h>
#include <efilib.h>

#include "c8display.h"
#include "c8input.h"

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
	CHAR16 **argv = NULL;
	INTN argc;

	InitializeLib(ImageHandle, SystemTable);
	argc = GetShellArgcArgv(ImageHandle, &argv);
	if (argc < 2) 
	{
		Print(L"CHIP-8 emulator.\nUsage: uc8 FILE\n");
		return EFI_SUCCESS;
	}

	EFI_STATUS Status;

	EFI_HANDLE *HandleBuffer = NULL;
	UINTN HandleCount;

	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FsProto = NULL;
	EFI_FILE_PROTOCOL *FsVol = NULL, *File = NULL;

	Status = uefi_call_wrapper(BS->LocateHandleBuffer, 5, ByProtocol, &gEfiSimpleFileSystemProtocolGuid, NULL, &HandleCount, &HandleBuffer);
	if (EFI_ERROR(Status))
	{
		Print(L"Failed opening file: BS->LocateHandleBuffer with gEfiSimpleFileSystemProtocolGuid returned %r\n", Status);
		return Status;
	}

	Status = uefi_call_wrapper(BS->HandleProtocol, 3, HandleBuffer[0], &gEfiSimpleFileSystemProtocolGuid, (VOID **) &FsProto);
	if (EFI_ERROR(Status))
	{
		Print(L"Failed opening file: BS->HandleProtocol at 0 with gEfiSimpleFileSystemProtocolGuid returned %r\n", Status);
		return Status;
	}

	Status = uefi_call_wrapper(FsProto->OpenVolume, 2, FsProto, &FsVol);
	if (EFI_ERROR(Status))
	{
		Print(L"Failed opening file: FsProto->OpenVolume returned %r\n", Status);
		return Status;
	}

	Status = uefi_call_wrapper(FsVol->Open, 5, FsVol, File, argv[1], EFI_FILE_MODE_READ);
	if (EFI_ERROR(Status))
	{
		Print(L"Failed opening file: FsVol->Open returned %r\n", Status);
		return Status;
	}

	Status = uefi_call_wrapper(FsVol->Open, 5, FsVol, File, argv[1], EFI_FILE_MODE_READ);
	if (EFI_ERROR(Status))
	{
		Print(L"Failed opening file: FsVol->Open returned %r\n", Status);
		return Status;
	}

	Status = uefi_call_wrapper(File->Close, 1, File);
	if (EFI_ERROR(Status))
	{
		/* This will never happen. */
		Print(L"Failed closing file: File->Close returned %r\n", Status);
		return Status;
	}

	EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphOut = NULL;

	Status = uefi_call_wrapper(BS->LocateHandleBuffer, 5, ByProtocol, &gEfiGraphicsOutputProtocolGuid, NULL, &HandleCount, &HandleBuffer);
	if (EFI_ERROR(Status))
	{
		Print(L"Failed initializing display: BS->LocateHandleBuffer with gEfiGraphicsOutputProtocolGuid returned %r\n", Status);
		return Status;
	}

	/* First GOP will most probably be the visible one. */
	Status = uefi_call_wrapper(BS->HandleProtocol, 3, HandleBuffer[0], &gEfiGraphicsOutputProtocolGuid, (VOID **) &GraphOut);
	if (EFI_ERROR(Status))
	{
		Print(L"Failed initializing display: BS->HandleProtocol at 0 with gEfiGraphicsOutputProtocolGuid returned %r\n", Status);
		return Status;
	}

	display_init(ST->ConOut, GraphOut);
	
	input_init(ST->ConIn);

	return EFI_SUCCESS;
}
