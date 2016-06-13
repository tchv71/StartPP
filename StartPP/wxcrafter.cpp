//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: wxcrafter.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "wxcrafter.h"


// Declare the bitmap loading function
extern void wxC9ED9InitBitmapResources();

static bool bBitmapLoaded = false;


MainFrameBaseClass::MainFrameBaseClass(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxFrame(parent, id, title, pos, size, style)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC9ED9InitBitmapResources();
        bBitmapLoaded = true;
    }
    // Set icon(s) to the application/dialog
    wxIconBundle app_icons;
    {
        wxBitmap iconBmp = wxXmlResource::Get()->LoadBitmap(wxT("MaiinIcon"));
        wxIcon icn;
        icn.CopyFromBitmap(iconBmp);
        app_icons.AddIcon( icn );
    }
    SetIcons( app_icons );

    
    m_menuBar = new wxMenuBar(0);
    this->SetMenuBar(m_menuBar);
    
    m_menuFile = new wxMenu();
    m_menuBar->Append(m_menuFile, wxT("&Файл"));
    
    m_menuItemFileNew = new wxMenuItem(m_menuFile, wxID_NEW, wxT("Созд&ать\tCtrl-N"), wxT(""), wxITEM_NORMAL);
    m_menuItemFileNew->SetBitmap(wxArtProvider::GetBitmap(wxART_NEW, wxART_MENU, wxDefaultSize));
    m_menuFile->Append(m_menuItemFileNew);
    
    m_menuItemFileOpen = new wxMenuItem(m_menuFile, wxID_OPEN, wxT("&Открыть...\tCtrl-O"), wxT(""), wxITEM_NORMAL);
    m_menuItemFileOpen->SetBitmap(wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_MENU, wxDefaultSize));
    m_menuFile->Append(m_menuItemFileOpen);
    
    m_menuItemFileClose = new wxMenuItem(m_menuFile, wxID_CLOSE, wxT("&Закрыть"), wxT(""), wxITEM_NORMAL);
    m_menuItemFileClose->SetBitmap(wxArtProvider::GetBitmap(wxART_CLOSE, wxART_MENU, wxDefaultSize));
    m_menuFile->Append(m_menuItemFileClose);
    
    m_menuItemFileSave = new wxMenuItem(m_menuFile, wxID_SAVE, wxT("Со&хранить\tCtrl-S"), wxT(""), wxITEM_NORMAL);
    m_menuItemFileSave->SetBitmap(wxArtProvider::GetBitmap(wxART_FILE_SAVE, wxART_MENU, wxDefaultSize));
    m_menuFile->Append(m_menuItemFileSave);
    
    m_menuItemSaveAs = new wxMenuItem(m_menuFile, wxID_SAVEAS, wxT("Сохранить &как..."), wxT(""), wxITEM_NORMAL);
    m_menuItemSaveAs->SetBitmap(wxArtProvider::GetBitmap(wxART_FILE_SAVE_AS, wxART_MENU, wxDefaultSize));
    m_menuFile->Append(m_menuItemSaveAs);
    
    m_menuFile->AppendSeparator();
    
    m_menuItemFilePipeDesc = new wxMenuItem(m_menuFile, wxID_PIPE_DESC, wxT("Па&раметры расчета..."), wxT(""), wxITEM_NORMAL);
    m_menuFile->Append(m_menuItemFilePipeDesc);
    
    m_menuDatabases = new wxMenu();
    m_menuFile->AppendSubMenu(m_menuDatabases, wxT("&Базы данных"));
    
    m_menuItemPipeTable = new wxMenuItem(m_menuDatabases, wxID_ANY, wxT("&Таблица труб..."), wxT(""), wxITEM_NORMAL);
    m_menuDatabases->Append(m_menuItemPipeTable);
    
    m_menuItemArmatTable = new wxMenuItem(m_menuDatabases, wxID_ANY, wxT("Таблица &арматуры..."), wxT(""), wxITEM_NORMAL);
    m_menuDatabases->Append(m_menuItemArmatTable);
    
    m_menuItemTroinicsTable = new wxMenuItem(m_menuDatabases, wxID_TROINICS_TABLE, wxT("Таблица &тройников..."), wxT(""), wxITEM_NORMAL);
    m_menuDatabases->Append(m_menuItemTroinicsTable);
    
    m_menuImport = new wxMenu();
    m_menuFile->AppendSubMenu(m_menuImport, wxT("&Импорт"));
    
    m_menuItemImportDbf = new wxMenuItem(m_menuImport, wxID_ImportDbf, wxT("Import Dbf...\tCtrl-I"), wxT(""), wxITEM_NORMAL);
    m_menuImport->Append(m_menuItemImportDbf);
    
    m_menuItemImportScheme = new wxMenuItem(m_menuImport, wxID_ADD_SCHEM, wxT("&Вставка схемы"), wxT(""), wxITEM_NORMAL);
    m_menuImport->Append(m_menuItemImportScheme);
    
    m_menuExport = new wxMenu();
    m_menuFile->AppendSubMenu(m_menuExport, wxT("&Экспорт"));
    
    m_menuItemExportIni = new wxMenuItem(m_menuExport, wxID_EXPORT_INI, wxT("Старт *.ini"), wxT(""), wxITEM_NORMAL);
    m_menuExport->Append(m_menuItemExportIni);
    
    m_menuFile->AppendSeparator();
    
    m_menuItemFilePrint = new wxMenuItem(m_menuFile, wxID_PRINT, wxT("&Печать...\tCtrl-p"), wxT(""), wxITEM_NORMAL);
    m_menuItemFilePrint->SetBitmap(wxArtProvider::GetBitmap(wxART_PRINT, wxART_MENU, wxDefaultSize));
    m_menuFile->Append(m_menuItemFilePrint);
    
    m_menuItemPrintPreview = new wxMenuItem(m_menuFile, wxID_PREVIEW, wxT("Пред&варительный просмотр"), wxT(""), wxITEM_NORMAL);
    m_menuFile->Append(m_menuItemPrintPreview);
    
    m_menuItemFilePrintSetup = new wxMenuItem(m_menuFile, wxID_PRINT_SETUP, wxT("Нас&тройка печати..."), wxT(""), wxITEM_NORMAL);
    m_menuFile->Append(m_menuItemFilePrintSetup);
    
    m_menuFile->AppendSeparator();
    
    m_menuItemFileExit = new wxMenuItem(m_menuFile, wxID_EXIT, wxT("Exit\tAlt-X"), wxT("Quit"), wxITEM_NORMAL);
    m_menuItemFileExit->SetBitmap(wxArtProvider::GetBitmap(wxART_QUIT, wxART_MENU, wxDefaultSize));
    m_menuFile->Append(m_menuItemFileExit);
    
    m_menuEdit = new wxMenu();
    m_menuBar->Append(m_menuEdit, wxT("&Правка"));
    
    m_menuItemUndo = new wxMenuItem(m_menuEdit, wxID_UNDO, wxT("&Отменить\tCtrl-Z"), wxT(""), wxITEM_NORMAL);
    m_menuItemUndo->SetBitmap(wxArtProvider::GetBitmap(wxART_UNDO, wxART_MENU, wxDefaultSize));
    m_menuEdit->Append(m_menuItemUndo);
    
    m_menuItemRedo = new wxMenuItem(m_menuEdit, wxID_REDO, wxT("Верн&уть\tCtrl-Y"), wxT(""), wxITEM_NORMAL);
    m_menuItemRedo->SetBitmap(wxArtProvider::GetBitmap(wxART_REDO, wxART_MENU, wxDefaultSize));
    m_menuEdit->Append(m_menuItemRedo);
    
    m_menuEdit->AppendSeparator();
    
    m_menuItemCut = new wxMenuItem(m_menuEdit, wxID_CUT, wxT("&Вырезать\tCtrl-X"), wxT(""), wxITEM_NORMAL);
    m_menuItemCut->SetBitmap(wxArtProvider::GetBitmap(wxART_CUT, wxART_MENU, wxDefaultSize));
    m_menuEdit->Append(m_menuItemCut);
    
    m_menuItemCopy = new wxMenuItem(m_menuEdit, wxID_COPY, wxT("&Копировать\tCtrl-C"), wxT(""), wxITEM_NORMAL);
    m_menuItemCopy->SetBitmap(wxArtProvider::GetBitmap(wxART_COPY, wxART_MENU, wxDefaultSize));
    m_menuEdit->Append(m_menuItemCopy);
    
    m_menuItemPaste = new wxMenuItem(m_menuEdit, wxID_PASTE, wxT("Вст&авить\tCtrl-V"), wxT(""), wxITEM_NORMAL);
    m_menuItemPaste->SetBitmap(wxArtProvider::GetBitmap(wxART_PASTE, wxART_MENU, wxDefaultSize));
    m_menuEdit->Append(m_menuItemPaste);
    
    m_menuItemDel = new wxMenuItem(m_menuEdit, wxID_DELETE, wxT("У&далить участки...\tDel"), wxT(""), wxITEM_NORMAL);
    m_menuItemDel->SetBitmap(wxArtProvider::GetBitmap(wxART_DELETE, wxART_MENU, wxDefaultSize));
    m_menuEdit->Append(m_menuItemDel);
    
    m_menuEdit->AppendSeparator();
    
    m_menuItemSpusk = new wxMenuItem(m_menuEdit, wxID_Spusk, wxT("&Спускники и ответвления..."), wxT(""), wxITEM_NORMAL);
    m_menuEdit->Append(m_menuItemSpusk);
    
    m_menuNode = new wxMenu();
    m_menuEdit->AppendSubMenu(m_menuNode, wxT("&Узел"));
    
    m_menuItemPropMert = new wxMenuItem(m_menuNode, wxID_PROP_MERT, wxT("&Мертвая опора"), wxT(""), wxITEM_NORMAL);
    m_menuNode->Append(m_menuItemPropMert);
    
    m_menuItemPropSk = new wxMenuItem(m_menuNode, wxID_PROP_SK, wxT("&Скользящая опора"), wxT(""), wxITEM_NORMAL);
    m_menuNode->Append(m_menuItemPropSk);
    
    m_menuItemPropNapr = new wxMenuItem(m_menuNode, wxID_PROP_NAPR, wxT("&Направляющая опора"), wxT(""), wxITEM_NORMAL);
    m_menuNode->Append(m_menuItemPropNapr);
    
    m_menuNode->AppendSeparator();
    
    m_menuItemOtvIz = new wxMenuItem(m_menuNode, wxID_PROP_OTV_IZ, wxT("Отвод &изогнутый"), wxT(""), wxITEM_NORMAL);
    m_menuNode->Append(m_menuItemOtvIz);
    
    m_menuItemOtvSv = new wxMenuItem(m_menuNode, wxID_PROP_OTV_SV, wxT("Отвод &сварной"), wxT(""), wxITEM_NORMAL);
    m_menuNode->Append(m_menuItemOtvSv);
    
    m_menuItemArmat = new wxMenuItem(m_menuNode, wxID_PROP_ARMAT, wxT("&Арматура"), wxT(""), wxITEM_NORMAL);
    m_menuNode->Append(m_menuItemArmat);
    
    m_menuScheme = new wxMenu();
    m_menuEdit->AppendSubMenu(m_menuScheme, wxT("С&хема"));
    
    m_menuItemNewPipe = new wxMenuItem(m_menuScheme, wxID_NEW_PIPE, wxT("&Новый участок..."), wxT(""), wxITEM_NORMAL);
    m_menuScheme->Append(m_menuItemNewPipe);
    
    m_menuItemDelPipe = new wxMenuItem(m_menuScheme, wxID_DEL_PIPE, wxT("У&далить участки..."), wxT(""), wxITEM_NORMAL);
    m_menuScheme->Append(m_menuItemDelPipe);
    
    m_menuItemMultPipe = new wxMenuItem(m_menuScheme, wxID_MULT_PIPE, wxT("&Pазмножить участок..."), wxT(""), wxITEM_NORMAL);
    m_menuScheme->Append(m_menuItemMultPipe);
    
    m_menuItemNewNode = new wxMenuItem(m_menuScheme, wxID_NEW_NODE, wxT("Раз&бить участок..."), wxT(""), wxITEM_NORMAL);
    m_menuScheme->Append(m_menuItemNewNode);
    
    m_menuItemCopyPipeParams = new wxMenuItem(m_menuScheme, wxID_COPY_PIPE_PARAMS, wxT("Коп&ировать параметры участка..."), wxT(""), wxITEM_NORMAL);
    m_menuScheme->Append(m_menuItemCopyPipeParams);
    
    m_menuScheme->AppendSeparator();
    
    m_menuItemDelNode = new wxMenuItem(m_menuScheme, wxID_DEL_NODE, wxT("Уда&лить узел..."), wxT(""), wxITEM_NORMAL);
    m_menuScheme->Append(m_menuItemDelNode);
    
    m_menuItemMoveNode = new wxMenuItem(m_menuScheme, wxID_MOVE_NODE, wxT("П&eредвинуть узел..."), wxT(""), wxITEM_NORMAL);
    m_menuScheme->Append(m_menuItemMoveNode);
    
    m_menuItemRenumPipes = new wxMenuItem(m_menuScheme, wxID_RENUM_PIPES, wxT("Перену&меровать узлы"), wxT(""), wxITEM_NORMAL);
    m_menuScheme->Append(m_menuItemRenumPipes);
    
    m_menuRecord = new wxMenu();
    m_menuBar->Append(m_menuRecord, wxT("&Запись"));
    
    m_menuItemRecordFirst = new wxMenuItem(m_menuRecord, wxID_ANY, wxT("&Первая запись"), wxT(""), wxITEM_NORMAL);
    m_menuRecord->Append(m_menuItemRecordFirst);
    
    m_menuItemRecordPrevious = new wxMenuItem(m_menuRecord, wxID_ANY, wxT("Пр&едыдущая запись\tCtrl-<"), wxT(""), wxITEM_NORMAL);
    m_menuRecord->Append(m_menuItemRecordPrevious);
    
    m_menuItemRecordNext = new wxMenuItem(m_menuRecord, wxID_ANY, wxT("&Следующая запись\tCtrl-N"), wxT(""), wxITEM_NORMAL);
    m_menuRecord->Append(m_menuItemRecordNext);
    
    m_menuItemRecordLast = new wxMenuItem(m_menuRecord, wxID_RECORD_LAST, wxT("Последн&яя запись"), wxT(""), wxITEM_NORMAL);
    m_menuRecord->Append(m_menuItemRecordLast);
    
    m_menuView = new wxMenu();
    m_menuBar->Append(m_menuView, wxT("&Вид"));
    
    m_menuNavigation = new wxMenu();
    m_menuView->AppendSubMenu(m_menuNavigation, wxT("&Навигация"));
    
    m_menuItemViewZoomWin = new wxMenuItem(m_menuNavigation, wxID_ZOOM_WIN, wxT("&Увеличение рамкой"), wxT(""), wxITEM_NORMAL);
    m_menuNavigation->Append(m_menuItemViewZoomWin);
    
    m_menuItemViewPan = new wxMenuItem(m_menuNavigation, wxID_PAN, wxT("&Панорамирование"), wxT(""), wxITEM_NORMAL);
    m_menuNavigation->Append(m_menuItemViewPan);
    
    m_menuItemViewRotate = new wxMenuItem(m_menuNavigation, wxID_ROTATE, wxT("&Вращение"), wxT(""), wxITEM_NORMAL);
    m_menuNavigation->Append(m_menuItemViewRotate);
    
    m_menuItemViewSelect = new wxMenuItem(m_menuNavigation, wxID_SELECT, wxT("В&ыбор"), wxT(""), wxITEM_NORMAL);
    m_menuNavigation->Append(m_menuItemViewSelect);
    
    m_menuFilter = new wxMenu();
    m_menuView->AppendSubMenu(m_menuFilter, wxT("&Отображать"));
    
    m_menuItemViewNodeNums = new wxMenuItem(m_menuFilter, wxID_VIEW_NODE_NUMS, wxT("&Номера узлов"), wxT(""), wxITEM_NORMAL);
    m_menuFilter->Append(m_menuItemViewNodeNums);
    
    m_menuItemViewSizes = new wxMenuItem(m_menuFilter, wxID_VIEW_SIZES, wxT("&Размеры"), wxT(""), wxITEM_NORMAL);
    m_menuFilter->Append(m_menuItemViewSizes);
    
    m_menuItemViewAprof = new wxMenuItem(m_menuFilter, wxID_VIEW_APROF, wxT("&Углы в профиле"), wxT(""), wxITEM_NORMAL);
    m_menuFilter->Append(m_menuItemViewAprof);
    
    m_menuItemViewElements = new wxMenuItem(m_menuFilter, wxID_VIEW_ELEMENTS, wxT("&Элементы"), wxT(""), wxITEM_NORMAL);
    m_menuFilter->Append(m_menuItemViewElements);
    
    m_menuItemViewNodes = new wxMenuItem(m_menuFilter, wxID_VIEW_NODES, wxT("У&злы"), wxT(""), wxITEM_NORMAL);
    m_menuFilter->Append(m_menuItemViewNodes);
    
    m_menuView->AppendSeparator();
    
    m_menuItem283 = new wxMenuItem(m_menuView, wxID_SHOW_OGL, wxT("О&бъемный вид"), wxT(""), wxITEM_NORMAL);
    m_menuView->Append(m_menuItem283);
    
    m_menuHelp = new wxMenu();
    m_menuBar->Append(m_menuHelp, wxT("&Справка"));
    
    m_menuItemHelpAbout = new wxMenuItem(m_menuHelp, wxID_ABOUT, wxT("About..."), wxT(""), wxITEM_NORMAL);
    m_menuHelp->Append(m_menuItemHelpAbout);
    
    m_statusBar = new wxStatusBar(this, wxID_ANY, wxSTB_DEFAULT_STYLE|wxSTB_SIZEGRIP);
    m_statusBar->SetFieldsCount(1);
    this->SetStatusBar(m_statusBar);
    
    m_mgr = new wxAuiManager;
    m_mgr->SetManagedWindow( this );
    m_mgr->SetFlags( wxAUI_MGR_LIVE_RESIZE|wxAUI_MGR_RECTANGLE_HINT|wxAUI_MGR_TRANSPARENT_HINT|wxAUI_MGR_TRANSPARENT_DRAG|wxAUI_MGR_ALLOW_ACTIVE_PANE|wxAUI_MGR_ALLOW_FLOATING);
    m_mgr->GetArtProvider()->SetMetric(wxAUI_DOCKART_GRADIENT_TYPE, wxAUI_GRADIENT_NONE);
    
    m_auiBook = new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition, wxSize(250,250), wxAUI_NB_DEFAULT_STYLE|wxBK_DEFAULT);
    m_auiBook->SetName(wxT("m_auiBook"));
    
    m_mgr->AddPane(m_auiBook, wxAuiPaneInfo().Direction(wxAUI_DOCK_CENTER).Layer(0).Row(0).Position(0).BestSize(100,100).MinSize(100,100).MaxSize(100,100).CaptionVisible(false).MaximizeButton(false).CloseButton(true).MinimizeButton(false).PinButton(true));
    
    m_panel = new wxPanel(m_auiBook, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxTAB_TRAVERSAL);
    m_auiBook->AddPage(m_panel, wxT("Page"), false);
    
    wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
    m_panel->SetSizer(boxSizer);
    
    m_auibarView = new wxAuiToolBar(m_panel, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxAUI_TB_PLAIN_BACKGROUND|wxAUI_TB_DEFAULT_STYLE);
    m_auibarView->SetToolBitmapSize(wxSize(16,16));
    
    boxSizer->Add(m_auibarView, 0, wxALL|wxEXPAND, 5);
    
    m_auibarView->AddTool(wxID_ViewZoomIn, wxT("Zoom In"), wxXmlResource::Get()->LoadBitmap(wxT("ToolViewZoomIn")), wxNullBitmap, wxITEM_NORMAL, wxT("Zoom In"), wxT(""), NULL);
    
    m_auibarView->AddTool(wxID_ViewZoomOut, wxT("Zoom Out"), wxXmlResource::Get()->LoadBitmap(wxT("ToolViewZoomOut")), wxNullBitmap, wxITEM_NORMAL, wxT("Zoom Out"), wxT(""), NULL);
    
    m_auibarView->AddSeparator();
    
    m_auibarView->AddTool(wxID_ZOOM_ALL, wxT("Zoom All"), wxXmlResource::Get()->LoadBitmap(wxT("ToolViewZoomAll")), wxNullBitmap, wxITEM_NORMAL, wxT("Zoom All"), wxT(""), NULL);
    
    m_auibarView->AddSeparator();
    
    m_auibarView->AddTool(wxID_ViewZoomWindow, wxT("Zoom Window"), wxXmlResource::Get()->LoadBitmap(wxT("ToolViewZoomWin")), wxNullBitmap, wxITEM_RADIO, wxT("Zoom Window"), wxT(""), NULL);
    
    m_auibarView->AddTool(wxID_PAN, wxT("Pan"), wxXmlResource::Get()->LoadBitmap(wxT("ToolViewPan")), wxNullBitmap, wxITEM_RADIO, wxT("Pan"), wxT(""), NULL);
    
    m_auibarView->AddTool(wxID_ROTATE, wxT("Rotate"), wxXmlResource::Get()->LoadBitmap(wxT("ToolViewRotate")), wxNullBitmap, wxITEM_RADIO, wxT("Rotate"), wxT(""), NULL);
    
    m_auibarView->AddTool(wxID_SELECT, wxT("Select"), wxXmlResource::Get()->LoadBitmap(wxT("ToolViewSelect")), wxNullBitmap, wxITEM_RADIO, wxT("Select"), wxT(""), NULL);
    
    m_auibarView->AddSeparator();
    
    m_auibarView->AddTool(wxID_ANY, wxT("Predefined Views"), wxXmlResource::Get()->LoadBitmap(wxT("ToolViewPredefView")), wxNullBitmap, wxITEM_NORMAL, wxT("Predefined Views"), wxT(""), NULL);
    wxAuiToolBarItem* m_tbiViewTop = m_auibarView->FindToolByIndex(m_auibarView->GetToolCount()-1);
    if (m_tbiViewTop) {
        m_tbiViewTop->SetHasDropDown(true);
        m_menuViewPredef = new wxMenu;
        m_menuItemViewTop = new wxMenuItem(m_menuViewPredef, wxID_ViewTop, wxT("Top"), wxT(""), wxITEM_NORMAL);
        m_menuItemViewTop->SetBitmap(wxXmlResource::Get()->LoadBitmap(wxT("ToolViewPredefView")));
        m_menuViewPredef->Append(m_menuItemViewTop);
        
        m_dropdownMenus.insert(std::make_pair( m_tbiViewTop->GetId(), m_menuViewPredef) );
    }
    
    m_auibarView->AddTool(wxID_SHOW_OGL, wxT("3D"), wxXmlResource::Get()->LoadBitmap(wxT("ToolView3D")), wxNullBitmap, wxITEM_CHECK, wxT("3D"), wxT(""), NULL);
    m_auibarView->Realize();
    
    m_view = new CStartPPView(m_panel);
    boxSizer->Add(m_view, 1, wxALL|wxEXPAND, 5);
    
    m_auibarFilter = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxAUI_TB_PLAIN_BACKGROUND|wxAUI_TB_DEFAULT_STYLE|wxAUI_TB_HORZ_LAYOUT|wxAUI_TB_GRIPPER);
    m_auibarFilter->SetToolBitmapSize(wxSize(16,16));
    
    m_mgr->AddPane(m_auibarFilter, wxAuiPaneInfo().Name(wxT("Filters")).Caption(wxT("Filters")).Direction(wxAUI_DOCK_TOP).Layer(0).Row(0).Position(0).Fixed().CaptionVisible(true).MaximizeButton(false).CloseButton(true).MinimizeButton(false).PinButton(false).ToolbarPane());
    
    m_auibarFilter->AddTool(wxID_VIEW_NODE_NUMS, wxT("Номера узлов"), wxXmlResource::Get()->LoadBitmap(wxT("ToolFilterNodenum")), wxNullBitmap, wxITEM_CHECK, wxT("Номера узлов"), wxT(""), NULL);
    
    m_auibarFilter->AddTool(wxID_VIEW_SIZES, wxT("Размеры"), wxXmlResource::Get()->LoadBitmap(wxT("ToolFilterLength")), wxNullBitmap, wxITEM_CHECK, wxT("Размеры"), wxT(""), NULL);
    
    m_auibarFilter->AddTool(wxID_VIEW_APROF, wxT("Углы в профиле"), wxXmlResource::Get()->LoadBitmap(wxT("ToolFilterAprof")), wxNullBitmap, wxITEM_CHECK, wxT("Углы в профиле"), wxT(""), NULL);
    
    m_auibarFilter->AddTool(wxID_VIEW_ELEMENTS, wxT("Элементы"), wxXmlResource::Get()->LoadBitmap(wxT("ToolFilterElements")), wxNullBitmap, wxITEM_CHECK, wxT("Элементы"), wxT(""), NULL);
    
    m_auibarFilter->AddTool(wxID_VIEW_NODES, wxT("Узлы"), wxXmlResource::Get()->LoadBitmap(wxT("ToolFilterNodes")), wxNullBitmap, wxITEM_CHECK, wxT("Узлы"), wxT(""), NULL);
    m_auibarFilter->Realize();
    
    m_simpleBook = new wxSimplebook(this, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxBK_DEFAULT);
    m_simpleBook->SetName(wxT("m_simpleBook"));
    m_simpleBook->SetEffect(wxSHOW_EFFECT_NONE);
    
    m_mgr->AddPane(m_simpleBook, wxAuiPaneInfo().Caption(wxT("Свойства участка")).Direction(wxAUI_DOCK_LEFT).Layer(0).Row(0).Position(0).BestSize(600,100).CaptionVisible(true).MaximizeButton(false).CloseButton(false).MinimizeButton(false).PinButton(false));
    m_mgr->Update();
    
    m_simpleBookPanel = new wxPanel(m_simpleBook, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxTAB_TRAVERSAL);
    m_simpleBook->AddPage(m_simpleBookPanel, wxT("Page"), false);
    
    wxBoxSizer* boxSizer218 = new wxBoxSizer(wxVERTICAL);
    m_simpleBookPanel->SetSizer(boxSizer218);
    
    m_propWnd= new CPropertiesWnd(m_simpleBookPanel, wxID_ANY);
    boxSizer218->Add(m_propWnd, 1, wxALL|wxEXPAND, 5);
    
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DLIGHT));
    SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DLIGHT));
    
    #if wxVERSION_NUMBER >= 2900
    if(!wxPersistenceManager::Get().Find(m_auiBook)){
        wxPersistenceManager::Get().RegisterAndRestore(m_auiBook);
    } else {
        wxPersistenceManager::Get().Restore(m_auiBook);
    }
    #endif
    
    #if wxVERSION_NUMBER >= 2900
    if(!wxPersistenceManager::Get().Find(m_simpleBook)){
        wxPersistenceManager::Get().RegisterAndRestore(m_simpleBook);
    } else {
        wxPersistenceManager::Get().Restore(m_simpleBook);
    }
    #endif
    
    SetName(wxT("MainFrameBaseClass"));
    SetSize(800,600);
    if (GetSizer()) {
         GetSizer()->Fit(this);
    }
    if(GetParent()) {
        CentreOnParent(wxBOTH);
    } else {
        CentreOnScreen(wxBOTH);
    }
#if wxVERSION_NUMBER >= 2900
    if(!wxPersistenceManager::Get().Find(this)) {
        wxPersistenceManager::Get().RegisterAndRestore(this);
    } else {
        wxPersistenceManager::Get().Restore(this);
    }
#endif
    // Connect events
    this->Connect(m_menuItemImportDbf->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnImportDbf), NULL, this);
    this->Connect(m_menuItemFileExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnExit), NULL, this);
    this->Connect(m_menuItemRecordPrevious->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnRecordPrevious), NULL, this);
    this->Connect(m_menuItemRecordNext->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnRecordNext), NULL, this);
    this->Connect(m_menuItemHelpAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnAbout), NULL, this);
    this->Connect(wxID_ViewZoomIn, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrameBaseClass::OnZoomIn), NULL, this);
    this->Connect(wxID_ViewZoomOut, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrameBaseClass::OnZoomOut), NULL, this);
    this->Connect(wxID_ZOOM_ALL, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrameBaseClass::OnZoomAll), NULL, this);
    this->Connect(wxID_ViewZoomWindow, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrameBaseClass::OnZoomWindow), NULL, this);
    this->Connect(wxID_PAN, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrameBaseClass::OnPan), NULL, this);
    this->Connect(wxID_ROTATE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrameBaseClass::OnRotate), NULL, this);
    this->Connect(wxID_SELECT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrameBaseClass::OnSelect), NULL, this);
    this->Connect(m_menuItemViewTop->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnViewTop), NULL, this);
    this->Connect(wxID_SHOW_OGL, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrameBaseClass::OnShowOgl), NULL, this);
    
    this->Connect(wxID_ANY, wxEVT_COMMAND_AUITOOLBAR_TOOL_DROPDOWN, wxAuiToolBarEventHandler(MainFrameBaseClass::ShowAuiToolMenu), NULL, this);
}

MainFrameBaseClass::~MainFrameBaseClass()
{
    this->Disconnect(m_menuItemImportDbf->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnImportDbf), NULL, this);
    this->Disconnect(m_menuItemFileExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnExit), NULL, this);
    this->Disconnect(m_menuItemRecordPrevious->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnRecordPrevious), NULL, this);
    this->Disconnect(m_menuItemRecordNext->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnRecordNext), NULL, this);
    this->Disconnect(m_menuItemHelpAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnAbout), NULL, this);
    this->Disconnect(wxID_ViewZoomIn, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrameBaseClass::OnZoomIn), NULL, this);
    this->Disconnect(wxID_ViewZoomOut, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrameBaseClass::OnZoomOut), NULL, this);
    this->Disconnect(wxID_ZOOM_ALL, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrameBaseClass::OnZoomAll), NULL, this);
    this->Disconnect(wxID_ViewZoomWindow, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrameBaseClass::OnZoomWindow), NULL, this);
    this->Disconnect(wxID_PAN, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrameBaseClass::OnPan), NULL, this);
    this->Disconnect(wxID_ROTATE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrameBaseClass::OnRotate), NULL, this);
    this->Disconnect(wxID_SELECT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrameBaseClass::OnSelect), NULL, this);
    this->Disconnect(m_menuItemViewTop->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnViewTop), NULL, this);
    this->Disconnect(wxID_SHOW_OGL, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrameBaseClass::OnShowOgl), NULL, this);
    
    m_mgr->UnInit();
    delete m_mgr;

    std::map<int, wxMenu*>::iterator menuIter = m_dropdownMenus.begin();
    for( ; menuIter != m_dropdownMenus.end(); ++menuIter ) {
        wxDELETE( menuIter->second );
    }
    m_dropdownMenus.clear();

    this->Disconnect(wxID_ANY, wxEVT_COMMAND_AUITOOLBAR_TOOL_DROPDOWN, wxAuiToolBarEventHandler(MainFrameBaseClass::ShowAuiToolMenu), NULL, this);
}


void MainFrameBaseClass::ShowAuiToolMenu(wxAuiToolBarEvent& event)
{
    event.Skip();
    if (event.IsDropDownClicked()) {
        wxAuiToolBar* toolbar = wxDynamicCast(event.GetEventObject(), wxAuiToolBar);
        if (toolbar) {
            wxAuiToolBarItem* item = toolbar->FindTool(event.GetId());
            if (item) {
                std::map<int, wxMenu*>::iterator iter = m_dropdownMenus.find(item->GetId());
                if (iter != m_dropdownMenus.end()) {
                    event.Skip(false);
                    wxPoint pt = event.GetItemRect().GetBottomLeft();
                    pt.y++;
                    toolbar->PopupMenu(iter->second, pt);
                }
            }
        }
    }
}
ImageList::ImageList()
    : wxImageList(16, 16, true)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC9ED9InitBitmapResources();
        bBitmapLoaded = true;
    }
    
    {
        wxBitmap bmp;
        wxIcon icn;
        bmp = wxXmlResource::Get()->LoadBitmap(wxT("PropMo"));
        icn.CopyFromBitmap( bmp );
        this->Add( icn );
        m_bitmaps.insert( std::make_pair(wxT("PropMo"), bmp ) );
    }
    
    {
        wxBitmap bmp;
        wxIcon icn;
        bmp = wxXmlResource::Get()->LoadBitmap(wxT("PropNapr"));
        icn.CopyFromBitmap( bmp );
        this->Add( icn );
        m_bitmaps.insert( std::make_pair(wxT("PropNapr"), bmp ) );
    }
    
    {
        wxBitmap bmp;
        wxIcon icn;
        bmp = wxXmlResource::Get()->LoadBitmap(wxT("PropSk"));
        icn.CopyFromBitmap( bmp );
        this->Add( icn );
        m_bitmaps.insert( std::make_pair(wxT("PropSk"), bmp ) );
    }
    
    {
        wxBitmap bmp;
        wxIcon icn;
        bmp = wxXmlResource::Get()->LoadBitmap(wxT("PropOtvIz"));
        icn.CopyFromBitmap( bmp );
        this->Add( icn );
        m_bitmaps.insert( std::make_pair(wxT("PropOtvIz"), bmp ) );
    }
    
    {
        wxBitmap bmp;
        wxIcon icn;
        bmp = wxXmlResource::Get()->LoadBitmap(wxT("PropOtvSv"));
        icn.CopyFromBitmap( bmp );
        this->Add( icn );
        m_bitmaps.insert( std::make_pair(wxT("PropOtvSv"), bmp ) );
    }
    
    {
        wxBitmap bmp;
        wxIcon icn;
        bmp = wxXmlResource::Get()->LoadBitmap(wxT("PropArm"));
        icn.CopyFromBitmap( bmp );
        this->Add( icn );
        m_bitmaps.insert( std::make_pair(wxT("PropArm"), bmp ) );
    }
    
    {
        wxBitmap bmp;
        wxIcon icn;
        bmp = wxXmlResource::Get()->LoadBitmap(wxT("Select"));
        icn.CopyFromBitmap( bmp );
        this->Add( icn );
        m_bitmaps.insert( std::make_pair(wxT("Select"), bmp ) );
    }
    
    {
        wxBitmap bmp;
        wxIcon icn;
        bmp = wxXmlResource::Get()->LoadBitmap(wxT("Pan"));
        icn.CopyFromBitmap( bmp );
        this->Add( icn );
        m_bitmaps.insert( std::make_pair(wxT("Pan"), bmp ) );
    }
    
    {
        wxBitmap bmp;
        wxIcon icn;
        bmp = wxXmlResource::Get()->LoadBitmap(wxT("Rotate"));
        icn.CopyFromBitmap( bmp );
        this->Add( icn );
        m_bitmaps.insert( std::make_pair(wxT("Rotate"), bmp ) );
    }
    
    {
        wxBitmap bmp;
        wxIcon icn;
        bmp = wxXmlResource::Get()->LoadBitmap(wxT("Zoom"));
        icn.CopyFromBitmap( bmp );
        this->Add( icn );
        m_bitmaps.insert( std::make_pair(wxT("Zoom"), bmp ) );
    }
    
}

ImageList::~ImageList()
{
}
