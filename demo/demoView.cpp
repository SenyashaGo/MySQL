
// demoView.cpp: реализация класса CdemoView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "demo.h"
#endif

#include "demoDoc.h"
#include "demoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CdemoView

IMPLEMENT_DYNCREATE(CdemoView, CListView)

BEGIN_MESSAGE_MAP(CdemoView, CListView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

// Создание или уничтожение CdemoView

CdemoView::CdemoView() noexcept
{
	// TODO: добавьте код создания

}

CdemoView::~CdemoView()
{
}

BOOL CdemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}


void CdemoView::OnDraw(CDC* /*pDC*/)
{
	CdemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: добавьте здесь код отрисовки для собственных данных
}


void CdemoView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: ListView можно заполнить элементами посредством непосредственного обращения
	//  к элементам управления этого списка через вызов GetListCtr().
}


// Печать CdemoView

BOOL CdemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CdemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CdemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика CdemoView

#ifdef _DEBUG
void CdemoView::AssertValid() const
{
	CListView::AssertValid();
}

void CdemoView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CdemoDoc* CdemoView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CdemoDoc)));
	return (CdemoDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CdemoView
