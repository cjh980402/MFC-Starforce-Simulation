
// starforceDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "starforce.h"
#include "starforceDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio15();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CstarforceDlg 대화 상자



CstarforceDlg::CstarforceDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STARFORCE_DIALOG, pParent)
	, m_count(1)
	, m_level(150)
	, m_starcat(5)
	, m_initial(0)
	, m_goal(10)
	, m_salerate(0)
	, m_star(0)
	, m_nodest(100)
	, m_itemtype(0)
	, m_mvp(0)
	, m_pc(0)
	, m_free(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_INCHANT);
}

void CstarforceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_count);
	DDV_MinMaxInt(pDX, m_count, 1, 100000);
	DDX_Text(pDX, IDC_EDIT2, m_level);
	DDV_MinMaxInt(pDX, m_level, 1, 250);

	DDX_Text(pDX, IDC_EDIT3, m_starcat);
	DDV_MinMaxDouble(pDX, m_starcat, 0, 10);

	m_limit = ItemStarLimit();

	DDX_Text(pDX, IDC_EDIT4, m_initial);
	DDV_MinMaxInt(pDX, m_initial, 0, m_limit);
	DDX_Text(pDX, IDC_EDIT5, m_goal);
	DDV_MinMaxInt(pDX, m_goal, m_initial, m_limit);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
}

BEGIN_MESSAGE_MAP(CstarforceDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CstarforceDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_RADIO3, &CstarforceDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO7, &CstarforceDlg::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_BUTTON1, &CstarforceDlg::OnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO8, &CstarforceDlg::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_RADIO5, &CstarforceDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO2, &CstarforceDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO1, &CstarforceDlg::OnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO9, &CstarforceDlg::OnClickedRadio9)
	ON_COMMAND(IDC_RADIO10, &CstarforceDlg::OnRadio10)
	ON_COMMAND(IDC_RADIO11, &CstarforceDlg::OnRadio11)
	ON_COMMAND(IDC_RADIO12, &CstarforceDlg::OnRadio12)
	ON_BN_CLICKED(IDC_RADIO13, &CstarforceDlg::OnClickedRadio13)
	ON_COMMAND(IDC_RADIO14, &CstarforceDlg::OnRadio14)
	ON_BN_CLICKED(IDC_BUTTON3, &CstarforceDlg::OnBnClickedButton3)
	ON_COMMAND(IDC_RADIO4, &CstarforceDlg::OnRadio4)
	ON_BN_CLICKED(IDC_RADIO15, &CstarforceDlg::OnBnClickedRadio15)
END_MESSAGE_MAP()


// CstarforceDlg 메시지 처리기

BOOL CstarforceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	m_progress.SetRange(0, 100);

	CheckDlgButton(IDC_RADIO1, TRUE);
	CheckDlgButton(IDC_RADIO5, TRUE);
	CheckDlgButton(IDC_RADIO8, TRUE);
	CheckDlgButton(IDC_RADIO12, TRUE);
	CheckDlgButton(IDC_RADIO14, TRUE);
	CheckDlgButton(IDC_RADIO17, TRUE);

	GetDlgItem(IDC_STATIC2)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_2)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC6)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_6)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC7)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_7)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC8)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_8)->EnableWindow(FALSE);

	srand(time(NULL));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CstarforceDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CstarforceDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CstarforceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CstarforceDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// CDialogEx::OnOK();
}


BOOL CstarforceDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_ESCAPE) {
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


int CstarforceDlg::randomInt(int min, int max)
{
	// TODO: 여기에 구현 코드 추가.
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(min, max); // 균일 분포 난수

	return dist(mt);
}


void CstarforceDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CstarforceDlg::starforce_once(int now)
{
	// TODO: 여기에 구현 코드 추가.
	int pmprob[2][25][2] = { { { 95,0 },{ 90,0 },{ 85,0 },{ 85,0 },{ 80,0 },{ 75,0 },{ 70,0 },{ 65,0 },{ 60,0 },{ 55,0 },{ 50,0 },{ 45,0 },{ 40,0 },{ 35,0 },{ 30,0 },{ 30,3 },{ 30,3 },{ 30,3 },{ 30,4 },{ 30,4 },{ 30,10 },{ 30,10 },{ 3,20 },{ 2,30 },{ 1,40 } },
		{ { 50, 0 },{ 50, 0 },{ 45, 0 },{ 40, 0 },{ 40, 0 },{ 40, 3 },{ 40, 5 },{ 40, 7 },{ 40, 10 }, { 37, 15 },{ 35, 20 },{ 35, 25 },{ 3, 50 },{ 2, 50 },{ 1, 50 } }
	};
	// 확률을 백분율 수치로 저장

	int sucprob = 1000 * ((IsDlgButtonChecked(IDC_RADIO16) == TRUE) ?
		(pmprob[m_itemtype][m_star[now]][0] + m_starcat) : (pmprob[m_itemtype][m_star[now]][0] * (1 + m_starcat / 100)));
	// 백분율->십만분율 변환, 버튼 16=합적용, 버튼 17=곱적용
	int destprob = (100000 - sucprob) * (1000 * pmprob[m_itemtype][m_star[now]][1]) / 100000; // 파괴확률=조건부 확률, 백분율->십만분율 변환
	double saletemp = m_salerate;

	if (m_itemtype == 0 && m_star[now] <= 16) // mvp, pc방 할인끼리는 합적용, 30퍼 이벤트와는 곱적용
	{
		saletemp = saletemp + (m_mvp + m_pc) * (100 - saletemp) / 100;
	}

	if (m_checkdown[now] == -2) // 찬스타임
	{
		m_chance[now]++;
		m_star[now]++;
		m_checkdown[now] = 0;
		m_sum[now] = m_sum[now] + (100 - saletemp) * (meso(m_star[now], m_level) / 100);
		return;
	}
	if (m_itemtype == 0 && IsDlgButtonChecked(IDC_RADIO4) == TRUE && m_star[now] < 20 && m_star[now] % 5 == 0) // 100퍼 이벤
	{
		m_star[now]++;
		m_checkdown[now] = 0;
		m_sum[now] = m_sum[now] + (100 - saletemp) * (meso(m_star[now], m_level) / 100);
		return;
	}

	if (m_itemtype == 0 && IsDlgButtonChecked(IDC_CHECK1) == TRUE && m_star[now] >= 12 && m_star[now] < 15) // 15성까지 무료파방
	{
		m_sum[now] = m_sum[now] + (100 - saletemp) * (meso(m_star[now], m_level) / 100);
		destprob = 0;
	}
	else if (m_itemtype == 0 && destprob && m_star[now] >= m_nodest && m_star[now] <= 16) // 파괴방지, 추가 비용은 할인 미적용으로 100퍼 그대로 추가
	{
		m_sum[now] = m_sum[now] + (200 - saletemp) * (meso(m_star[now], m_level) / 100);
		destprob = 0;
	}
	else if (m_itemtype == 0) // 그 외 일반템인 경우
	{
		m_sum[now] = m_sum[now] + (100 - saletemp) * (meso(m_star[now], m_level) / 100);
	}
	else if (m_itemtype == 1) // 슈페리얼템
	{
		m_sum[now] = m_sum[now] + meso(m_star[now], m_level);
	}

	int i = randomInt(0, 99999); // [0,99999] 범위 난수 생성

	if (i < sucprob) // 성공
	{
		m_star[now] += (m_itemtype == 0 && IsDlgButtonChecked(IDC_RADIO15) == TRUE && m_star[now] <= 10) ? 2 : 1; // 1 + 1 이벤이면 2단계 상승
		m_checkdown[now] = 0;
	}
	else if (i < sucprob + destprob) // 파괴
	{
		if (m_itemtype == 0)
			m_star[now] = 12;
		else if (m_itemtype == 1)
			m_star[now] = 0;

		m_dest[now]++;
		m_checkdown[now] = 0;
	}
	else // 실패
	{
		if ((m_itemtype == 0 && m_star[now] > 15 && m_star[now] % 5) || (m_itemtype == 1 && m_star[now] > 0))
		{
			m_star[now]--;
			m_checkdown[now]--;
		}

		m_fail[now]++;
	}
}


int CstarforceDlg::meso(int star, int lev)
{
	// TODO: 여기에 구현 코드 추가.
	if (m_itemtype == 0) {
		double temp = 0;
		if (star >= 15) {
			temp = pow(star + 1, 2.7) / 200.0;
		}
		else if (star == 14) {
			temp = pow(star + 1, 2.7) / 75.0;
		}
		else if (star == 13) {
			temp = pow(star + 1, 2.7) / 110.0;
		}
		else if (star == 12) {
			temp = pow(star + 1, 2.7) / 150.0;
		}
		else if (star == 11) {
			temp = pow(star + 1, 2.7) / 220.0;
		}
		else if (star == 10) {
			temp = pow(star + 1, 2.7) / 400.0;
		}
		else {
			temp = (star + 1) / 25.0;
		}
		return floor((1000 + pow(lev, 3) * temp) / 100 + 0.5) * 100;
	}
	else {
		return floor(pow((lev / 10) * 10, 3.56) / 100 + 0.5) * 100;
	}
}


void CstarforceDlg::OnBnClickedRadio3() // 30퍼 세일 이벤트
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_salerate = 30;
}

void CstarforceDlg::OnRadio4() // 100퍼 이벤
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_salerate = 0;
}

void CstarforceDlg::OnBnClickedRadio5() // 세일 미적용
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_salerate = 0;
}

void CstarforceDlg::OnBnClickedRadio15() // 15성까지 무료 파방
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_free = 1;
}

void CstarforceDlg::OnBnClickedRadio7() // 15~17 파방
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nodest = 15;
}

void CstarforceDlg::OnBnClickedRadio8() // 파방 미적용
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nodest = 100;
}

void CstarforceDlg::OnClickedButton1() // 강화 버튼
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	reset();

	if (m_count > 1) {
		GetDlgItem(IDC_STATIC2)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_2)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC6)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_6)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC7)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_7)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC8)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_8)->EnableWindow(TRUE);
	}
	else if (m_count == 1) {
		GetDlgItem(IDC_STATIC2)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC6)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_6)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC7)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_7)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC8)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_8)->EnableWindow(FALSE);
	}

	if (CheckCondition() == TRUE) {
		m_sum = std::vector<unsigned long long>(m_count);
		m_star = std::vector<int>(m_count);
		m_checkdown = std::vector<int>(m_count);
		m_chance = std::vector<int>(m_count);
		m_fail = std::vector<int>(m_count);
		m_dest = std::vector<int>(m_count);
		m_progress.SetPos(0);

		for (int i = 0; i < m_count; i++)
		{
			m_star[i] = m_initial;
			m_fail[i] = 0;
			m_dest[i] = 0;
			m_chance[i] = 0;
			m_sum[i] = 0;
			m_checkdown[i] = 0;
			CString s;
			while (m_star[i] < m_goal)
			{
				starforce_once(i);
			}
			if ((100 * (i + 1)) / m_count != (100 * i) / m_count) { // 퍼센트가 달라질 때만 갱신을 수행
				s.Format(_T("표본 %d번째 완료, 현재 진행률 : %d%%"), i + 1, 100 * (i + 1) / m_count);
				SetDlgItemText(IDC_STATICCOUNT, s);
				m_progress.SetPos(100 * (i + 1) / m_count);
			}
		}

		AfxMessageBox(_T("입력한 조건의 강화를 완료하였습니다."), MB_ICONINFORMATION);
		showresult();
	}

}

CString CstarforceDlg::InsertCm(unsigned long long i)
{
	// TODO: 여기에 구현 코드 추가.
	CString B;
	B.Format(_T("%llu"), i);
	int count = 1;
	int len = B.GetLength();
	int temp = 0;
	while (count <= len + temp)
	{
		if (count == len)
			break;
		if ((len - count) % 3 == 0) {
			B.Insert(count + temp, _T(","));
			temp++;
		}
		count++;
	}
	return B;
}

CString CstarforceDlg::InsertCm(double d)
{
	// TODO: 여기에 구현 코드 추가.
	CString B;
	B.Format(_T("%.2f"), d);
	int count = 1;
	int len = B.GetLength() - 3;
	int temp = 0;
	while (count <= len + temp)
	{
		if (count == len)
			break;
		if ((len - count) % 3 == 0) {
			B.Insert(count + temp, _T(","));
			temp++;
		}
		count++;
	}
	return B;
}

unsigned long long CstarforceDlg::aver(std::vector<unsigned long long> array) // 큰 수 평균
{
	int count = array.size();
	unsigned long long aver = 0, sum = 0;
	for (int i = 0; i < count; i++)
		sum = sum + array[i];
	aver = sum / count;
	return aver;
}

double CstarforceDlg::aver(std::vector<int> array) // 작은 수 평균, 함수 오버로딩
{
	int count = array.size();
	double aver = 0, sum = 0;
	for (int i = 0; i < count; i++)
		sum = sum + array[i];
	aver = sum / count;
	return aver;
}

unsigned long long CstarforceDlg::stddev(std::vector<unsigned long long> array, unsigned long long aver) // 큰 수 표본표준편차
{
	int count = array.size();
	unsigned long long sum = 0, stddev = 0;
	for (int i = 0; i < count; i++)
		sum = sum + (array[i] - aver) * (array[i] - aver);
	stddev = sqrt(sum / (count - 1));
	return stddev;
}

void CstarforceDlg::showresult()
{
	// TODO: 여기에 구현 코드 추가.
	CString s;
	if (m_count == 1)
	{
		s = InsertCm(m_sum[0]) + _T(" 메소");
		SetDlgItemText(IDC_STATIC1, s);

		s = InsertCm((unsigned long long)m_chance[0]) + _T(" 회");
		SetDlgItemText(IDC_STATIC3, s);

		s = InsertCm((unsigned long long)m_fail[0]) + _T(" 회");
		SetDlgItemText(IDC_STATIC4, s);

		s = InsertCm((unsigned long long)m_dest[0]) + _T(" 회");
		SetDlgItemText(IDC_STATIC5, s);
	}
	else
	{
		unsigned long long aver_sum = aver(m_sum);

		s = InsertCm(aver_sum) + _T(" 메소"); // 평균
		SetDlgItemText(IDC_STATIC1, s);

		s = InsertCm(stddev(m_sum, aver_sum)) + _T(" 메소"); // 표준편차
		SetDlgItemText(IDC_STATIC2, s);

		std::sort(m_sum.begin(), m_sum.end()); // 오름차순 정렬 적용

		s = InsertCm(m_sum[m_count - 1]) + _T(" 메소"); // 최댓값
		SetDlgItemText(IDC_STATIC6, s);

		s = InsertCm(m_sum[0]) + _T(" 메소"); // 최솟값
		SetDlgItemText(IDC_STATIC7, s);

		s = InsertCm(m_count % 2 == 0 ? (m_sum[m_count / 2] + m_sum[m_count / 2 - 1]) / 2 : m_sum[m_count / 2]) + _T(" 메소"); // 중앙값
		SetDlgItemText(IDC_STATIC8, s);

		s = InsertCm(aver(m_chance)) + _T(" 회"); // 찬스타임
		SetDlgItemText(IDC_STATIC3, s);

		s = InsertCm(aver(m_fail)) + _T(" 회"); // 실패
		SetDlgItemText(IDC_STATIC4, s);

		s = InsertCm(aver(m_dest)) + _T(" 회"); // 파괴
		SetDlgItemText(IDC_STATIC5, s);
	}
}

void CstarforceDlg::OnClickedRadio1() // 일반템
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_itemtype = 0;

	GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);

	GetDlgItem(IDC_STATICEVENT)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATICNODEST)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATICMVP)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATICPC)->EnableWindow(TRUE);

	GetDlgItem(IDC_RADIO3)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO4)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO5)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO7)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO8)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO9)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO10)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO11)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO12)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO13)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO14)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO15)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);

	SetDlgItemText(IDC_STATICLEVELLIMIT, _T("(레벨 제한 범위는 1제~250제)"));

	reset();

}

void CstarforceDlg::OnBnClickedRadio2() // 타일런트
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_itemtype = 1;
	m_level = 150;

	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);

	GetDlgItem(IDC_STATICEVENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATICNODEST)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATICMVP)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATICPC)->EnableWindow(FALSE);

	GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO4)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO5)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO7)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO8)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO9)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO10)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO11)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO12)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO13)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO14)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO15)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);

	SetDlgItemText(IDC_STATICLEVELLIMIT, _T(""));

	reset();

	UpdateData(FALSE);
}

int CstarforceDlg::ItemStarLimit()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_itemtype == 0 && m_level >= 138)
		return 25;
	else if (m_itemtype == 0 && m_level >= 128)
		return 20;
	else if (m_itemtype == 0 && m_level >= 118)
		return 15;
	else if (m_itemtype == 0 && m_level >= 108)
		return 10;
	else if (m_itemtype == 0 && m_level >= 98)
		return 8;
	else if (m_itemtype == 0 && m_level >= 1)
		return 5;
	else if (m_itemtype == 1 && m_level >= 150)
		return 15;
	else if (m_itemtype == 1 && m_level >= 110)
		return 8;
	else if (m_itemtype == 1 && m_level >= 80)
		return 3;

}


void CstarforceDlg::reset()
{
	// TODO: 여기에 구현 코드 추가.
	m_limit = ItemStarLimit();
	CString s = _T("표본 0번째 완료, 현재 진행률 0%");
	SetDlgItemText(IDC_STATICCOUNT, s);
	s = _T("0 메소");
	SetDlgItemText(IDC_STATIC1, s);
	SetDlgItemText(IDC_STATIC2, s);
	SetDlgItemText(IDC_STATIC6, s);
	SetDlgItemText(IDC_STATIC7, s);
	SetDlgItemText(IDC_STATIC8, s);
	s = _T("0 회");
	SetDlgItemText(IDC_STATIC3, s);
	SetDlgItemText(IDC_STATIC4, s);
	SetDlgItemText(IDC_STATIC5, s);
}


void CstarforceDlg::OnClickedRadio9() // mvp 다이아
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_mvp = 10;
}


void CstarforceDlg::OnRadio10() // mvp 골드
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_mvp = 5;
}


void CstarforceDlg::OnRadio11() // mvp 실버
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_mvp = 3;
}


void CstarforceDlg::OnRadio12() // mvp 브론즈
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_mvp = 0;
}


void CstarforceDlg::OnClickedRadio13() // pc방 할인 적용
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pc = 5;
}


void CstarforceDlg::OnRadio14() // pc방 할인 미적용
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_pc = 0;
}


void CstarforceDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if (CheckCondition() == TRUE) {
		int limittemp = ItemStarLimit();
		CString s1, s2;
		if (m_itemtype == 0) {
			s1.Format(_T("<일반 아이템 %d제 강화 비용 (기본 -> 입력조건)>\n"), m_level);
		}
		else if (m_itemtype == 1) {
			s1.Format(_T("<슈페리얼 아이템 %d제 강화 비용>\n"), m_level);
		}

		unsigned long long mesotemp = 0;
		for (int i = 0; i < limittemp; i++) {
			s2.Format(_T("%2d성 강화시도 비용 : "), i + 1);
			mesotemp = meso(i, m_level);
			s2 += InsertCm(mesotemp) + _T(" 메소");

			int saletemp = m_salerate;
			if (m_itemtype == 0 && i <= 16) // 할인률 고려
			{
				saletemp = saletemp + (m_mvp + m_pc) * (100 - saletemp) / 100;
			}
			if (m_itemtype == 0 && IsDlgButtonChecked(IDC_RADIO4) == TRUE && i < 20 && i % 5 == 0) // 100퍼 이벤
			{
				mesotemp = (100 - saletemp) * (meso(i, m_level) / 100);
			}
			else if (m_itemtype == 0 && IsDlgButtonChecked(IDC_CHECK1) == TRUE && i < 15) // 15까지 무료 파방
			{
				mesotemp = (100 - saletemp) * (meso(i, m_level) / 100);
			}
			else if (m_itemtype == 0 && i >= m_nodest && i <= 16) // 파괴방지
			{
				mesotemp = (200 - saletemp) * (meso(i, m_level) / 100);
			}
			else if (m_itemtype == 0) // 그 외 일반템인 경우
			{
				mesotemp = (100 - saletemp) * (meso(i, m_level) / 100);
			}
			else if (m_itemtype == 1) // 슈페리얼템
			{
				mesotemp = meso(i, m_level);
			}

			if (m_itemtype == 0)
			{
				s2 += _T(" -> ") + InsertCm(mesotemp) + _T(" 메소\n");
			}
			else if (m_itemtype == 1)
			{
				s2 += _T("\n");
			}

			if ((i == 10 || i == 15) && i != limittemp && m_itemtype != 1) {
				s2 += _T("\n");
			}
			s1 += s2;
		}
		AfxMessageBox(s1, MB_ICONINFORMATION);
	}
}


BOOL CstarforceDlg::CheckCondition()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_goal >= m_initial && m_goal <= m_limit && m_count > 0 && m_count <= 100000 && m_level >= 1 && m_level <= 250 && m_starcat >= 0 && m_starcat <= 10 && m_initial >= 0 && m_initial <= m_limit) {
		return TRUE;
	}
	else
		return FALSE;
}

