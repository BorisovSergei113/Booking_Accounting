#pragma once


// Диалоговое окно Del_Order

class Del_Order : public CDialogEx
{
	DECLARE_DYNAMIC(Del_Order)

public:
	Del_Order(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~Del_Order();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEL_ORDER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_BarCodeBook;
	CString m_NumOrder;
	CString m_NumReader;
	CEdit m_Date;
	CString m_EndTrial;
	CString m_PasportReader;
};
