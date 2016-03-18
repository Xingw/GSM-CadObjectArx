#pragma once
#include "MyStruct.h"


class SQliteSave
{
public:
	SQliteSave(void);
	~SQliteSave(void);
    void init(const ACHAR* path);
    void close();
	void SaveData(LINE *line);
	void SaveData(POLY *poly);
	void SaveData(T2DPOLY *p2dpoly);
	void SaveData(PTEXT *text);
	void SaveData(CIRCLE *circle);
	//static SQliteSave dbshare;
private:
	FILE *fp;
};
