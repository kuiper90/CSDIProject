#include "stdafx.h"
#include "CMyDatabase.h"

CMyDatabase::CMyDatabase(CString loginName, CString dbPassword)
{
	CDatabase database;
	queryResult = new CStringArray();
	connectionString.Format(_T("DRIVER={Sql Server};Server=localhost;Port=1433;Database=master;UID=%s;Password=%s;"), loginName, dbPassword);
}

CStringArray* CMyDatabase::GetQueryResult(CString sqlQuery)
{
	AccessDatabase();
	CRecordset records(&database);
	if (records.Open(CRecordset::forwardOnly, sqlQuery, CRecordset::readOnly))
	{
		(*queryResult).RemoveAll();
		SaveToArray(records);		
	}
	return queryResult;
}

void CMyDatabase::SaveToArray(CRecordset &records)
{
	long size = 0;
	CStringArray& res = *queryResult;

	while (!records.IsEOF())
	{
		CString name, city, currency, category;
		records.GetFieldValue(static_cast<short>(1), name);
		records.GetFieldValue(static_cast<short>(2), city);
		records.GetFieldValue(static_cast<short>(3), currency);
		records.GetFieldValue(static_cast<short>(4), category);
		size = (long)(res.GetSize());
		res.SetSize(size + 4);
		res.SetAt(size, name);
		res.SetAt(size + 1, city);
		res.SetAt(size + 2, currency);
		res.SetAt(size + 3, category);
		records.MoveNext();
	}
}

void CMyDatabase::AccessDatabase()
{
	try
	{
		database.OpenEx(connectionString, CDatabase::openReadOnly);
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
	}
	catch (...)
	{
		AfxMessageBox(_T("Un-caught exception"));
	}
}

CMyDatabase::~CMyDatabase()
{
	database.Close();
}