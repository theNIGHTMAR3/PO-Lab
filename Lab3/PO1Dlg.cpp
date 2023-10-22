
// PO1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "PO1.h"
#include "PO1Dlg.h"
#include "ParamsDlg.h"
#include "afxdialogex.h"
#include "Lab1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IMG_WND_ID_IN	100
#define IMG_WND_ID_OUT	101


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPODlg dialog



CPODlg::CPODlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPODlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Control(pDX, IDC_SLIDER1, sliderValue);
	DDX_Control(pDX, IDC_BUTTON_LOAD, textValue);
}

BEGIN_MESSAGE_MAP(CPODlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CPODlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_PROCESS, &CPODlg::OnBnClickedButtonProcess)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CPODlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_PARAMS, &CPODlg::OnBnClickedButtonParams)
//	ON_CBN_SELCHANGE(IDC_COMBO1, &CPODlg::On)
ON_CBN_SELCHANGE(IDC_COMBO1, &CPODlg::OnCbnSelchangeCombo1)
ON_BN_CLICKED(IDC_BUTTON1, &CPODlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CPODlg message handlers

BOOL CPODlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CRect rDlg(7,7,407,407);
	MapDialogRect(rDlg);

	m_imgIN.Create(rDlg, this, IMG_WND_ID_IN);
		
	rDlg = CRect(530, 7, 930, 407);
	MapDialogRect(rDlg);

	m_imgOUT.Create(rDlg, this, IMG_WND_ID_OUT);
	
	// lab2
	m_combo1.AddString(L"convert to greyscale");
	m_combo1.AddString(L"change brightness");
	m_combo1.AddString(L"change contrast");
	m_combo1.AddString(L"to power");
	m_combo1.AddString(L"negative");
	m_combo1.SelectString(0, L"change brightness");
	// lab3
	m_combo1.AddString(L"threshold");
	m_combo1.AddString(L"iterative threshold");
	m_combo1.AddString(L"gradient threshold");
	m_combo1.AddString(L"otsu threshold");
	m_combo1.AddString(L"otsu locally");



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPODlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPODlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);

		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPODlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPODlg::OnBnClickedButtonLoad()
{
	WCHAR strFilter[] = { L"Image Files (*.bmp)|*.bmp|All Files (*.*)|*.*||" };

	CFileDialog FileDlg(TRUE, NULL, NULL, 0, strFilter);

	if (FileDlg.DoModal() == IDOK)
	{
		this->m_imgIN.loadedFile = m_imgIN.image.LoadDIB(FileDlg.GetPathName());
		ClearOutputImage();

		// refresh
		InvalidateRect(NULL);
	}
}


void CPODlg::OnBnClickedButtonProcess()
{
	CString sOption;
	m_combo1.GetLBText(m_combo1.GetCurSel(), sOption);


	if (sOption == L"convert to greyscale")
	{
		ConvertImageToGrayscale();
		this->m_imgOUT.loadedFile = true;
		// refresh window
		InvalidateRect(NULL);
		MessageBox(L"Converted to Grayscale");

	}
	else if (sOption == L"change brightness")
	{
		//sliderValue.SetRange(-100,100);

		ChangeImageBrightness(sliderValue.GetPos());
		this->m_imgOUT.loadedFile = true;
		// refresh window
		InvalidateRect(NULL);
		MessageBox(L"Changed brightness");
	}
	else if (sOption == L"change contrast")
	{
		//sliderValue.SetRange(1, 50);


		ChangeImageContrast((float)sliderValue.GetPos()/10);
		this->m_imgOUT.loadedFile = true;
		// refresh window
		InvalidateRect(NULL);
		MessageBox(L"Changed contrast");
	}
	else if (sOption == L"to power")
	{
		//sliderValue.SetRange(1, 30);

		ExponentImage((float)sliderValue.GetPos()/10);
		this->m_imgOUT.loadedFile = true;
		// refresh window
		InvalidateRect(NULL);
		MessageBox(L"Changed exponent");
	}
	else if (sOption == L"negative")
	{
		sliderValue.SetRange(0,1);

		ImageNegative();
		this->m_imgOUT.loadedFile = true;
		// refresh window
		InvalidateRect(NULL);
		MessageBox(L"negated image");
	}
	else if (sOption == L"threshold")
	{
		Threshold(sliderValue.GetPos());
		this->m_imgOUT.loadedFile = true;
		// refresh window
		InvalidateRect(NULL);
	}
	else if (sOption == L"iterative threshold")
	{
		IterativeThreshold(sliderValue.GetPos());
		this->m_imgOUT.loadedFile = true;
		// refresh window
		InvalidateRect(NULL);
	}
	else if (sOption == L"Gradient threshold")
	{
		//GradientThreshold();
		this->m_imgOUT.loadedFile = true;
		// refresh window
		InvalidateRect(NULL);
	}
	else if (sOption == L"Otsu threshold")
	{
		//OtsuThreshold();
		this->m_imgOUT.loadedFile = true;
		// refresh window
		InvalidateRect(NULL);
		//otsuWindow.DoModal();
	}
	else if (sOption == L"Otsu locally")
	{
		//OtsuLocally();
		this->m_imgOUT.loadedFile = true;
		// refresh window
		InvalidateRect(NULL);
	}
}

void CPODlg::OnBnClickedButtonSave()
{
	WCHAR strFilter[] = { L"Image Files (*.bmp)|*.bmp|All Files (*.*)|*.*||" };

	CFileDialog FileDlg(FALSE, NULL, NULL, 0, strFilter);

	if (FileDlg.DoModal() == IDOK)
	{
		this->m_imgOUT.image.SaveDIB(FileDlg.GetPathName());
		MessageBox(L"Image saved");
	}
}


void CPODlg::OnBnClickedButtonParams()
{
	CParamsDlg paramsDlg;
	CString s;

	if (paramsDlg.DoModal() == IDOK)
	{
		s = paramsDlg.m_sParams;
	}
}

void CPODlg::ChangeImageBrightness(int range)
{
	InitializeOutputImage();

	// set brightness of each pixel
	BYTE brightness;
	for (int y = 0; y < end.y; y++)
	{
		for (int x = 0; x < end.x; x++)
		{
			brightness = m_imgIN.image.GetPixel8(x, y);
			BYTE newBrightness = m_imgIN.image.ChangeBrightness(brightness,range);
			m_imgOUT.image.SetPixel8(x, y, newBrightness);
		}
	}
}

void CPODlg::ExponentImage(float exponent)
{
	InitializeOutputImage();

	// set brightness of each pixel
	BYTE brightness;
	for (int y = 0; y < end.y; y++)
	{
		for (int x = 0; x < end.x; x++)
		{
			brightness = m_imgIN.image.GetPixel8(x, y);
			BYTE newBrightness = m_imgIN.image.ToPower(brightness, exponent);
			m_imgOUT.image.SetPixel8(x, y, newBrightness);
		}
	}
}

void CPODlg::ChangeImageContrast(float multiplier)
{
	InitializeOutputImage();

	// set brightness of each pixel
	BYTE brightness;
	for (int y = 0; y < end.y; y++)
	{
		for (int x = 0; x < end.x; x++)
		{
			brightness = m_imgIN.image.GetPixel8(x, y);
			BYTE newBrightness = m_imgIN.image.ChangeContrast(brightness, multiplier);
			m_imgOUT.image.SetPixel8(x, y, newBrightness);
		}
	}
}


void CPODlg::ImageNegative()
{
	InitializeOutputImage();

	// set brightness of each pixel
	BYTE brightness;
	for (int y = 0; y < end.y; y++)
	{
		for (int x = 0; x < end.x; x++)
		{
			brightness = m_imgIN.image.GetPixel8(x, y);
			BYTE newBrightness = m_imgIN.image.Negative(brightness);
			m_imgOUT.image.SetPixel8(x, y, newBrightness);
		}
	}
}


void CPODlg::ClearOutputImage()
{
	InitializeOutputImage();

	// set brightness of each pixel
	BYTE brightness;
	for (int y = 0; y < end.y; y++)
	{
		for (int x = 0; x < end.x; x++)
		{
			m_imgOUT.image.SetPixel8(x, y, 240);
		}
	}
}

void CPODlg::ConvertImageToGrayscale()
{
	InitializeOutputImage();

	// set brightness of each pixel
	BYTE brightness;
	for (int y = 0; y < end.y; y++)
	{
		for (int x = 0; x < end.x; x++)
		{
			brightness = GetGrayscalePixelValue(x,y);
			m_imgOUT.image.SetPixel8(x, y, brightness);
		}
	}
}

void CPODlg::InitializeOutputImage()
{
	// setting start and end point of rect
	this->start.x = 0;
	this->start.y = 0;
	this->end.x = m_imgIN.image.bitmapInfoHeader.biWidth;
	this->end.y = m_imgIN.image.bitmapInfoHeader.biHeight;

	CPaintDC dc(this);

	this->sourceRect.SetRect(start, end);

	// setting resolution
	this->horizontalPixels = GetDeviceCaps(dc.GetSafeHdc(), HORZRES);
	this->verticalPixels = GetDeviceCaps(dc.GetSafeHdc(), HORZSIZE);

	// create empty black image
	m_imgOUT.image.CreateGreyscaleDIB(sourceRect, horizontalPixels, verticalPixels);
}


BYTE CPODlg::GetGrayscalePixelValue(int x, int y)
{
	// cheking bits count
	if (m_imgIN.image.bitmapInfoHeader.biBitCount == 1)
	{
		return (m_imgIN.image.GetPixel1(x, y)) ? 255 : 0;
	}
	else if (m_imgIN.image.bitmapInfoHeader.biBitCount == 8)
	{
		return m_imgIN.image.GetPixel8(x, y);
	}
	else if (m_imgIN.image.bitmapInfoHeader.biBitCount == 24)
	{
		RGBTRIPLE rgb = m_imgIN.image.GetPixel24(x, y);
		// calculating value using given equation
		return (BYTE)(0.299 * rgb.rgbtRed + 0.587 * rgb.rgbtGreen + 0.114 * rgb.rgbtBlue);
	}
}

void CPODlg::DrawHistogram(int bits)
{
	histogramWindow.image.LoadDIB(m_imgIN.image.filePath);
	histogramWindow.bitCount = bits;
	histogramWindow.DoModal();
}


void CPODlg::OnBnClickedButton1()
{
	DrawHistogram(m_imgIN.image.bitmapInfo->bmiHeader.biBitCount);
}

void CPODlg::OnCbnSelchangeCombo1()
{
	CString sOption;
	m_combo1.GetLBText(m_combo1.GetCurSel(), sOption);
	if (sOption == L"change brightness")
	{
		sliderValue.SetRange(-100, 100, true);
		sliderValue.SetPos(0);
	}
	if (sOption == L"change contrast")
	{
		sliderValue.SetRange(1, 50, true);
		sliderValue.SetPos(1);
	}
	if (sOption == L"to power")
	{
		sliderValue.SetRange(1, 30, true);
		sliderValue.SetPos(1);
	}
	if (sOption == L"negative")
	{
		sliderValue.SetRange(1, 2);
		sliderValue.SetPos(1);
	}
	if (sOption == L"threshold")
	{
		sliderValue.SetRange(1, 255,true);
		sliderValue.SetPos(1);
	}
}

void CPODlg::Threshold(int treshold)
{
	InitializeOutputImage();

	if (this->m_imgIN.image.bitmapInfoHeader.biBitCount != 8)
	{
		return;
	}

	this->m_imgIN.image.pictureTreshold = treshold;

	// set brightness of each pixel
	for (int y = 0; y < end.y; y++)
	{
		for (int x = 0; x < end.x; x++)
		{
			int pixelValue = this->m_imgIN.image.GetPixel8(x, y);
			// black if above shreshold
			if (this->m_imgIN.image.pictureTreshold > pixelValue)
			{
				pixelValue = 0;
			}
			// white if below
			else 
			{
				pixelValue = 255;
			}

			this->m_imgOUT.image.SetPixel8(x, y, pixelValue);
		}
	}
}

double CPODlg::getAverageValueFromHistogram(int start, int end)
{
	double u0 = 0;
	int p0 = 0;

	for (int i = start; i < end; i++)
	{
		u0 += i * this->m_imgIN.image.histogram8[i];
		p0 += this->m_imgIN.image.histogram8[i];
	}
	return u0 / p0;
}


void CPODlg::IterativeThreshold(int treshold)
{
	InitializeOutputImage();

	if (this->m_imgIN.image.bitmapInfoHeader.biBitCount != 8)
	{
		return;
	}

	this->m_imgIN.image.Create8BitHistogram();

	int p1 = 110;
	int p2 = 156;
	int epsilon = 2;

	auto average1 = 0, average2 = 0;
	int newValue = 0;
	while (std::abs(p1 - p2) > epsilon)
	{ 
		average1 = getAverageValueFromHistogram(0, p1);
		average2 = getAverageValueFromHistogram(p1, 256);
		p2 = p1;
		p1 = (average1 + average2) / 2;
	}
	this->histogramWindow.p = p2;

	// set brightness of each pixel
	for (int y = 0; y < end.y; y++)
	{
		for (int x = 0; x < end.x; x++)
		{
			int pixelValue = this->m_imgIN.image.GetPixel8(x, y);
			// white if above shreshold
			if (pixelValue>p1)
			{
				newValue = 255;
			}
			// black if below
			else
			{
				newValue = 0;
			}

			this->m_imgOUT.image.SetPixel8(x, y, newValue);
		}
	}
}



