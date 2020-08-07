
// CSDIProjectDoc.h : interface of the CCSDIProjectDoc class
//


#pragma once

struct CDescription
{
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
	CMap<CString, LPCTSTR, CDescription, CDescription> strCountry;
// Operations
public:
	void PopulateStruct(CString countryName, CString cityName, CString currency, CString category);
	void PopulateMap();
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
