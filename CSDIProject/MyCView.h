#pragma once


// MyCView view

class MyCView : public CListView
{
	DECLARE_DYNCREATE(MyCView)

protected:
	MyCView(); 
	virtual ~MyCView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

public:
	void OnInitialUpdate();

public:
	void SqlConnector(CListCtrl& listCtrl);
};