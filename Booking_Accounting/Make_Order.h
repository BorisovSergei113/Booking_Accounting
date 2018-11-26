#pragma once


// Диалоговое окно Make_Order

class Make_Order : public CDialogEx
{
	DECLARE_DYNAMIC(Make_Order)

public:
	Make_Order(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~Make_Order();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_ORDER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_NameBook;
	CString m_AutorBook;
	CString m_YearBook;
	afx_msg void OnBnClickedButton1();
	CListCtrl m_ListBookOrder;
	afx_msg void OnBnClickedCancel();
	CString m_FIOreader;
	CString m_AddresReader;
	CString m_trelnumberReader;
	CString m_PassportnumberReader;
	CString m_StartRegistration;
	CString m_StartTrial;
	CString m_DaysTrial;
	CString m_idReader;
	CEdit m_StartRegEdit;
	CEdit m_StartTrialEdit;
};
