#pragma once
#include ".\xml\tinyxml.h"
#include "MyStruct.h"
class xmlSave
{
public:
    xmlSave(void);
    ~xmlSave(void);
    void Save(const ACHAR* path);
    void init();
    TiXmlDocument doc;  
    TiXmlDeclaration * decl;
    TiXmlElement * data;
    char ch[20];
    void SaveData(LINE *line);
	void SaveData(POLY *poly);
	void SaveData(T2DPOLY *p2dpoly);
	void SaveData(PTEXT *text);
	void SaveData(CIRCLE *circle);
};
