#pragma once
/*
游戏计时器设置
*/
class CGameTimer
{
public:
	explicit CGameTimer(unsigned int timeout = 3000,	// 构造函数 参数有默认值		
		unsigned int timeval = 300)	// 当调用时不传参数,值为 3000,300
		: m_timeout(timeout)
		, m_timeval(timeval)
	{
	}
	virtual ~CGameTimer()
	{

	}
	//设置时间间隔
	void SetTimeval(unsigned int timeval);
	//设置上一次时间
	void SetLastTime();
	//重设起始时间为当前时间
	void StartTimer();
	//设置总超时时间
	void SetTimeout(unsigned int timeout);
	//判断是否超时
	bool IsTimeout() const;
	//判断是否到达时间间隔：如果到了，是否更新
	bool IsTimeval(bool bUpdate = true);
	size_t GetTimes() const;
private:
	unsigned int m_timeStart{ ::GetTickCount() }; 			// 计时器开始时间
	unsigned int m_timeout{ 3000 }; 						// 总的超时时间
	unsigned int m_timeLast{ m_timeStart }; 				// 上一次更新时间
	unsigned int m_timeval{ 300 }; 						// 时间间隔
	unsigned int m_times{ 0 }; 							// 符合IsTimeval(true注意)的次数
};

// 判断时间隔的
class CGameTimeval {
public:

	explicit CGameTimeval(unsigned int timeval = 300)
		: m_timeval(timeval)
	{
	}

	virtual ~CGameTimeval()
	{
	}
	void Restart()
	{
		m_timeLast = GetTickCount();
		m_times = 0;
	}
	void SetTimeval(unsigned int timeval)
	{
		m_timeval = timeval;
	}
	// 重设 起始时间 : 为当前时间
	void SetLastTime()
	{
		m_timeLast = GetTickCount();
	}

	// 是否到达时间隔:如果到了，是否更新
	bool IsTimeval(bool bUpdate = true)
	{
		if (GetTickCount() - m_timeLast >= m_timeval) {	// 判断时间间隔光点大于指定的间隔
			if (bUpdate) {								// 如果要求更新时间,记录本次时间
				m_timeLast = GetTickCount();
				m_times++;							// 记录更新了多少次
			}
			return true;								// 返回时间间隔到
		}
		else {
			return false;								// 返回时间间隔未到
		}
	}

	size_t GetTimes() const
	{
		return m_times;								// 返回时间间隔到达的总次数
	}
private:

	unsigned int m_timeLast{ GetTickCount() };

	unsigned int m_timeval{ 300 };

	// 符合IsTimeval(true注意)的次数
	unsigned int m_times{ 0 };
};
