#pragma once
typedef struct pLine
{
  AcGePoint3d start;
  AcGePoint3d end;
  ACHAR* layer;
  struct pLine *next;
}LINE;

typedef struct pPoly
{
  int id;
  int order;
  double x;
  double y;
  ACHAR* layer;
  struct pPoly *next;
}POLY;

typedef struct p2dPoly
{
  int id;
  int order;
  double x;
  double y;
  ACHAR* layer;
  struct p2dPoly *next;
}T2DPOLY;

typedef struct pText
{
  char* value;
  ACHAR* layer;
  AcGePoint3d position;
  struct pText *next;
}PTEXT;

typedef struct pCircle
{
  double radious;
  ACHAR* layer;
  AcGePoint3d center;
  struct pCircle *next;
}CIRCLE;

typedef struct pLayer
{
  bool choose;
  ACHAR *layer;
  struct pLayer *next;
}LAYER;

typedef struct pHead
{
  LINE *HLine;
  POLY *HPoly;
  T2DPOLY *H2dPoly;
  PTEXT *HText;
  CIRCLE *HCircle;
  LAYER *HLAYER;
}Head;

