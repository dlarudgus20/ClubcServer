
// ClubcChat2View.h : CClubcChat2View Ŭ������ �������̽�
//

#pragma once


class CClubcChat2View : public CView
{
protected: // serialization������ ��������ϴ�.
	CClubcChat2View();
	DECLARE_DYNCREATE(CClubcChat2View)

// Ư���Դϴ�.
public:
	CClubcChat2Doc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CClubcChat2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ClubcChat2View.cpp�� ����� ����
inline CClubcChat2Doc* CClubcChat2View::GetDocument() const
   { return reinterpret_cast<CClubcChat2Doc*>(m_pDocument); }
#endif

