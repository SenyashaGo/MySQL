
// demoView.h: интерфейс класса CdemoView
//

#pragma once
#include "demoDoc.h"

class CdemoView : public CListView
{
protected: // создать только из сериализации
	CdemoView() noexcept;
	DECLARE_DYNCREATE(CdemoView)

// Атрибуты
public:
	CdemoDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // вызывается в первый раз после конструктора
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CdemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // версия отладки в demoView.cpp
inline CdemoDoc* CdemoView::GetDocument() const
   { return reinterpret_cast<CdemoDoc*>(m_pDocument); }
#endif

