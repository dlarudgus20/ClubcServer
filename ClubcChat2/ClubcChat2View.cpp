
// ClubcChat2View.cpp : CClubcChat2View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ClubcChat2.h"
#endif

#include "ClubcChat2Doc.h"
#include "ClubcChat2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClubcChat2View

IMPLEMENT_DYNCREATE(CClubcChat2View, CView)

BEGIN_MESSAGE_MAP(CClubcChat2View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CClubcChat2View ����/�Ҹ�

CClubcChat2View::CClubcChat2View()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CClubcChat2View::~CClubcChat2View()
{
}

BOOL CClubcChat2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CClubcChat2View �׸���

void CClubcChat2View::OnDraw(CDC* /*pDC*/)
{
	CClubcChat2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}

void CClubcChat2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CClubcChat2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CClubcChat2View ����

#ifdef _DEBUG
void CClubcChat2View::AssertValid() const
{
	CView::AssertValid();
}

void CClubcChat2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CClubcChat2Doc* CClubcChat2View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClubcChat2Doc)));
	return (CClubcChat2Doc*)m_pDocument;
}
#endif //_DEBUG


// CClubcChat2View �޽��� ó����
