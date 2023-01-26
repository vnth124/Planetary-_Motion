
// CounterThreadingView.cpp : implementation of the CCounterThreadingView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CounterThreading.h"
#endif

#include "CounterThreadingDoc.h"
#include "CounterThreadingView.h"
#include "TestThread.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCounterThreadingView

IMPLEMENT_DYNCREATE(CCounterThreadingView, CView)

BEGIN_MESSAGE_MAP(CCounterThreadingView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_THREAD_START, &CCounterThreadingView::OnThreadStart)
	ON_COMMAND(ID_THREAD_PAUSE, &CCounterThreadingView::OnThreadPause)
	ON_COMMAND(ID_THREAD_RESUME, &CCounterThreadingView::OnThreadResume)
END_MESSAGE_MAP()

// CCounterThreadingView construction/destruction

CCounterThreadingView::CCounterThreadingView()

{
	m_iCounter = 0;
	angle = 0, a=200, b=190, p=296, q=240;
	t = 3.14 / 180.0;
	x = 350, y = 350;
}
CCounterThreadingView::~CCounterThreadingView()
{
}

BOOL CCounterThreadingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCounterThreadingView drawing

void CCounterThreadingView::OnDraw(CDC* pDC)
{
	CCounterThreadingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	m_iCounter++;
	CString strCounter;
	strCounter.Format(L"The Counter i %d", m_iCounter);
	pDC->TextOut(700, 100, strCounter);

	//largest orbit

	CPen blackpen;
	blackpen.CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	CPen* pOldpen1 = pDC->SelectObject(&blackpen);
	pDC->Ellipse(10, 70, 600, 550);
	pDC->SelectObject(pOldpen1);

	//Smallest orbit

	CPen bluepen;
	bluepen.CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
	CPen* pOldpen = pDC->SelectObject(&bluepen);
	pDC->Ellipse(100, 120, 500, 500);
	pDC->SelectObject(pOldpen);



	//sun in yellow color

	CBrush brushyellow(RGB(255, 255, 0));
	CBrush *pOldBrush = pDC->SelectObject(&brushyellow);
	pDC->Ellipse(250, 250, 350, 350);
	pDC->SelectObject(pOldBrush);

	
	// smallest orbit rotation

	for (int i = 0; i < m_iCounter; i++)
	{
		angle = i;
		x = a * cos(t * angle);

		y = b* sin(t * angle);

	}
	for (int i = 0; i < m_iCounter; i++)
	{
		CBrush brushblue(RGB(0, 0, 255));
		CBrush *pOldBrush = pDC->SelectObject(&brushblue);


		pDC->Ellipse(300+x + 15, 310+y + 20, 300+x - 20, 310+y - 20);

		Invalidate();
		pDC->SelectObject(pOldBrush);

	}



	// largest orbit rotation

	for (int i = 0; i<m_iCounter; i++)
	{
		angle = i;
		x = p * cos(t * angle);

		y = q * sin(t * angle);

	}
	for (int i = 0; i< m_iCounter;i++)
	{
		CBrush brushblack(RGB(0, 0, 0));
		CBrush *pOldBrush = pDC->SelectObject(&brushblack);


		pDC->Ellipse(305 + x + 20, 310 + y + 20, 305 + x - 20, 310 + y - 20);

		Invalidate();
		pDC->SelectObject(pOldBrush);


	}



}


// CCounterThreadingView printing

BOOL CCounterThreadingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCounterThreadingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCounterThreadingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CCounterThreadingView diagnostics

#ifdef _DEBUG
void CCounterThreadingView::AssertValid() const
{
	CView::AssertValid();
}

void CCounterThreadingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCounterThreadingDoc* CCounterThreadingView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCounterThreadingDoc)));
	return (CCounterThreadingDoc*)m_pDocument;
}
#endif //_DEBUG


// CCounterThreadingView message handlers


void CCounterThreadingView::OnThreadStart()
{
	pThread = AfxBeginThread(CTestThread::RunThreadFunction, this);
}


void CCounterThreadingView::OnThreadPause()
{
	pThread -> SuspendThread();
}


void CCounterThreadingView::OnThreadResume()
{
	pThread->ResumeThread();
}
