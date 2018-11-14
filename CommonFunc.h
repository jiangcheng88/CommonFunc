#pragma once
/*

常见函数实现
*/
enum AudioType{
	UNKNOWN_AUDIO,
	WAV_AUDIO,
	PCM_AUDIO,
	MP3_AUDIO
};
class CommonFunc
{
public:
	CommonFunc();
	~CommonFunc();
public:
	static size_t GetFileSize(const char * filename);
	static AudioType GetAudioType(const char* filename);
	static bool CheckFolderExit(char* folderName, bool flag = false);
	bool CommonFunc::CheckFileExit(char* folderName, bool flag = false)
};

