
// CSDIProjectView.cpp : implementation of the CCSDIProjectView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CSDIProject.h"
#endif

#include "CSDIProjectDoc.h"
#include "CSDIProjectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCSDIProjectView

IMPLEMENT_DYNCREATE(CCSDIProjectView, CListView)

BEGIN_MESSAGE_MAP(CCSDIProjectView, CListView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCSDIProjectView::OnFilePrintPreview)
	ON_COMMAND(ID_GET_DATA, &CCSDIProjectView::OnGetData)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CCSDIProjectView construction/destruction

CCSDIProjectView::CCSDIProjectView()
{
	// TODO: add construction code here
}

CCSDIProjectView::~CCSDIProjectView()
{
}

BOOL CCSDIProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

//void CCSDIProjectView::PopulateList(CListCtrl& listCtrl)
//{
//	//CString name, city, category;
//	int item;
//
//	CArray<CString, LPCTSTR>strCountry;
//	SetCountry(strCountry);
//
//	CList<CString, LPCTSTR>strCity;
//	SetCity(strCity);
//
//	CMapStringToString strCategory;
//	CMapStringToString::CPair *pCurVal;
//
//	SetCategory(strCategory, strCountry);
//
//	listCtrl.InsertColumn(0, _T("Country"), LVCFMT_LEFT);
//	listCtrl.InsertColumn(1, _T("Category"), LVCFMT_LEFT);
//	listCtrl.InsertColumn(2, _T("Description"), LVCFMT_LEFT);
//
//	POSITION pos = strCity.GetHeadPosition();
//	pCurVal = strCategory.PGetFirstAssoc();
//	for (int i = 0; i < strCountry.GetSize(); i++)
//	{
//		item = listCtrl.InsertItem(0, strCountry[i]);
//		listCtrl.SetItemText(item, 1, strCity.GetNext(pos));
//		listCtrl.SetItemText(item, 2, pCurVal->value);
//		pCurVal = strCategory.PGetNextAssoc(pCurVal);
//	}
//}

void CCSDIProjectView::CreateTable(CListCtrl& listCtrl)
{
	ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	listCtrl.InsertColumn(0, _T("Country"), LVCFMT_LEFT);
	listCtrl.InsertColumn(1, _T("Category"), LVCFMT_LEFT);
	listCtrl.InsertColumn(2, _T("Currency"), LVCFMT_LEFT);
	listCtrl.InsertColumn(3, _T("Description"), LVCFMT_LEFT);	

	//CCSDIProjectView::PopulateList(listCtrl);

	listCtrl.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	listCtrl.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	listCtrl.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	listCtrl.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
}

void CCSDIProjectView::OnInitialUpdate()
{
	CListCtrl& listCtrl = GetListCtrl();
	CHeaderCtrl* h = listCtrl.GetHeaderCtrl();
	if (!h)
		CCSDIProjectView::CreateTable(listCtrl);
}

// CCSDIProjectView drawing

void CCSDIProjectView::OnDraw(CDC* /*pDC*/)
{
	CCSDIProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

// CCSDIProjectView printing

void CCSDIProjectView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCSDIProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCSDIProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCSDIProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CCSDIProjectView::OnGetData()
{
	int item;
	CCSDIProjectDoc* pDoc = GetDocument();
	CListCtrl& listCtrl = GetListCtrl();
	pDoc->PopulateMap();
	CMap<CString, LPCTSTR, CDescription, CDescription>::CPair *pCurVal;
	pCurVal = pDoc->strCountry.PGetFirstAssoc();
	for (int i = 0; i < pDoc->strCountry.GetSize(); i++)
	{
		item = listCtrl.InsertItem(0, pCurVal->key);
		listCtrl.SetItemText(item, 1, pCurVal->value.city);
		listCtrl.SetItemText(item, 2, pCurVal->value.currency);
		listCtrl.SetItemText(item, 3, pCurVal->value.category);
		pCurVal = pDoc->strCountry.PGetNextAssoc(pCurVal);
	}
}

void CCSDIProjectView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCSDIProjectView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// CCSDIProjectView diagnostics

#ifdef _DEBUG
void CCSDIProjectView::AssertValid() const
{
	CListView::AssertValid();
}

void CCSDIProjectView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CCSDIProjectDoc* CCSDIProjectView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCSDIProjectDoc)));
	return (CCSDIProjectDoc*)m_pDocument;
}
#endif //_DEBUG


// CCSDIProjectView message handlers