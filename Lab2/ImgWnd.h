#pragma once
#include "Lab1.h"

// CImgWnd

class CImgWnd : public CWnd
{
	DECLARE_DYNAMIC(CImgWnd)

public:
	CImgWnd();
	virtual ~CImgWnd();

	Lab1 image;
	bool loadedFile = false;

	BOOL Create(const RECT& rect, CWnd*  pParentWnd, UINT nID);

protected:
	

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


