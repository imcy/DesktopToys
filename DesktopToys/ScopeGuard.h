#pragma once
/*
管理函数，代码执行环境离开变量作用域时，自动执行析构函数，析构函数为之前传入的函数
*/

#include "stdafx.h"
#include <functional>

class ScopeGuard
{
	public:
		explicit ScopeGuard(std::function<void()> onExitScope) //构造函数
			:onExitScope_(onExitScope),dismissed_(false)   //初始化列表
		{}
		~ScopeGuard()
		{
			if (!dismissed_) {//判断是否释放资源
				onExitScope_();  
			}
		}
		void Dismiss()
		{
			dismissed_=true;
		}
	private:
		std::function<void()> onExitScope_;
		bool dismissed_;
	private:
		ScopeGuard(ScopeGuard const &); //去掉复制构造函数
		ScopeGuard &operator=(ScopeGuard const &);//去掉赋值操作符
};

#define SCOPEGUARD_LINENAME_CAT(name,line) name##line
#define SCOPEGUARD_LINENAME(name,line) SCOPEGUARD_LINENAME_CAT(name,line)

#define ON_SCOPE_EXIT(callback) ScopeGuard SCOPEGUARD_LINENAME(EXIT,__LINE__)(callback)
