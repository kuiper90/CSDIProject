// CSDIProjectDoc.cpp : implementation of the CCSDIProjectDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CSDIProject.h"
#include "CMyDatabase.h"
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

CStringArray* CCSDIProjectDoc::GetDBData()
{
	CString sSQL;
	CMyDatabase database(_T("sa"), _T("kk"));
	sSQL.Format(_T("select SDI_Db.dbo.Country.Id, Country, City, Currency, SDI_Db.dbo.Category.Description from SDI_Db.dbo.Country"
		" inner join SDI_Db.dbo.Category on Country.CategoryId = Category.Id ORDER BY SDI_Db.dbo.Country.Id OFFSET %d ROWS"
		" FETCH NEXT 5 ROWS ONLY"), m_currIndex);	
	m_currIndex += 5;
	return database.GetQueryResult(sSQL);
}

CCSDIProjectDoc::CCSDIProjectDoc()
{
	// TODO: add one-time construction code here
	m_currIndex = 0;
}

int CCSDIProjectDoc::GetCurrentIndex()
{
	return m_currIndex;
}

void CCSDIProjectDoc::SetCurrentIndex(int value)
{
	m_currIndex = value;
}

// CCSDIProjectDoc construction/destruction

CCSDIProjectDoc::~CCSDIProjectDoc()
{ }

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