#include "StdAfx.h"
#include "AcDbUtil.h"

AcDbUtil::AcDbUtil(void)
{
}

AcDbUtil::~AcDbUtil(void)
{
}

void AcDbUtil::collectVertices(const AcDb2dPolyline *pline, AcGePoint3dArray &pts)
{
	ASSERT(pline != NULL);
    ASSERT(pts.isEmpty());

    AcDbObjectIterator* vertexIter = pline->vertexIterator();
    ASSERT(vertexIter != NULL);
    if (vertexIter == NULL)
        return;

    AcDb2dVertex* vertex;
    for (; !vertexIter->done(); vertexIter->step()) {
        if (acdbOpenObject(vertex, vertexIter->objectId(), AcDb::kForRead) == Acad::eOk) {
                pts.append(pline->vertexPosition(*vertex));
            vertex->close();
        }
    }
    delete vertexIter;

    ASSERT(pts.isEmpty() == false);

    if (pline->isClosed()) {
        AcGePoint3d tmpPt = pts[0];        // used to be a bug in dynamic arrays (not sure if its still there??)
        pts.append(tmpPt);
    }
}