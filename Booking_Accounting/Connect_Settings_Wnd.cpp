// Connect_Settings_Wnd.cpp: файл реализации
//

#include "stdafx.h"
#include "Booking_Accounting.h"
#include "Connect_Settings_Wnd.h"
#include "afxdialogex.h"


// Диалоговое окно Connect_Settings_Wnd

IMPLEMENT_DYNAMIC(Connect_Settings_Wnd, CDialogEx)

Connect_Settings_Wnd::Connect_Settings_Wnd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_AddresServer_Val(_T("localhost"))
	, m_NameDB_Val(_T("mydb"))
	, m_Port_Val(_T("3306"))
	, m_Socket_Val(_T("0"))
	, m_Flag_Val(_T("0"))
	, m_NameUser_Val(_T("root"))
	, m_PasswordUser_Val(_T("1234"))
{

}

Connect_Settings_Wnd::~Connect_Settings_Wnd()
{
}

void Connect_Settings_Wnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_AddresServer);
	DDX_Text(pDX, IDC_EDIT1, m_AddresServer_Val);
	DDX_Control(pDX, IDC_EDIT4, m_NameDB);
	DDX_Text(pDX, IDC_EDIT4, m_NameDB_Val);
	DDX_Control(pDX, IDC_EDIT5, m_Port);
	DDX_Text(pDX, IDC_EDIT5, m_Port_Val);
	DDX_Control(pDX, IDC_EDIT6, m_Socket);
	DDX_Text(pDX, IDC_EDIT6, m_Socket_Val);
	DDX_Control(pDX, IDC_EDIT7, m_Flag);
	DDX_Text(pDX, IDC_EDIT7, m_Flag_Val);
	DDX_Control(pDX, IDC_EDIT2, m_NameUser);
	DDX_Text(pDX, IDC_EDIT2, m_NameUser_Val);
	DDX_Control(pDX, IDC_EDIT3, m_PasswordUser);
	DDX_Text(pDX, IDC_EDIT3, m_PasswordUser_Val);
}


BEGIN_MESSAGE_MAP(Connect_Settings_Wnd, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &Connect_Settings_Wnd::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &Connect_Settings_Wnd::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений Connect_Settings_Wnd
BOOL Connect_Settings_Wnd::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	UpdateData(FALSE);
	m_AddresServer.SetWindowText(m_AddresServer_Val);
	m_NameDB.SetWindowText(m_NameDB_Val);
	m_Port.SetWindowText(m_Port_Val);
	m_Socket.SetWindowText(m_Socket_Val);
	m_Flag.SetWindowText(m_Flag_Val);
	m_NameUser.SetWindowText(m_NameUser_Val);
	m_PasswordUser.SetWindowText(m_PasswordUser_Val);
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void Connect_Settings_Wnd::OnBnClickedCancel()
{
	AfxMessageBox(_T("Невозможна работа без подключения к БД!"), MB_ICONSTOP);
	CDialogEx::OnCancel();
}


void Connect_Settings_Wnd::OnBnClickedOk()
{
	UpdateData(TRUE);
	if (m_AddresServer_Val.IsEmpty() || m_NameDB_Val.IsEmpty() || m_Port_Val.IsEmpty() || m_Socket_Val.IsEmpty() || m_Flag_Val.IsEmpty() ||
		m_NameUser_Val.IsEmpty() || m_PasswordUser_Val.IsEmpty()) {
		AfxMessageBox(_T("Все поля должны быть не пустыми !"), MB_ICONSTOP);
	}
	else {
		CDialogEx::OnOK();
	}
}
