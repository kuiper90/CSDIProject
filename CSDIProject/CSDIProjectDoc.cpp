// CSDIProjectDoc.cpp : implementation of the CCSDIProjectDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CSDIProject.h"
#endif

#include "CSDIProjectDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCSDIProjectDoc

IMPLEMENT_DYNCREATE(CCSDIProjectDoc, CDocument)

BEGIN_MESSAGE_MAP(CCSDIProjectDoc, CDocument)
END_MESSAGE_MAP()

void CCSDIProjectDoc::GetDBData(CStringArray& saData, CString sSQL)
{
	CDatabase database;
	CString connectionString;
	connectionString.Format(L"ODBC;DRIVER={SQL Server};Server=localhost, 1433;DATABASE=master;Trusted=true;");

	try
	{
		database.Open(NULL, false, false, connectionString);
		CRecordset records(&database);
		if (records.Open(CRecordset::forwardOnly, sSQL, CRecordset::readOnly))
		{
			SaveToArray(records, saData);
			database.Close();
			m_currIndex += 5;
		}
	}
	// ++++ row useless
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
	}
	catch (...)
	{
		AfxMessageBox(_T("Un-caught exception"));
	}
}

void CCSDIProjectDoc::GetDBData(LPCTSTR lpszFormat, ...)
{
	va_list args;
	va_start(args, lpszFormat);
	CString s;
	s.FormatV(lpszFormat, args);
	AfxMessageBox(s);
}

void CCSDIProjectDoc::SaveToArray(CRecordset &records, CStringArray& saData)
{
	int size = 0;

	while (!records.IsEOF())
	{
		CString name, city, currency, category;
		records.GetFieldValue(static_cast<short>(1), name);
		records.GetFieldValue(static_cast<short>(2), city);
		records.GetFieldValue(static_cast<short>(3), currency);
		records.GetFieldValue(static_cast<short>(4), category);
		size = saData.GetSize();	// ++++ convert type INT_PTR to int
		saData.SetSize(size + 4);
		saData.SetAt(size, name);
		saData.SetAt(size + 1, city);
		saData.SetAt(size + 2, currency);
		saData.SetAt(size + 3, category);
		records.MoveNext();
	}
}

int CCSDIProjectDoc::GetCount()
{
	return m_currIndex;
}

// CCSDIProjectDoc construction/destruction

CCSDIProjectDoc::CCSDIProjectDoc()
{
	// TODO: add one-time construction code here
	m_currIndex = 0;
}

CCSDIProjectDoc::~CCSDIProjectDoc()
{
}

BOOL CCSDIProjectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

// CCSDIProjectDoc serialization

void CCSDIProjectDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CCSDIProjectDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CCSDIProjectDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CCSDIProjectDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCSDIProjectDoc diagnostics

#ifdef _DEBUG
void CCSDIProjectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCSDIProjectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

// CCSDIProjectDoc commands