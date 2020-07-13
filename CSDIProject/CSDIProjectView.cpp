
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

void CCSDIProjectView::SqlConnector(CListCtrl& listCtrl)
{
	CDatabase database;
	CString SqlQuery;
	CString name, city, category;
	CString sFile = _T("E:\\Git\\Flaviu\\SDI_Db\\SDI_Db.mdf");
	CString connectionString;
	connectionString.Format(L"ODBC;DRIVER={SQL Server};Server=localhost, 1433;DATABASE=master;Trusted=true;");

	int iRec = 0;

	try
	{
		database.Open(NULL, false, false, connectionString);
		CRecordset recset(&database);
		SqlQuery = _T("select Name, City, SDI_Db.dbo.Category.Description from SDI_Db.dbo.Country inner join SDI_Db.dbo.Category on Country.CategoryId = Category.Id");

		recset.Open(CRecordset::forwardOnly, SqlQuery, CRecordset::readOnly);
		int item;

		while (!recset.IsEOF())
		{
			recset.GetFieldValue(_T("Name"), name);
			recset.GetFieldValue(_T("City"), city);
			recset.GetFieldValue(_T("Description"), category);
			item = listCtrl.InsertItem(0, name);
			listCtrl.SetItemText(item, 1, city);
			listCtrl.SetItemText(item, 2, category);
			recset.MoveNext();
		}
		database.Close();
	}

	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
	};
}

void CCSDIProjectView::OnInitialUpdate()
{
	//CListView::OnInitialUpdate();

	CListCtrl& listCtrl = GetListCtrl();

	ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	listCtrl.InsertColumn(0, _T("Country"), LVCFMT_LEFT);
	listCtrl.InsertColumn(1, _T("Category"), LVCFMT_LEFT);
	listCtrl.InsertColumn(2, _T("Description"), LVCFMT_LEFT);

	//LVCOLUMN col;
	//col.mask = LVCF_FMT | LVCF_TEXT;
	//col.pszText = _T("Category");
	//col.fmt = LVCFMT_LEFT;
	//listCtrl.InsertColumn(1, &col);
	/*int item;
	item = listCtrl.InsertItem(0, _T("a"));
	listCtrl.SetItemText(item, 1, _T("a"));
	listCtrl.SetItemText(item, 2, _T("a"));*/

	CCSDIProjectView::SqlConnector(listCtrl);

	listCtrl.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	listCtrl.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	listCtrl.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);


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
