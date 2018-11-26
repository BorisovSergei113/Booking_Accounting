// Del_Order.cpp: файл реализации
//

#include "stdafx.h"
#include "Booking_Accounting.h"
#include "Del_Order.h"
#include "afxdialogex.h"
#include"GlobalMYSQL.h"

// Диалоговое окно Del_Order

IMPLEMENT_DYNAMIC(Del_Order, CDialogEx)

Del_Order::Del_Order(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DEL_ORDER, pParent)
	, m_BarCodeBook(_T(""))
	, m_NumOrder(_T(""))
	, m_NumReader(_T(""))
	, m_EndTrial(_T(""))
	, m_PasportReader(_T(""))
{

}

Del_Order::~Del_Order()
{
}

void Del_Order::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_BarCodeBook);
	DDX_Text(pDX, IDC_EDIT1, m_NumOrder);
	DDX_Text(pDX, IDC_EDIT3, m_NumReader);
	DDX_Control(pDX, IDC_EDIT4, m_Date);
	DDX_Text(pDX, IDC_EDIT4, m_EndTrial);
	DDX_Text(pDX, IDC_EDIT5, m_PasportReader);
}


BEGIN_MESSAGE_MAP(Del_Order, CDialogEx)
	ON_BN_CLICKED(IDOK, &Del_Order::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Del_Order::OnBnClickedCancel)
END_MESSAGE_MAP()


// Обработчики сообщений Del_Order
BOOL Del_Order::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CTime t = CTime::GetCurrentTime();
	CString s = t.Format("%Y-%m-%d");
	m_EndTrial = s;
	m_Date.SetWindowText(m_EndTrial);
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void Del_Order::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(TRUE);
	bool del_correct = false;
	if (m_NumReader.IsEmpty() && m_PasportReader.IsEmpty()) {
		del_correct = false;
		AfxMessageBox(_T("Нет данных о читателе!"), MB_ICONSTOP);
	}
	if (m_BarCodeBook.IsEmpty() && m_NumOrder.IsEmpty()) {
		del_correct = false;
		AfxMessageBox(_T("Нет данных о книге или о заказе !"), MB_ICONSTOP);
	}
	if (!m_NumReader.IsEmpty() && !m_BarCodeBook.IsEmpty()) {
		CString query = "UPDATE mydb.order o JOIN (SELECT o.id_order FROM books b JOIN mydb.order o ON b.id_book = o.id_book \
	WHERE  b.barcode = \"" + m_BarCodeBook + "\" AND   o.id_reader = \"" + m_NumReader + "\" AND  o.receive_date IS NULL ORDER BY o.give_date ASC LIMIT 1) AS temp \
	ON o.id_order = temp.id_order SET o.receive_date = \"" + m_EndTrial + "\";";
		del_correct = true;
		if (mysql_query(connection, query) != 0) {
			CString error_str = mysql_error(&mysql);
			AfxMessageBox(error_str, MB_ICONSTOP);
			del_correct = false;
		}
	}
	if (!m_NumReader.IsEmpty() && !m_NumOrder.IsEmpty()) {
		CString query = "UPDATE mydb.order SET mydb.order.receive_date=\"" + m_EndTrial + "\" \
	    WHERE mydb.order.id_reader = \"" + m_NumReader + "\" AND mydb.order.id_order =  \"" + m_NumOrder + "\" AND \
	    mydb.order.receive_date IS NULL;";
		del_correct = true;
		if (mysql_query(connection, query) != 0) {
			CString error_str = mysql_error(&mysql);
			AfxMessageBox(error_str, MB_ICONSTOP);
			del_correct = false;
		}
	}
	if (!m_PasportReader.IsEmpty() && !m_BarCodeBook.IsEmpty()) {
		CString query = "UPDATE mydb.order o JOIN (SELECT o.id_order FROM  mydb.order o  JOIN books b ON b.id_book = o.id_book \
       JOIN readers r ON o.id_reader = r.id_reader  WHERE  b.barcode =\"" + m_BarCodeBook + "\" AND r.pasport_number = \"" + m_PasportReader + "\" AND o.receive_date IS NULL \
       ORDER BY o.give_date ASC LIMIT 1) AS temp ON o.id_order = temp.id_order SET o.receive_date =\"" + m_EndTrial + "\";";
		del_correct = true;
		if (mysql_query(connection, query) != 0) {
			CString error_str = mysql_error(&mysql);
			AfxMessageBox(error_str, MB_ICONSTOP);
			del_correct = false;
		}
	}
	if (!m_PasportReader.IsEmpty() && !m_NumOrder.IsEmpty()) {
		CString query = "UPDATE mydb.order INNER JOIN readers ON mydb.order.id_reader = readers.id_reader \
		SET  mydb.order.receive_date = \"" + m_EndTrial + "\" WHERE  readers.pasport_number = \"" + m_PasportReader + "\" AND  mydb.order.id_reader = \"" + m_NumOrder + "\" \
	    AND  mydb.order.receive_date IS NULL;";
		del_correct = true;
		if (mysql_query(connection, query) != 0) {
			CString error_str = mysql_error(&mysql);
			AfxMessageBox(error_str, MB_ICONSTOP);
			del_correct = false;
		}
	}
	if (del_correct == true) {
		AfxMessageBox(_T("Заказ успешно удалён"),MB_ICONINFORMATION);
		CDialogEx::OnOK();
	}
}


void Del_Order::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnCancel();
}
