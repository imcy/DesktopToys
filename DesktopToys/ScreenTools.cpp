#include "stdafx.h"
#include "ScreenTools.h"


CScreenTools::CScreenTools()
{
}


CScreenTools::~CScreenTools()
{
}

int CScreenTools::GetBits()
{
	//��ʾ��ǰ�ֱ�����ÿ��������ռ�ֽ���
	int iBits;
	HDC hDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL); //Ϊ��Ļ�����豸����
	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);  //����ֽ���
	DeleteDC(hDC);
	return iBits;
	
}

int CScreenTools::GetBitCount(int iBits)
{
	int wBitCount;
	if (iBits <= 1) {
		wBitCount = 1;
	}
	else if (iBits <= 4) {
		wBitCount = 4;
	}
	else if (iBits <= 8) {
		wBitCount = 8;
	}
	else if (iBits <= 24) {
		wBitCount = 24;
	}
	else {
		wBitCount = 32;
	}
	return wBitCount;
}

BOOL CScreenTools::WriteBmpDataToFile(PCTSTR szFileName, PBITMAPINFOHEADER pBitmapInfoHeader, DWORD dwPaletteSize, DWORD dwBmBitsSize)
{
	// д����ֽ���
	DWORD dwWrite;
	//λͼ�ļ�ͷ�ṹ,����һ���ļ����
	HANDLE hFile = CreateFile(szFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
		NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		return FALSE;
	}
	BITMAPFILEHEADER bitmapFileHeader;
	// ����λͼ�ļ�ͷ����bmp�ļ�ͷ������
	bitmapFileHeader.bfType = 0x4D42; // 0x4D42��"BM"
	bitmapFileHeader.bfSize = sizeof(BITMAPFILEHEADER) +
		sizeof(BITMAPINFOHEADER) +
		dwPaletteSize + dwBmBitsSize;
	bitmapFileHeader.bfReserved1 = 0;
	bitmapFileHeader.bfReserved2 = 0;
	bitmapFileHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) +
		(DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;

	// д��λͼ�ļ�ͷ
	WriteFile(hFile, (LPSTR)&bitmapFileHeader, sizeof(BITMAPFILEHEADER),
		&dwWrite, NULL);
	// д��λͼ�ļ���������
	WriteFile(hFile, (LPSTR)pBitmapInfoHeader, sizeof(BITMAPINFOHEADER) +
		dwPaletteSize + dwBmBitsSize,
		&dwWrite, NULL);
	// �ر��ļ����
	CloseHandle(hFile);
	return TRUE;
}

int CScreenTools::SaveBitmapToFile(HBITMAP hBitmap, LPCTSTR lpFileName)
{
	/*
	bitmap �ļ��ṹ����:
	BITMAPFILEHEADER
	BITMAPINFOHEADER
	RGBQUAD array
	Color-index array
	*/
	//����ֵ
	BOOL bRet = FALSE;
	//λͼ��ÿ��������ռ�ֽ���
	WORD wBitCount;
	//�����ɫ���С�� λͼ�������ֽڴ�С �� λͼ�ļ���С �� д���ļ��ֽ���
	DWORD dwPaletteSize = 0;
	DWORD dwBmBitsSize;
	BITMAP Bitmap; 								//λͼ���Խṹ
	BITMAPINFOHEADER bitmapInfoHeader; 			//λͼ��Ϣͷ�ṹ
	LPBITMAPINFOHEADER pBitmapInfoHeader; 			//ָ��λͼ��Ϣͷ�ṹ
	wBitCount = GetBitCount(GetBits());			// ����GetBitCount����ȷ���༸λ(1,4,8,24,32)λͼ

	if (wBitCount <= 8) { 							//�����ɫ���С
		dwPaletteSize = (1 << wBitCount) * sizeof(RGBQUAD);
	}
	//����λͼ��Ϣͷ�ṹ
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
	bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfoHeader.biWidth = Bitmap.bmWidth;
	bitmapInfoHeader.biHeight = Bitmap.bmHeight;
	bitmapInfoHeader.biPlanes = 1;
	bitmapInfoHeader.biBitCount = wBitCount;
	bitmapInfoHeader.biCompression = BI_RGB;
	bitmapInfoHeader.biSizeImage = 0;
	bitmapInfoHeader.biXPelsPerMeter = 0;
	bitmapInfoHeader.biYPelsPerMeter = 0;
	bitmapInfoHeader.biClrUsed = 0;
	bitmapInfoHeader.biClrImportant = 0;

	// �������ݵĴ�С
	// ÿһ�еĴ�С(������4��������)
	dwBmBitsSize = ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4
		* Bitmap.bmHeight;
	HANDLE hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize +
		sizeof(BITMAPINFOHEADER));
	pBitmapInfoHeader = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*pBitmapInfoHeader = bitmapInfoHeader;

	// ��ȡ ��ɫ�����µ�����ֵ
	{
		HDC hDC; 										//�豸������
		HPALETTE hOldPal = NULL;						// ��ȡ�ɵĵ�ɫ��
		hDC = ::GetDC(NULL); 							// ��ȡ ��ĻDC
		HANDLE hPal = GetStockObject(DEFAULT_PALETTE);	// ��ȡĬ�ϵ�ɫ��
		if (hPal) {
			hOldPal = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
			RealizePalette(hDC);
		}
		// ��ȡ�õ�ɫ�����µ�����ֵ
		GetDIBits(hDC, hBitmap
			, 0
			, (UINT)Bitmap.bmHeight
			, (LPSTR)pBitmapInfoHeader + sizeof(BITMAPINFOHEADER) +
			dwPaletteSize
			, (BITMAPINFO *)pBitmapInfoHeader
			, DIB_RGB_COLORS); 					//λͼ���Խṹ
		if (hOldPal) { 								//�ָ���ɫ��
			SelectPalette(hDC, hOldPal, TRUE);
			RealizePalette(hDC);
		}
		::ReleaseDC(NULL, hDC); 						// �ͷ���ĻDC
	}
	//����λͼ�ļ�  ,��д��
	{
		if (!WriteBmpDataToFile(lpFileName, pBitmapInfoHeader, dwPaletteSize,
			dwBmBitsSize)) {
			goto __Cleanup;
		}
	}
	bRet = TRUE;
__Cleanup: 												// ���
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	return bRet;
}

HBITMAP CScreenTools::CopyScreenToBitmap(LPRECT lpRect)
{
	HDC hScrDC, hMemDC;
	HBITMAP hBitmap, hOldBitmap; 						// ��Ļ���ڴ��豸������
	int nX, nY, nX2, nY2; 							// λͼ���
	int nWidth, nHeight; 								// ѡ����������
	int xScrn, yScrn; 								// λͼ��Ⱥ͸߶�
	if (IsRectEmpty(lpRect)) { 							// ȷ��ѡ������Ϊ�վ���
		return NULL;
	}
	hScrDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL); //Ϊ��Ļ�����豸������
	hMemDC = CreateCompatibleDC(hScrDC); 		//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
	// ���ѡ����������
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	// �����Ļ�ֱ���
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//ȷ��ѡ�������ǿɼ���
	if (nX < 0) {
		nX = 0;
	}
	if (nY < 0) {
		nY = 0;
	}
	if (nX2 > xScrn) {
		nX2 = xScrn;
	}
	if (nY2 > yScrn) {
		nY2 = yScrn;
	}
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;
	// ����һ������Ļ�豸��������ݵ�λͼ
	hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight);
	// ����λͼѡ���ڴ��豸��������
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	// ����Ļ�豸�����������ڴ��豸��������
	BitBlt(hMemDC, 0, 0, nWidth, nHeight, hScrDC, nX, nY, SRCCOPY);
	// �õ���Ļλͼ�ľ��
	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
	// ���
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	// ����λͼ���
	return hBitmap;
}

HBITMAP CScreenTools::PrintScreen()
{
	CRect rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = GetSystemMetrics(SM_CXSCREEN);
	rect.bottom = GetSystemMetrics(SM_CYSCREEN);
	return CopyScreenToBitmap(rect);
}

HBITMAP CScreenTools::PrintWindow(HWND hwnd)
{
	RECT rrrr;
	LPRECT lpRect = &rrrr;
	::GetWindowRect(hwnd, &rrrr);
	HDC hScrDC, hMemDC; 							// ��Ļ���ڴ��豸������
	HBITMAP hBitmap, hOldBitmap; 					// λͼ���
	hScrDC = ::GetWindowDC(hwnd); 					//Ϊ��Ļ�����豸������
	hMemDC = CreateCompatibleDC(hScrDC); 		//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
	int nWidth = lpRect->right - lpRect->left; // λͼ��Ⱥ͸߶�
	int nHeight = lpRect->bottom - lpRect->top;;
	// ����һ������Ļ�豸��������ݵ�λͼ
	hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight);
	// ����λͼѡ���ڴ��豸��������
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	// ����Ļ�豸�����������ڴ��豸��������
	BitBlt(hMemDC, 0, 0, nWidth, nHeight, hScrDC, 0, 0, SRCCOPY);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);	// �õ���Ļλͼ�ľ��
	DeleteDC(hScrDC); 									// �ͷ���Դ
	DeleteDC(hMemDC);
	return hBitmap; 										// ����λͼ���
}

void CScreenTools::DawMouse(POINT pnt)
{
	HWND DeskHwnd = ::GetDesktopWindow(); 					// ȡ��������
	HDC DeskDC = ::GetWindowDC(DeskHwnd); 					// ȡ�������豸����
	int oldRop2 = SetROP2(DeskDC, R2_NOTXORPEN);
	HPEN newPen = ::CreatePen(0, 1, RGB(255, 0, 0)); 		// �����»���,����DeskDC
	HGDIOBJ oldPen = ::SelectObject(DeskDC, newPen);		// ѡ������,������ɻ���
	::MoveToEx(DeskDC, pnt.x - 10, pnt.y, NULL);			// �ڴ���������һ������
	::LineTo(DeskDC, pnt.x + 10, pnt.y);					// �ڴ���������һ������
	::MoveToEx(DeskDC, pnt.x, pnt.y + 10, NULL);			// �ڴ���������һ������
	::LineTo(DeskDC, pnt.x, pnt.y - 10);					// �ڴ���������һ������
	::SetROP2(DeskDC, oldRop2);
	::SelectObject(DeskDC, oldPen);						// �ָ�Ϊ�ɻ���
	::DeleteObject(newPen);								// �ͷ���Դ,ɾ������
	::ReleaseDC(DeskHwnd, DeskDC);							// �ͷ���Դ,�ͷ��豸
	DeskDC = NULL;
}


