// MyCView.cpp : implementation file
//

#include "stdafx.h"
#include "CSDIProject.h"
#include "MyCView.h"


// MyCView

IMPLEMENT_DYNCREATE(MyCView, CListView)

MyCView::MyCView()
{
	
}

MyCView::~MyCView()
{
}

BEGIN_MESSAGE_MAP(MyCView, CListView)
END_MESSAGE_MAP()


// MyCView diagnostics

#ifdef _DEBUG
void MyCView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void MyCView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// MyCView message handlers

void MyCView::SqlConnector(CListCtrl& listCtrl)
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

void MyCView::OnInitialUpdate()
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

	MyCView::SqlConnector(listCtrl);

	listCtrl.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	listCtrl.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	listCtrl.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);

	
}


