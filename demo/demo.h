
// demo.h: основной файл заголовка для приложения demo
//
#pragma once
#include <mysql.h>
#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CdemoApp:
// Сведения о реализации этого класса: demo.cpp
//

class CdemoApp : public CWinApp
{
public:
	CdemoApp() noexcept;
	MYSQL* conn;

	bool bMySQLConnected = false;

// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDatabaseConnect();
};

extern CdemoApp theApp;
