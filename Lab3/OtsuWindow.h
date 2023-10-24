#pragma once
#include <afxdialogex.h>
class OtsuWindow : public CDialogEx
{
	DECLARE_DYNAMIC(OtsuWindow)

public:
	float values[256];
	int p = 0;
	int height = 600;
	OtsuWindow(CWnd* pParent = nullptr);   
	virtual ~OtsuWindow();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();

};

