#include "StdAfx.h"
#include "xmlSave.h"
char* EncodeToUTF8(const char* mbcsStr) ;
xmlSave::xmlSave(void)
{
}

xmlSave::~xmlSave(void)
{
}
void xmlSave::init()
{
    data = new TiXmlElement( "Data" );  
}
void xmlSave::Save(const ACHAR* path)
{
    char* xmlFile;
    USES_CONVERSION;
    xmlFile=T2A(path);
    decl = new TiXmlDeclaration("1.0", "utf-8", ""); 
    doc.LinkEndChild(decl);  
    doc.LinkEndChild(data); 
    doc.SaveFile(xmlFile);
}

void xmlSave::SaveData(LINE *line)
{
    LINE *pointer=(LINE*)malloc(sizeof(line));
    pointer=line->next;
    TiXmlElement * lineElement;
    while(pointer!=NULL)
    {
        lineElement = new TiXmlElement( "LINE" );
        int char_count = WideCharToMultiByte(CP_ACP, 0, pointer->layer, -1, NULL, 0, NULL, NULL);
        char *layer=(char*)malloc(char_count);
        WideCharToMultiByte(CP_ACP, 0, pointer->layer, -1, layer, char_count, NULL, NULL);
        lineElement->SetAttribute("layer",EncodeToUTF8(layer) );
        sprintf_s(ch, "%.6lf", pointer->start.x);
        lineElement->SetAttribute("longitude_start",ch);
        sprintf_s(ch, "%.6lf", pointer->start.y);
        lineElement->SetAttribute("latitude_start",ch);
        sprintf_s(ch, "%.6lf", pointer->end.x);
        lineElement->SetAttribute("longitude_end",ch);
        sprintf_s(ch, "%.6lf", pointer->end.y);
        lineElement->SetAttribute("latitude_end",ch);
        data->LinkEndChild(lineElement);
        pointer=pointer->next;
    }
}

void xmlSave::SaveData(CIRCLE *cirlce)
{
    CIRCLE *pointer=(CIRCLE*)malloc(sizeof(cirlce));
    pointer=cirlce->next;
    TiXmlElement * circleElement;
    while(pointer!=NULL)
    {
        circleElement = new TiXmlElement( "CIRCLE" );
        int char_count = WideCharToMultiByte(CP_ACP, 0, pointer->layer, -1, NULL, 0, NULL, NULL);
        char *layer=(char*)malloc(char_count);
        WideCharToMultiByte(CP_ACP, 0, pointer->layer, -1, layer, char_count, NULL, NULL);
        circleElement->SetAttribute("layer",EncodeToUTF8(layer) );
        sprintf_s(ch, "%.6lf", pointer->center.x);
        circleElement->SetAttribute("longitude",ch);
        sprintf_s(ch, "%.6lf", pointer->center.y);
        circleElement->SetAttribute("latitude",ch);
        sprintf_s(ch, "%.6lf", pointer->radious);
        circleElement->SetAttribute("radious",ch);
        data->LinkEndChild(circleElement);
        pointer=pointer->next;
    }
}

void xmlSave::SaveData(POLY *poly)
{
    POLY *pointer=(POLY*)malloc(sizeof(poly));
    pointer=poly->next;
    TiXmlElement * polyElement;
    while(pointer!=NULL)
    {
        polyElement = new TiXmlElement( "POLY" );
        int char_count = WideCharToMultiByte(CP_ACP, 0, pointer->layer, -1, NULL, 0, NULL, NULL);
        char *layer=(char*)malloc(char_count);
        WideCharToMultiByte(CP_ACP, 0, pointer->layer, -1, layer, char_count, NULL, NULL);
        polyElement->SetAttribute("layer",EncodeToUTF8(layer) );
        polyElement->SetAttribute("id",pointer->id);
        polyElement->SetAttribute("order",pointer->order);
        sprintf_s(ch, "%.6lf", pointer->x);
        polyElement->SetAttribute("longitude",ch);
        sprintf_s(ch, "%.6lf", pointer->y);
        polyElement->SetAttribute("latitude",ch);
        data->LinkEndChild(polyElement);
        pointer=pointer->next;
    }
}

void xmlSave::SaveData(PTEXT *text)
{
    PTEXT *pointer=(PTEXT*)malloc(sizeof(text));
    pointer=text->next;
    TiXmlElement * textElement;
    while(pointer!=NULL)
    {
        textElement = new TiXmlElement( "TEXT" );
        int char_count = WideCharToMultiByte(CP_ACP, 0, pointer->layer, -1, NULL, 0, NULL, NULL);
        char *layer=(char*)malloc(char_count);
        WideCharToMultiByte(CP_ACP, 0, pointer->layer, -1, layer, char_count, NULL, NULL);
        textElement->SetAttribute("layer",EncodeToUTF8(layer) );
        sprintf_s(ch, "%.6lf", pointer->position.x);
        textElement->SetAttribute("longitude",ch);
        sprintf_s(ch, "%.6lf", pointer->position.y);
        textElement->SetAttribute("latitude",ch); 
        textElement->SetAttribute("value",EncodeToUTF8(pointer->value) );
        data->LinkEndChild(textElement);
        pointer=pointer->next;
    }
}

void xmlSave::SaveData(T2DPOLY *p2dpoly)
{
    T2DPOLY *pointer=(T2DPOLY*)malloc(sizeof(p2dpoly));
    pointer=p2dpoly->next;
    TiXmlElement * p2dpolyElement;
    while(pointer!=NULL)
    {
        p2dpolyElement = new TiXmlElement( "P2DPOLY" );
        int char_count = WideCharToMultiByte(CP_ACP, 0, pointer->layer, -1, NULL, 0, NULL, NULL);
        char *layer=(char*)malloc(char_count);
        WideCharToMultiByte(CP_ACP, 0, pointer->layer, -1, layer, char_count, NULL, NULL);
        p2dpolyElement->SetAttribute("layer",EncodeToUTF8(layer) );
        p2dpolyElement->SetAttribute("id",pointer->id);
        p2dpolyElement->SetAttribute("order",pointer->order);
        sprintf_s(ch, "%.6lf", pointer->x);
        p2dpolyElement->SetAttribute("longitude",ch);
        sprintf_s(ch, "%.6lf", pointer->y);
        p2dpolyElement->SetAttribute("latitude",ch);
        data->LinkEndChild(p2dpolyElement);
        pointer=pointer->next;
    }
}

char* EncodeToUTF8(const char* mbcsStr) 
{ 
 wchar_t*  wideStr; 
 char*   utf8Str; 
 int   charLen; 

 charLen = MultiByteToWideChar(CP_UTF8, 0, mbcsStr, -1, NULL, 0); 
 wideStr = (wchar_t*) malloc(sizeof(wchar_t)*charLen); 
 MultiByteToWideChar(CP_ACP, 0, mbcsStr, -1, wideStr, charLen); 

 charLen = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL); 

 utf8Str = (char*) malloc(charLen);

 WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, utf8Str, charLen, NULL, NULL);

 free(wideStr); 
 return utf8Str;

}
