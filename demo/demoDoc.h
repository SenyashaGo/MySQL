
// demoDoc.h: интерфейс класса CdemoDoc 
//


#pragma once
#include <string>

class CMyTreeView;
class CdemoView;
class CMyListView;

class CdemoDoc : public CDocument
{
protected: // создать только из сериализации
	CdemoDoc() noexcept;
	DECLARE_DYNCREATE(CdemoDoc)

// Атрибуты
public:
	bool clients, policies, agents;

	CdemoView* pView;
	CMyTreeView* pTree;
	CMyListView* pList;
	std::string tableName;
	MYSQL* conn;
// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CdemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
