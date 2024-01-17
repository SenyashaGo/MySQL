#pragma once
#include "demoDoc.h"
#include <memory>
#define IDC_MYLIST  1000

// Просмотр CMyListView

class CMyListView : public CListView
{
	DECLARE_DYNCREATE(CMyListView)

protected:
	CMyListView();           // защищенный конструктор, используемый при динамическом создании
	virtual ~CMyListView();

public:
	CdemoDoc* m_pDoc;
	int clickedItemIndex;
	CString* columnNames;
	CString columnName;
	int num_fields;
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void DisplayTables(const char* req);
	void DeleteRow();
	void AddRow(CString str);
	void ChangeRow(CString str1, CString str2);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};
