
// starforceDlg.h: 헤더 파일
//

#pragma once

#include <algorithm>
#include <random>
#include <vector>
#include <cmath>

// CstarforceDlg 대화 상자
class CstarforceDlg : public CDialogEx
{
// 생성입니다.
public:
	CstarforceDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STARFORCE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int randomInt(int, int);
	int m_count;
	int m_level;
	double m_starcat;
	int m_initial;
	int m_goal;
	afx_msg void OnBnClickedButton2();
	void starforce_once(int);
	std::vector<unsigned long long> m_sum;
	std::vector<int> m_star;
	std::vector<int> m_checkdown;
	std::vector<int> m_chance;
	std::vector<int> m_fail;
	std::vector<int> m_dest;
	int meso(int, int);
	int m_nodest;
	int m_salerate;
	int m_free;
	int m_mvp;
	int m_pc;
	int m_limit;
	CProgressCtrl m_progress;
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnClickedButton1();
	afx_msg void OnBnClickedRadio8();
	afx_msg void OnBnClickedRadio5();
	CString InsertCm(unsigned long long);
	CString InsertCm(double);
	unsigned long long aver(std::vector<unsigned long long>);
	double aver(std::vector<int>);//함수 오버로딩
	unsigned long long stddev(std::vector<unsigned long long>, unsigned long long);
	void showresult();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnClickedRadio1();
	int m_itemtype;
	int ItemStarLimit();
	void reset();
	afx_msg void OnClickedRadio9();
	afx_msg void OnRadio10();
	afx_msg void OnRadio11();
	afx_msg void OnRadio12();
	afx_msg void OnClickedRadio13();
	afx_msg void OnRadio14();
	afx_msg void OnBnClickedButton3();
	BOOL CheckCondition();
	afx_msg void OnRadio4();
	afx_msg void OnBnClickedRadio15();
};
