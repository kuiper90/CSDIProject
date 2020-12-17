
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
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EDIT_TEST, &CCSDIProjectView::OnEditTest)
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

void CCSDIProjectView::CreateListHeader(CListCtrl& listCtrl)
{
	ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	listCtrl.InsertColumn(0, _T("Country"), LVCFMT_LEFT);
	listCtrl.InsertColumn(1, _T("Category"), LVCFMT_LEFT);
	listCtrl.InsertColumn(2, _T("Currency"), LVCFMT_LEFT);
	listCtrl.InsertColumn(3, _T("Description"), LVCFMT_LEFT);	
	
	listCtrl.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	listCtrl.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	listCtrl.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	listCtrl.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
}

void CCSDIProjectView::OnInitialUpdate()
{
	CListCtrl& listCtrl = GetListCtrl();
	CHeaderCtrl* pHeaderCtrl = listCtrl.GetHeaderCtrl();
	if (!pHeaderCtrl)
	{
		CreateListHeader(listCtrl);
		GetDocument()->UpdateAllViews(NULL, 1);
	}	
}

CStringArray* CCSDIProjectView::PopulateData()
{
	CCSDIProjectDoc* pDoc = GetDocument();	
	CStringArray* test =  NULL;	
	return pDoc->GetDBData();
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

void CCSDIProjectView::UpdateTable(CStringArray* saData, int currentIndex)
{
	int item;
	CListCtrl& listCtrl = GetListCtrl();
	if ((*saData).GetSize() == 0)
	{
		return;
	}
	for (int i = 0; i < (*saData).GetSize(); i+=4)
	{	
		item = listCtrl.InsertItem(currentIndex, (*saData)[i]);
		listCtrl.SetItemText(item, 1, (*saData)[i+1]);
		listCtrl.SetItemText(item, 2, (*saData)[i+2]);
		listCtrl.SetItemText(item, 3, (*saData)[i+3]);
		currentIndex++;
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

void CCSDIProjectView::OnGetData()
{
	// TODO: Add your command handler code here
	HACCEL hAccel = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
}

void CCSDIProjectView::OnEditTest()
{
	// TODO: Add your command update UI handler code here	
//	OnUpdate();
	GetDocument()->UpdateAllViews(NULL, 1);
}

void CCSDIProjectView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// TODO: Add your specialized code here and/or call the base class
	if (0 != lHint)
	{
		CCSDIProjectDoc* pDoc = GetDocument();
		int currentIndex = pDoc->GetCurrentIndex();
		UpdateTable(PopulateData(), currentIndex);
		return;
	}
	Invalidate();	// need this !!!
}
