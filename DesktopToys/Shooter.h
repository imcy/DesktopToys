#pragma once
#include "IMouseAction.h"
#include "IDrawable.h"

class CShooter :
	public IMouseAction,public IDrawable
{
public:
	CShooter();
	virtual ~CShooter();
};

