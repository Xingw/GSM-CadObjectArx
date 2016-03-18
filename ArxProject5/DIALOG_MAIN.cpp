// DIALOG_MAIN.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DIALOG_MAIN.h"
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

    DDX_Control(pDX, IDC_LIST1, m_list);
    //List1 ����趨
	LONG lStyle;
	lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle);//����style
	DWORD dwStyle = m_list.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
    dwStyle |= LVS_EX_CHECKBOXES;
	m_list.SetExtendedStyle(dwStyle); //������չ���
	m_list.InsertColumn(0, L"ѡ��", LVCFMT_LEFT, 60);//������
	m_list.InsertColumn(1, L" ͼ��", LVCFMT_LEFT, 120);
}


BEGIN_MESSAGE_MAP(DIALOG_MAIN, CDialog)
	ON_BN_CLICKED(IDC_BUTTON3, &DIALOG_MAIN::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &DIALOG_MAIN::OnBnClickedButton1)
    ON_BN_CLICKED(IDCANCEL, &DIALOG_MAIN::OnBnClickedCancel)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &DIALOG_MAIN::OnLvnItemchangedList1)
    ON_BN_CLICKED(IDC_BUTTON2, &DIALOG_MAIN::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON4, &DIALOG_MAIN::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BUTTON5, &DIALOG_MAIN::OnBnClickedButton5)
END_MESSAGE_MAP()


// DIALOG_MAIN ��Ϣ�������

void DIALOG_MAIN::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog opendlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("xml Files(*.xml)|*.xml"), NULL);
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
	ACHAR* path = NULL;
    CString meridian_input=NULL;
    CString path_save=NULL;
    
	GetDlgItemText(IDC_EDIT1, meridian_input);
	GetDlgItemText(IDC_EDIT2, path_save);
    path = path_save.AllocSysString();
	if (path_save == ""){
		AfxMessageBox(_T("��ѡ���ļ���ַ��"));
	}else if(meridian_input == ""){
		AfxMessageBox(_T("���������뾭γ��(-180~180)��"));
	}else{
        //memcpy(path_save, path, path.GetLength());
		const ACHAR* suffix = _T(".xml");         /*ֻ�����ļ������������׺.*/
	    if (!wcsstr(path, _T(".xml"))){
		    wcscat(path, suffix);
        }
        //acutPrintf(path);
        if (PathFileExists(path))//���ͬ���ļ�������ɾ��
	    {
		    DeleteFile(path);
	    }
        double L1=_wtof(meridian_input);
        if(L1<180 && L1>-180)
        {
            id=0;
            id2=0;
            ch.L1=L1;
            //��ȡ����
            Get_LayerState();
            LAYER *p1=NULL;
            p1=head->HLAYER->next;
            while(p1!=NULL)
            {
                if(p1->choose)
                Data_Read(p1->layer);
                p1=p1->next;
            }
            //����ת��
            ch.XYtoBL(head->HLine);
            ch.XYtoBL(head->HPoly);
            ch.XYtoBL(head->HCircle);
            ch.XYtoBL(head->HText);
            ch.XYtoBL(head->H2dPoly);
            //XML�洢
            xml.init();
            xml.SaveData(head->HLine);
            xml.SaveData(head->HPoly);
            xml.SaveData(head->HCircle);
            xml.SaveData(head->HText);
            xml.SaveData(head->H2dPoly);
            xml.Save(path);
            /*db.init(path);
            db.SaveData(head->HLine);   
            db.SaveData(head->HPoly);
            db.SaveData(head->HCircle);
            db.SaveData(head->HText);
            db.SaveData(head->H2dPoly);
            db.close();*/

            CString str = path_save;
	        int len=str.ReverseFind('\\');
	        CString path_open=str.Left(len);
	        ShellExecute(NULL, _T("open"), path_open, NULL, NULL, SW_SHOW);

            AfxMessageBox(_T("ת����ɣ�"));
            OnOK();
        }else{
            AfxMessageBox(_T("��������ȷ�����뾭��(-180~180)��"));
        }
        
    }
}

void DIALOG_MAIN::Data_Read(ACHAR* Layer){
    AcDbObjectIdArray allEntIds = CDwgDatabaseUtil::GetAllEntityIds(Layer);
	for(int i=0;i<allEntIds.length();i++)
	{
		AcDbLine *pLine = NULL;
		if(acdbOpenObject(pLine,allEntIds[i],AcDb::kForWrite)==Acad::eOk)
		{			
			//pLine->setColorIndex(1);
            
            line2=(LINE *)malloc(sizeof(LINE));
            line2->layer=pLine->layer();
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

            for(int i =0;i<(int) pPoly->numVerts();i+=3)
            {
                AcGePoint3d vert;
		        pPoly->getPointAt(i, vert);
                poly2=(POLY *)malloc(sizeof(POLY));
                poly2->id=id2;
                poly2->order=i/3;
                poly2->x=vert.x;
                poly2->y=vert.y;
                poly2->layer=pPoly->layer();
                poly1->next=poly2;
                poly1=poly2;
            }
            id2++;
			/*pPoly->getStartPoint(saveStartpoint);
			pPoly->getEndPoint(saveEndpoint);
			poly2=(POLY *)malloc(sizeof(POLY));
            poly2->start=saveStartpoint;
            poly2->end=saveEndpoint;
            poly2->layer=pPoly->layer();*/
            
			pPoly->close();
		}
		AcDbText *pText=NULL;
		if(acdbOpenObject(pText,allEntIds[i],AcDb::kForWrite)==Acad::eOk)
		{
			
			//pText->textString();
            text2=(PTEXT *)malloc(sizeof(PTEXT));
            int char_count = WideCharToMultiByte(CP_ACP, 0, pText->textString(), -1, NULL, 0, NULL, NULL);
            text2->value=(char*)malloc(char_count);
            WideCharToMultiByte(CP_ACP, 0, pText->textString(), -1, text2->value, char_count, NULL, NULL);
            text2->position=pText->position();
            text2->layer=pText->layer();
            //text2->value=pText->textString();
            text1->next=text2;
            text1=text2;
			//pText->setColorIndex(1);
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
            dpoly2->layer=p2dPoly->layer();
            dpoly2->x=PointArry[k].x;
            dpoly2->y=PointArry[k].y;
            dpoly1->next=dpoly2;
            dpoly1=dpoly2;
		    }
            id++;
			//p2dPoly->setColorIndex(3);
			p2dPoly->close();
		}
		AcDbCircle *pCircle=NULL;
		if(acdbOpenObject(pCircle,allEntIds[i],AcDb::kForWrite)==Acad::eOk)
		{
            circle2=(CIRCLE *)malloc(sizeof(CIRCLE));
            circle2->center=pCircle->center();
            circle2->radious=pCircle->radius();
            circle2->layer=pCircle->layer();
            circle1->next=circle2;
            circle1=circle2;
			//pCircle->setColorIndex(1);
			pCircle->close();
		}
	}
    line1->next=NULL;
    text1->next=NULL;
    dpoly1->next=NULL;
    poly1->next=NULL;
    circle1->next=NULL; 
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
    layer1=(LAYER *)malloc(sizeof(LAYER));
    head->H2dPoly=dpoly1;
    head->HCircle=circle1;
    head->HLine=line1;
    head->HPoly=poly1;
    head->HText=text1;
    head->HLAYER=layer1;
    if(!Layer_Read()){
        AfxMessageBox(TEXT("ͼ���ȡ�����볢������autocad"));
        OnOK();
    }
    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}

void DIALOG_MAIN::OnBnClickedCancel()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    OnCancel();
}

void DIALOG_MAIN::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    *pResult = 0;
}


void DIALOG_MAIN::add_to_list(ACHAR* layer){//���������б�
	int iRow = m_list.GetItemCount();
	m_list.InsertItem(iRow, L"");
    m_list.SetCheck(iRow);
	m_list.SetItemText(iRow, 1, layer);
}

bool DIALOG_MAIN::Layer_Read(){
    AcDbLayerTable *pLayerTbl = NULL;
    AcDbLayerTableIterator* pIterator=NULL;
		acdbHostApplicationServices()->workingDatabase()
			->getSymbolTable(pLayerTbl, AcDb::kForRead);
        pLayerTbl->newIterator(pIterator);
        for (pIterator->start(); !pIterator->done(); pIterator->step())
        {
            AcDbLayerTableRecord *re=NULL;
            Acad::ErrorStatus es=pIterator->getRecord(re,AcDb::kForRead);
             if (es == Acad::eOk)
		    {
                layer2=(LAYER *)malloc(sizeof(LAYER));
                re->getName(layer2->layer);
                layer2->choose=true;
                layer1->next=layer2;
                layer1=layer2;
		    }
		    else
		    {
			    acutPrintf(TEXT("\nCDwgDatabaseUtil::GetAllEntityIds�д�ʵ��ʧ��(�������:%d)."), (int)es);
		        return false;
             }
        }
    layer1->next=NULL;
    layer1=head->HLAYER->next;
    while(layer1!=NULL)
    {
        add_to_list(layer1->layer);
        layer1=layer1->next;
    }
    return true;
}

void DIALOG_MAIN::Get_LayerState()
{
    for(int i=0;i<m_list.GetItemCount();i++)
    {
        LAYER *p1=NULL;
        p1=head->HLAYER->next;
        while(p1!=NULL)
        {
            if(p1->layer==m_list.GetItemText(i,1))
            {
                p1->choose=m_list.GetCheck(i);
                break;
            }
            p1=p1->next;
        }
    }
}
void DIALOG_MAIN::OnBnClickedButton2()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    for(int i=0;i<m_list.GetItemCount();i++)
    {
        m_list.SetCheck(i);
    }
}

void DIALOG_MAIN::OnBnClickedButton4()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    for(int i=0;i<m_list.GetItemCount();i++)
    {
        if(m_list.GetCheck(i)==true)
        {
            m_list.SetCheck(i,false);
        }else{
            m_list.SetCheck(i);
        }
    }
}

void DIALOG_MAIN::OnBnClickedButton5()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
        for(int i=0;i<m_list.GetItemCount();i++)
    {
        m_list.SetCheck(i,false);
    }
}
