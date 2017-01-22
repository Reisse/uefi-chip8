#include "c8fs.h"

EFI_STATUS read_file(CHAR16 *path, UINTN *buf_sz, VOID *buf)
{
	EFI_STATUS status;

	EFI_HANDLE *HandleBuffer = NULL;
	UINTN HandleCount;

	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FsProto = NULL;
	EFI_FILE_PROTOCOL *FsVol = NULL, *File = NULL;

	status = uefi_call_wrapper(BS->LocateHandleBuffer, 5, ByProtocol, &gEfiSimpleFileSystemProtocolGuid, NULL, &HandleCount, &HandleBuffer);
	if (EFI_ERROR(status))
	{
		LOG(L"Failed opening file: BS->LocateHandleBuffer with gEfiSimpleFileSystemProtocolGuid returned %r\n", status);
		return status;
	}

	status = uefi_call_wrapper(BS->HandleProtocol, 3, HandleBuffer[0], &gEfiSimpleFileSystemProtocolGuid, (VOID **) &FsProto);
	if (EFI_ERROR(status))
	{
		LOG(L"Failed opening file: BS->HandleProtocol at 0 with gEfiSimpleFileSystemProtocolGuid returned %r\n", status);
		return status;
	}

	status = uefi_call_wrapper(FsProto->OpenVolume, 2, FsProto, &FsVol);
	if (EFI_ERROR(status))
	{
		LOG(L"Failed opening file: FsProto->OpenVolume returned %r\n", status);
		return status;
	}

	status = uefi_call_wrapper(FsVol->Open, 5, FsVol, &File, path, EFI_FILE_MODE_READ);
	if (EFI_ERROR(status))
	{
		LOG(L"Failed opening file \"%s\": FsVol->Open returned %r\n", path, status);
		return status;
	}

	status = uefi_call_wrapper(File->Read, 3, File, buf_sz, buf);
	uefi_call_wrapper(File->Close, 1, File);

	return status;
}