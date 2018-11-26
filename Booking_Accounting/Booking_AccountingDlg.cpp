
// Booking_AccountingDlg.cpp: файл реализации

#include "stdafx.h"
#include "Booking_Accounting.h"
#include "Booking_AccountingDlg.h"
#include "AddDelBookWnd.h"
#include "Make_Order.h"
#include "Del_Order.h"
//#include "mysql.h"
#include "GLOBALMYSQL.h"
#include <string>
#include <iostream>
#include <sstream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

 MYSQL *connection, mysql;
 int query_state;
 MYSQL_RES *result;
 MYSQL_ROW row;
 



bool updateTable(CString str) { //Запрос информации с нужной таблицы в БД
	CString query = _T("SELECT * FROM ") + str + _T(";");
	query_state = mysql_query(connection, query);
	if (query_state != 0) {
		CString s = mysql_error(&mysql);
		AfxMessageBox(s, MB_ICONSTOP);
		return false;
	}
	result = mysql_store_result(connection);
	return true;
}

bool ConnectionSQL() { //соединие с БД
	mysql_init(&mysql);
	/*connection = mysql_real_connect(&mysql,"host","user","password","database",port,"unix_socket",clientflag);*/
	connection = mysql_real_connect(&mysql, "localhost", "root", "1234", "mydb", 3306, 0, 0);
	if (connection == NULL) {
		CString s = mysql_error(&mysql);
		AfxMessageBox(s, MB_ICONSTOP);
		return false;
	}
	mysql_select_db(&mysql, "mydb");
	mysql_query(&mysql, "SET NAMES 'cp1251'"); // Задаем кодировку соединения
	if(updateTable(_T("books"))) mysql_dump_debug_info(&mysql); //  Записывать отладочную информацию в журнал сервера
	else return false;
	return true;
}

void Fill_ctrl_list(CListCtrl& m_List) {  //вставка в таблицу 
	m_List.DeleteAllItems(); //Удалить все элементы
	int columns = mysql_num_fields(result);
	int nItem;
	while ((row = mysql_fetch_row(result)) != NULL) {
		nItem = m_List.InsertItem(m_List.GetItemCount(), row[0], -1); //индекс вставляемого элемента 
		//CString index_column;
		//index_column.Format(_T("%d"), nItem+1); //индекс в таблице для пользователя
		//m_List.SetItemText(nItem, 0, index_column);
		for (int i = 0; i < columns; ++i) { //заполнение значениями строки
			m_List.SetItemText(nItem, i, row[i]);
		}
	}
	mysql_data_seek(result, 0); //перемещение указателя на первую строку
	return;
}

// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CBookingAccountingDlg



CBookingAccountingDlg::CBookingAccountingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BOOKING_ACCOUNTING_DIALOG, pParent)
	, m_editControlVal(_T(""))
	, ver_mysql(_T(""))
	, m_myEditvar2(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBookingAccountingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_myEditControl);
	DDX_Text(pDX, IDC_EDIT1, m_editControlVal);
	DDX_Text(pDX, Version_Mysql, ver_mysql);
	DDX_Text(pDX, IDC_EDIT2, m_myEditvar2);
	DDX_Control(pDX, IDC_LIST1, m_ListBooks);
	DDX_Control(pDX, IDC_LIST2, m_ListReaders);
}

BEGIN_MESSAGE_MAP(CBookingAccountingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CBookingAccountingDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CBookingAccountingDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CBookingAccountingDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CBookingAccountingDlg::OnBnClickedButton3)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CBookingAccountingDlg::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUT_ADD_DEL_BOOK, &CBookingAccountingDlg::OnBnClickedButAdddelbook)
	ON_BN_CLICKED(IDC_BUTTON_MAKE_ORDER, &CBookingAccountingDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_DEL_ORDER, &CBookingAccountingDlg::OnBnClickedButtonDelOrder)
END_MESSAGE_MAP()


// Обработчики сообщений CBookingAccountingDlg

BOOL CBookingAccountingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	//SetIcon(m_hIcon, FALSE);		// Мелкий значок

	ver_mysql = _T("Mysql ver ") + (CString)mysql_get_client_info(); //version mysqlclient

	UpdateData(FALSE); //выводим в диалог 
	// TODO: добавьте дополнительную инициализацию
	if (!ConnectionSQL()) return FALSE; //соеденинение с сервером 
	m_ListBooks.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE); //вид таблицы с возможностью выделения 
	m_ListBooks.InsertColumn(0, _T("№"), LVCFMT_LEFT, 50);
	m_ListBooks.InsertColumn(1, _T("Название"), LVCFMT_LEFT, 100);
	m_ListBooks.InsertColumn(2, _T("Автор"), LVCFMT_LEFT, 100);
	m_ListBooks.InsertColumn(3, _T("Жанр"), LVCFMT_LEFT, 100);
	m_ListBooks.InsertColumn(4, _T("Издательство"), LVCFMT_LEFT, 100);
	m_ListBooks.InsertColumn(5, _T("Стоимость"), LVCFMT_LEFT, 100);
	m_ListBooks.InsertColumn(6, _T("Год Издания"), LVCFMT_LEFT, 100);
	m_ListBooks.InsertColumn(7, _T("Стеллаж"), LVCFMT_LEFT, 100);
	m_ListBooks.InsertColumn(8, _T("Место на стеллаже"), LVCFMT_LEFT, 100);
	m_ListBooks.InsertColumn(9, _T("Количество"), LVCFMT_LEFT, 100);
	m_ListBooks.InsertColumn(10, _T("Штрихкод"), LVCFMT_LEFT, 100);
	Fill_ctrl_list(m_ListBooks); //заполнение таблицы

	m_ListReaders.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE);
	m_ListReaders.InsertColumn(0, _T("№"), LVCFMT_LEFT, 50);
	m_ListReaders.InsertColumn(1, _T("Имя"), LVCFMT_LEFT, 100);
	m_ListReaders.InsertColumn(2, _T("Фамилия"), LVCFMT_LEFT, 100);
	m_ListReaders.InsertColumn(3, _T("Отчество"), LVCFMT_LEFT, 100);
	m_ListReaders.InsertColumn(4, _T("Адрес"), LVCFMT_LEFT, 100);
	m_ListReaders.InsertColumn(5, _T("Телефон"), LVCFMT_LEFT, 150);
	m_ListReaders.InsertColumn(6, _T("Номер Паспорта"), LVCFMT_LEFT, 150);
	m_ListReaders.InsertColumn(7, _T("Дата Регистрации"), LVCFMT_LEFT, 100);
	updateTable("readers");
	Fill_ctrl_list(m_ListReaders);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CBookingAccountingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CBookingAccountingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CBookingAccountingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBookingAccountingDlg::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnCancel();
}


void CBookingAccountingDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	if (connection) {
		mysql_free_result(result);
		mysql_close(connection);
	}
	CDialogEx::OnOK();
}


void CBookingAccountingDlg::OnBnClickedButton2()
{
	row = mysql_fetch_row(result);
	 if (row != NULL) {
		  CString str1 = row[0];
		  CString str2 = row[1];
		  CString res = str1 + " " + str2;
		  m_editControlVal = res;
	 }
	 else {
		 m_editControlVal = "Rows ended";
		 m_myEditControl.EnableWindow(FALSE); //загружаем данные переменных в ресурсы
	 }
	 UpdateData(FALSE);
}


void CBookingAccountingDlg::OnBnClickedButton3()
{
	if(mysql_ping(connection) > 0) AfxMessageBox(_T("Connection with server lost !"), MB_ICONSTOP);
	UpdateData(TRUE);
	std::string str = m_myEditvar2;
	std::istringstream stream(str);
	std::string str1, str2;
	stream >> str1 >> str2;
	std::string buf("INSERT INTO books (id_book,title) VALUES (\"" + str1 + "\", \"" + str2 + "\")");
	if (mysql_query(connection, buf.c_str())) {
		CString error_str = mysql_error(&mysql);
		AfxMessageBox(error_str, MB_ICONSTOP);
	}
	UpdateData(FALSE);
	updateTable("books");
	Fill_ctrl_list(m_ListBooks);
}





void CBookingAccountingDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: добавьте свой код обработчика уведомлений
	POSITION pos = m_ListBooks.GetFirstSelectedItemPosition(); //позиция выделенного элемента
	if (pos != NULL) {
		int Index = m_ListBooks.GetNextSelectedItem(pos);
		CString index_str = m_ListBooks.GetItemText(Index, 0); //получаем id выделенной книги
		CString data;
		data = "SELECT readers.id_reader, readers.first_name, readers.second_name, readers.third_name, readers.home_addres, readers.tel_number, readers.pasport_number,\
		readers.data_registration, mydb.order.give_date, mydb.order.days \
		FROM mydb.order, readers WHERE mydb.order.id_book = \"" + index_str + "\" AND  mydb.order.id_reader = readers.id_reader \
        AND mydb.order.receive_date IS NULL";
		if (mysql_query(connection, data)) {
			CString error_str = mysql_error(&mysql);
			AfxMessageBox(error_str, MB_ICONSTOP);
		}
		result = mysql_store_result(connection);
		Fill_ctrl_list(m_ListReaders);
	}
	else AfxMessageBox(_T("Книга не выбрана !"));
	*pResult = 0;
}




void CBookingAccountingDlg::OnBnClickedButAdddelbook()
{
	AddBookWnd dlg;
	if (dlg.DoModal() == IDOK) {
		updateTable("books");
		Fill_ctrl_list(m_ListBooks);
	}
}





void CBookingAccountingDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	Make_Order dlg;
	dlg.DoModal();
}


void CBookingAccountingDlg::OnBnClickedButtonDelOrder()
{
	Del_Order dlg;
	dlg.DoModal();
	// TODO: добавьте свой код обработчика уведомлений
}
