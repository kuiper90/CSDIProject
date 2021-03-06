
// CSDIProject.h : main header file for the CSDIProject application
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

// CCSDIProjectApp:
// See CSDIProject.cpp for the implementation of this class

class CCSDIProjectApp : public CWinAppEx
{
public:
	CCSDIProjectApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCSDIProjectApp theApp;
