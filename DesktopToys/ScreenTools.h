#pragma once
class CScreenTools
{
public:
	CScreenTools();
	~CScreenTools();
private:
	// ����λͼ�ļ�ÿ��������ռ�ֽ���
	static int GetBits();
	//ȷ���Ƕ���λ��λͼ
	static int GetBitCount(int iBits);
	//��bmp����д���ļ�
	static BOOL WriteBmpDataToFile(PCTSTR szFileName,
		PBITMAPINFOHEADER pBitmapInfoHeader,
		DWORD dwPaletteSize, DWORD dwBmBitsSize);
public:
	// ���浽�ļ�
	static int SaveBitmapToFile(HBITMAP hBitmap, LPCTSTR lpFileName);
	// ��ȡ λͼ���
	static HBITMAP CopyScreenToBitmap(LPRECT lpRect); 		// lpRect ����ѡ������
	// ȫ����ͼ
	static HBITMAP PrintScreen();
	// ��ָ������
	static HBITMAP PrintWindow(HWND hwnd);
	static void DawMouse(POINT pnt);
};

