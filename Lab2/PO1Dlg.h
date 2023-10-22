
// PO1Dlg.h : header file
//

#pragma once
#include "ImgWnd.h"
#include "afxwin.h"
#include "HistogramWindow.h"



// CPODlg dialog
class CPODlg : public CDialogEx
{
// Construction
public:
	CPODlg(CWnd* pParent = NULL);	// standard constructor

	POINT start, end;
	CRect sourceRect;
	int horizontalPixels;
	int verticalPixels;

// Dialog Data
	enum { IDD = IDD_PO1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	CImgWnd m_imgIN;
	CImgWnd m_imgOUT;

	CComboBox m_combo1;
	HistogramWindow histogramWindow;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void CPODlg::ConvertImageToGrayscale();
	BYTE CPODlg::GetGrayscalePixelValue(int x, int y);
	void CPODlg::ChangeImageBrightness(int range);
	void CPODlg::ChangeImageContrast(float multiplier);
	void CPODlg::ExponentImage(float exponent);
	void CPODlg::ImageNegative();
	void CPODlg::ClearOutputImage();
	void CPODlg::InitializeOutputImage();
	void CPODlg::DrawHistogram(int bits);


public:
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonProcess();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonParams();
	CSliderCtrl sliderValue;
	CButton textValue;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton1();
};
