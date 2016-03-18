#include "StdAfx.h"
#include "WGSXYtoBL.h"
#include "MyStruct.h"
#define PI 3.14159265358979323846
#include <math.h>
WGSXYtoBL::WGSXYtoBL(void)
{
}

WGSXYtoBL::~WGSXYtoBL(void)
{
}
    /**
     *
     * @param Xn    横轴坐标
     * @param Yn    纵轴坐标
     * @return  经纬度数组
     */
void WGSXYtoBL::UTMWGSXYtoBL(double* Yn, double* Xn)
{
        //最后输出的数据
        //double* XYtoBL=new double [2];
        
        //工程中的--------中央经线-----数据
        double Mf;
        double Nf;
        double Tf, Bf;
        double Cf;
        double Rf;
        double b1, b2, b3;
        double r1, r2;
        double K0 = 0.9996;
        double D, S;
        double FE = 500000;//东纬偏移
        double FN = 0;
        double a = 6378137;
        double b = 6356752.3142;
        double e1, e2, e3;
        double B;
        double L;

        double L0 = L1 * PI / 180;//弧度

        e1 = sqrt(1 - pow((b / a), 2.00));
        e2 = sqrt(pow((a / b), 2.00) - 1);
        e3 = (1 - b / a) / (1 + b / a);

        Mf = (*Xn - FN) / K0;
        S = Mf / (a * (1 - pow(e1, 2.00) / 4 - 3 * pow(e1, 4.00) / 64 - 5 * pow(e1, 6.00) / 256));

        b1 = (3 * e3 / 2.00 - 27 * pow(e3, 3.00) / 32.00) * sin(2.00 * S);
        b2 = (21 * pow(e3, 2.00) / 16 - 55 * pow(e3, 4.00) / 32) * sin(4 * S);
        b3 = (151 * pow(e3, 3.00) / 96) * sin(6 * S);
        Bf = S + b1 + b2 + b3;

        Nf = (pow(a, 2.00) / b) / sqrt(1 + pow(e2, 2.00) * pow(cos(Bf), 2.00));
        r1 = a * (1 - pow(e1, 2.00));
        r2 = pow((1 - pow(e1, 2.00) * pow(sin(Bf), 2.00)), 3.0 / 2.0);
        Rf = r1 / r2;
        Tf = pow(tan(Bf), 2.00);
        Cf = pow(e2, 2.00) * pow(cos(Bf), 2.00);
        D = (*Yn - FE) / (K0 * Nf);

        b1 = pow(D, 2.00) / 2.0;
        b2 = (5 + 3 * Tf + 10 * Cf - 4 * pow(Cf, 2.0) - 9 * pow(e2, 2.0)) * pow(D, 4.00) / 24;
        b3 = (61 + 90 * Tf + 298 * Cf + 45 * pow(Tf, 2.00) - 252 * pow(e2, 2.0) - 3 * pow(Cf, 2.0)) * pow(D, 6.00) / 720;
        B = Bf - Nf * tan(Bf) / Rf * (b1 - b2 + b3);
        B = B * 180 / PI;
        L = (L0 + (1 / cos(Bf)) * (D - (1 + 2 * Tf + Cf) * pow(D, 3) / 6 + (5 + 28 * Tf - 2 * Cf - 3
                * pow(Cf, 2.0) + 8 * pow(e2, 2.0) + 24 * pow(Tf, 2.0)) * pow(D, 5.00) / 120)) * 180 / PI;
        L0 = L0 * 180 / PI;//转化为度

        ////给结果赋值
        *Xn = B;
        *Yn = L;
        //XYtoBL[0] = B;
        //XYtoBL[1] = L;

        //return XYtoBL;
}

void WGSXYtoBL::XYtoBL(LINE *line)
{
    if(line->next!=NULL)
    {
        LINE *pointer=(LINE*)malloc(sizeof(line));
        pointer=line->next;

	     while (pointer != NULL)
	     {
             p1= &pointer->start.x;
             p2= &pointer->start.y;
             UTMWGSXYtoBL(p1,p2);
             p1=&pointer->end.x;
             p2=&pointer->end.y;
             UTMWGSXYtoBL(p1,p2);  
		     pointer = pointer->next;
	    }
    }
}
void WGSXYtoBL::XYtoBL(POLY *poly)
{
     if(poly->next!=NULL)
    {
        POLY *pointer=(POLY*)malloc(sizeof(poly));
        pointer=poly->next;
	     while (pointer != NULL)
	     {
             p1= &pointer->x;
             p2= &pointer->y;
             UTMWGSXYtoBL(p1,p2);
		    //sqlite3_exec(db,sql, 0, 0, &pErrMsg);
		    pointer = pointer->next;
	    }
    }
}
void WGSXYtoBL::XYtoBL(T2DPOLY *p2dpoly)
{
     if(p2dpoly->next!=NULL)
    {
        T2DPOLY *pointer=(T2DPOLY*)malloc(sizeof(p2dpoly));
        pointer=p2dpoly->next;
	     while (pointer != NULL)
	     {
             p1= &pointer->x;
             p2= &pointer->y;
             UTMWGSXYtoBL(p1,p2);
		    //sqlite3_exec(db,sql, 0, 0, &pErrMsg);
		    pointer = pointer->next;
	    }
    }
}
void WGSXYtoBL::XYtoBL(PTEXT *text)
{
     if(text->next!=NULL)
    {
        PTEXT *pointer=(PTEXT*)malloc(sizeof(text));
        pointer=text->next;
	     while (pointer != NULL)
	     {
            p1= &pointer->position.x;
            p2= &pointer->position.y;
            UTMWGSXYtoBL(p1,p2);
		    //sqlite3_exec(db,sql, 0, 0, &pErrMsg);
		    pointer = pointer->next;
	    }
    }
}
void WGSXYtoBL::XYtoBL(CIRCLE *circle)
{
    if(circle->next!=NULL)
    {
        CIRCLE *pointer=(CIRCLE*)malloc(sizeof(circle));
        pointer=circle->next;
	     while (pointer != NULL)
	     {
             p1 = &pointer->center.x;
             p2 = &pointer->center.y;
            UTMWGSXYtoBL(p1, p2);
		    //sqlite3_exec(db,sql, 0, 0, &pErrMsg);
		    pointer = pointer->next;
	    }
    }
}