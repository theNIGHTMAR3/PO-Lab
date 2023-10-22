#pragma once


class Lab1
{	
public:
	CString filePath;
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
	BITMAPINFO *bitmapInfo = nullptr;

	BYTE* bitmapArrayPtr;
	int lineBytes;

	int histogram8[256];
	int maxHistogram8 = 0;

	Lab1();
	~Lab1();

	bool LoadDIB(CString filePath);

	bool PaintDIB(HDC context, CRect goalRect, CRect sourceRect);

	bool CreateGreyscaleDIB(CRect imageSize, int xPPM, int yPPM);

	bool GetPixel1(int x, int y);

	BYTE GetPixel8(int x, int y);

	RGBTRIPLE GetPixel24(int x, int y);

	bool SetPixel8(int x, int y, BYTE val);

	bool SaveDIB(CString filePath);

	BYTE ChangeBrightness(BYTE pixel, int range);

	BYTE ChangeContrast(BYTE pixel,float multiplier);

	BYTE ToPower(BYTE pixel, float exponent);

	BYTE Negative(BYTE pixel);

	int Create8BitHistogram();

	bool ShowHistogram();

	bool AlignHistogram();
};

