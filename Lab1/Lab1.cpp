#include "stdafx.h"
#include "Lab1.h"


Lab1::Lab1(){}

Lab1::~Lab1(){
	// free memory if not nullptr
	if (this->bitmapInfo != nullptr)
	{
		HeapFree(GetProcessHeap(), NULL, this->bitmapInfo);
	}
}


bool Lab1::LoadDIB(CString path)
{
	if (path.IsEmpty())
	{
		return false;
	}
	CFile file;
	this->filePath = path;

	try {
		// open file
		file.Open(filePath, CFile::modeReadWrite);

		// read bitmapFileHeader
		file.Read(&this->bitmapFileHeader, sizeof(BITMAPFILEHEADER));

		// get amount of bytes used by the structure
		DWORD bytesUsed = (this->bitmapFileHeader.bfSize) - sizeof(BITMAPFILEHEADER);

		// free memory if not nullptr
		if (this->bitmapInfo != nullptr)
		{
			HeapFree(GetProcessHeap(), NULL, this->bitmapInfo);
		}

		// allocate memory for bitmapInfo
		this->bitmapInfo = (BITMAPINFO*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, bytesUsed);
		file.Read(this->bitmapInfo, bytesUsed);


		// pointer to bitmap array, (bitmapInfo + offset - bytes for bitmapFileHeader
		this->bitmapArrayPtr = (BYTE*)this->bitmapInfo + this->bitmapFileHeader.bfOffBits - sizeof(BITMAPFILEHEADER);
		file.Close();
		this->bitmapInfoHeader = ((BITMAPINFO*)this->bitmapInfo)->bmiHeader;

		// read line of bytes using given equation
		this->lineBytes = ((this->bitmapInfoHeader.biBitCount * this->bitmapInfoHeader.biWidth + 31) / 32) * 4;
	}
	catch (const CFileException *e)
	{
		file.Close();
		return false;
	}

	return true;
}


bool Lab1::PaintDIB(HDC context, CRect destRect, CRect sourceRect)
{
	// set pointers
	BYTE* byteArrayPtr = this->bitmapArrayPtr;
	BITMAPINFO* bitmapInfoPtr = this->bitmapInfo;

	// set source rect
	int sourceX = 0;
	int sourceY = 0;
	int sourceWidth = this->bitmapInfoHeader.biWidth;
	int sourceHeight = this->bitmapInfoHeader.biHeight;

	// set destination rect
	int destX = 0;
	int destY = 0;
	int destWidth = destRect.Width();
	int destHeight = destRect.Height();

	// set proportions
	if (sourceWidth < sourceHeight)
	{
		// update destWidth
		double proportion = (double)sourceHeight / (double)destHeight;
		destWidth *= (1 / proportion);
	}
	else {
		// update destHeight
		double proportion = (double)sourceWidth / (double)destWidth;
		destHeight *= (1 / proportion);
	}
	
	// paint image
	SetStretchBltMode(context, COLORONCOLOR);

	StretchDIBits(context, destX,destY,destWidth,destHeight,
		sourceX,sourceY,sourceWidth,sourceHeight,
		byteArrayPtr,
		bitmapInfoPtr,
		DIB_RGB_COLORS,
		SRCCOPY);

	return true;
}

bool Lab1::CreateGreyscaleDIB(CRect imageSize, int xPPM, int yPPM) {

	// set bfType to "BM"
	((BYTE*)&this->bitmapFileHeader.bfType)[0] = 0x42;
	((BYTE*)&this->bitmapFileHeader.bfType)[1] = 0x4D;

	// set reserved bits to 0
	this->bitmapFileHeader.bfReserved1 = 0;
	this->bitmapFileHeader.bfReserved2 = 0;

	// calculate bytes in line using given equation
	this->lineBytes = ((8 * imageSize.right + 31) / 32) * 4;

	// calculate image size, rows*bytes in line
	long int bitmapSize = imageSize.bottom * lineBytes;

	// free memory if not nullptr
	if (this->bitmapInfo != nullptr)
	{
		HeapFree(GetProcessHeap(), NULL, this->bitmapInfo);
	}

	// allocate right amount of memory
	this->bitmapInfo =(BITMAPINFO*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) + bitmapSize);

	// set bitmap properties 
	this->bitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	this->bitmapInfo->bmiHeader.biWidth = imageSize.right;
	this->bitmapInfo->bmiHeader.biHeight = imageSize.bottom;
	this->bitmapInfo->bmiHeader.biPlanes = 1;
	this->bitmapInfo->bmiHeader.biBitCount = 8;
	this->bitmapInfo->bmiHeader.biCompression = BI_RGB;
	this->bitmapInfo->bmiHeader.biSizeImage = 0;
	this->bitmapInfo->bmiHeader.biXPelsPerMeter = xPPM;
	this->bitmapInfo->bmiHeader.biYPelsPerMeter = yPPM;
	this->bitmapInfo->bmiHeader.biClrUsed = 0;
	this->bitmapInfo->bmiHeader.biClrImportant = 0;

	// set color pallete
	for (int i = 0; i < 256; i++)
	{
		this->bitmapInfo->bmiColors[i].rgbBlue = i;
		this->bitmapInfo->bmiColors[i].rgbGreen = i;
		this->bitmapInfo->bmiColors[i].rgbRed = i;
		this->bitmapInfo->bmiColors[i].rgbReserved = i;
	}

	// set info header
	this->bitmapInfoHeader = this->bitmapInfo->bmiHeader;

	// calculate offBits 
	this->bitmapFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD);
	this->bitmapFileHeader.bfSize = this->bitmapFileHeader.bfOffBits + bitmapSize;
	this->bitmapArrayPtr = (BYTE*)this->bitmapInfo + this->bitmapFileHeader.bfOffBits - sizeof(BITMAPFILEHEADER);

	return true;

}


bool Lab1::GetPixel1(int x, int y) {

	// if image is black-white
	if (this->bitmapInfoHeader.biBitCount == 1)
	{
		int shift = x / 8;

		// calculate byte's index in bytesArray
		long int index = y * this->lineBytes + shift;

		BYTE byte = ((BYTE*)this->bitmapArrayPtr)[index];

		// generate mask returning x mod 8 value
		BYTE pattern = 0x80 >> (x % 8);

		// return true if pixel is white, false if black
		return  byte & pattern;
	}
	return false;
}

BYTE Lab1::GetPixel8(int x, int y) {
	// if image is in grayscale
	if (this->bitmapInfoHeader.biBitCount == 8)
	{
		// calculate lienBbytes from given equation
		this->lineBytes = ((this->bitmapInfoHeader.biBitCount * this->bitmapInfoHeader.biWidth + 31) / 32) * 4;

		// calculate index and get byte from array at that index
		int index = x + y * (this->lineBytes);
		BYTE value = ((BYTE*)this->bitmapArrayPtr)[index];
		return value;
	}
	// return false if image is not grayscale
	return false;
}

RGBTRIPLE Lab1::GetPixel24(int x, int y) {
	// if image is in color
	if (this->bitmapInfoHeader.biBitCount == 24)
	{
		RGBTRIPLE rgbValue;
		// calculate pixel's index, 3 - amount of bytes
		int index = 3 * x + y * this->lineBytes;

		// get pixels rgb values
		rgbValue.rgbtGreen = ((BYTE*)this->bitmapArrayPtr)[index + 1];
		rgbValue.rgbtBlue = ((BYTE*)this->bitmapArrayPtr)[index + 2];
		rgbValue.rgbtRed = ((BYTE*)this->bitmapArrayPtr)[index];

		return rgbValue;
	}
	// return empty RGBTriple if not in color
	return RGBTRIPLE();
}

bool Lab1::SetPixel8(int x, int y, BYTE val) {
	// check if image is grayscale
	if (this->bitmapInfoHeader.biBitCount == 8)
	{
		// calculate lineBytes from given equation
		this->lineBytes = ((this->bitmapInfoHeader.biBitCount * this->bitmapInfoHeader.biWidth + 31) / 32) * 4;

		// calculate index and set byte in array at that index
		int index = x + y * (this->lineBytes);
		((BYTE*)this->bitmapArrayPtr)[index] = val;
	}
	return false;
}


bool Lab1::SaveDIB(CString filePath)
{
	CFile f;
	// add file extension
	filePath += ".bmp";
	f.Open(filePath, CFile::modeCreate | CFile::modeWrite);

	// write fileHeader
	f.Write(&this->bitmapFileHeader, sizeof(BITMAPFILEHEADER));

	// calculate bitmapInfoSize(file size - header size) and write it
	DWORD bitmapInfoSize = (this->bitmapFileHeader.bfSize) - sizeof(BITMAPFILEHEADER);
	f.Write(this->bitmapInfo, bitmapInfoSize);

	f.Close();
	return true;
}

