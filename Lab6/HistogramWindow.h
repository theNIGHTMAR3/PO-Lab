#pragma once
#include <afxdialogex.h>
#include "Lab1.h"

class HistogramWindow :public CDialogEx
{

	DECLARE_DYNAMIC(HistogramWindow);

public:
	int bitCount;
	int height = 600;
	int p = 0;
	Lab1 image;
	bool show;


	HistogramWindow(CWnd* pParent = nullptr);
	virtual ~HistogramWindow();
	
	// dialog window data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP();

public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();

};

