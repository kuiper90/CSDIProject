// CSDIProjectDoc.h : interface of the CCSDIProjectDoc class
//

#pragma once

struct CDescription
{
	CString country;
	CString city;
	CString currency;
	CString category;
};

class CCSDIProjectDoc : public CDocument
{
protected: // create from serialization only
	CCSDIProjectDoc();
	DECLARE_DYNCREATE(CCSDIProjectDoc)

// Attributes
public:
	CList<CDescription> itemList;
	int m_currIndex;
// Operations
public:
	void GetDBData(LPCTSTR lpszFormat, ...);
	void CCSDIProjectDoc::GetDBData(CStringArray& saData, CString sSQL);	// ++++ without CCSDIProjectDoc::
	void SaveToArray(CRecordset& records, CStringArray& saData);	// make it protected
	int GetCount();
	void PopulateStruct(CString countryName, CString cityName, CString currency, CString category);	// ++++ useless
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CCSDIProjectDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};