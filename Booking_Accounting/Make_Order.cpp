// Make_Order.cpp: файл реализации
//

#include "stdafx.h"
#include "Booking_Accounting.h"
#include "Make_Order.h"
#include "afxdialogex.h"
#include "GlobalMYSQL.h"


// Диалоговое окно Make_Order


void Make_Order::Fill_ctrl_listExample(CListCtrl& m_List) {  //вставка в таблицу 
	m_List.DeleteAllItems(); //Удалить все элементы
	int columns = mysql_num_fields(result);
	int nItem;
	CString index_column;
	while ((row = mysql_fetch_row(result)) != NULL) {
		nItem = m_List.InsertItem(m_List.GetItemCount(), row[0], -1); //индекс вставляемого элемента 
		for (int i = 0; i < columns; ++i) { //заполнение значениями строки
			m_List.SetItemText(nItem, i, row[i]);
		}
	}
	mysql_data_seek(result, 0); //перемещение указателя на первую строку
	return;
}

IMPLEMENT_DYNAMIC(Make_Order, CDialogEx)

Make_Order::Make_Order(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD_ORDER, pParent)
	, m_NameBook(_T(""))
	, m_AutorBook(_T(""))
	, m_YearBook(_T(""))
	, m_FIOreader(_T(""))
	, m_AddresReader(_T(""))
	, m_trelnumberReader(_T(""))
	, m_PassportnumberReader(_T(""))
	, m_StartRegistration(_T(""))
	, m_StartTrial(_T(""))
	, m_DaysTrial(_T(""))
	, m_idReader(_T(""))
{

}

Make_Order::~Make_Order()
{
}

void Make_Order::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_NameBook);
	DDX_Text(pDX, IDC_EDIT2, m_AutorBook);
	DDX_Text(pDX, IDC_EDIT6, m_YearBook);
	DDX_Control(pDX, IDC_LIST4, m_ListBookOrder);
	DDX_Text(pDX, IDC_EDIT8, m_FIOreader);
	DDX_Text(pDX, IDC_EDIT9, m_AddresReader);
	DDX_Text(pDX, IDC_EDIT10, m_trelnumberReader);
	DDX_Text(pDX, IDC_EDIT11, m_PassportnumberReader);
	DDX_Text(pDX, IDC_EDIT12, m_StartRegistration);
	DDX_Text(pDX, IDC_EDIT15, m_StartTrial);
	DDX_Text(pDX, IDC_EDIT14, m_DaysTrial);
	DDX_Text(pDX, IDC_EDIT13, m_idReader);
	DDX_Control(pDX, IDC_EDIT12, m_StartRegEdit);
	DDX_Control(pDX, IDC_EDIT15, m_StartTrialEdit);
	DDX_Control(pDX, IDC_EDIT13, m_NumberReader);
}


BEGIN_MESSAGE_MAP(Make_Order, CDialogEx)
	ON_BN_CLICKED(IDOK, &Make_Order::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &Make_Order::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &Make_Order::OnBnClickedCancel)
END_MESSAGE_MAP()


// Обработчики сообщений Make_Order

BOOL Make_Order::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	UpdateData(FALSE); //выводим в диалог 
	m_ListBookOrder.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE); //вид таблицы с возможностью выделения 
	m_ListBookOrder.InsertColumn(0, _T("№"), LVCFMT_LEFT, 50);
	m_ListBookOrder.InsertColumn(1, _T("Название"), LVCFMT_LEFT, 100);
	m_ListBookOrder.InsertColumn(2, _T("Автор"), LVCFMT_LEFT, 100);
	m_ListBookOrder.InsertColumn(3, _T("Жанр"), LVCFMT_LEFT, 100);
	m_ListBookOrder.InsertColumn(4, _T("Издательство"), LVCFMT_LEFT, 100);
	m_ListBookOrder.InsertColumn(5, _T("Стоимость"), LVCFMT_LEFT, 100);
	m_ListBookOrder.InsertColumn(6, _T("Год Издания"), LVCFMT_LEFT, 100);
	m_ListBookOrder.InsertColumn(7, _T("Стеллаж"), LVCFMT_LEFT, 100);
	m_ListBookOrder.InsertColumn(8, _T("Место на стеллаже"), LVCFMT_LEFT, 100);
	m_ListBookOrder.InsertColumn(9, _T("Количество"), LVCFMT_LEFT, 100);
	m_ListBookOrder.InsertColumn(10, _T("Штрихкод"), LVCFMT_LEFT, 100);
	CTime t = CTime::GetCurrentTime();
	CString s = t.Format("%Y-%m-%d");
	m_StartRegistration = m_StartTrial = s; // текущая дата
	m_StartTrialEdit.SetWindowText(m_StartTrial);
	m_StartRegEdit.SetWindowText(m_StartTrial);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void Make_Order::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(TRUE);
	CString idReader; //индекс читателя делающего заказ
	bool correct_order = false;
	if (!m_idReader.IsEmpty()) { //читатель уже находится в базе
		idReader = m_idReader;
		correct_order = true;
	}
	else {
		//Добавление нового пользователя
		if (!m_FIOreader.IsEmpty() && !m_AddresReader.IsEmpty() && !m_trelnumberReader.IsEmpty() && !m_PassportnumberReader.IsEmpty()) { //Проверка на правильность данных о читателе
			CStringArray arr;
			int curPos = 0;
			CString resToken = m_FIOreader.Tokenize(_T(" "), curPos);
			while (resToken != _T(""))
			{
				arr.Add(resToken);
				resToken = m_FIOreader.Tokenize(_T(" "), curPos);
			}
			if (arr.GetCount() == 3) { //проверка на корректность ФИО
				CString FirstName, SecondName, ThirdName;
				FirstName = arr[0];
				SecondName = arr[1];
				ThirdName = arr[2];
				CString query = "INSERT INTO readers VALUES (NULL, \"" + FirstName + "\"  ,  \"" + SecondName + "\"  ,  \"" + ThirdName + "\"  ,\
          \"" + m_AddresReader + "\"  ,  \"" + m_trelnumberReader + "\"  ,  \"" + m_PassportnumberReader + "\"  , \"" + m_StartRegistration + "\" );";
				if (mysql_query(connection, query) != 0) {
					CString error_str = mysql_error(&mysql);
					AfxMessageBox(error_str, MB_ICONSTOP);
					correct_order = false;
				}
				else correct_order = true;
				//Вывод о успешном добавлении читателя
				if (correct_order) {
					CString query2 = " SELECT * FROM readers WHERE pasport_number =  \"" + m_PassportnumberReader + "\" ;";
					mysql_query(connection, query2);
					result = mysql_store_result(connection);
					row = mysql_fetch_row(result);
					idReader = row[0];
					CString FIO = row[1];
					FIO += _T(" ");
					FIO += row[2];
					FIO += _T(" ");
					FIO += row[3];
					CString message = _T("Пользователь ") + FIO + _T(" был добавлен в БД с номером ") + idReader;
					m_NumberReader.SetWindowText(idReader); //подставить в поле номер читателя только-что добавленного читателя
					AfxMessageBox(message, MB_ICONINFORMATION);
				}
			}
			else { AfxMessageBox(_T("ФИО не корректно !"), MB_ICONSTOP); correct_order = false; }
		}
		else { AfxMessageBox(_T("Нет данных о читателе \n или они не полны !"), MB_ICONSTOP); correct_order = false; }
	}
	if (m_ListBookOrder.GetSelectedCount() == 0) { AfxMessageBox(_T("Книга не выбрана"), MB_ICONSTOP); correct_order = false; }

	if (m_DaysTrial.IsEmpty()) { AfxMessageBox(_T("Заполните поле: Дней аренды"), MB_ICONSTOP); correct_order = false; }

	if (correct_order) {
		POSITION pos = m_ListBookOrder.GetFirstSelectedItemPosition(); //позиция выделенного элемента
		if (pos != NULL) {  //если выделенный элемент присутствует 
			int Index = m_ListBookOrder.GetNextSelectedItem(pos);
			CString id_book = m_ListBookOrder.GetItemText(Index, 0); //получаем id выделенной книги
			CString query = "UPDATE books SET books.amount = books.amount - 1 WHERE books.id_book = \"" + id_book + "\" ;"; //проверка на наличие книги в хранилище 
			if (mysql_query(connection, query) != 0) {
				CString error_str = mysql_error(&mysql);
				AfxMessageBox(_T("Ошибка в количестве данной книги. Возможно её нет в хранилище.\n") + error_str, MB_ICONSTOP);
				correct_order = false;
			}
			if (correct_order) {
				CString create_order = "INSERT INTO mydb.order VALUES (NULL, \"" + idReader + "\",\"" + id_book + "\", \"" + m_StartTrial + "\", \"" + m_DaysTrial + "\", NULL );";
				if (mysql_query(connection, create_order) != 0) {
					CString error_str = mysql_error(&mysql);
					AfxMessageBox(_T("Ошибка в добавлении заказа. Проверьте номер читателя и дни арнеды книги.") + error_str, MB_ICONSTOP);
					correct_order = false;
				}
			}
		}
	}
	if (correct_order) {
		//выдача номера заказа
		CString query2 = "SELECT id_order FROM mydb.order ORDER BY id_order DESC LIMIT 1;";
		if (mysql_query(connection, query2) != 0) {
			CString error_str = mysql_error(&mysql);
			AfxMessageBox(error_str, MB_ICONSTOP);
		}
		result = mysql_store_result(connection);
		row = mysql_fetch_row(result);
		CString about_order = _T("Заказ ");
		about_order += _T(" сохранён под номером ");
		about_order += row[0];
		AfxMessageBox(about_order, MB_ICONINFORMATION);
		CDialogEx::OnOK();
	}
}


void Make_Order::OnBnClickedButton1()
{
	UpdateData(TRUE);
	CString query = " SELECT * FROM books WHERE title LIKE  \"%" + m_NameBook + "%\"  AND  autor LIKE  \"%" + m_AutorBook + "%\"   \
    AND year LIKE \"%" + m_YearBook + "%\" ;";
	if (mysql_query(connection, query) != 0) {
		CString error_str = mysql_error(&mysql);
		AfxMessageBox(error_str, MB_ICONSTOP);
	}
	else {
	result = mysql_store_result(connection);
	Fill_ctrl_listExample(m_ListBookOrder);
	}
}


void Make_Order::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnCancel();
}
