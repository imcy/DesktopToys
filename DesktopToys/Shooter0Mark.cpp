#include "stdafx.h"
#include "Shooter0Mark.h"


CShooter0Mark::CShooter0Mark(float x, float y)
{
	// ����ͼƬ
	// 161 * 139
	m_img.push_back(Image::FromFile(
		_T("images/Foton The Desktop Hero Left Fire Marks 0.png")));
	m_img.push_back(Image::FromFile(
		_T("images/Foton The Desktop Hero Left Fire Marks 1.png")));
	m_img.push_back(Image::FromFile(
		_T("images/Foton The Desktop Hero Left Fire Marks 2.png")));
	m_img.push_back(Image::FromFile(
		_T("images/Foton The Desktop Hero Left Fire Marks 3.png")));
	m_img.push_back(Image::FromFile(
		_T("images/Foton The Desktop Hero Left Fire Marks 4.png")));


	srand(GetTickCount());                      // ����[0,5)֮����������
	m_index = rand() % 5;
	m_dir = Degree2Radian((rand() / 360));    // ���� [0,360) ֮����������

											  // �����Լ��Ĵ�С
	RectF rc;
	rc.X = 0; 								// ����λ��Ϊ��Ļ���Ͻ�(0,0)
	rc.Y = 0;
	rc.Width = (float)m_img[0]->GetWidth();    // ���ÿ��ΪͼƬ����Ŀ��
	rc.Height = (float)m_img[0]->GetHeight();  // ���ÿ��ΪͼƬ����Ŀ��
	SetRect(rc);

	SetCenterPos(x, y); 						// �������ĵ�
}


CShooter0Mark::~CShooter0Mark()
{
}

void CShooter0Mark::Draw(Gdiplus::Graphics & gh)
{
	gh.DrawImage(m_img[m_index], GetRect());   // ���ƴ��������ͼƬ
}

bool CShooter0Mark::IsChanging() const
{
	return false;                                // ֱ�ӷ���false,����ñ��û�б仯
}
