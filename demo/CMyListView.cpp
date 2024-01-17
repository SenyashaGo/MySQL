// CMyListView.cpp: файл реализации
//

#include "pch.h"
#include "demo.h"
#include "CDeleteDialog.h"
#include "CAddDialog.h"
#include "CChangeDialog.h"
#include "CMyTreeView.h"
#include "CMyListView.h"
#include "MainFrm.h"
#include <string>
#include <memory>
#include "CAddDialog.h"
using namespace std;


// CMyListView

IMPLEMENT_DYNCREATE(CMyListView, CListView)

CMyListView::CMyListView()
{

}

CMyListView::~CMyListView()
{
	delete[] columnNames;
}

BEGIN_MESSAGE_MAP(CMyListView, CListView)
	ON_WM_CREATE()
	ON_WM_RBUTTONDOWN()
//	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
//	ON_WM_MBUTTONDBLCLK()
ON_WM_MBUTTONDOWN()
ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// Диагностика CMyListView

#ifdef _DEBUG
void CMyListView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// Обработчики сообщений CMyListView


void CMyListView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	TRACE(_T("CMyListView::OnInitialUpdate()\n"));


    CRect rect;
    GetClientRect(&rect);

}


int CMyListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	lpCreateStruct->style |= WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_EX_GRIDLINES;

	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания

	return 0;
}


void CMyListView::DisplayTables(const char* req) {

	CListCtrl& listCtrl = GetListCtrl();
	
	int numColumns = listCtrl.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < numColumns; ++i) {
		listCtrl.DeleteColumn(0); // удаляем предыдущие столбцы
	}
	listCtrl.DeleteAllItems(); // удаляем предыдущие данные

	MYSQL* conn = mysql_init(nullptr);
	if (!conn) {
		AfxMessageBox(L"Ошибка");
	}

	if (mysql_real_connect(conn, "localhost", "root", "0000", "insurance_company", NULL, NULL, 0) == nullptr) {
		AfxMessageBox(L"Ошибка");
	}

	mysql_query(conn, req);
	MYSQL_RES* result = mysql_store_result(conn);

	int rowIndex = 0; // индекс строки в списке
	MYSQL_ROW row; // строки запроса
	MYSQL_FIELD* fields; // поля запроса
	fields = mysql_fetch_fields(result);
	num_fields = mysql_num_fields(result);
	columnNames = new CString[num_fields];

	for (int i = 0; i < num_fields; ++i) { // для каждого поля добавляется столбец в список
		listCtrl.InsertColumn(i, CString(fields[i].name), LVCFMT_LEFT, 200);
		columnNames[i] = CString(fields[i].name); // имена столбцов сохраняются в массиве
	}

	while ((row = mysql_fetch_row(result))) { // каждая строка результата добавляется в список
		int nIndex = listCtrl.GetItemCount(); // получение текущего количества элементов в списке
		int itemIndex = listCtrl.InsertItem(nIndex, CString(row[0])); // вставка нового элемента в список 
		for (int i = 1; i < num_fields; ++i) {
			listCtrl.SetItem(nIndex, i, LVIF_TEXT, CString(row[i]), 0, 0, 0, 0); // вставляет текст в ячейку
		}
	}

	mysql_free_result(result); // освобождение памяти

}

void  CMyListView::DeleteRow() {

	CListCtrl& listCtrl = GetListCtrl();

	if (clickedItemIndex != -1) {

		CString cstrColumnName = columnNames[0];
		string columnID(CT2A(cstrColumnName.GetString()));


		wstring wstr = listCtrl.GetItemText(clickedItemIndex, 0).GetString();
		string id(wstr.begin(), wstr.end());

		// запрос DELETE 
		string query = "DELETE FROM " + m_pDoc->tableName + " WHERE " + columnID + " = '" + id + "'";

		MYSQL* conn = mysql_init(nullptr);
		if (!conn)
		{
			AfxMessageBox(L"Ошибка");
			return;
		}

		if (mysql_real_connect(conn, "localhost", "root", "0000", "insurance_company", NULL, NULL, 0) == nullptr)
		{
			AfxMessageBox(L"Ошибка");
			return;
		}

		if (mysql_query(conn, query.c_str()) != 0)
		{
			AfxMessageBox(L"Ошибка выполнения запроса");
		}

		mysql_close(conn);
		m_pDoc->pTree->FillTree();
		m_pDoc->pList->DisplayTables(string("SELECT * FROM " + m_pDoc->tableName).c_str());
	}

}

void CMyListView::AddRow(CString str)
{

	CString formattedString;

	// Проверка, что массив не равен nullptr
	if (columnNames != nullptr) {
		// Проход по массиву и формирование строки
		for (int i = 1; i < num_fields; ++i) {
			formattedString += columnNames[i];  // Добавление значения в строку
			if (i < num_fields - 1) {
				formattedString += _T(", ");  // Добавление запятой и пробела, если это не последний элемент
			}
		}
	}

	string str2 = CT2A(str);
	string str1 = CT2A(formattedString);

	string query = "INSERT INTO " + m_pDoc->tableName + " (" + str1 + ") VALUES (" + str2 + ");";

	MYSQL* conn = mysql_init(nullptr);
	if (!conn)
	{
		AfxMessageBox(L"Ошибка");
		return;
	}

	if (mysql_real_connect(conn, "localhost", "root", "0000", "insurance_company", NULL, NULL, 0) == nullptr)
	{
		AfxMessageBox(L"Ошибка");
		return;
	}

	if (mysql_query(conn, query.c_str()) != 0)
	{
		AfxMessageBox(L"Ошибка выполнения запроса");
	}

	mysql_close(conn);
	m_pDoc->pTree->FillTree();
	m_pDoc->pList->DisplayTables(string("SELECT * FROM " + m_pDoc->tableName).c_str());
}

void CMyListView::ChangeRow(CString str1, CString str2) 
{
	CListCtrl& listCtrl = GetListCtrl();
	string str3 = CT2A(str1);
	string str4 = CT2A(str2);
	CString cstrColumnName = columnNames[0];
	string columnID(CT2A(cstrColumnName.GetString()));
	wstring wstr = listCtrl.GetItemText(clickedItemIndex, 0).GetString();
	string id(wstr.begin(), wstr.end());

	string query = "UPDATE " + m_pDoc->tableName + " SET " + str3 + " = " + str4 + " WHERE " + columnID + " = " + id + ";";

	MYSQL* conn = mysql_init(nullptr);
	if (!conn)
	{
		AfxMessageBox(L"Ошибка");
		return;
	}

	if (mysql_real_connect(conn, "localhost", "root", "0000", "insurance_company", NULL, NULL, 0) == nullptr)
	{
		AfxMessageBox(L"Ошибка");
		return;
	}

	if (mysql_query(conn, query.c_str()) != 0)
	{
		AfxMessageBox(L"Ошибка выполнения запроса");
	}

	mysql_close(conn);
	m_pDoc->pTree->FillTree();
	m_pDoc->pList->DisplayTables(string("SELECT * FROM " + m_pDoc->tableName).c_str());
}

//void CMyListView::OnRButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
//
//	CListCtrl& listCtrl = GetListCtrl();
//
//	// определение индекса строки по координатам точки
//	LVHITTESTINFO hitTestInfo;
//	hitTestInfo.pt = point;
//	clickedItemIndex = listCtrl.HitTest(&hitTestInfo);
//
//	// проверка, что произошло нажатие на небходимую ячейку
//	if (clickedItemIndex != -1)
//	{
//		columnName = listCtrl.GetItemText(clickedItemIndex, 0);
//		CDeleteDialog dlg(this); // передаем указатель на текущий объект CMyListView
//		dlg.SetListView(this);   // устанавливаем указатель на текущий объект CMyListView в диалоговое окно
//		dlg.DoModal();
//	}
//
//	CListView::OnRButtonDown(nFlags, point);
//}
void CMyListView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CListCtrl& listCtrl = GetListCtrl();

	// определение индекса строки по координатам точки
	LVHITTESTINFO hitTestInfo;
	hitTestInfo.pt = point;
	int clickedItemIndex = listCtrl.HitTest(&hitTestInfo);

	// проверка, что произошло нажатие на необходимую ячейку
	if (clickedItemIndex != -1)
	{
		CString columnName = listCtrl.GetItemText(clickedItemIndex, 0);
		CString message;
		message.Format(_T("Вы хотите удалить строку с именем: %s?"), columnName);

		// Выводим AfxMessageBox с запросом на удаление строки
		if (AfxMessageBox(message, MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
		{
			// Пользователь нажал "OK", вызываем метод для удаления строки
			DeleteRow();
		}
	}

	CListView::OnRButtonDown(nFlags, point);
}



void CMyListView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CListCtrl& listCtrl = GetListCtrl();

	// определение индекса строки по координатам точки
	LVHITTESTINFO hitTestInfo;
	hitTestInfo.pt = point;
	clickedItemIndex = listCtrl.HitTest(&hitTestInfo);

	// проверка, что произошло нажатие на небходимую ячейку
	if (clickedItemIndex != -1)
	{
		columnName = listCtrl.GetItemText(clickedItemIndex, 0);
		CChangeDialog dlg(this); // передаем указатель на текущий объект CMyListView
		dlg.SetListView(this);   // устанавливаем указатель на текущий объект CMyListView в диалоговое окно
		dlg.DoModal();
	}

	CListView::OnMButtonDown(nFlags, point);
}


void CMyListView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CListCtrl& listCtrl = GetListCtrl();

	// определение индекса строки по координатам точки
	LVHITTESTINFO hitTestInfo;
	hitTestInfo.pt = point;
	clickedItemIndex = listCtrl.HitTest(&hitTestInfo);

	// проверка, что произошло нажатие на небходимую ячейку
	if (clickedItemIndex != -1)
	{
		columnName = listCtrl.GetItemText(clickedItemIndex, 0);
		CAddDialog dlg(this); // передаем указатель на текущий объект CMyListView
		dlg.SetListView(this);   // устанавливаем указатель на текущий объект CMyListView в диалоговое окно
		dlg.DoModal();
	}

	CListView::OnLButtonDblClk(nFlags, point);
}
