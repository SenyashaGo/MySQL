#pragma once
#include "afxdialogex.h"
#include "CMyListView.h"
using namespace std;

// Диалоговое окно CAddDialog

class CAddDialog : public CDialog
{
	DECLARE_DYNAMIC(CAddDialog)

public:
	CAddDialog(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CAddDialog();
	CMyListView* m_pListView;
	CString* selectedValues;
	int numColumns;
	int lastSelectedIndex = -1;

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_DIALOG };
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
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
};
