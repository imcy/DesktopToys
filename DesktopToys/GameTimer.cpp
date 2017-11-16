#include "stdafx.h"
#include "GameTimer.h"

void CGameTimer::SetTimeval(unsigned int timeval)
{
	m_timeval = timeval;
}

void CGameTimer::SetLastTime()
{
	m_timeLast = GetTickCount();
}

void CGameTimer::StartTimer()
{
	m_timeStart = ::GetTickCount();
	m_times = 0;
}

void CGameTimer::SetTimeout(unsigned int timeout)
{
	m_timeout = timeout;
}

bool CGameTimer::IsTimeout() const
{
	return (GetTickCount() - m_timeStart) >= m_timeout;
}

bool CGameTimer::IsTimeval(bool bUpdate)
{
	if ((GetTickCount() - m_timeLast) >= m_timeval) {	// �ж�ʱ�����Ƿ����ָ���ļ��
		if (bUpdate) {									// ���Ҫ�����ʱ��,��¼����ʱ��
			m_timeLast = GetTickCount();
			m_times++;								// ��¼�����˶��ٴ�
		}
		return true;									// ����ʱ������
	}
	else {
		return false;									// ����ʱ����δ��
	}
}

size_t CGameTimer::GetTimes() const
{
	return m_times;
}
