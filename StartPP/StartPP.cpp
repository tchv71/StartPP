// StartPP.cpp : Определяет поведение классов для приложения.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "StartPP.h"
#include "resource.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "StartPPDoc.h"
#include "StartPPView.h"
#include <Odbcinst.h>
#include <locale.h>

extern "C" int __stdcall _imp___vsnprintf(
	char* buffer,
	size_t count,
	const char* format,
	va_list argptr
)
{
	return vsnprintf(buffer, count, format, argptr);
}


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStartPPApp

BEGIN_MESSAGE_MAP(CStartPPApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CStartPPApp::OnAppAbout)
	// Стандартные команды по работе с файлами документов
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// Стандартная команда настройки печати
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_IMPORT_DBF, &CStartPPApp::OnImportDbf)
	END_MESSAGE_MAP()


// создание CStartPPApp

CStartPPApp::CStartPPApp()
{
	EnableHtmlHelp();
	m_bHiColorIcons = TRUE;

	// поддержка диспетчера перезагрузки
	//m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// Если приложение построено с поддержкой среды Common Language Runtime (/clr):
	//     1) Этот дополнительный параметр требуется для правильной поддержки работы диспетчера перезагрузки.
	//     2) В своем проекте для построения необходимо добавить ссылку на System.Windows.Forms.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: замените ниже строку идентификатора приложения строкой уникального идентификатора; рекомендуемый
	// формат для строки: ИмяКомпании.ИмяПродукта.СубПродукт.СведенияОВерсии
	//SetAppID(_T("StartPP.AppID.NoVersion"));

	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}

// Единственный объект CStartPPApp

CStartPPApp theApp;


// инициализация CStartPPApp

BOOL CStartPPApp::InitInstance()
{
	setlocale(LC_ALL, "");
	// InitCommonControlsEx() требуются для Windows XP, если манифест
	// приложения использует ComCtl32.dll версии 6 или более поздней версии для включения
	// стилей отображения. В противном случае будет возникать сбой при создании любого окна.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Выберите этот параметр для включения всех общих классов управления, которые необходимо использовать
	// в вашем приложении.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// Инициализация библиотек OLE
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();
#ifdef _M_AMD64
	BOOL RES = SQLConfigDataSource(nullptr,ODBC_ADD_DSN, _T("Microsoft Access Driver (*.mdb, *.accdb)"),
	                               _T("DSN=DBF\0")
	                               _T("DBQ=C:\\DBF\0")
	                               //_T("Driver=C:\\Windows\\system32\\odbcjt32.dll\0") 
	                               _T("FIL=MS Access\0\0") /* 
					_T("MaxScanRows=20\0\0")*/);

	RES = SQLConfigDataSource(nullptr,ODBC_ADD_DSN, _T("Microsoft Access dBASE Driver (*.dbf, *.ndx, *.mdx)"),
	                          _T("DSN=dBASE Files\0")
	                          _T("DBQ=C:\\DBF\0")
	                          _T("FIL=dBASE IV;\0\0"));

#else
		BOOL RES =SQLConfigDataSource(nullptr,ODBC_ADD_DSN, _T("Microsoft Access Driver (*.mdb)"), 
                   _T("DSN=DBF\0") 
				   _T("DBQ=C:\\DBF\0")
	//_T("Driver=C:\\Windows\\system32\\odbcjt32.dll\0") 
					_T("FIL=MS Access\0\0") /* 
					_T("MaxScanRows=20\0\0")*/);
		ASSERT(RES);
		RES =SQLConfigDataSource(nullptr,ODBC_ADD_DSN, _T("Microsoft dBase Driver (*.dbf)"), 
                   _T("DSN=dBASE Files\0") 
				   _T("DBQ=C:\\DBF\0")
					_T("FIL=dBASE IV;\0\0"));
		ASSERT(RES);


#endif
	//EnableTaskbarInteraction();

	// Для использования элемента управления RichEdit требуется метод AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// Стандартная инициализация
	// Если эти возможности не используются и необходимо уменьшить размер
	// конечного исполняемого файла, необходимо удалить из следующего
	// конкретные процедуры инициализации, которые не требуются
	// Измените раздел реестра, в котором хранятся параметры
	// TODO: следует изменить эту строку на что-нибудь подходящее,
	// например на название организации
	SetRegistryKey(_T("MIP3"));
	LoadStdProfileSettings(4); // Загрузите стандартные параметры INI-файла (включая MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
	                                                                 RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Зарегистрируйте шаблоны документов приложения. Шаблоны документов
	//  выступают в роли посредника между документами, окнами рамок и представлениями
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_StartPPTYPE,
	                                                    RUNTIME_CLASS(CStartPPDoc),
	                                                    RUNTIME_CLASS(CChildFrame), // настраиваемая дочерняя рамка MDI
	                                                    RUNTIME_CLASS(CStartPPView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// создайте главное окно рамки MDI
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;


	// Разрешить использование расширенных символов в горячих клавишах меню
	CMFCToolBar::m_bExtCharTranslation = TRUE;

	// Синтаксический разбор командной строки на стандартные команды оболочки, DDE, открытие файлов
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// Команды диспетчеризации, указанные в командной строке. Значение FALSE будет возвращено, если
	// приложение было запущено с параметром /RegServer, /Register, /Unregserver или /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	RegisterShellFileTypes();
	// Главное окно было инициализировано, поэтому отобразите и обновите его
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	setlocale(LC_ALL, "");
	return TRUE;
}

int CStartPPApp::ExitInstance()
{
	//TODO: обработайте дополнительные ресурсы, которые могли быть добавлены
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// обработчики сообщений CStartPPApp


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Данные диалогового окна
	enum
	{
		IDD = IDD_ABOUTBOX
	};

protected:
	void DoDataExchange(CDataExchange* pDX) override; // поддержка DDX/DDV

	// Реализация
protected:
	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog() override;
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	END_MESSAGE_MAP()

// Команда приложения для запуска диалога
void CStartPPApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CStartPPApp настройка методов загрузки и сохранения

void CStartPPApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_TABLE);

	//bNameValid = strName.LoadString(IDS_EXPLORER);
	//ASSERT(bNameValid);
	//GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CStartPPApp::LoadCustomState()
{
}

void CStartPPApp::SaveCustomState()
{
}

// обработчики сообщений CStartPPApp


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	DWORD dwHandle = 0;
	unsigned uiDataSize = 80;

	PWSTR pData = nullptr;
	WCHAR buff[80];
	// Get the version information block size,
	// then use it to allocate a storage buffer.
	CString strExeName = AfxGetApp()->m_pszExeName;
	strExeName += _T(".exe");
	DWORD dwSize = ::GetFileVersionInfoSize(LPCTSTR(strExeName), &dwHandle);
	void* pBuffer = malloc(dwSize);
	if (!pBuffer)
		return TRUE;
	// Get the version information block
	::GetFileVersionInfo(LPCTSTR(strExeName), 0, dwSize, pBuffer);
	//Use the version information block to obtain the file version.
	::VerQueryValue(pBuffer,
	                TEXT("\\StringFileInfo\\041904b0\\FileVersion"),
	                reinterpret_cast<void **>(&pData),
	                &uiDataSize);
	wcsncpy_s(buff, pData, uiDataSize + 1);
	pData = buff;
#ifdef _DEBUG
	wcscat_s(pData, uiDataSize + 1, _T("D"));
#endif
#ifdef _M_AMD64
	wcscat_s(pData, uiDataSize + 5, _T(" x64"));
#endif

	if (pData)
		GetDlgItem(IDC_ABOUT_VER)->SetWindowText(pData);
	free(pBuffer);
	// TODO: Add extra initialization here

	return TRUE; // return TRUE unless you set the focus to a control
}


void CStartPPApp::OnImportDbf()
{
	POSITION pos = m_pDocManager->GetFirstDocTemplatePosition();

	CDocTemplate* pDocTemplate = m_pDocManager->GetNextDocTemplate(pos);
	CStartPPDoc* pDoc = dynamic_cast<CStartPPDoc*>(pDocTemplate->OpenDocumentFile(nullptr));
	pDoc->OnImportDbf();
}

