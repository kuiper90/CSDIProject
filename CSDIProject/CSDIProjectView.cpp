
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
	//ON_COMMAND(ID_GET_DATA, &CCSDIProjectView::OnGetData)
	//ON_UPDATE_COMMAND_UI(ID_GET_DATA, &CCSDIProjectView::OnUpdateGetData)
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
	CHeaderCtrl* pHeaderCtrl = listCtrl.GetHeaderCtrl();
	if (!pHeaderCtrl)
	{
		CCSDIProjectView::CreateTable(listCtrl);
		LoadDataFromDb();
	}	
}

void CCSDIProjectView::LoadDataFromDb()
{
	CCSDIProjectDoc* pDoc = GetDocument();
	int lastIndex = pDoc->GetCount();
	pDoc->SqlConnector();
	UpdateTable(pDoc, lastIndex);
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

void CCSDIProjectView::UpdateTable(CCSDIProjectDoc * pDoc, int lastIndex)
{
	int item;	
	CListCtrl& listCtrl = GetListCtrl();	
	CDescription pCurVal;

	if (pDoc->itemList.GetCount() == 0)
	{
		return;
	}
	
	POSITION index = pDoc->itemList.GetTailPosition();
	for (int i = lastIndex; i < pDoc->itemList.GetSize() && index != NULL; i++)
	{
		pCurVal = pDoc->itemList.GetPrev(index);
		item = listCtrl.InsertItem(lastIndex, pCurVal.country);
		listCtrl.SetItemText(item, 1, pCurVal.city);
		listCtrl.SetItemText(item, 2, pCurVal.currency);
		listCtrl.SetItemText(item, 3, pCurVal.category);
	}
}

void CCSDIProjectView::Populate()
{
	LoadDataFromDb();
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
	Populate();
}

void CCSDIProjectView::OnEditTest()
{
	// TODO: Add your command update UI handler code here
	//AfxMessageBox(_T("Edit_Test_Main_Menu"));
	Populate();
}
