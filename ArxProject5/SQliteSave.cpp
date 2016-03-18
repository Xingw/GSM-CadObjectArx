#include "StdAfx.h"
#include "SQliteSave.h"
#include "MyStruct.h"
#include "WGSXYtoBL.h"

const char *sSQL1 = "create table if not exists Line(id int identity(1,1) PRIMARY KEY, X1 float, Y1 float, X2 float, Y2 float)";
const char *sSQL2 = "create table if not exists Text(id int identity(1,1) PRIMARY KEY, text varchar(60), X float, Y float)";
const char *sSQL3 = "create table if not exists Circle(id int identity(1,1) PRIMARY KEY, X float, Y float, radius float)";
const char *sSQL4 = "create table if not exists Poly(id int identity(1,1) PRIMARY KEY, X1 float, Y1 float, X2 float, Y2 float)";
const char *sSQL5 = "create table if not exists 2DPoly(id int identity(1,1) PRIMARY KEY, ID int, ORDER int, X float, Y float)";

SQliteSave::SQliteSave(void)
{
}

SQliteSave::~SQliteSave(void)
{
}

void SQliteSave::init(const ACHAR* path)
{
    if((fp=_wfopen(path,_T("w")))==NULL)
    {
    acutPrintf(TEXT("打开文件错误"));
    }
    else
    {
     acutPrintf(TEXT("打开文件成功"));
    }
}
void SQliteSave::close()
{
    fclose(fp);
}

void SQliteSave::SaveData(CIRCLE *circle)
{
	//char sql[1024];
	//sqlite3_exec(db, "BEGIN;", 0, 0, &pErrMsg);
	CIRCLE *pointer=(CIRCLE*)malloc(sizeof(circle));
    if(circle->next!=NULL)
    {
        pointer=circle->next;
	     while (pointer != NULL)
	     {
             fprintf(fp, "Circle %f %f %f\n", pointer->center.x, pointer->center.y, pointer->radious);
		    //sqlite3_exec(db,sql, 0, 0, &pErrMsg);
            //acutPrintf(_T("%f\n"),pointer->center.x);
		    pointer = pointer->next;
	    }
    }
	//sqlite3_exec(db, "COMMIT;", 0, 0, &pErrMsg);
}

void SQliteSave::SaveData(LINE *line)
{
	//char sql[1024];
	//sqlite3_exec(db, "BEGIN;", 0, 0, &pErrMsg);
    //fprintf(fp, "LINELINELINE\n");
    if(line->next!=NULL)
    {
        LINE *pointer=(LINE*)malloc(sizeof(line));
        pointer=line->next;
	     while (pointer != NULL)
	     {
             fprintf(fp, "Line %f %f %f %f\n", pointer->start.x, pointer->start.y, pointer->end.x,pointer->end.y);
		    //sqlite3_exec(db,sql, 0, 0, &pErrMsg);
		    pointer = pointer->next;
	    }
    }
	//sqlite3_exec(db, "COMMIT;", 0, 0, &pErrMsg);
}

void SQliteSave::SaveData(POLY *poly)
{
	//char sql[1024];
    //fprintf(fp, "POLYPOLYPOLYPOLY\n");
	//sqlite3_exec(db, "BEGIN;", 0, 0, &pErrMsg);
    if(poly->next!=NULL)
    {
        POLY *pointer=(POLY*)malloc(sizeof(poly));
	    pointer=poly->next;
	     while (pointer != NULL)
	     {
             fprintf(fp, "Poly %f %f %f %f\n",pointer->start.x,pointer->start.y,pointer->end.x,pointer->end.y);
		    //sqlite3_exec(db,sql, 0, 0, &pErrMsg);
		    pointer = pointer->next;
	    }
    }
	//sqlite3_exec(db, "COMMIT;", 0, 0, &pErrMsg);
}

void SQliteSave::SaveData(PTEXT *text)
{
	//char sql[1024];
	//sqlite3_exec(db, "BEGIN;", 0, 0, &pErrMsg);
    //fprintf(fp, "TEXTTEXTTEXTTEXTTEXTTEXTTEXT\n");
    if(text->next!=NULL)
    {
	PTEXT *pointer=(PTEXT*)malloc(sizeof(text));
    pointer=text->next;
	 while (pointer != NULL)
	 {
		fprintf(fp, "Text %s %f %f\n",pointer->value,pointer->position.x,pointer->position.y);
		//sqlite3_exec(db,sql, 0, 0, &pErrMsg);
		pointer = pointer->next;
	}
    }
	//sqlite3_exec(db, "COMMIT;", 0, 0, &pErrMsg);
}

void SQliteSave::SaveData(T2DPOLY *p2dpoly)
{
	//char sql[1024];
	//sqlite3_exec(db, "BEGIN;", 0, 0, &pErrMsg);
    if(p2dpoly->next!=NULL)
    {
	    T2DPOLY *pointer=(T2DPOLY*)malloc(sizeof(p2dpoly));
        pointer=p2dpoly->next;
	    int i=0;
	     while (pointer != NULL)
	     {
             fprintf(fp, "2DPoly %d %d %f %f\n",pointer->id,pointer->order,pointer->x,pointer->y);
			    //sqlite3_exec(db,sql, 0, 0, &pErrMsg);
		     pointer = pointer->next;
	    }
    }
	//sqlite3_exec(db, "COMMIT;", 0, 0, &pErrMsg);
}