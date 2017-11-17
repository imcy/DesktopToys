#include "stdafx.h"
#include "Game.h"
#include "IMark.h"

CGame::CGame(HWND hWnd, float x, float y, float w, float h):
	m_hWnd(hWnd),m_x(x),m_y(y),m_width(w),m_height(h)
{
	//����ȫ��ָ��
	g_game = this;
	m_menu = std::make_shared<CDMenu>(hWnd);
	{
		//��ͼ�����ڴ�����
		// ��ͼ������Ļ�������Լ��Ĵ�����
		RECT r{ (long)x, (long)y, (long)(x + w), (long)(y + h) };
		HBITMAP hBmp = CScreenTools::CopyScreenToBitmap(&r);
		// ���汳��ͼ,m_imgBkΪλͼָ��
		m_imgBk = Bitmap::FromHBITMAP(hBmp, NULL);
	}
	// ��ȡ���ڿͻ�����С
	GetClientRect(m_hWnd, &m_rcClient);
}

CGame::~CGame()
{
}

bool CGame::EnterFrame(DWORD dwTime)
{
	Draw();
	return false;
}

void CGame::OnLButtonDown(UINT nFlags, CPoint point)
{
	switch (m_eStatus) {
	case CGame::EGameStatusSelect: {
		if (m_menu->OnLButtonDown(nFlags, point)) {
			break;
		}
		break;
	}
	case CGame::EGameStatusNormal: {
		m_pTool->OnLButtonDown(nFlags, point);
		break;
	}
	default: {
		break;
	}
	}
}

void CGame::OnLButtonUp(UINT nFlags, CPoint point)
{
	switch (m_eStatus) {
	case CGame::EGameStatusSelect: {
		if (m_menu->OnLButtonUp(nFlags, point)) {
			break;
		}
		break;
	}
	case CGame::EGameStatusNormal: {
		m_pTool->OnLButtonUp(nFlags, point);
		break;
	}
	default: {
		break;
	}
	}
}

void CGame::OnLButtonDblClk(UINT nFlags, CPoint point)
{
}

void CGame::OnRButtonDown(UINT nFlags, CPoint point)
{
	switch (m_eStatus) {
	case CGame::EGameStatusSelect: {
		// �˵� �׶� : ���� m_menu �˵�����
		if (m_menu->OnRButtonDown(nFlags, point)) {
			break;
		}
	}
	case CGame::EGameStatusNormal: {
		m_pTool->OnRButtonDown(nFlags,point);
		break;
	}
	default: {

		break;
	}
	}
}

void CGame::OnRButtonUp(UINT nFlags, CPoint point)
{
	switch (m_eStatus) {
	case CGame::EGameStatusSelect: {
		// �˵� �׶� : ���� m_menu �˵�����
		if (m_menu->OnRButtonUp(nFlags, point)) {
			break;
		}
	}
	case CGame::EGameStatusNormal: {
		m_pTool->OnRButtonUp(nFlags, point);
		break;
	}
	default: {

		break;
	}
	}
}

void CGame::OnRButtonDblClk(UINT nFlags, CPoint point)
{
}

void CGame::OnMouseMove(UINT nFlags, CPoint point)
{
	switch (m_eStatus) {
	case CGame::EGameStatusSelect: {
		break;
	}
	case CGame::EGameStatusNormal: {
		// ��Ϸ �׶�
		m_pTool->OnMouseMove(nFlags,point);
		break;
	}
	default: {
		break;
	}
	}
}

BOOL CGame::OnESC()
{
	switch (m_eStatus) {
	case CGame::EGameStatusSelect:
		// ��ǰ û������Ϸ��������
		return FALSE;
	case CGame::EGameStatusNormal:
		// ��ǰ����Ϸ���ص� �˵�
		m_eStatus = EGameStatusSelect;
		// ��ʾ���
		{
			// ��ʼ״̬,������0,���Ա�֤��0�Ϳ�����ʾ��
			int i = ShowCursor(TRUE);
			if (i > 0) {
				// ���ٵ�0
				while (ShowCursor(FALSE) > 0) {
					;
				}
			}
			else if (i < 0) {
				// ���ӵ�0
				while (ShowCursor(TRUE) < 0) {
					;
				}
			}
		}
		return TRUE;
	default:
		break;
	}

	return FALSE;
}

void CGame::SetStatusNormal(std::shared_ptr<CShooter> pTool, BOOL bCursor)
{
	// ����ʹ�õĹ���
	m_pTool = pTool;
	// ������Ϸ״̬
	m_eStatus = EGameStatusNormal;
	// �������
	if (!bCursor) {
		while (true) {
			int i = ShowCursor(FALSE);
			TRACE("���ع�� %d \r\n", i);
			if (i < 0) {
				break;
			}
		}
	}
	else {
		int i = ShowCursor(bCursor);
		TRACE("��ʾ��� %d \n", i);
	}
}

void CGame::Draw()
{
	HDC hdc = ::GetDC(m_hWnd);
	ON_SCOPE_EXIT([&]()  //�뿪����������ʱ�ͷ�DC
	{
		::ReleaseDC(m_hWnd, hdc);
	});
	CDC *dc = CClientDC::FromHandle(hdc); 		// ��ָ����һ����ʱָ�룬�����ͷ�

												// ˫�����ͼ��
	CDC m_dcMemory; 							// �ڴ�DC
	CBitmap bmp; 								// ��������λͼ���󣬲�ѡ�� �ڴ�DC
	bmp.CreateCompatibleBitmap(dc, m_rcClient.Width(), m_rcClient.Height());
	m_dcMemory.CreateCompatibleDC(dc);
	CBitmap *pOldBitmap = m_dcMemory.SelectObject(&bmp);		// ѡ��DC

	Graphics gh(m_dcMemory.GetSafeHdc());						// �������
	gh.SetPageUnit(Gdiplus::UnitPixel); 						// ���õ�λ

	Color clr; 												// �������
	clr.SetFromCOLORREF(BACK_GROUND_LAYER);
	gh.Clear(clr);
	gh.ResetClip();

	// �ϲ�����ͼ�Ͳ�������
	if (!m_vMarks.empty()) {
		Graphics gh(m_imgBk);
		for (auto ptr : m_vMarks) {
			// ���ٱ仯�Ķ���ֱ�Ӻϲ��뱳��ͼƬ�У�������߻�ͼЧ��
			if (!ptr->IsChanging()) {
				ptr->Draw(gh);
			}
		}
		// ɾ�����ٱ仯�ĵĶ���
		m_vMarks.erase(std::remove_if(m_vMarks.begin(),
			m_vMarks.end(),
			[](auto & lhs)->bool {return !lhs->IsChanging(); })
			, m_vMarks.end());
	}

	gh.DrawImage(m_imgBk, m_x, m_y, m_width, m_height);			// ������ͼƬ
	//���������䶯�Ķ��󣺲��䶯���ѻ��뱳��ͼƬ��
	for (auto &ptr : m_vMarks) {
		ptr->Draw(gh);
	}

																// ������Ϸ��ǰ�׶Σ�����ͬ�Ķ���
	{
		switch (m_eStatus) {
		case CGame::EGameStatusSelect:
			// ���˵� ��ʱע�͵�,��Ϊ����Ĵ��뻹ûʵ��
			m_menu->Draw(gh);
			break;
		case CGame::EGameStatusNormal:
			// �������� ��ʱע�͵�,��Ϊ����Ĵ��뻹ûʵ��
			m_pTool->Draw(gh);
			break;
		default:
			break;
		}
	}

	DrawFps(gh); 												// ����FPS

	::BitBlt(hdc, 0, 0, m_rcClient.Width(), m_rcClient.Height(),// ��������Ļ
		m_dcMemory.GetSafeHdc(), 0, 0, SRCCOPY);

	return;
}

void CGame::DrawFps(Gdiplus::Graphics & gh)
{
	static int fps = 0; 					// ��¼��ǰfps
	m_fps++; 							// ÿ֡+1
	static DWORD dwLast = GetTickCount();	// ���һ�����ʱ��
	if (GetTickCount() - dwLast >= 1000) { 	// ������� 1���ӣ������fps,�����������
		fps = m_fps;
		m_fps = 0;
		dwLast = GetTickCount();
	}

	// ���fps
	{
		// ���������
		CString s;
		s.Format(_T("FPS:%d"), fps);
		gh.DrawString(s.GetString(), -1, &m_font, origin, &m_brush);
	}
}


