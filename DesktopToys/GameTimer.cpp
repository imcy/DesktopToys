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
	if ((GetTickCount() - m_timeLast) >= m_timeval) {	// 判断时间间隔是否大于指定的间隔
		if (bUpdate) {									// 如果要求更新时间,记录本次时间
			m_timeLast = GetTickCount();
			m_times++;								// 记录更新了多少次
		}
		return true;									// 返回时间间隔到
	}
	else {
		return false;									// 返回时间间隔未到
	}
}

size_t CGameTimer::GetTimes() const
{
	return m_times;
}
