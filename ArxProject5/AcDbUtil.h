#pragma once

class AcDbUtil
{
public:
	AcDbUtil(void);
	~AcDbUtil(void);
	static void collectVertices(const AcDb2dPolyline* pline, AcGePoint3dArray& pts);
};
