
// PO1Dlg.h : header file
//

#pragma once
#include "ImgWnd.h"
#include "afxwin.h"
#include "HistogramWindow.h"
#include "OtsuWindow.h"

#include <vector>



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

	enum DistanceMapEnum {
		object,
		background,
		skeleton,
		toDelete
	};


// Implementation
protected:
	HICON m_hIcon;

	CImgWnd m_imgIN;
	CImgWnd m_imgOUT;

	CComboBox m_combo1;
	HistogramWindow histogramWindow;
	OtsuWindow otsuWindow;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void CPODlg::ConvertImageToGrayscale();
	BYTE CPODlg::GetGrayscalePixelValue(int x, int y);

	// lab2
	void CPODlg::ChangeImageBrightness(int range);
	void CPODlg::ChangeImageContrast(float multiplier);
	void CPODlg::ExponentImage(float exponent);
	void CPODlg::ImageNegative();
	void CPODlg::ClearOutputImage();
	void CPODlg::InitializeOutputImage();
	void CPODlg::DrawHistogram(int bits);

	// lab3
	void CPODlg::Threshold(int treshold);
	void CPODlg::IterativeThreshold();
	void CPODlg::GradientThreshold();
	double CPODlg::getAverageValueFromHistogram(int start, int end);
	void CPODlg::OtsuThreshold();
	void CPODlg::OtsuLocally();

	// lab4
	void CPODlg::AverageFilter();
	int CPODlg::Clip(int value);
	void CPODlg::GaussFilter();
	void CPODlg::SobelFirstFilter();
	void CPODlg::SobelSecondFilter();
	void CPODlg::LaplacianFilter();
	void CPODlg::SharpenFilter();
	void CPODlg::Median3x3Filter();
	void CPODlg::Median5x5Filter();
	void CPODlg::MedianCrossFilter();
	void CPODlg::LoGFilter(float range);
	int CPODlg::VectorMedian(std::vector<int>& v);
	void CPODlg::Erosion();
	void CPODlg::Dilatation();
	void CPODlg::Opening();
	void CPODlg::Closing();
	void CPODlg::KonturWew();

	// lab5
	void CPODlg::Pavlidis();
	void CPODlg::DistanceMap();
	int CPODlg::CalculateDistance(int x, int y);



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
