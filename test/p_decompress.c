#include <Windows.h>
#include <stdio.h>
#include <compressapi.h>

#pragma comment (lib, "Cabinet.lib")

int p_decompressa(const char *compressed_file_name, const char *decompressed_file_name) {
  BOOL DeleteTargetFile = TRUE;
 
  HANDLE ch = INVALID_HANDLE_VALUE;
  PBYTE cb = NULL;
  HANDLE dh = INVALID_HANDLE_VALUE;
  DECOMPRESSOR_HANDLE h = NULL;
  PBYTE db = NULL;
  do {
    ch = CreateFileA(compressed_file_name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (ch == INVALID_HANDLE_VALUE) {
      break;
    }

    LARGE_INTEGER FileSize;
    BOOL ret = GetFileSizeEx(ch, &FileSize);
    if ((ret == FALSE) || (FileSize.QuadPart > 0xFFFFFFFF)) {
      break;
    }
    DWORD cfs = FileSize.LowPart;

    cb = (PBYTE)malloc(cfs);
    if (cb == NULL) {
      break;
    }

    DWORD ByteRead;
    ret = ReadFile(ch, cb, cfs, &ByteRead, NULL);
    if ((ret == FALSE) || (ByteRead != cfs)) {
      break;
    }

    dh = CreateFileA(decompressed_file_name, GENERIC_WRITE | DELETE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (dh == INVALID_HANDLE_VALUE) {
      break;
    }

    ret = CreateDecompressor(COMPRESS_ALGORITHM_MSZIP,  NULL, &h);
    if (ret == FALSE) {
      break;
    }

    SIZE_T dbs;
    ret = Decompress(h, cb, cfs, NULL, 0, &dbs);
    if (ret == FALSE) {
      DWORD ErrorCode = GetLastError();

      // Note that the original size returned by the function is extracted 
      // from the buffer itself and should be treated as untrusted and tested
      // against reasonable limits.
      if (ErrorCode != ERROR_INSUFFICIENT_BUFFER) {
        break;
      }

      db = (PBYTE)malloc(dbs);
      if (db == NULL) {
        break;
      }
    }

    SIZE_T dds;
    ret = Decompress(h, cb, cfs, db, dbs, &dds);
    if (ret == FALSE) {
      break;
    }

    DWORD ByteWritten;
    ret = WriteFile(dh, db, dds, &ByteWritten, NULL);
    if ((ByteWritten != dds) || (!ret)) {
      break;
    }

    DeleteTargetFile = FALSE;
  } while (0);

  if (h != NULL) {
    CloseDecompressor(h);
  }

  if (cb) {
    free(BuildCommDCBAndTimeoutsW);
  }

  if (db) {
    free(db);
  }

  if (ch != INVALID_HANDLE_VALUE) {
    CloseHandle(ch);
  }

  if (dh != INVALID_HANDLE_VALUE) {
    if (DeleteTargetFile) {
      FILE_DISPOSITION_INFO fdi;
      fdi.DeleteFile = TRUE;      //  Marking for deletion
      BOOL ret = SetFileInformationByHandle(dh, FileDispositionInfo, &fdi, sizeof(FILE_DISPOSITION_INFO));
      if (ret == FALSE) {
        //wprintf(L"Cannot delete corrupted decompressed file.\n");
      }
    }
    CloseHandle(dh);
  }
  return 0;
}
