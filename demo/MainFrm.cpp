
// MainFrm.cpp: реализация класса CMainFrame
//

#include "pch.h"
#include "framework.h"
#include "demo.h"
#include "demoView.h"
#include "demoDoc.h"
#include "MainFrm.h"
#include "CMyTreeView.h"
#include "CMyListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // индикатор строки состояния
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// Создание или уничтожение CMainFrame

CMainFrame::CMainFrame() noexcept
{
	// TODO: добавьте код инициализации члена
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Не удалось создать панель инструментов\n");
		return -1;      // не удалось создать
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Не удалось создать строку состояния\n");
		return -1;      // не удалось создать
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Удалите эти три строки, если не собираетесь закреплять панель инструментов
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return TRUE;
}

// Диагностика CMainFrame

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// Обработчики сообщений CMainFrame



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: добавьте специализированный код или вызов базового класса
	m_wndSplitter.CreateStatic(this, 1, 2);

	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CMyTreeView), CSize(400, 0), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CMyListView), CSize(0, 0), pContext);

	m_wndSplitter.SetColumnInfo(0, 400, 10);

	SetActiveView((CView*)m_wndSplitter.GetPane(0, 1));

	((CdemoDoc*)GetActiveDocument())->pTree = (CMyTreeView*)m_wndSplitter.GetPane(0, 0);
	((CdemoDoc*)GetActiveDocument())->pList = (CMyListView*)m_wndSplitter.GetPane(0, 1);
	((CdemoDoc*)GetActiveDocument())->pTree->m_pList = (CMyListView*)m_wndSplitter.GetPane(0, 1); //связь указателя

	((CMyTreeView*)m_wndSplitter.GetPane(0, 0))->m_pDoc = ((CdemoDoc*)GetActiveDocument());
	((CMyListView*)m_wndSplitter.GetPane(0, 1))->m_pDoc = ((CdemoDoc*)GetActiveDocument());

	CdemoDoc* pDoc = ((CdemoDoc*)GetActiveDocument());

	int i = 0;
	// Получаем дескриптор соединения
	pDoc->conn = mysql_init(NULL);
	if (pDoc->conn == NULL)
	{
		// Если дескриптор не получен – выводим сообщение об ошибке
		AfxMessageBox(L"Error: can't create MySQL-descriptor!");
		//exit(1); //Если используется оконное приложение
	}
	// Подключаемся к серверу
	if (!mysql_real_connect(pDoc->conn, "localhost", "root", "0000", "insurance_company", NULL, NULL, 0))
	{
		AfxMessageBox(L"Error: can't connect to database!");
		return FALSE;
	}
	

	mysql_set_character_set(pDoc->conn, "utf8");


	return TRUE;
}
