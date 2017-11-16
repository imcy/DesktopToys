#pragma once
/*
��Ϸ��ʱ������
*/
class CGameTimer
{
public:
	explicit CGameTimer(unsigned int timeout = 3000,	// ���캯�� ������Ĭ��ֵ		
		unsigned int timeval = 300)	// ������ʱ��������,ֵΪ 3000,300
		: m_timeout(timeout)
		, m_timeval(timeval)
	{
	}
	virtual ~CGameTimer()
	{

	}
	//����ʱ����
	void SetTimeval(unsigned int timeval);
	//������һ��ʱ��
	void SetLastTime();
	//������ʼʱ��Ϊ��ǰʱ��
	void StartTimer();
	//�����ܳ�ʱʱ��
	void SetTimeout(unsigned int timeout);
	//�ж��Ƿ�ʱ
	bool IsTimeout() const;
	//�ж��Ƿ񵽴�ʱ������������ˣ��Ƿ����
	bool IsTimeval(bool bUpdate = true);
	size_t GetTimes() const;
private:
	unsigned int m_timeStart{ ::GetTickCount() }; 			// ��ʱ����ʼʱ��
	unsigned int m_timeout{ 3000 }; 						// �ܵĳ�ʱʱ��
	unsigned int m_timeLast{ m_timeStart }; 				// ��һ�θ���ʱ��
	unsigned int m_timeval{ 300 }; 						// ʱ����
	unsigned int m_times{ 0 }; 							// ����IsTimeval(trueע��)�Ĵ���
};

// �ж�ʱ�����
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
	// ���� ��ʼʱ�� : Ϊ��ǰʱ��
	void SetLastTime()
	{
		m_timeLast = GetTickCount();
	}

	// �Ƿ񵽴�ʱ���:������ˣ��Ƿ����
	bool IsTimeval(bool bUpdate = true)
	{
		if (GetTickCount() - m_timeLast >= m_timeval) {	// �ж�ʱ����������ָ���ļ��
			if (bUpdate) {								// ���Ҫ�����ʱ��,��¼����ʱ��
				m_timeLast = GetTickCount();
				m_times++;							// ��¼�����˶��ٴ�
			}
			return true;								// ����ʱ������
		}
		else {
			return false;								// ����ʱ����δ��
		}
	}

	size_t GetTimes() const
	{
		return m_times;								// ����ʱ����������ܴ���
	}
private:

	unsigned int m_timeLast{ GetTickCount() };

	unsigned int m_timeval{ 300 };

	// ����IsTimeval(trueע��)�Ĵ���
	unsigned int m_times{ 0 };
};
