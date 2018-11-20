#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <time.h>
#include "../../../CommonFunction/CommonFunc.h"
#ifdef _WIN32_WCE
#include <windows.h>
#define main _tmain
time_t time(time_t *inTT) {
	SYSTEMTIME sysTimeStruct;
	FILETIME fTime;
	ULARGE_INTEGER int64time;
	time_t locTT = 0;

	if (inTT == NULL) {
		inTT = &locTT;
	}

	GetSystemTime(&sysTimeStruct);
	if (SystemTimeToFileTime(&sysTimeStruct, &fTime)) {
		memcpy(&int64time, &fTime, sizeof(FILETIME));
		/* Subtract the value for 1970-01-01 00:00 (UTC) */
		int64time.QuadPart -= 0x19db1ded53e8000;
		/* Convert to seconds. */
		int64time.QuadPart /= 10000000;
		*inTT = int64time.QuadPart;
	}

	return *inTT;
}
#endif

int main(int argc, char **argv)
{
	getchar();
	return 0;
}

