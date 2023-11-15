#include "stdafx.h"
#include "PO1.h"
#include "HistogramWindow.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(HistogramWindow, CDialogEx)

HistogramWindow::HistogramWindow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

HistogramWindow::~HistogramWindow()
{
}

void HistogramWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(HistogramWindow, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void HistogramWindow::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages

 	CRect dst;
	HDC ctx = ::GetDC(this->m_hWnd);
	POINT topLeft, bottomRight;
	int max = 0;
	int maxB = 0;
	if (bitCount == 8)
	{
		int thresholding = image.Create8BitHistogram();

		for (int i = 1; i < 255; i++) {

			topLeft.y = height - ((float)image.histogram8[i] / image.maxHistogram8) * height;
			topLeft.x = i;
			bottomRight.x = i + 1;
			bottomRight.y = height;
			if (p > 0 && i == p)
			{
				//dst.SetRect(topLeft, bottomRight);
				//FillRect(ctx, dst, CreateSolidBrush(RGB(255, 0, 0)));
				SelectObject(dc,GetStockObject(DC_PEN));
				SetDCPenColor(dc,RGB(255, 0, 0));
				dc.MoveTo(i, 0);
				dc.LineTo(i, height);
				//LineTo(ctx,)
			}
			else
			{
				dst.SetRect(topLeft, bottomRight);
				FillRect(ctx, dst, CreateSolidBrush(RGB(0, 0, 0)));
			}
		}
	}
}

BOOL HistogramWindow::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowPos(NULL, 0, 0, 1200, height * 1.1, SWP_NOMOVE | SWP_NOZORDER);

	return TRUE;  
}
