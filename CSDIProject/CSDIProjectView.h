
// CSDIProjectView.h : interface of the CCSDIProjectView class
//

#pragma once


class CCSDIProjectView : public CListView
{
protected: // create from serialization only
	CCSDIProjectView();
	DECLARE_DYNCREATE(CCSDIProjectView)

// Attributes
public:
	CCSDIProjectDoc* GetDocument() const;

// Operations
public:
	void SqlConnector(CListCtrl& listCtrl);

public:
	void OnInitialUpdate();
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CCSDIProjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CSDIProjectView.cpp
inline CCSDIProjectDoc* CCSDIProjectView::GetDocument() const
   { return reinterpret_cast<CCSDIProjectDoc*>(m_pDocument); }
#endif

