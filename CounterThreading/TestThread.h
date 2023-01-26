#pragma once



// CTestThread

class CTestThread : public CWinThread
{
	DECLARE_DYNCREATE(CTestThread)

protected:
	CTestThread();           // protected constructor used by dynamic creation
	virtual ~CTestThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:
	static unsigned int RunThreadFunction();
	static UINT RunThreadFunction(LPVOID param);
};


