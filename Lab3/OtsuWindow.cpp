#include "stdafx.h"
#include "PO1.h"
#include "OtsuWindow.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(OtsuWindow, CDialogEx)

OtsuWindow::OtsuWindow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

OtsuWindow::~OtsuWindow()
{
}

void OtsuWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(OtsuWindow, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void OtsuWindow::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Dodaj tutaj swój kod procedury obs³ugi komunikatów
					   // Nie wywo³uj CDialogEx::OnPaint() do malowania komunikatów

	CRect dst;
	//GetClientRect(docelowy);
	HDC ctx = ::GetDC(this->m_hWnd);
	POINT topLeft, bottomRight;
	float maxVal = -FLT_MAX;

	for (int i = 0; i < 256; i++) {
		if (values[i] > maxVal) maxVal = values[i];
	}

	for (int i = 0; i < 256; i++) {

		topLeft.y = height - ((float)values[i] / maxVal) * height;
		topLeft.x = i + 50;
		bottomRight.x = i + 51;
		bottomRight.y = height;
		if (i == p)
		{
			dst.SetRect(topLeft, bottomRight);
			FillRect(ctx, dst, CreateSolidBrush(RGB(255, 0, 0)));
		}
		else
		{
			dst.SetRect(topLeft, bottomRight);
			FillRect(ctx, dst, CreateSolidBrush(RGB(0, 0, 0)));
		}
	}


}

BOOL OtsuWindow::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowPos(NULL, 0, 0, 1200, height * 1.1, SWP_NOMOVE | SWP_NOZORDER);

	return TRUE;
}