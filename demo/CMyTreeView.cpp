// CMyTreeView.cpp: файл реализации
//

#include "pch.h"
#include "demo.h"
#include "demoDoc.h"
#include "CMyTreeView.h"
#include "demoView.h"
#include "CMyListView.h"

// CMyTreeView

IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

CMyTreeView::CMyTreeView()
{

}

CMyTreeView::~CMyTreeView()
{
}

BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// Диагностика CMyTreeView

#ifdef _DEBUG
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// Обработчики сообщений CMyTreeView


int CMyTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SHOWSELALWAYS;

	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания

	return 0;
}

void CMyTreeView::FillTree()
{

	CTreeCtrl& tree = GetTreeCtrl();
	tree.DeleteAllItems();

	m_hAgents = tree.InsertItem(L"Агенты", -1, -1, NULL, TVI_FIRST);
	m_hPolicies = tree.InsertItem(L"Полисы", -1, -1, NULL, TVI_FIRST);
	m_hClients = tree.InsertItem(L"Клиенты", -1, -1, NULL, TVI_FIRST);

	tree.SetCheck(m_hAgents, m_pDoc->agents);
	tree.SetCheck(m_hPolicies, m_pDoc->policies);
	tree.SetCheck(m_hClients, m_pDoc->clients);

	tree.Expand(m_hAgents, TVE_EXPAND);
	tree.Expand(m_hPolicies, TVE_EXPAND);
	tree.Expand(m_hClients, TVE_EXPAND);

}

void CMyTreeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
		// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CTreeView::OnLButtonDown(nFlags, point);

	CTreeCtrl& tree = GetTreeCtrl();

	CRect rc;

	tree.GetItemRect(m_hAgents, &rc, false);
	if (rc.PtInRect(point)) {
		tree.SelectItem(m_hAgents);
		m_pList->DisplayTables("SELECT * FROM agents");
		m_pDoc->tableName = "agents";
	}

	tree.GetItemRect(m_hPolicies, &rc, false);
	if (rc.PtInRect(point)) {
		tree.SelectItem(m_hPolicies);
		m_pList->DisplayTables("SELECT * FROM policies");
		m_pDoc->tableName = "policies";
	}

	tree.GetItemRect(m_hClients, &rc, false);
	if (rc.PtInRect(point)) {
		tree.SelectItem(m_hClients);
		m_pList->DisplayTables("SELECT * FROM clients");
		m_pDoc->tableName = "clients";
	}

	if (tree.GetSelectedItem() == m_hAgents)
	{
		tree.SetCheck(m_hClients, false);
		tree.SetCheck(m_hPolicies, false);
	}
	else
	{
		tree.SetCheck(m_hAgents, false);
	}

	if (tree.GetSelectedItem() == m_hClients)
	{
		tree.SetCheck(m_hAgents, false);
		tree.SetCheck(m_hPolicies, false);
	}
	else
	{
		tree.SetCheck(m_hClients, false);
	}

	if (tree.GetSelectedItem() == m_hPolicies)
	{
		tree.SetCheck(m_hClients, false);
		tree.SetCheck(m_hAgents, false);
	}
	else
	{
		tree.SetCheck(m_hPolicies, false);
	}

	m_pDoc->agents = tree.GetCheck(m_hAgents);
	m_pDoc->policies = tree.GetCheck(m_hPolicies);
	m_pDoc->clients = tree.GetCheck(m_hClients);

}
