#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>




int fileCount = 0;
int folderCount = 0;
int largeFileCount = 0;

FILETIME fileTime;

int isRoot = 0;

void fileCounter(WCHAR* src) {

	WCHAR* path = (WCHAR*)malloc(2048 * sizeof(WCHAR));
	StringCchCopyW(path, 2048, src);
	StringCchCatW(path, 2048, TEXT("\\*"));

	WIN32_FIND_DATA fileData;
	HANDLE filehandle = FindFirstFileW(path, &fileData);

	if (filehandle == INVALID_HANDLE_VALUE) {
		return;
	}

	if (isRoot == 0) {
		isRoot == 1;
		fileTime = fileData.ftCreationTime;
	}

	do {
		if (fileData.cFileName[0] == TEXT('.')) {
			continue;
		}

		if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			folderCount++;

			WCHAR* path2 = (WCHAR*)malloc(2048 * sizeof(WCHAR));
			wmemcpy(path2, path, 2048);

			for (int i = 0; i < 2048; i++) {
				if (path2[i] == TEXT('*')) {
					path2[i] = TEXT('\0');
					break;
				}
			}

			StringCchCatW(path2, 2048, fileData.cFileName);

			fileCounter(path2);

			free(path2);
		}
		else {
			fileCount++;

			LARGE_INTEGER fileSize;
			fileSize.LowPart = fileData.nFileSizeLow;
			fileSize.HighPart = fileData.nFileSizeHigh;

			if (fileSize.QuadPart > 2ll * 1024ll * 1024ll * 1024ll) {
				largeFileCount++;
			}
			if (CompareFileTime(&fileData.ftCreationTime, &fileTime) == -1) {
				fileTime = fileData.ftCreationTime;
			}
		}
	} while (FindNextFileW(filehandle, &fileData) != 0);

	FindClose(filehandle);

	free(path);
}



int wmain(int argc, WCHAR* argv[]) {

	if (argc != 2) {
		printf("Only provide source path\n");
		return 1;
	}

	fileCounter(argv[1]);

	wprintf(TEXT("Source directory is %s\n"), argv[1]);
	printf("%d Files, %d Folders\n", fileCount, folderCount);
	printf("%d Large files\n", largeFileCount);

	SYSTEMTIME time;
	if (FileTimeToSystemTime(&fileTime, &time)) {
		printf("%d.%d.%d", time.wDay, time.wMonth, time.wYear);
	}

	return 0;
}

