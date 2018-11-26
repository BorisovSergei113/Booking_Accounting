#pragma once


// Диалоговое окно AddBookWnd

class AddBookWnd : public CDialogEx
{
	DECLARE_DYNAMIC(AddBookWnd)

public:
	AddBookWnd(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~AddBookWnd();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_DEL_BOOK};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CString m_TitleEdit;
	CString m_AutorEdit;
	CString m_CategoryEdit;
	CString m_PublisherEdit;
	CString m_CostEdit;
	CString m_YearEdit;
	CString m_AmountEdit;
	CString m_BarcodeEdit;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtDel();
	CString m_Rack;
	CString m_PlaceRack;
};
