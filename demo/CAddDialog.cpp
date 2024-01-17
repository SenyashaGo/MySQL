// CAddDialog.cpp: файл реализации
//

#include "pch.h"
#include "demo.h"
#include "afxdialogex.h"
#include "CMyListView.h"
#include "CAddDialog.h"


// Диалоговое окно CAddDialog

IMPLEMENT_DYNAMIC(CAddDialog, CDialog)

CAddDialog::CAddDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CAddDialog, pParent)
{

}

CAddDialog::~CAddDialog()
{
}

void CAddDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, columnName);
    DDX_Control(pDX, IDC_EDIT1, value);
}


BEGIN_MESSAGE_MAP(CAddDialog, CDialog)
    ON_BN_CLICKED(IDC_BUTTON2, &CAddDialog::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON1, &CAddDialog::OnBnClickedButton1)
    ON_BN_CLICKED(IDCANCEL, &CAddDialog::OnBnClickedCancel)
END_MESSAGE_MAP()

BOOL CAddDialog::OnInitDialog()
{

    if (!CDialog::OnInitDialog())
        return FALSE;

    fillComboBox();

    return TRUE;  // return TRUE unless you set the focus to a control
    // Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CAddDialog::SetListView(CMyListView* pListView)
{
    m_pListView = pListView;
}

void CAddDialog::fillComboBox()
{
    // указатель на ComboBox
    CComboBox* pComboBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO1));
    /*pComboBox->ModifyStyle(0, CBS_DROPDOWNLIST);*/
    pComboBox->ResetContent();

    // Получите названия колонок из вашей таблицы
    numColumns = m_pListView->num_fields;

    if (selectedValues != nullptr) {
        for (int i = 0; i < numColumns; ++i) {
            delete[] selectedValues[i];
        }
        delete[] selectedValues;
    }

    selectedValues = new CString [numColumns];

    // Сохраните значение в массиве selectedValues
    for (int i = 1; i < numColumns; ++i) {
        pComboBox->AddString(m_pListView->columnNames[i]);
        selectedValues[i] = _T("");
    }

    // устанавливаем выбранный по дефолту элемент 
    pComboBox->SetCurSel(0);
}


void CAddDialog::OnBnClickedButton2()
{
    // TODO: добавьте свой код обработчика уведомлений
    int selectedIndex = columnName.GetCurSel();

    if (selectedIndex != CB_ERR) {
        // Получите текст выбранного элемента
        CString selectedColumn;
        columnName.GetLBText(selectedIndex, selectedColumn);

        // Получите текст из EditControl
        CString editedValue;
        value.GetWindowText(editedValue);

        selectedValues[selectedIndex] = editedValue;

        if (selectedIndex != lastSelectedIndex) { // проверка, изменился ли индекс

            // Обновите последний сохраненный индекс
            lastSelectedIndex = selectedIndex;

            return CAddDialog::OnBnClickedButton2();
        }
    }
}


void CAddDialog::OnBnClickedButton1()
{
    CString formattedString;

    // Проверка, что массив не равен nullptr
    if (selectedValues != nullptr) {
        // Проход по массиву и формирование строки
        for (int i = 0; i < m_pListView->num_fields - 1; ++i) {
            if (!selectedValues[i].IsEmpty()) {
                formattedString += _T("'") + selectedValues[i] + _T("'");  // Добавление значения в строку
            }
            else
            {
                formattedString += _T("NULL");
            }
            if (i < m_pListView->num_fields - 2) {
                formattedString += _T(", ");  // Добавление запятой и пробела, если это не последний элемент
            }
        }
    }

    if (m_pListView != nullptr)
    {
        m_pListView->AddRow(formattedString);
    }
    // TODO: добавьте свой код обработчика уведомлений
}


void CAddDialog::OnBnClickedCancel()
{
    // TODO: добавьте свой код обработчика уведомлений
    CDialog::OnCancel();
}
