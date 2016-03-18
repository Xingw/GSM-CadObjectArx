// DIALOG_MAIN.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DIALOG_MAIN.h"
#include "SQliteSave.h"
#include "DwgDatabaseUtil.h"
#include "AcDbUtil.h"
#include "MyStruct.h"

// DIALOG_MAIN �Ի���

IMPLEMENT_DYNAMIC(DIALOG_MAIN, CDialog)

DIALOG_MAIN::DIALOG_MAIN(CWnd* pParent /*=NULL*/)
	: CDialog(DIALOG_MAIN::IDD, pParent)
{

}

DIALOG_MAIN::~DIALOG_MAIN()
{
}

void DIALOG_MAIN::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    
}


BEGIN_MESSAGE_MAP(DIALOG_MAIN, CDialog)
	ON_BN_CLICKED(IDC_BUTTON3, &DIALOG_MAIN::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &DIALOG_MAIN::OnBnClickedButton1)
END_MESSAGE_MAP()


// DIALOG_MAIN ��Ϣ�������

void DIALOG_MAIN::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog opendlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("SQLite Files(*.db)|*.db"), NULL);
	if (opendlg.DoModal() == IDOK)
	{
		CString filename;
		filename = opendlg.GetPathName();
		SetDlgItemText(IDC_EDIT2, filename);
	}
}

void DIALOG_MAIN::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString meridian_input = NULL;
	CString path = NULL;
	GetDlgItemText(IDC_EDIT1, meridian_input);
	GetDlgItemText(IDC_EDIT2, path);
	/*if (path == ""){
		AfxMessageBox(_T("��ѡ���ļ���ַ��"));
	}else if(meridian_input == ""){
		AfxMessageBox(_T("���������뾭γ�ߣ�"));
	}else{*/
		/*int meridian=_ttoi(path);
        char *path_save=NULL;*/
        //memcpy(path_save, path, path.GetLength());
		//char suffix[6] =".db";         /*ֻ�����ļ������������׺.*/
	    /*if (!strstr(path_save, ".db")){
		    strcat(path_save, suffix);
	    }*/
     //   USES_CONVERSION; 
     //   if (PathFileExists(A2CW(path_save)))//���ͬ���ļ�������ɾ��
	    //{
		   // DeleteFile(A2CW(path_save));
	    //}
        Data_Read();
        /*db.SaveData(head->HCircle);
        db.SaveData(head->H2dPoly);
        db.SaveData(head->HLine);
        db.SaveData(head->HPoly);
        db.SaveData(head->HText);*/
	/*}*/
}

void DIALOG_MAIN::Data_Read(){
    AcDbObjectIdArray allEntIds = CDwgDatabaseUtil::GetAllEntityIds();
    int id=0;
	for(int i=0;i<allEntIds.length();i++)
	{
		AcDbLine *pLine = NULL;
		if(acdbOpenObject(pLine,allEntIds[i],AcDb::kForWrite)==Acad::eOk)
		{			
			pLine->setColorIndex(1);
            line2=(LINE *)malloc(sizeof(LINE));
            line2->start=pLine->startPoint();
            line2->end=pLine->endPoint();
            line1->next=line2;
            line1=line2;
			pLine->close();
		}
		AcDbPolyline *pPoly=NULL;
		if(acdbOpenObject(pPoly,allEntIds[i],AcDb::kForWrite)==Acad::eOk)
		{
			AcGePoint3d saveStartpoint,saveEndpoint;
			pPoly->getStartPoint(saveStartpoint);
			pPoly->getEndPoint(saveEndpoint);
			poly2=(POLY *)malloc(sizeof(POLY));
            poly2->start=saveStartpoint;
            poly2->end=saveEndpoint;
            poly1->next=poly2;
            poly1=poly2;
			pPoly->setColorIndex(1);
			pPoly->close();
		}
		AcDbText *pText=NULL;
		if(acdbOpenObject(pText,allEntIds[i],AcDb::kForWrite)==Acad::eOk)
		{
			
			//pText->textString();
            text2=(PTEXT *)malloc(sizeof(PTEXT));
            text2->position=pText->position();
            USES_CONVERSION;
            text2->value=T2A(pText->textString());
            text1->next=text2;
            text1=text2;
			pText->setColorIndex(1);
			pText->close();
		}
		AcDb2dPolyline *p2dPoly=NULL;
		if(acdbOpenObject(p2dPoly,allEntIds[i],AcDb::kForWrite)==Acad::eOk)
		{
			AcGePoint3dArray PointArry;
			AcDbUtil::collectVertices(p2dPoly,PointArry);
            for(int k=0;k<PointArry.length();k++)
		    {
			dpoly2=(T2DPOLY *)malloc(sizeof(T2DPOLY));
            dpoly2->id=id;
            dpoly2->order=k;
            dpoly2->x=PointArry[k].x;
            dpoly2->y=PointArry[k].y;
		    }
            dpoly1->next=dpoly2;
            dpoly1=dpoly2;
			p2dPoly->setColorIndex(1);
			p2dPoly->close();
		}
		AcDbCircle *pCircle=NULL;
		if(acdbOpenObject(pCircle,allEntIds[i],AcDb::kForWrite)==Acad::eOk)
		{
            circle2=(CIRCLE *)malloc(sizeof(CIRCLE));
            circle2->center=pCircle->center();
            circle2->radious=pCircle->radius();
            circle1->next=circle2;
            circle1=circle2;
			pCircle->setColorIndex(1);
			pCircle->close();
		}
	}
    line1->next=NULL;
    text1->next=NULL;
    dpoly1->next=NULL;
    poly1->next=NULL;
    circle1->next=NULL; 
    allEntIds.removeAll();
    acutPrintf(TEXT("��ȡ�ɹ�"));
}
BOOL DIALOG_MAIN::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    head=(Head *)malloc(sizeof(Head));
    line1=(LINE *)malloc(sizeof(LINE));
    circle1=(CIRCLE *)malloc(sizeof(CIRCLE));
    poly1=(POLY *)malloc(sizeof(POLY));
    text1=(PTEXT *)malloc(sizeof(PTEXT));
    dpoly1=(T2DPOLY *)malloc(sizeof(T2DPOLY));
    head->H2dPoly=dpoly1;
    head->HCircle=circle1;
    head->HLine=line1;
    head->HPoly=poly1;
    head->HText=text1;
    /*db.init();*/
    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}
