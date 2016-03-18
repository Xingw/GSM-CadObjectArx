#include "StdAfx.h"
#include "SQliteSave.h"
#include "MyStruct.h"


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
	sqlite3_close(db);
}

void SQliteSave::init()
{
    db=0;pErrMsg=0;
	int ret = sqlite3_open("./test.db", &db);
	if (ret != SQLITE_OK) {
		acutPrintf(TEXT("无法打开数据库"));
	}
	acutPrintf(TEXT("数据库连接成功!\n"));
	// 执行建表SQL
	sqlite3_exec(db, sSQL1, 0, 0, &pErrMsg);
	sqlite3_exec(db, sSQL2, 0, 0, &pErrMsg);
	sqlite3_exec(db, sSQL3, 0, 0, &pErrMsg);
	sqlite3_exec(db, sSQL4, 0, 0, &pErrMsg);
	sqlite3_exec(db, sSQL5, 0, 0, &pErrMsg);
	if (ret != SQLITE_OK){
		acutPrintf(TEXT("SQL 错误"));
		//fprintf(stderr, "SQL error: %s\n", pErrMsg);
		sqlite3_free(pErrMsg);
	}
}
void SQliteSave::SaveData(CIRCLE *circle)
{
	char sql[1024];
	sqlite3_exec(db, "BEGIN;", 0, 0, &pErrMsg);
	CIRCLE *pointer=(CIRCLE*)malloc(sizeof(circle));
	pointer=circle;
	 while (pointer != NULL)
	 {
		sprintf(sql, "insert into Circle(x,y,radious) values(%f,%f,%f)", pointer->center.x, pointer->center.y, pointer->radious);
		sqlite3_exec(db,sql, 0, 0, &pErrMsg);
		pointer = pointer->next;
	}
	sqlite3_exec(db, "COMMIT;", 0, 0, &pErrMsg);
}

void SQliteSave::SaveData(LINE *line)
{
	char sql[1024];
	sqlite3_exec(db, "BEGIN;", 0, 0, &pErrMsg);
	LINE *pointer=(LINE*)malloc(sizeof(line));
	pointer=line;
	 while (pointer != NULL)
	 {
		sprintf(sql, "insert into Line(x1,y1,x2,y2) values(%f,%f,%f,%f)", pointer->start.x, pointer->start.y, pointer->end.x,pointer->end.y);
		sqlite3_exec(db,sql, 0, 0, &pErrMsg);
		pointer = pointer->next;
	}
	sqlite3_exec(db, "COMMIT;", 0, 0, &pErrMsg);
}

void SQliteSave::SaveData(POLY *poly)
{
	char sql[1024];
	sqlite3_exec(db, "BEGIN;", 0, 0, &pErrMsg);
	POLY *pointer=(POLY*)malloc(sizeof(poly));
	pointer=poly;
	 while (pointer != NULL)
	 {
		 sprintf(sql, "insert into Poly(x1,y1,x2,y2) values(%f,%f,%f,%f)",pointer->start.x,pointer->start.y,pointer->end.x,pointer->end.y);
		sqlite3_exec(db,sql, 0, 0, &pErrMsg);
		pointer = pointer->next;
	}
	sqlite3_exec(db, "COMMIT;", 0, 0, &pErrMsg);
}

void SQliteSave::SaveData(PTEXT *text)
{
	char sql[1024];
	sqlite3_exec(db, "BEGIN;", 0, 0, &pErrMsg);
	PTEXT *pointer=(PTEXT*)malloc(sizeof(text));
	pointer=text;
	 while (pointer != NULL)
	 {
		 sprintf(sql, "insert into Text(text,x,y) values('%s',%f,%f)",pointer->value,pointer->position.x,pointer->position.y);
		sqlite3_exec(db,sql, 0, 0, &pErrMsg);
		pointer = pointer->next;
	}
	sqlite3_exec(db, "COMMIT;", 0, 0, &pErrMsg);
}

void SQliteSave::SaveData(T2DPOLY *p2dpoly)
{
	char sql[1024];
	sqlite3_exec(db, "BEGIN;", 0, 0, &pErrMsg);
	T2DPOLY *pointer=(T2DPOLY*)malloc(sizeof(p2dpoly));
	pointer=p2dpoly;
	int i=0;
	 while (pointer != NULL)
	 {
		 for(int k=0;k<pointer->PointArry.length();k++)
		 {
			sprintf(sql, "insert into 2DPoly(id,order,x,y) values(%d,%d,%f,%f)",i,k,pointer->PointArry[k].x,pointer->PointArry[k].y);
			sqlite3_exec(db,sql, 0, 0, &pErrMsg);
		 }
		 pointer = pointer->next;
	}
	sqlite3_exec(db, "COMMIT;", 0, 0, &pErrMsg);
}