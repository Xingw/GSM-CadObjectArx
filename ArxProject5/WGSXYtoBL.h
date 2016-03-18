#pragma once
#include "MyStruct.h"
class WGSXYtoBL
{
public:
    WGSXYtoBL(void);
    ~WGSXYtoBL(void);
    void UTMWGSXYtoBL(double* Xn, double* Yn);
    double L1;
    void XYtoBL(LINE *line);
	void XYtoBL(POLY *poly);
	void XYtoBL(T2DPOLY *p2dpoly);
	void XYtoBL(PTEXT *text);
	void XYtoBL(CIRCLE *circle);
    double* p1;
    double* p2;
};
