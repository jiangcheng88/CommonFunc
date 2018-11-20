#include "CommonFunc.h"
#include <string.h>
#include<fstream>
#include <io.h>
#include "shlwapi.h"
#pragma comment(lib,"shlwapi.lib")
CommonFunc::CommonFunc()
{
}


CommonFunc::~CommonFunc()
{
}
//-------------------计算文件的长度并返回大小------------------------//
size_t CommonFunc::GetFileSize(const char * filename)
{
	std::ifstream ifs(filename);
	if (!ifs)
	{
		printf("%s文件打开失败(计算文件长度)",filename);
		return 0;
	}
	ifs.seekg(0, std::ios::end);
	size_t size = ifs.tellg();
	ifs.close();
	return size;
}
//------------------获得音频文件的类型后期可以扩展更多的类型----------------------//
AudioType CommonFunc::GetAudioType(const char* filename)
{
	if (filename == NULL)
		return UNKNOWN_AUDIO;
	size_t len = strlen(filename);
	if (filename[len - 1] == '3')
		return MP3_AUDIO;
	if (filename[len - 1] == 'v' || filename[len - 1] == 'V')
		return WAV_AUDIO;
	if (filename[len - 1] == 'm' || filename[len - 1] == 'M')
		return PCM_AUDIO;
	return UNKNOWN_AUDIO;

}
bool CommonFunc::CheckFolderExit(char* folderName, bool flag = false)
{
	if (_access(folderName, 0) == -1)
	{
		if (flag)
			CreateDirectory(folderName, NULL);
		else
			return false;
	}
	return true;
}
bool CommonFunc::CheckFileExit(char* fileName, bool flag = false)
{
	if (_access(fileName, 0) == -1)
	{
		if (flag)
		{
			if (!fopen(fileName, "ab+"))
			{
				printf("文件创建失败!");
				return false;
			}
			else
				return true;
		}
		else
			return false;
	}
}