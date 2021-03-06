#pragma once


// Диалоговое окно Connect_Settings_Wnd

class Connect_Settings_Wnd : public CDialogEx
{
	DECLARE_DYNAMIC(Connect_Settings_Wnd)

public:
	Connect_Settings_Wnd(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~Connect_Settings_Wnd();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONNECT_SETTINGS};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
public:
	CEdit m_AddresServer;
	CString m_AddresServer_Val = _T("localhost");
	CEdit m_NameDB;
	CString m_NameDB_Val = "mydb";
	CEdit m_Port;
	CString m_Port_Val = "3306";
	CEdit m_Socket;
	CString m_Socket_Val = "0";
	CEdit m_Flag;
	CString m_Flag_Val = "0";
	CEdit m_NameUser;
	CString m_NameUser_Val = "root";
	CEdit m_PasswordUser;
	CString m_PasswordUser_Val = "1234";
};
