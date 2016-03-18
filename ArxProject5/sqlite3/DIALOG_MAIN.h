#pragma once

#include "resource.h"
#include "MyStruct.h"

// DIALOG_MAIN �Ի���

class DIALOG_MAIN : public CDialog
{
	DECLARE_DYNAMIC(DIALOG_MAIN)

public:
	DIALOG_MAIN(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DIALOG_MAIN();

// �Ի�������
	enum { IDD = IDD_DIALOG_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
    void Data_Read();
    Head *head;
    LINE *line1,*line2;
    CIRCLE *circle1,*circle2;
    PTEXT *text1,*text2;
    POLY *poly1,*poly2;
    T2DPOLY *dpoly1,*dpoly2;
    virtual BOOL OnInitDialog();
    /*SQliteSave db;*/
};
