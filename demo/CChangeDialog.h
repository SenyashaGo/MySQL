#pragma once
#include "afxdialogex.h"
#include "CMyListView.h"
using namespace std;

// Диалоговое окно CChangeDialog

class CChangeDialog : public CDialog
{
	DECLARE_DYNAMIC(CChangeDialog)

public:
	CChangeDialog(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CChangeDialog();
	CMyListView* m_pListView;
	CString* selectedValues;
	int numColumns;

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CChangeDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void SetListView(CMyListView* pListView);
	void fillComboBox();
	CComboBox columnName;
	CEdit value;
	afx_msg void OnBnClickedButton1();
};
