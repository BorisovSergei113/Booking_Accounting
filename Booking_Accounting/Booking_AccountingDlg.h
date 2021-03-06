
// Booking_AccountingDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CBookingAccountingDlg
class CBookingAccountingDlg : public CDialogEx
{
// Создание
public:
	CBookingAccountingDlg(CWnd* pParent = nullptr);	// стандартный конструктор
// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BOOKING_ACCOUNTING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV
// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButAdddelbook();
	afx_msg void OnBnClickedButtonMakeOrder();
	afx_msg void OnBnClickedButtonDelOrder();
	void Update_Promisers_List();
	bool ConnectionSQL();
	bool updateTable(CString str);
	void Fill_ctrl_list(CListCtrl& m_List);
	DECLARE_MESSAGE_MAP()

	//settings for connect MySQL server
	CString addres_database = "localhost";
	CString name_user = "root";
	CString password = "1234";
	CString name_database = "mydb";
	unsigned port = 3306;
	CString unix_socket = "0";
	unsigned clientflag = 0;

	CString m_editControlVal;
	CString ver_mysql;
	CListCtrl m_ListBooks;
	CListCtrl m_ListReaders;
	CListCtrl m_ListPromisers;
public:
	afx_msg void OnSetingsConnect();
	afx_msg void OnTestConnect();
};
