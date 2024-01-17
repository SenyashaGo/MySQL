// CChangeDialog.cpp: файл реализации
//

#include "pch.h"
#include "demo.h"
#include "afxdialogex.h"
#include "CMyListView.h"
#include "CChangeDialog.h"


// Диалоговое окно CChangeDialog

IMPLEMENT_DYNAMIC(CChangeDialog, CDialog)

CChangeDialog::CChangeDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CChangeDialog, pParent)
{

}

CChangeDialog::~CChangeDialog()
{
}

void CChangeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, columnName);
	DDX_Control(pDX, IDC_EDIT1, value);
}


BEGIN_MESSAGE_MAP(CChangeDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CChangeDialog::OnBnClickedButton1)
END_MESSAGE_MAP()


// Обработчики сообщений CChangeDialog
BOOL CChangeDialog::OnInitDialog()
{

    if (!CDialog::OnInitDialog())
        return FALSE;

    fillComboBox();

    return TRUE;  // return TRUE unless you set the focus to a control
    // Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CChangeDialog::SetListView(CMyListView* pListView)
{
    m_pListView = pListView;
}

void CChangeDialog::fillComboBox()
{
    // указатель на ComboBox
    CComboBox* pComboBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO1));

    pComboBox->ResetContent();

    // Получите названия колонок из вашей таблицы
    numColumns = m_pListView->num_fields;

    if (selectedValues != nullptr) {
        for (int i = 0; i < numColumns; ++i) {
            delete[] selectedValues[i];
        }
        delete[] selectedValues;
    }

    selectedValues = new CString[numColumns];

    // Сохраните значение в массиве selectedValues
    for (int i = 1; i < numColumns; ++i) {
        pComboBox->AddString(m_pListView->columnNames[i]);
        selectedValues[i] = _T("");
    }

    // устанавливаем выбранный по дефолту элемент 
    pComboBox->SetCurSel(0);
}

void CChangeDialog::OnBnClickedButton1() {
	// TODO: добавьте свой код обработчика уведомлений

    int selectedIndex = columnName.GetCurSel();
    CString selectedColumn, editedValue;;

    if (selectedIndex != CB_ERR) {
        // Получите текст выбранного элемента
        columnName.GetLBText(selectedIndex, selectedColumn);

        // Получите текст из EditControl
        value.GetWindowText(editedValue);

    }
    CString editedValue1 = _T("'") + editedValue + _T("'");


    if (m_pListView != nullptr)
    {
        m_pListView->ChangeRow(selectedColumn, editedValue1);
    }
}

