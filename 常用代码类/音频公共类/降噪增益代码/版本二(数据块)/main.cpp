#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <time.h>
#include "AudioGain.h"
#include "common/common/WavFile.h"
#include "NoiseSuppression.h"
#include<fstream>
#include <windows.h>
#include <mmsystem.h>            
#pragma comment(lib, "winmm.lib")
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
	//test();
	int samples = 16000;
	WavFile wf;
	//CAudioGain cag;
	//cag.AudioFileGain("qq.pcm", "qq1.pcm", samples);
	CAudioGain cag;
	cag.InitAudioGain(16000, AgcModeFixedDigital, 20);
	CNoiseSuppression cns;
	cns.InitNoiseSuppression(16000, 2, true);
	FILE* fpIn;
	FILE* fpOut;
	fpIn = fopen("HciTest.pcm", "rb");
	fpOut = fopen("HciTestGN.pcm", "wb");
	fseek(fpIn, 0, SEEK_END);
	int nFileSize = ftell(fpIn);
	fseek(fpIn, 0, SEEK_SET);
	char buffer[6400];
	int len;
	for (int index = 0; index < nFileSize; index += 6400)
	{
		len = fread(buffer, 1, 6400, fpIn);
		printf("%d", len);
		cag.AudioFileGain(buffer, len);
		cns.NoiseSuppressionProcessT(buffer, len);
		fwrite(buffer, 1, len, fpOut);

	}
	fclose(fpIn);
	fclose(fpOut);
	//std::cout << WavFile::PCMTranceWav("test.pcm", 1, 16, 8000, "zheng.wav");
	//std::cout << WavFile::PCMTranceWav("qq2.pcm", 1, 16, 32000, "qq2K.wav");
	//std::cout << WavFile::PCMTranceWav("lhydd_1C_16bit_32K.pcm", 1, 16, 32000, "lhydd_1C_16bit_32K.wav");
	///std::cout<<WavFile::PCMTranceWav("lhydd_1C_16bit_32K_ns.pcm", 1, 16, 32000, "lhydd_1C_16bit_32K_ns.wav");
	//std::cout << WavFile::PCMTranceWav("lhydd_1C_16bit_32K_nsx.pcm", 1, 16, 32000, "lhydd_1C_16bit_32K_nsx.wav");
	printf("³ÌÐò½áÊø");
	getchar();
	return 0;
}

