#pragma once
#include "IMark.h"
class CShooter1Mark :
	public IMark
{
public:
	CShooter1Mark(float x,float y,int index=0);
	virtual ~CShooter1Mark();
	// ���� �Լ���ǰ�����Ի��Լ�
	virtual void Draw(Gdiplus::Graphics &gh);
	//״̬�Ƿ��ڸı���
	virtual bool IsChanging() const;

private:
	std::vector<Image *>m_img;//ͼƬ
	size_t m_index{ 0 }; //�ڼ���ͼƬ
};

