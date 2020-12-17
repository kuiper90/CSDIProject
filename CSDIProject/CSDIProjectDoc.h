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
	friend class CMyDatabase;
protected: // create from serialization only
	CCSDIProjectDoc();
	DECLARE_DYNCREATE(CCSDIProjectDoc)

// Attributes
public:
	CList<CDescription> itemList;
private:
	int m_currIndex;
// Operations
public:
	//void GetDBData(LPCTSTR lpszFormat, ...);
	CStringArray* GetDBData();	
	int GetCurrentIndex();
protected:
	void SetCurrentIndex(int value);
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

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};