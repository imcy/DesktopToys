#pragma once
/*
������������ִ�л����뿪����������ʱ���Զ�ִ��������������������Ϊ֮ǰ����ĺ���
*/

#include "stdafx.h"
#include <functional>

class ScopeGuard
{
	public:
		explicit ScopeGuard(std::function<void()> onExitScope) //���캯��
			:onExitScope_(onExitScope),dismissed_(false)   //��ʼ���б�
		{}
		~ScopeGuard()
		{
			if (!dismissed_) {//�ж��Ƿ��ͷ���Դ
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
		ScopeGuard(ScopeGuard const &); //ȥ�����ƹ��캯��
		ScopeGuard &operator=(ScopeGuard const &);//ȥ����ֵ������
};

#define SCOPEGUARD_LINENAME_CAT(name,line) name##line
#define SCOPEGUARD_LINENAME(name,line) SCOPEGUARD_LINENAME_CAT(name,line)

#define ON_SCOPE_EXIT(callback) ScopeGuard SCOPEGUARD_LINENAME(EXIT,__LINE__)(callback)
