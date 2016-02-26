#pragma once
#include "afxwin.h"
#include <memory>
#include "Calculator.h"

class CCalculatorDlg : public CDialogEx
{
public:
	CCalculatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonEquals();
	afx_msg void OnBnClickedButtonC();
	afx_msg void OnBnClickedButtonDivide();
	afx_msg void OnBnClickedButtonMultiply();
	afx_msg void OnBnClickedButtonMinus();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	bool m_errorInput = false;
	const CString m_outputResetString{"0"};
	void resetOutput();
	void reset();
	void addDigit(char digit);
	void doOperation(Calculator::ActionType operation, bool handleNumber=true);
	void createHistoryText();

	Calculator m_calculator;
	CString m_output;
	CFont m_font;
	CFont m_historyFont;
	BOOL m_firstDigitEntered = FALSE;
	CEdit m_editResult;
	CButton m_button0;
	CButton m_button1;
	CButton m_button2;
	CButton m_button3;
	CButton m_button4;
	CButton m_button5;
	CButton m_button6;
	CButton m_button7;
	CButton m_button8;
	CButton m_button9;
	CButton m_buttonPlus;
	CButton m_buttonEquals;
	CButton m_buttonC;
	CButton m_buttonMinus;
	CButton m_buttonMultiply;
	CButton m_buttonDivide;
	CEdit m_editHistory;
	CString m_historyText;
	std::unique_ptr<CBrush> m_historyBkBrush;
	COLORREF m_historyBkColor;
};
