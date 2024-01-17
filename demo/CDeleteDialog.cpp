// CDeleteDialog.cpp: файл реализации
//

#include "pch.h"
#include "demo.h"
#include "afxdialogex.h"
#include "CMyListView.h"
#include "CDeleteDialog.h"


// Диалоговое окно CDeleteDialog

IMPLEMENT_DYNAMIC(CDeleteDialog, CDialog)

CDeleteDialog::CDeleteDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CDeleteDialog, pParent)
{

}

CDeleteDialog::~CDeleteDialog()
{
}

void CDeleteDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDeleteDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDeleteDialog::OnBnClickedButton1)
END_MESSAGE_MAP()


// Обработчики сообщений CDeleteDialog


void CDeleteDialog::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений


	if (m_pListView != nullptr)
	{
		m_pListView->DeleteRow();
	}
}

void CDeleteDialog::SetListView(CMyListView* pListView)
{
	m_pListView = pListView;
}
