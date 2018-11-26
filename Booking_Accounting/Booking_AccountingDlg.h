
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
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_myEditControl;
	CString m_editControlVal;
	CString ver_mysql;
	CString m_myEditvar2;
	CListCtrl m_ListBooks;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_ListReaders;
	afx_msg void OnBnClickedButAdddelbook();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonDelOrder();
};
