// AddBookWnd.cpp: файл реализации
//

#include "stdafx.h"
#include "Booking_Accounting.h"
#include "AddDelBookWnd.h"
#include "afxdialogex.h"
#include "GlobalMYSQL.h"

// Диалоговое окно AddBookWnd

IMPLEMENT_DYNAMIC(AddBookWnd, CDialogEx)

AddBookWnd::AddBookWnd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD_DEL_BOOK, pParent)
	, m_TitleEdit(_T(""))
	, m_AutorEdit(_T(""))
	, m_CategoryEdit(_T(""))
	, m_PublisherEdit(_T(""))
	, m_CostEdit(_T(""))
	, m_YearEdit(_T(""))
	, m_AmountEdit(_T(""))
	, m_BarcodeEdit(_T(""))
	, m_Rack(_T(""))
	, m_PlaceRack(_T(""))
{

}

AddBookWnd::~AddBookWnd()
{
}

void AddBookWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_TitleEdit);
	DDX_Text(pDX, IDC_EDIT2, m_AutorEdit);
	DDX_Text(pDX, IDC_EDIT3, m_CategoryEdit);
	DDX_Text(pDX, IDC_EDIT4, m_PublisherEdit);
	DDX_Text(pDX, IDC_EDIT5, m_CostEdit);
	DDX_Text(pDX, IDC_EDIT6, m_YearEdit);
	DDX_Text(pDX, IDC_EDIT7, m_AmountEdit);
	DDX_Text(pDX, IDC_EDIT8, m_BarcodeEdit);
	DDX_Text(pDX, IDC_EDIT16, m_Rack);
	DDX_Text(pDX, IDC_EDIT17, m_PlaceRack);
}


BEGIN_MESSAGE_MAP(AddBookWnd, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddBookWnd::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTT_DEL, &AddBookWnd::OnBnClickedButtDel)
END_MESSAGE_MAP()


// Обработчики сообщений AddBookWnd


void AddBookWnd::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(TRUE);
	CString query = ("INSERT INTO books ( title, autor, type, publisher, cost, year,rack,place_rack, amount, barcode) VALUES (\"" + m_TitleEdit + "\", \
     \"" + m_AutorEdit + "\" , \"" + m_CategoryEdit + "\",\"" + m_PublisherEdit + "\",\"" + m_CostEdit + "\",\"" + m_YearEdit + "\", \
     \"" + m_Rack+ "\",\"" + m_PlaceRack + "\",\"" + m_AmountEdit + "\",\"" + m_BarcodeEdit + "\" )");
	if (mysql_query(connection,query) != 0) {
		CString error_str = mysql_error(&mysql);
		AfxMessageBox(_T("Ошибка добавления\n") + error_str, MB_ICONSTOP);
	}
	else {
		AfxMessageBox(_T("Успешное добавление"), MB_ICONINFORMATION);
		CDialogEx::OnOK();
	}
}


void AddBookWnd::OnBnClickedButtDel()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(TRUE);
	CString query = ("DELETE FROM books WHERE barcode = ");
	query += m_BarcodeEdit; // добавить в запрос штрих код удаляемой книги
	if (mysql_query(connection, query) != 0) {
		CString error_str = mysql_error(&mysql);
		AfxMessageBox(_T("Ошибка удаления\n") + error_str, MB_ICONSTOP);
	}
	else {
		AfxMessageBox(_T("Успешное удаление "), MB_ICONINFORMATION);
		CDialogEx::OnOK();
	}
}

