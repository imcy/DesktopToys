#pragma once
#include "IDrawable.h"
class IMark :
	public IDrawable
{
public:
	IMark();
	virtual ~IMark();
	//标记本类当前是否动态
	virtual bool IsChanging() const = 0;
};

