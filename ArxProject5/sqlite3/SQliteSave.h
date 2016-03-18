#pragma once
#include "MyStruct.h"
#include "sqlite3.h"
#pragma comment(lib,"sqlite3/sqlite3.lib") 

class SQliteSave
{
public:
	SQliteSave(void);
	~SQliteSave(void);
    void init();
	void SaveData(LINE *line);
	void SaveData(POLY *poly);
	void SaveData(T2DPOLY *p2dpoly);
	void SaveData(PTEXT *text);
	void SaveData(CIRCLE *circle);
	//static SQliteSave dbshare;
private:
	sqlite3 *db;
	char *pErrMsg;
};
