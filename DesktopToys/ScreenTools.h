#pragma once
class CScreenTools
{
public:
	CScreenTools();
	~CScreenTools();
private:
	// 计算位图文件每个像素所占字节数
	static int GetBits();
	//确定是多少位的位图
	static int GetBitCount(int iBits);
	//将bmp数据写入文件
	static BOOL WriteBmpDataToFile(PCTSTR szFileName,
		PBITMAPINFOHEADER pBitmapInfoHeader,
		DWORD dwPaletteSize, DWORD dwBmBitsSize);
public:
	// 保存到文件
	static int SaveBitmapToFile(HBITMAP hBitmap, LPCTSTR lpFileName);
	// 获取 位图句柄
	static HBITMAP CopyScreenToBitmap(LPRECT lpRect); 		// lpRect 代表选定区域
	// 全屏截图
	static HBITMAP PrintScreen();
	// 截指定窗体
	static HBITMAP PrintWindow(HWND hwnd);
	static void DawMouse(POINT pnt);
};

