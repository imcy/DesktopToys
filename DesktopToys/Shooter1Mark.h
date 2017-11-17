#pragma once
#include "IMark.h"
class CShooter1Mark :
	public IMark
{
public:
	CShooter1Mark(float x,float y,int index=0);
	virtual ~CShooter1Mark();
	// 根据 自己当前的属性画自己
	virtual void Draw(Gdiplus::Graphics &gh);
	//状态是否在改变中
	virtual bool IsChanging() const;

private:
	std::vector<Image *>m_img;//图片
	size_t m_index{ 0 }; //第几幅图片
};

