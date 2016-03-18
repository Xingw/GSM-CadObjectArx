#pragma once

#include "resource.h"
#include "MyStruct.h"
#include "SQliteSave.h"
#include "WGSXYtoBL.h"
#include "xmlSave.h"
#include "afxcmn.h"
// DIALOG_MAIN 对话框

class DIALOG_MAIN : public CDialog
{
	DECLARE_DYNAMIC(DIALOG_MAIN)

public:
	DIALOG_MAIN(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DIALOG_MAIN();

// 对话框数据
	enum { IDD = IDD_DIALOG_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
    void Data_Read(ACHAR* Layer);
    int id;int id2;
    Head *head;
    LINE *line1,*line2;
    CIRCLE *circle1,*circle2;
    PTEXT *text1,*text2;
    POLY *poly1,*poly2;
    T2DPOLY *dpoly1,*dpoly2;
    LAYER *layer1,*layer2;
    virtual BOOL OnInitDialog();
    //SQliteSave db;
    xmlSave xml;
    WGSXYtoBL ch;
    afx_msg void OnBnClickedCancel();
    afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
    void add_to_list(ACHAR* layer);
    bool Layer_Read();
    void Get_LayerState();
    CListCtrl m_list;
    afx_msg void OnBnClickedButton2();
    afx_msg void OnBnClickedButton4();
    afx_msg void OnBnClickedButton5();
};
