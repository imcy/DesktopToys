#pragma once
#include "IDrawable.h"
class IMark :
	public IDrawable
{
public:
	IMark();
	virtual ~IMark();
	//��Ǳ��൱ǰ�Ƿ�̬
	virtual bool IsChanging() const = 0;
};

