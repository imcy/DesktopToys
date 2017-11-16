#include "stdafx.h"
#include "DMenu.h"

CDMenu::CDMenu(HWND hWnd):m_hWnd(hWnd)
{
	// ����˵�����,����ͼƬ����������ָ��
	m_box = make_shared<CMenuItem>(100.0f, 100.0f,
		_T("images/Menu Center01.png"), _T(""));
	m_cover = make_shared<CMenuItem>(100.0f, 100.0f,
		_T("images/Menu Center02.png"), _T(""));
	m_cover2 = make_shared<CMenuItem>(100.0f, 100.0f,
		_T("images/Menu Center02.png"), _T(""));
	m_item0 = make_shared<CMenuItem>(200.0f, 100.0f,
		_T("images/MenuItem00.png"), _T("I'm ������"));
	m_item1 = make_shared<CMenuItem>(300.0f, 100.0f,
		_T("images/MenuItem01.png"), _T("���С����ˢ��??"));
	m_item2 = make_shared<CMenuItem>(400.0f, 100.0f,
		_T("images/MenuItem02.png"), _T("��ʵ�Ҳ��Ǵ���"));
	m_item3 = make_shared<CMenuItem>(500.0f, 100.0f,
		_T("images/MenuItem03.png"), _T("ͬ������Ƥ"));

	{
		RECT rc;
		GetWindowRect(m_hWnd, &rc);
		PointF pt((rc.right - rc.left) / 2.0f, (rc.bottom - rc.top) / 2.0f);   //���ò˵����м�λ��
		SetCenterPos(pt);
	}

	InitAnimateInfo0();
}


CDMenu::~CDMenu()
{
}

void CDMenu::InitAnimateInfo0()
{
   //��ȡ��Ļ���ĵ�λ�ã������ø���λ��
	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	// ���ĵ�
	PointF pt = GetCenterPos();
	// ���ø�������ĵ�
	m_box->SetCenterPos(pt);
	// �˵������ĵ�����������
	m_item0->SetCenterPos(pt);
	m_item1->SetCenterPos(pt);
	m_item2->SetCenterPos(pt);
	m_item3->SetCenterPos(pt);

	// ���ӵ����ĵ������ӵ�����
	{
		PointF pt2 = pt;
		pt2.Y -= 30;
		m_cover->SetCenterPos(pt2);	//m_coverΪ �򿪵ĸ���
	}

	{
		PointF pt2 = pt;
		pt2.Y -= 30;
		m_cover2->SetCenterPos(pt2);	// m_cover2Ϊ�رյĸ���
	}

	// ��ʼ��������Ϣ
	m_box->InitAnimateInfo3(pt.X, pt.Y);
	m_cover->InitAnimateInfo1(pt.X, pt.Y - 100, PI(0.5f));
	// ��ʼ���ĸ��˵�����Ķ���
	m_item0->InitAnimateInfo0(pt.X, pt.Y, 0.0f);
	m_item1->InitAnimateInfo0(pt.X, pt.Y, PI(0.5f));
	m_item2->InitAnimateInfo0(pt.X, pt.Y, PI(1.0f));
	m_item3->InitAnimateInfo0(pt.X, pt.Y, PI(1.5f));
	// ��ʼ��������Ϣ
	m_cover2->InitAnimateInfo1(pt.X, pt.Y - 100, PI(0.5f));
	m_cover2->InitAnimateInfoReverse();
}

void CDMenu::Draw(Gdiplus::Graphics & gh)
{
	switch (m_eStatus) {
	case EStatusOverCover1: {				// ��ǰ״̬Ϊ���Ӵ򿪹���
		PointF pt = GetCenterPos();
		if (m_cover->IsAnimateEnd()) {		// ����������
			m_eStatus = EStatusItem0;		// ת��Ϊ��һ���˵���ɳ����̶���
			break;
		}
		m_box->Draw(gh);					// ��ʱ��Ҫ������
		m_cover->Draw(gh);				// ��ʱ��Ҫ������(��״̬)
		break;
	}
	case EStatusItem0: {					// �˵���һ�ɳ�����
		if (m_item0->IsAnimateEnd()) {
			m_eStatus = EStatusItem1;
			break;
		}
		m_box->Draw(gh);
		m_cover->Draw(gh);
		m_item0->Draw(gh);
		break;
	}
	case EStatusItem1: {					// �˵�����ɳ�����
		if (m_item1->IsAnimateEnd()) {
			m_eStatus = EStatusItem2;
			break;
		}
		m_box->Draw(gh);
		m_cover->Draw(gh);
		m_item0->Draw(gh);
		m_item1->Draw(gh);
		break;
	}
	case EStatusItem2: {					// �˵������ɳ�����
		if (m_item2->IsAnimateEnd()) {
			m_eStatus = EStatusItem3;
			break;
		}
		m_box->Draw(gh);
		m_cover->Draw(gh);
		m_item0->Draw(gh);
		m_item1->Draw(gh);
		m_item2->Draw(gh);
		break;
	}
	case EStatusItem3: {					// �˵����ķɳ�����
		if (m_item3->IsAnimateEnd()) {
			m_eStatus = EStatusOverCover2;
			break;
		}
		m_box->Draw(gh);
		m_cover->Draw(gh);
		m_item0->Draw(gh);
		m_item1->Draw(gh);
		m_item2->Draw(gh);
		m_item3->Draw(gh);
		break;
	}
	case EStatusOverCover2: {				// ���ӹرչ���
		if (m_cover2->IsAnimateEnd()) {
			m_eStatus = EStatusAll;
			break;
		}
		m_box->Draw(gh);    // ������
		m_cover2->Draw(gh); // ����
		m_item0->Draw(gh);
		m_item1->Draw(gh);
		m_item2->Draw(gh);
		m_item3->Draw(gh);
		break;
	}
	case EStatusAll: {					// ����,�������̽���
		m_box->Draw(gh);
		m_cover2->Draw(gh);
		m_item0->Draw(gh);
		m_item1->Draw(gh);
		m_item2->Draw(gh);
		m_item3->Draw(gh);
		break;
	}
	default:
		break;
	}
}

void CDMenu::EndAnimate()// ���ô˺����������еĶ�������
{
	m_eStatus = EStatusAll;					// ����״̬Ϊ����ȫ������
	m_item0->EndAnimate();					// �����˵���һ��������
	m_item1->EndAnimate();					// �����˵������������
	m_item2->EndAnimate();					// �����˵�������������
	m_item3->EndAnimate();					// �����˵����Ķ�������
	m_cover->EndAnimate();					// �������Ӷ�������
	m_cover2->EndAnimate();					// �������Ӷ�������
}
// ����������
bool CDMenu::OnLButtonDown(UINT nFlags, CPoint point)
{
	// �鿴�������ĸ��˵�
	if (m_item0->OnLButtonDown(nFlags, point)) {
		// ��������
		EndAnimate();
		AfxMessageBox(_T("���� ��Ϸ���� ��Ϸ�׶Σ������õ�ǰ����Ϊ CShooter0"));
		return true;
	}
	if (m_item1->OnLButtonDown(nFlags, point)) {
		// ��������
		EndAnimate();

		// �����Ļ�߶�
		RECT rc;
		GetClientRect(m_hWnd, &rc);
		AfxMessageBox(_T("���� ��Ϸ���� ��Ϸ�׶Σ������õ�ǰ����Ϊ CShooter1"));
		return true;
	}
	if (m_item2->OnLButtonDown(nFlags, point)) {
		// ��������
		EndAnimate();
		AfxMessageBox(_T("���� ��Ϸ���� ��Ϸ�׶Σ������õ�ǰ����Ϊ CShooter2"));
		return true;
	}
	if (m_item3->OnLButtonDown(nFlags, point)) {
		// ��������
		EndAnimate();
		AfxMessageBox(_T("���� ��Ϸ���� ��Ϸ�׶Σ������õ�ǰ����Ϊ CShooter3"));
		return true;
	}

	return false;
}

// ����Ҽ�����
bool CDMenu::OnRButtonDown(UINT nFlags, CPoint point)
{
	return false;
}

// ����ƶ�
bool CDMenu::OnMouseMove(UINT nFlags, CPoint point)
{
	// ���ø����˵���ĺ���, �������Ϣת����ȥ,ʹ�����˵�������Դ���
	if (m_item0->OnMouseMove(nFlags, point)) {
		return true;
	}
	if (m_item1->OnMouseMove(nFlags, point)) {
		return true;
	}
	if (m_item2->OnMouseMove(nFlags, point)) {
		return true;
	}
	if (m_item3->OnMouseMove(nFlags, point)) {
		return true;
	}

	return false;
}