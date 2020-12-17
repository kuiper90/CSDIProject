#pragma once
class CMyDatabase
{
//Attributes
protected:
	CDatabase database;
	CString connectionString;
	CStringArray* queryResult;

public:
	CMyDatabase(CString loginName, CString dbPassword);
	~CMyDatabase();
	CStringArray* GetQueryResult(CString sqlQuery);

protected:
	void AccessDatabase();
	void SaveToArray(CRecordset &records);
};