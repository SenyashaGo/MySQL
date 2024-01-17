#pragma once
#include "afxdialogex.h"
#include "afxwin.h"
#include "CMyListView.h"

// Диалоговое окно CDeleteDialog

class CDeleteDialog : public CDialog
{
	DECLARE_DYNAMIC(CDeleteDialog)

public:
	CDeleteDialog(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CDeleteDialog();
	CMyListView* m_pListView;

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDeleteDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	void SetListView(CMyListView* pListView);
};
