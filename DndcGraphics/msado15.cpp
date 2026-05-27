// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "msado15.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// _Collection properties

/////////////////////////////////////////////////////////////////////////////
// _Collection operations

long _Collection::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Collection::Refresh()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// _DynaCollection properties

/////////////////////////////////////////////////////////////////////////////
// _DynaCollection operations

long _DynaCollection::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _DynaCollection::Refresh()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _DynaCollection::Append(LPDISPATCH Object)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x60030000, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Object);
}

void _DynaCollection::Delete(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60030001, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}


/////////////////////////////////////////////////////////////////////////////
// _ADO properties

/////////////////////////////////////////////////////////////////////////////
// _ADO operations

LPDISPATCH _ADO::GetProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x1f4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Properties properties

/////////////////////////////////////////////////////////////////////////////
// Properties operations

long Properties::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Properties::Refresh()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Properties::GetItem(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Property properties

/////////////////////////////////////////////////////////////////////////////
// Property operations

VARIANT Property::GetValue()
{
	VARIANT result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void Property::SetValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

CString Property::GetName()
{
	CString result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long Property::GetType()
{
	long result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Property::GetAttributes()
{
	long result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Property::SetAttributes(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// Error properties

/////////////////////////////////////////////////////////////////////////////
// Error operations

long Error::GetNumber()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString Error::GetSource()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString Error::GetDescription()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString Error::GetHelpFile()
{
	CString result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long Error::GetHelpContext()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString Error::GetSQLState()
{
	CString result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long Error::GetNativeError()
{
	long result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Errors properties

/////////////////////////////////////////////////////////////////////////////
// Errors operations

long Errors::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Errors::Refresh()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Errors::GetItem(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

void Errors::Clear()
{
	InvokeHelper(0x60030001, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Command15 properties

/////////////////////////////////////////////////////////////////////////////
// Command15 operations

LPDISPATCH Command15::GetProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x1f4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Command15::GetActiveConnection()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Command15::SetRefActiveConnection(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

void Command15::SetActiveConnection(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

CString Command15::GetCommandText()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Command15::SetCommandText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long Command15::GetCommandTimeout()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Command15::SetCommandTimeout(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL Command15::GetPrepared()
{
	BOOL result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Command15::SetPrepared(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH Command15::Execute(VARIANT* RecordsAffected, VARIANT* Parameters, long Options)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT VTS_I4;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		RecordsAffected, Parameters, Options);
	return result;
}

LPDISPATCH Command15::CreateParameter(LPCTSTR Name, long Type, long Direction, long Size, const VARIANT& Value)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_VARIANT;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name, Type, Direction, Size, &Value);
	return result;
}

LPDISPATCH Command15::GetParameters()
{
	LPDISPATCH result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Command15::SetCommandType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Command15::GetCommandType()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString Command15::GetName()
{
	CString result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Command15::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// _Connection properties

/////////////////////////////////////////////////////////////////////////////
// _Connection operations

LPDISPATCH _Connection::GetProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x1f4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Connection::GetConnectionString()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Connection::SetConnectionString(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _Connection::GetCommandTimeout()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Connection::SetCommandTimeout(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Connection::GetConnectionTimeout()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Connection::SetConnectionTimeout(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _Connection::GetVersion()
{
	CString result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Connection::Close()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _Connection::Execute(LPCTSTR CommandText, VARIANT* RecordsAffected, long Options)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_I4;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		CommandText, RecordsAffected, Options);
	return result;
}

long _Connection::BeginTrans()
{
	long result;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

void _Connection::CommitTrans()
{
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Connection::RollbackTrans()
{
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Connection::Open(LPCTSTR ConnectionString, LPCTSTR UserID, LPCTSTR Password, long Options)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ConnectionString, UserID, Password, Options);
}

LPDISPATCH _Connection::GetErrors()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Connection::GetDefaultDatabase()
{
	CString result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Connection::SetDefaultDatabase(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _Connection::GetIsolationLevel()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Connection::SetIsolationLevel(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Connection::GetAttributes()
{
	long result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Connection::SetAttributes(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Connection::GetCursorLocation()
{
	long result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Connection::SetCursorLocation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Connection::GetMode()
{
	long result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Connection::SetMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _Connection::GetProvider()
{
	CString result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Connection::SetProvider(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _Connection::GetState()
{
	long result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Connection::OpenSchema(long Schema, const VARIANT& Restrictions, const VARIANT& SchemaID)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Schema, &Restrictions, &SchemaID);
	return result;
}

void _Connection::Cancel()
{
	InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Connection15 properties

/////////////////////////////////////////////////////////////////////////////
// Connection15 operations

LPDISPATCH Connection15::GetProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x1f4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString Connection15::GetConnectionString()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Connection15::SetConnectionString(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long Connection15::GetCommandTimeout()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Connection15::SetCommandTimeout(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Connection15::GetConnectionTimeout()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Connection15::SetConnectionTimeout(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString Connection15::GetVersion()
{
	CString result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Connection15::Close()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Connection15::Execute(LPCTSTR CommandText, VARIANT* RecordsAffected, long Options)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_I4;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		CommandText, RecordsAffected, Options);
	return result;
}

long Connection15::BeginTrans()
{
	long result;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

void Connection15::CommitTrans()
{
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Connection15::RollbackTrans()
{
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Connection15::Open(LPCTSTR ConnectionString, LPCTSTR UserID, LPCTSTR Password, long Options)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ConnectionString, UserID, Password, Options);
}

LPDISPATCH Connection15::GetErrors()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString Connection15::GetDefaultDatabase()
{
	CString result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Connection15::SetDefaultDatabase(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long Connection15::GetIsolationLevel()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Connection15::SetIsolationLevel(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Connection15::GetAttributes()
{
	long result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Connection15::SetAttributes(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Connection15::GetCursorLocation()
{
	long result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Connection15::SetCursorLocation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Connection15::GetMode()
{
	long result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Connection15::SetMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString Connection15::GetProvider()
{
	CString result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Connection15::SetProvider(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long Connection15::GetState()
{
	long result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Connection15::OpenSchema(long Schema, const VARIANT& Restrictions, const VARIANT& SchemaID)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Schema, &Restrictions, &SchemaID);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _Recordset properties

/////////////////////////////////////////////////////////////////////////////
// _Recordset operations

LPDISPATCH _Recordset::GetProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x1f4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Recordset::GetAbsolutePosition()
{
	long result;
	InvokeHelper(0x3e8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Recordset::SetAbsolutePosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3e8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void _Recordset::SetRefActiveConnection(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

void _Recordset::SetActiveConnection(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT _Recordset::GetActiveConnection()
{
	VARIANT result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

BOOL _Recordset::GetBof()
{
	BOOL result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

VARIANT _Recordset::GetBookmark()
{
	VARIANT result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void _Recordset::SetBookmark(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long _Recordset::GetCacheSize()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Recordset::SetCacheSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Recordset::GetCursorType()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Recordset::SetCursorType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL _Recordset::GetEof()
{
	BOOL result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Recordset::GetFields()
{
	LPDISPATCH result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Recordset::GetLockType()
{
	long result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Recordset::SetLockType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Recordset::GetMaxRecords()
{
	long result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Recordset::SetMaxRecords(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Recordset::GetRecordCount()
{
	long result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Recordset::SetRefSource(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

void _Recordset::SetSource(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

VARIANT _Recordset::GetSource()
{
	VARIANT result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void _Recordset::AddNew(const VARIANT& FieldList, const VARIANT& Values)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x3f4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FieldList, &Values);
}

void _Recordset::CancelUpdate()
{
	InvokeHelper(0x3f5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Recordset::Close()
{
	InvokeHelper(0x3f6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Recordset::Delete(long AffectRecords)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AffectRecords);
}

VARIANT _Recordset::GetRows(long Rows, const VARIANT& Start, const VARIANT& Fields)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x3f8, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Rows, &Start, &Fields);
	return result;
}

void _Recordset::Move(long NumRecords, const VARIANT& Start)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x3f9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 NumRecords, &Start);
}

void _Recordset::MoveNext()
{
	InvokeHelper(0x3fa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Recordset::MovePrevious()
{
	InvokeHelper(0x3fb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Recordset::MoveFirst()
{
	InvokeHelper(0x3fc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Recordset::MoveLast()
{
	InvokeHelper(0x3fd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Recordset::Open(const VARIANT& Source, const VARIANT& ActiveConnection, long CursorType, long LockType, long Options)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x3fe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Source, &ActiveConnection, CursorType, LockType, Options);
}

void _Recordset::Requery(long Options)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ff, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Options);
}

void _Recordset::Update(const VARIANT& Fields, const VARIANT& Values)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x401, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Fields, &Values);
}

long _Recordset::GetAbsolutePage()
{
	long result;
	InvokeHelper(0x417, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Recordset::SetAbsolutePage(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x417, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Recordset::GetEditMode()
{
	long result;
	InvokeHelper(0x402, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT _Recordset::GetFilter()
{
	VARIANT result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void _Recordset::SetFilter(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x406, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long _Recordset::GetPageCount()
{
	long result;
	InvokeHelper(0x41a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _Recordset::GetPageSize()
{
	long result;
	InvokeHelper(0x418, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Recordset::SetPageSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x418, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _Recordset::GetSort()
{
	CString result;
	InvokeHelper(0x407, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Recordset::SetSort(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x407, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _Recordset::GetStatus()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _Recordset::GetState()
{
	long result;
	InvokeHelper(0x41e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Recordset::UpdateBatch(long AffectRecords)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x40b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AffectRecords);
}

void _Recordset::CancelBatch(long AffectRecords)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x419, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AffectRecords);
}

long _Recordset::GetCursorLocation()
{
	long result;
	InvokeHelper(0x41b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Recordset::SetCursorLocation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x41b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH _Recordset::NextRecordset(VARIANT* RecordsAffected)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x41c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		RecordsAffected);
	return result;
}

BOOL _Recordset::Supports(long CursorOptions)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x40c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		CursorOptions);
	return result;
}

long _Recordset::GetMarshalOptions()
{
	long result;
	InvokeHelper(0x41d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Recordset::SetMarshalOptions(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x41d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void _Recordset::Find(LPCTSTR Criteria, long SkipRecords, long SearchDirection, const VARIANT& Start)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_VARIANT;
	InvokeHelper(0x422, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Criteria, SkipRecords, SearchDirection, &Start);
}

void _Recordset::Cancel()
{
	InvokeHelper(0x41f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPUNKNOWN _Recordset::GetDataSource()
{
	LPUNKNOWN result;
	InvokeHelper(0x420, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

void _Recordset::SetRefDataSource(LPUNKNOWN newValue)
{
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x420, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH _Recordset::GetActiveCommand()
{
	LPDISPATCH result;
	InvokeHelper(0x425, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Recordset::SetStayInSync(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x427, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _Recordset::GetStayInSync()
{
	BOOL result;
	InvokeHelper(0x427, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString _Recordset::GetString(long StringFormat, long NumRows, LPCTSTR ColumnDelimeter, LPCTSTR RowDelimeter, LPCTSTR NullExpr)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x426, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		StringFormat, NumRows, ColumnDelimeter, RowDelimeter, NullExpr);
	return result;
}

CString _Recordset::GetDataMember()
{
	CString result;
	InvokeHelper(0x428, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Recordset::SetDataMember(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x428, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _Recordset::CompareBookmarks(const VARIANT& Bookmark1, const VARIANT& Bookmark2)
{
	long result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x429, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		&Bookmark1, &Bookmark2);
	return result;
}

LPDISPATCH _Recordset::Clone(long LockType)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x40a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		LockType);
	return result;
}

void _Recordset::Resync(long AffectRecords, long ResyncValues)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x400, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AffectRecords, ResyncValues);
}

void _Recordset::Seek(const VARIANT& KeyValues, long SeekOption)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_I4;
	InvokeHelper(0x42a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &KeyValues, SeekOption);
}

void _Recordset::SetIndex(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x42b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _Recordset::GetIndex()
{
	CString result;
	InvokeHelper(0x42b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Recordset::Save(const VARIANT& Destination, long PersistFormat)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_I4;
	InvokeHelper(0x421, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Destination, PersistFormat);
}


/////////////////////////////////////////////////////////////////////////////
// Recordset21 properties

/////////////////////////////////////////////////////////////////////////////
// Recordset21 operations

LPDISPATCH Recordset21::GetProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x1f4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Recordset21::GetAbsolutePosition()
{
	long result;
	InvokeHelper(0x3e8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset21::SetAbsolutePosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3e8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void Recordset21::SetRefActiveConnection(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

void Recordset21::SetActiveConnection(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT Recordset21::GetActiveConnection()
{
	VARIANT result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

BOOL Recordset21::GetBof()
{
	BOOL result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

VARIANT Recordset21::GetBookmark()
{
	VARIANT result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void Recordset21::SetBookmark(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long Recordset21::GetCacheSize()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset21::SetCacheSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Recordset21::GetCursorType()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset21::SetCursorType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL Recordset21::GetEof()
{
	BOOL result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH Recordset21::GetFields()
{
	LPDISPATCH result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Recordset21::GetLockType()
{
	long result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset21::SetLockType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Recordset21::GetMaxRecords()
{
	long result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset21::SetMaxRecords(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Recordset21::GetRecordCount()
{
	long result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset21::SetRefSource(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

void Recordset21::SetSource(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

VARIANT Recordset21::GetSource()
{
	VARIANT result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void Recordset21::AddNew(const VARIANT& FieldList, const VARIANT& Values)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x3f4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FieldList, &Values);
}

void Recordset21::CancelUpdate()
{
	InvokeHelper(0x3f5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Recordset21::Close()
{
	InvokeHelper(0x3f6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Recordset21::Delete(long AffectRecords)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AffectRecords);
}

VARIANT Recordset21::GetRows(long Rows, const VARIANT& Start, const VARIANT& Fields)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x3f8, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Rows, &Start, &Fields);
	return result;
}

void Recordset21::Move(long NumRecords, const VARIANT& Start)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x3f9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 NumRecords, &Start);
}

void Recordset21::MoveNext()
{
	InvokeHelper(0x3fa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Recordset21::MovePrevious()
{
	InvokeHelper(0x3fb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Recordset21::MoveFirst()
{
	InvokeHelper(0x3fc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Recordset21::MoveLast()
{
	InvokeHelper(0x3fd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Recordset21::Open(const VARIANT& Source, const VARIANT& ActiveConnection, long CursorType, long LockType, long Options)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x3fe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Source, &ActiveConnection, CursorType, LockType, Options);
}

void Recordset21::Requery(long Options)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ff, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Options);
}

void Recordset21::Update(const VARIANT& Fields, const VARIANT& Values)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x401, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Fields, &Values);
}

long Recordset21::GetAbsolutePage()
{
	long result;
	InvokeHelper(0x417, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset21::SetAbsolutePage(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x417, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Recordset21::GetEditMode()
{
	long result;
	InvokeHelper(0x402, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT Recordset21::GetFilter()
{
	VARIANT result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void Recordset21::SetFilter(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x406, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long Recordset21::GetPageCount()
{
	long result;
	InvokeHelper(0x41a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Recordset21::GetPageSize()
{
	long result;
	InvokeHelper(0x418, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset21::SetPageSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x418, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString Recordset21::GetSort()
{
	CString result;
	InvokeHelper(0x407, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Recordset21::SetSort(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x407, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long Recordset21::GetStatus()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Recordset21::GetState()
{
	long result;
	InvokeHelper(0x41e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset21::UpdateBatch(long AffectRecords)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x40b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AffectRecords);
}

void Recordset21::CancelBatch(long AffectRecords)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x419, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AffectRecords);
}

long Recordset21::GetCursorLocation()
{
	long result;
	InvokeHelper(0x41b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset21::SetCursorLocation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x41b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH Recordset21::NextRecordset(VARIANT* RecordsAffected)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x41c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		RecordsAffected);
	return result;
}

BOOL Recordset21::Supports(long CursorOptions)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x40c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		CursorOptions);
	return result;
}

long Recordset21::GetMarshalOptions()
{
	long result;
	InvokeHelper(0x41d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset21::SetMarshalOptions(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x41d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void Recordset21::Find(LPCTSTR Criteria, long SkipRecords, long SearchDirection, const VARIANT& Start)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_VARIANT;
	InvokeHelper(0x422, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Criteria, SkipRecords, SearchDirection, &Start);
}

void Recordset21::Cancel()
{
	InvokeHelper(0x41f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPUNKNOWN Recordset21::GetDataSource()
{
	LPUNKNOWN result;
	InvokeHelper(0x420, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

void Recordset21::SetRefDataSource(LPUNKNOWN newValue)
{
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x420, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH Recordset21::GetActiveCommand()
{
	LPDISPATCH result;
	InvokeHelper(0x425, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Recordset21::SetStayInSync(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x427, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL Recordset21::GetStayInSync()
{
	BOOL result;
	InvokeHelper(0x427, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString Recordset21::GetString(long StringFormat, long NumRows, LPCTSTR ColumnDelimeter, LPCTSTR RowDelimeter, LPCTSTR NullExpr)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x426, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		StringFormat, NumRows, ColumnDelimeter, RowDelimeter, NullExpr);
	return result;
}

CString Recordset21::GetDataMember()
{
	CString result;
	InvokeHelper(0x428, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Recordset21::SetDataMember(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x428, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long Recordset21::CompareBookmarks(const VARIANT& Bookmark1, const VARIANT& Bookmark2)
{
	long result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x429, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		&Bookmark1, &Bookmark2);
	return result;
}

LPDISPATCH Recordset21::Clone(long LockType)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x40a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		LockType);
	return result;
}

void Recordset21::Resync(long AffectRecords, long ResyncValues)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x400, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AffectRecords, ResyncValues);
}

void Recordset21::Seek(const VARIANT& KeyValues, long SeekOption)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_I4;
	InvokeHelper(0x42a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &KeyValues, SeekOption);
}

void Recordset21::SetIndex(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x42b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString Recordset21::GetIndex()
{
	CString result;
	InvokeHelper(0x42b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Recordset20 properties

/////////////////////////////////////////////////////////////////////////////
// Recordset20 operations

LPDISPATCH Recordset20::GetProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x1f4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Recordset20::GetAbsolutePosition()
{
	long result;
	InvokeHelper(0x3e8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset20::SetAbsolutePosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3e8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void Recordset20::SetRefActiveConnection(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

void Recordset20::SetActiveConnection(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT Recordset20::GetActiveConnection()
{
	VARIANT result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

BOOL Recordset20::GetBof()
{
	BOOL result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

VARIANT Recordset20::GetBookmark()
{
	VARIANT result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void Recordset20::SetBookmark(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long Recordset20::GetCacheSize()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset20::SetCacheSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Recordset20::GetCursorType()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset20::SetCursorType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL Recordset20::GetEof()
{
	BOOL result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH Recordset20::GetFields()
{
	LPDISPATCH result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Recordset20::GetLockType()
{
	long result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset20::SetLockType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Recordset20::GetMaxRecords()
{
	long result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset20::SetMaxRecords(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Recordset20::GetRecordCount()
{
	long result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset20::SetRefSource(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

void Recordset20::SetSource(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

VARIANT Recordset20::GetSource()
{
	VARIANT result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void Recordset20::AddNew(const VARIANT& FieldList, const VARIANT& Values)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x3f4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FieldList, &Values);
}

void Recordset20::CancelUpdate()
{
	InvokeHelper(0x3f5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Recordset20::Close()
{
	InvokeHelper(0x3f6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Recordset20::Delete(long AffectRecords)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AffectRecords);
}

VARIANT Recordset20::GetRows(long Rows, const VARIANT& Start, const VARIANT& Fields)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x3f8, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Rows, &Start, &Fields);
	return result;
}

void Recordset20::Move(long NumRecords, const VARIANT& Start)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x3f9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 NumRecords, &Start);
}

void Recordset20::MoveNext()
{
	InvokeHelper(0x3fa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Recordset20::MovePrevious()
{
	InvokeHelper(0x3fb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Recordset20::MoveFirst()
{
	InvokeHelper(0x3fc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Recordset20::MoveLast()
{
	InvokeHelper(0x3fd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Recordset20::Open(const VARIANT& Source, const VARIANT& ActiveConnection, long CursorType, long LockType, long Options)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x3fe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Source, &ActiveConnection, CursorType, LockType, Options);
}

void Recordset20::Requery(long Options)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ff, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Options);
}

void Recordset20::Update(const VARIANT& Fields, const VARIANT& Values)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x401, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Fields, &Values);
}

long Recordset20::GetAbsolutePage()
{
	long result;
	InvokeHelper(0x417, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset20::SetAbsolutePage(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x417, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Recordset20::GetEditMode()
{
	long result;
	InvokeHelper(0x402, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT Recordset20::GetFilter()
{
	VARIANT result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void Recordset20::SetFilter(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x406, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long Recordset20::GetPageCount()
{
	long result;
	InvokeHelper(0x41a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Recordset20::GetPageSize()
{
	long result;
	InvokeHelper(0x418, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset20::SetPageSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x418, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString Recordset20::GetSort()
{
	CString result;
	InvokeHelper(0x407, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Recordset20::SetSort(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x407, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long Recordset20::GetStatus()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Recordset20::GetState()
{
	long result;
	InvokeHelper(0x41e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset20::UpdateBatch(long AffectRecords)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x40b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AffectRecords);
}

void Recordset20::CancelBatch(long AffectRecords)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x419, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AffectRecords);
}

long Recordset20::GetCursorLocation()
{
	long result;
	InvokeHelper(0x41b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset20::SetCursorLocation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x41b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH Recordset20::NextRecordset(VARIANT* RecordsAffected)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x41c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		RecordsAffected);
	return result;
}

BOOL Recordset20::Supports(long CursorOptions)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x40c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		CursorOptions);
	return result;
}

long Recordset20::GetMarshalOptions()
{
	long result;
	InvokeHelper(0x41d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset20::SetMarshalOptions(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x41d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void Recordset20::Find(LPCTSTR Criteria, long SkipRecords, long SearchDirection, const VARIANT& Start)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_VARIANT;
	InvokeHelper(0x422, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Criteria, SkipRecords, SearchDirection, &Start);
}

void Recordset20::Cancel()
{
	InvokeHelper(0x41f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPUNKNOWN Recordset20::GetDataSource()
{
	LPUNKNOWN result;
	InvokeHelper(0x420, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

void Recordset20::SetRefDataSource(LPUNKNOWN newValue)
{
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x420, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH Recordset20::GetActiveCommand()
{
	LPDISPATCH result;
	InvokeHelper(0x425, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Recordset20::SetStayInSync(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x427, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL Recordset20::GetStayInSync()
{
	BOOL result;
	InvokeHelper(0x427, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString Recordset20::GetString(long StringFormat, long NumRows, LPCTSTR ColumnDelimeter, LPCTSTR RowDelimeter, LPCTSTR NullExpr)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x426, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		StringFormat, NumRows, ColumnDelimeter, RowDelimeter, NullExpr);
	return result;
}

CString Recordset20::GetDataMember()
{
	CString result;
	InvokeHelper(0x428, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Recordset20::SetDataMember(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x428, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long Recordset20::CompareBookmarks(const VARIANT& Bookmark1, const VARIANT& Bookmark2)
{
	long result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x429, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		&Bookmark1, &Bookmark2);
	return result;
}

LPDISPATCH Recordset20::Clone(long LockType)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x40a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		LockType);
	return result;
}

void Recordset20::Resync(long AffectRecords, long ResyncValues)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x400, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AffectRecords, ResyncValues);
}


/////////////////////////////////////////////////////////////////////////////
// Recordset15 properties

/////////////////////////////////////////////////////////////////////////////
// Recordset15 operations

LPDISPATCH Recordset15::GetProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x1f4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Recordset15::GetAbsolutePosition()
{
	long result;
	InvokeHelper(0x3e8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset15::SetAbsolutePosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3e8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void Recordset15::SetRefActiveConnection(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

void Recordset15::SetActiveConnection(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT Recordset15::GetActiveConnection()
{
	VARIANT result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

BOOL Recordset15::GetBof()
{
	BOOL result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

VARIANT Recordset15::GetBookmark()
{
	VARIANT result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void Recordset15::SetBookmark(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long Recordset15::GetCacheSize()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset15::SetCacheSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Recordset15::GetCursorType()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset15::SetCursorType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL Recordset15::GetEof()
{
	BOOL result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH Recordset15::GetFields()
{
	LPDISPATCH result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Recordset15::GetLockType()
{
	long result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset15::SetLockType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Recordset15::GetMaxRecords()
{
	long result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset15::SetMaxRecords(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Recordset15::GetRecordCount()
{
	long result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset15::SetRefSource(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

void Recordset15::SetSource(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

VARIANT Recordset15::GetSource()
{
	VARIANT result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void Recordset15::AddNew(const VARIANT& FieldList, const VARIANT& Values)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x3f4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FieldList, &Values);
}

void Recordset15::CancelUpdate()
{
	InvokeHelper(0x3f5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Recordset15::Close()
{
	InvokeHelper(0x3f6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Recordset15::Delete(long AffectRecords)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AffectRecords);
}

VARIANT Recordset15::GetRows(long Rows, const VARIANT& Start, const VARIANT& Fields)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x3f8, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Rows, &Start, &Fields);
	return result;
}

void Recordset15::Move(long NumRecords, const VARIANT& Start)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x3f9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 NumRecords, &Start);
}

void Recordset15::MoveNext()
{
	InvokeHelper(0x3fa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Recordset15::MovePrevious()
{
	InvokeHelper(0x3fb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Recordset15::MoveFirst()
{
	InvokeHelper(0x3fc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Recordset15::MoveLast()
{
	InvokeHelper(0x3fd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Recordset15::Open(const VARIANT& Source, const VARIANT& ActiveConnection, long CursorType, long LockType, long Options)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x3fe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Source, &ActiveConnection, CursorType, LockType, Options);
}

void Recordset15::Requery(long Options)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ff, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Options);
}

void Recordset15::Update(const VARIANT& Fields, const VARIANT& Values)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x401, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Fields, &Values);
}

long Recordset15::GetAbsolutePage()
{
	long result;
	InvokeHelper(0x417, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset15::SetAbsolutePage(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x417, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Recordset15::GetEditMode()
{
	long result;
	InvokeHelper(0x402, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT Recordset15::GetFilter()
{
	VARIANT result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void Recordset15::SetFilter(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x406, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long Recordset15::GetPageCount()
{
	long result;
	InvokeHelper(0x41a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Recordset15::GetPageSize()
{
	long result;
	InvokeHelper(0x418, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset15::SetPageSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x418, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString Recordset15::GetSort()
{
	CString result;
	InvokeHelper(0x407, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Recordset15::SetSort(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x407, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long Recordset15::GetStatus()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Recordset15::GetState()
{
	long result;
	InvokeHelper(0x41e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset15::UpdateBatch(long AffectRecords)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x40b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AffectRecords);
}

void Recordset15::CancelBatch(long AffectRecords)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x419, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AffectRecords);
}

long Recordset15::GetCursorLocation()
{
	long result;
	InvokeHelper(0x41b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset15::SetCursorLocation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x41b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH Recordset15::NextRecordset(VARIANT* RecordsAffected)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x41c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		RecordsAffected);
	return result;
}

BOOL Recordset15::Supports(long CursorOptions)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x40c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		CursorOptions);
	return result;
}

long Recordset15::GetMarshalOptions()
{
	long result;
	InvokeHelper(0x41d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recordset15::SetMarshalOptions(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x41d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void Recordset15::Find(LPCTSTR Criteria, long SkipRecords, long SearchDirection, const VARIANT& Start)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_VARIANT;
	InvokeHelper(0x422, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Criteria, SkipRecords, SearchDirection, &Start);
}


/////////////////////////////////////////////////////////////////////////////
// Fields properties

/////////////////////////////////////////////////////////////////////////////
// Fields operations

long Fields::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Fields::Refresh()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Fields::GetItem(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

void Fields::Delete(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}

void Fields::Append(LPCTSTR Name, long Type, long DefinedSize, long Attrib, const VARIANT& FieldValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name, Type, DefinedSize, Attrib, &FieldValue);
}

void Fields::Update()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Fields::Resync(long ResyncValues)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ResyncValues);
}

void Fields::CancelUpdate()
{
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Fields20 properties

/////////////////////////////////////////////////////////////////////////////
// Fields20 operations

long Fields20::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Fields20::Refresh()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Fields20::GetItem(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

void Fields20::Delete(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}


/////////////////////////////////////////////////////////////////////////////
// Fields15 properties

/////////////////////////////////////////////////////////////////////////////
// Fields15 operations

long Fields15::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Fields15::Refresh()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Fields15::GetItem(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Field properties

/////////////////////////////////////////////////////////////////////////////
// Field operations

LPDISPATCH Field::GetProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x1f4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Field::GetActualSize()
{
	long result;
	InvokeHelper(0x455, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Field::GetAttributes()
{
	long result;
	InvokeHelper(0x45a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Field::GetDefinedSize()
{
	long result;
	InvokeHelper(0x44f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString Field::GetName()
{
	CString result;
	InvokeHelper(0x44c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long Field::GetType()
{
	long result;
	InvokeHelper(0x44e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT Field::GetValue()
{
	VARIANT result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void Field::SetValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void Field::AppendChunk(const VARIANT& Data)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x453, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Data);
}

VARIANT Field::GetChunk(long Length)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x454, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Length);
	return result;
}

VARIANT Field::GetOriginalValue()
{
	VARIANT result;
	InvokeHelper(0x450, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Field::GetUnderlyingValue()
{
	VARIANT result;
	InvokeHelper(0x451, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

LPUNKNOWN Field::GetDataFormat()
{
	LPUNKNOWN result;
	InvokeHelper(0x45b, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

void Field::SetRefDataFormat(LPUNKNOWN newValue)
{
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x45b, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

void Field::SetType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x44e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void Field::SetDefinedSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x44f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void Field::SetAttributes(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x45a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Field::GetStatus()
{
	long result;
	InvokeHelper(0x45c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Field20 properties

/////////////////////////////////////////////////////////////////////////////
// Field20 operations

LPDISPATCH Field20::GetProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x1f4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Field20::GetActualSize()
{
	long result;
	InvokeHelper(0x455, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Field20::GetAttributes()
{
	long result;
	InvokeHelper(0x45a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Field20::GetDefinedSize()
{
	long result;
	InvokeHelper(0x44f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString Field20::GetName()
{
	CString result;
	InvokeHelper(0x44c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long Field20::GetType()
{
	long result;
	InvokeHelper(0x44e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT Field20::GetValue()
{
	VARIANT result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void Field20::SetValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void Field20::AppendChunk(const VARIANT& Data)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x453, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Data);
}

VARIANT Field20::GetChunk(long Length)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x454, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Length);
	return result;
}

VARIANT Field20::GetOriginalValue()
{
	VARIANT result;
	InvokeHelper(0x450, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Field20::GetUnderlyingValue()
{
	VARIANT result;
	InvokeHelper(0x451, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

LPUNKNOWN Field20::GetDataFormat()
{
	LPUNKNOWN result;
	InvokeHelper(0x45b, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

void Field20::SetRefDataFormat(LPUNKNOWN newValue)
{
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x45b, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

void Field20::SetType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x44e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void Field20::SetDefinedSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x44f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void Field20::SetAttributes(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x45a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// _Parameter properties

/////////////////////////////////////////////////////////////////////////////
// _Parameter operations

LPDISPATCH _Parameter::GetProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x1f4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Parameter::GetName()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Parameter::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

VARIANT _Parameter::GetValue()
{
	VARIANT result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void _Parameter::SetValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long _Parameter::GetType()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Parameter::SetType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void _Parameter::SetDirection(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Parameter::GetDirection()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Parameter::SetSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Parameter::GetSize()
{
	long result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Parameter::AppendChunk(const VARIANT& Val)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Val);
}

long _Parameter::GetAttributes()
{
	long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Parameter::SetAttributes(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// Parameters properties

/////////////////////////////////////////////////////////////////////////////
// Parameters operations

long Parameters::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Parameters::Refresh()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Parameters::Append(LPDISPATCH Object)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x60030000, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Object);
}

void Parameters::Delete(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60030001, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}

LPDISPATCH Parameters::GetItem(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Command25 properties

/////////////////////////////////////////////////////////////////////////////
// Command25 operations

LPDISPATCH Command25::GetProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x1f4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Command25::GetActiveConnection()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Command25::SetRefActiveConnection(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

void Command25::SetActiveConnection(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

CString Command25::GetCommandText()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Command25::SetCommandText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long Command25::GetCommandTimeout()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Command25::SetCommandTimeout(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL Command25::GetPrepared()
{
	BOOL result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Command25::SetPrepared(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH Command25::Execute(VARIANT* RecordsAffected, VARIANT* Parameters, long Options)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT VTS_I4;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		RecordsAffected, Parameters, Options);
	return result;
}

LPDISPATCH Command25::CreateParameter(LPCTSTR Name, long Type, long Direction, long Size, const VARIANT& Value)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_VARIANT;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name, Type, Direction, Size, &Value);
	return result;
}

LPDISPATCH Command25::GetParameters()
{
	LPDISPATCH result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Command25::SetCommandType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Command25::GetCommandType()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString Command25::GetName()
{
	CString result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Command25::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long Command25::GetState()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Command25::Cancel()
{
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// _Command properties

/////////////////////////////////////////////////////////////////////////////
// _Command operations

LPDISPATCH _Command::GetProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x1f4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Command::GetActiveConnection()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Command::SetRefActiveConnection(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

void _Command::SetActiveConnection(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

CString _Command::GetCommandText()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Command::SetCommandText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _Command::GetCommandTimeout()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Command::SetCommandTimeout(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL _Command::GetPrepared()
{
	BOOL result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Command::SetPrepared(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _Command::Execute(VARIANT* RecordsAffected, VARIANT* Parameters, long Options)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT VTS_I4;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		RecordsAffected, Parameters, Options);
	return result;
}

LPDISPATCH _Command::CreateParameter(LPCTSTR Name, long Type, long Direction, long Size, const VARIANT& Value)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_VARIANT;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name, Type, Direction, Size, &Value);
	return result;
}

LPDISPATCH _Command::GetParameters()
{
	LPDISPATCH result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Command::SetCommandType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Command::GetCommandType()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _Command::GetName()
{
	CString result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Command::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _Command::GetState()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Command::Cancel()
{
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Command::SetRefCommandStream(LPUNKNOWN newValue)
{
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT _Command::GetCommandStream()
{
	VARIANT result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void _Command::SetDialect(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _Command::GetDialect()
{
	CString result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Command::SetNamedParameters(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _Command::GetNamedParameters()
{
	BOOL result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ConnectionEvents properties

/////////////////////////////////////////////////////////////////////////////
// ConnectionEvents operations


/////////////////////////////////////////////////////////////////////////////
// RecordsetEvents properties

/////////////////////////////////////////////////////////////////////////////
// RecordsetEvents operations


/////////////////////////////////////////////////////////////////////////////
// _Record properties

/////////////////////////////////////////////////////////////////////////////
// _Record operations

LPDISPATCH _Record::GetProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x1f4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT _Record::GetActiveConnection()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void _Record::SetActiveConnection(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void _Record::SetRefActiveConnection(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

long _Record::GetState()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT _Record::GetSource()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void _Record::SetSource(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void _Record::SetRefSource(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

long _Record::GetMode()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Record::SetMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _Record::GetParentURL()
{
	CString result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Record::MoveRecord(LPCTSTR Source, LPCTSTR Destination, LPCTSTR UserName, LPCTSTR Password, long Options, BOOL Async)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BOOL;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		Source, Destination, UserName, Password, Options, Async);
	return result;
}

CString _Record::CopyRecord(LPCTSTR Source, LPCTSTR Destination, LPCTSTR UserName, LPCTSTR Password, long Options, BOOL Async)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BOOL;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		Source, Destination, UserName, Password, Options, Async);
	return result;
}

void _Record::DeleteRecord(LPCTSTR Source, BOOL Async)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Source, Async);
}

void _Record::Open(const VARIANT& Source, const VARIANT& ActiveConnection, long Mode, long CreateOptions, long Options, LPCTSTR UserName, LPCTSTR Password)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Source, &ActiveConnection, Mode, CreateOptions, Options, UserName, Password);
}

void _Record::Close()
{
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _Record::GetFields()
{
	LPDISPATCH result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Record::GetRecordType()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Record::GetChildren()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Record::Cancel()
{
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// _Stream properties

/////////////////////////////////////////////////////////////////////////////
// _Stream operations

long _Stream::GetSize()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL _Stream::GetEos()
{
	BOOL result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long _Stream::GetPosition()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Stream::SetPosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Stream::GetType()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Stream::SetType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Stream::GetLineSeparator()
{
	long result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Stream::SetLineSeparator(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Stream::GetState()
{
	long result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _Stream::GetMode()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Stream::SetMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _Stream::GetCharset()
{
	CString result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Stream::SetCharset(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

VARIANT _Stream::Read(long NumBytes)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumBytes);
	return result;
}

void _Stream::Open(const VARIANT& Source, long Mode, long Options, LPCTSTR UserName, LPCTSTR Password)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Source, Mode, Options, UserName, Password);
}

void _Stream::Close()
{
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Stream::SkipLine()
{
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Stream::Write(const VARIANT& Buffer)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Buffer);
}

void _Stream::SetEOS()
{
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Stream::CopyTo(LPDISPATCH DestStream, long CharNumber)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DestStream, CharNumber);
}

void _Stream::Flush()
{
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Stream::SaveToFile(LPCTSTR FileName, long Options)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName, Options);
}

void _Stream::LoadFromFile(LPCTSTR FileName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName);
}

CString _Stream::ReadText(long NumChars)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		NumChars);
	return result;
}

void _Stream::WriteText(LPCTSTR Data, long Options)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Data, Options);
}

void _Stream::Cancel()
{
	InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Field15 properties

/////////////////////////////////////////////////////////////////////////////
// Field15 operations

LPDISPATCH Field15::GetProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x1f4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Field15::GetActualSize()
{
	long result;
	InvokeHelper(0x455, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Field15::GetAttributes()
{
	long result;
	InvokeHelper(0x45a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Field15::GetDefinedSize()
{
	long result;
	InvokeHelper(0x44f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString Field15::GetName()
{
	CString result;
	InvokeHelper(0x44c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long Field15::GetType()
{
	long result;
	InvokeHelper(0x44e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT Field15::GetValue()
{
	VARIANT result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void Field15::SetValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void Field15::AppendChunk(const VARIANT& Data)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x453, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Data);
}

VARIANT Field15::GetChunk(long Length)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x454, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Length);
	return result;
}

VARIANT Field15::GetOriginalValue()
{
	VARIANT result;
	InvokeHelper(0x450, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Field15::GetUnderlyingValue()
{
	VARIANT result;
	InvokeHelper(0x451, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}
