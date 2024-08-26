// ChemistryPusher.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "ChemistryPusher.h"
#include<objbase.h>

struct listPasser {
    int listSize = 0;
    bool showMassFraction = false;
    std::wstring* massGet = nullptr, * numGet = nullptr,
        * elenameGet = nullptr, * eletolmassGet = nullptr;
    double* massFractionAcc = nullptr;
    listPasser(){}
    listPasser(int newSize) :listSize(newSize) {
        massGet = new std::wstring[listSize];
        numGet = new std::wstring[listSize];
        elenameGet = new std::wstring[listSize];
        eletolmassGet = new std::wstring[listSize];
        massFractionAcc = new double[listSize];
    }
    ~listPasser() {
        delete[] massGet;
        delete[] numGet;
        delete[] elenameGet;
        delete[] eletolmassGet;
        delete[] massFractionAcc;
    }
};

struct FontAndColorCreater {
    static const int members = 7;

    HFONT defaultFont = CreateFontW(25, 0, 0, 0, FW_ULTRABOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"宋体");//默认字体。用于static控件
    HBRUSH defaultBkColor = CreateSolidBrush(RGB(169, 72, 242));//默认背景。用于static控件
    HBRUSH readOnlyBkColor = CreateSolidBrush(RGB(255, 255, 255));//只读背景。用于只读编辑框控件
    HFONT inputFont = CreateFontW(25, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");//输入字体。用于edit控件
    HFONT buttonFont = CreateFontW(22, 0, 0, 0, FW_NORMAL + 60, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"宋体");//按钮字体。用于button控件

    HFONT FractionFont = CreateFontW(20, 0, 0, 0, FW_NORMAL + 60, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"微软雅黑");//质量分数文本框字体。用于成分表static和button控件
    HBRUSH FractionBkColor = CreateSolidBrush(RGB(255, 255, 255));//质量分数文本框背景。用于成分表static控件

    HGDIOBJ FontAndColors[members] = {
        defaultFont,defaultBkColor,readOnlyBkColor,inputFont,
        buttonFont,FractionFont,FractionBkColor
    };

    ~FontAndColorCreater() {
        for (int i = 0; i < members; i++) {
            DeleteObject(FontAndColors[i]);
        }
    }
};



// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
HWND g_hWnd;                                    //主窗口句柄
RECT g_rect;                                    //主窗口客户区rect

static int keepFractionPlaces = 1;              //用于记录用户所需质量分数保留小数位数

static bool AlreadyAlpha = true;                //用于输入字母或数字判断，以区分尺寸
static bool IngreBtnAble = false;               //用于判断用户点击成分表按钮后是否弹出对话框

MassCalc MC;                                    //MassCalc类初始化
FontAndColorCreater FCC;                        //FontAndColorCreater结构体初始化

LPWSTR titles[5] = {
    (LPWSTR)L"元素",
    (LPWSTR)L"单个相对原子质量",
    (LPWSTR)L"数量",
    (LPWSTR)L"总相对原子质量",
    (LPWSTR)L"质量分数"
};                                              //成分表列表视图文本

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    hIngredient(HWND, UINT, WPARAM, LPARAM);
static bool         onUserInputing(std::wstring& inputchar, int len);
static void         RLMInputVisualDealer(HWND hWnd, int wmId);
static listPasser*  prelistCalc();
static void         ListShow(listPasser* listData, HWND hWndParent);
static void         onCreateIngreDlgCombobox(HWND hDlg);
static void         ChangeFractionData(int number, HWND hListview, listPasser* listData);


//主窗口函数
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    //初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CHEMISTRYPUSHER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    //执行应用程序初始化
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CHEMISTRYPUSHER));

    MSG msg;

    //主消息循环
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//注册窗口类
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CHEMISTRYPUSHER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(RGB(169, 72, 242));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CHEMISTRYPUSHER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_CHEMISTRYPUSHER));

    WNDCLASSEXW IngreDlg = { 0 };

    IngreDlg.cbSize = sizeof(WNDCLASSEX);

    IngreDlg.style = CS_HREDRAW | CS_VREDRAW;
    IngreDlg.lpfnWndProc = hIngredient;
    IngreDlg.cbClsExtra = 0;
    IngreDlg.cbWndExtra = 0;
    IngreDlg.hInstance = hInstance;
    IngreDlg.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_CHEMISTRYPUSHER));
    IngreDlg.hCursor = LoadCursor(nullptr, IDC_ARROW);
    IngreDlg.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    IngreDlg.lpszMenuName = NULL;
    IngreDlg.lpszClassName = L"IngredientsDialog";
    IngreDlg.hIconSm = LoadIcon(IngreDlg.hInstance, MAKEINTRESOURCE(IDI_CHEMISTRYPUSHER));

    RegisterClassExW(&IngreDlg);
    return RegisterClassExW(&wcex);
}


//保存实例句柄并创建主窗口
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   
   return TRUE;
}



//窗口回调函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    
    switch (message)
    {
    case WM_CREATE: {
        g_hWnd = hWnd;

        //type=static,id=ID_OUTPUT_EQUATION,act=create
        CreateWindowW(L"static", L"请输入化学式：", WS_VISIBLE | WS_CHILD, 129, 100, 250, 30, hWnd, (HMENU)ID_OUTPUT_EQUATION, NULL, NULL);

        //type=edit,id=ID_INPUT_EQUATION,act=create
        CreateWindowW(L"edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER | ES_AUTOHSCROLL, 129, 150, 250, 30, hWnd, (HMENU)ID_INPUT_EQUATION, NULL, NULL);

        //type=static,id=ID_OUTPUT_NUM,act=create
        CreateWindowW(L"static", L"请输入数量：", WS_VISIBLE | WS_CHILD, 129, 200, 250, 30, hWnd, (HMENU)ID_OUTPUT_NUM, NULL, NULL);

        //type=edit,id=ID_INPUT_NUM,act=create
        CreateWindowW(L"edit", L"1", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER | ES_NUMBER, 129, 250, 250, 30, hWnd, (HMENU)ID_INPUT_NUM, NULL, NULL);

        //type=button,id=ID_CLICKBUTTON,act=create
        CreateWindowW(L"button", L"计算", WS_VISIBLE | WS_CHILD, 200, 320, 100, 40, hWnd, (HMENU)ID_CLICKBUTTON, NULL, NULL);

        //type=static,id=ID_OUTPUT_RESULT,act=create
        CreateWindowW(L"static", L"结果：", WS_VISIBLE | WS_CHILD, 529, 135, 250, 30, hWnd, (HMENU)ID_OUTPUT_RESULT, NULL, NULL);

        //type=edit,id=ID_OUTPUT_RESULTVAL,act=create
        CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER | ES_READONLY | ES_AUTOHSCROLL, 529, 185, 250, 30, hWnd, (HMENU)ID_OUTPUT_RESULTVAL, NULL, NULL);

        //type=button,id=ID_INGREDIENTS_LIST_BUTTON,act=create
        CreateWindowW(L"button", L"查看成分表", WS_VISIBLE | WS_CHILD, 549, 235, 150, 40, hWnd, (HMENU)ID_INGREDIENTS_LIST_BUTTON, NULL, NULL);

        //type=static,id=ALLID_OUTPUT,act=set font
        for (int iterID = ITERID_OUTPUT_BEGIN; iterID < ITERID_OUTPUT_END; iterID++) {
            SendMessageW(GetDlgItem(hWnd, iterID), WM_SETFONT, (WPARAM)FCC.defaultFont, TRUE);
        }

        //type=edit,id=ALLID_INPUT,act=set font
        for (int iterID = ITERID_INPUT_BEGIN; iterID < ITERID_INPUT_END; iterID++) {
            SendMessageW(GetDlgItem(hWnd, iterID), WM_SETFONT, (WPARAM)FCC.inputFont, TRUE);
        }

        //type=edit,id=ID_INPUT_EQUATION,act=limit text length
        SendMessageW(GetDlgItem(hWnd, ID_INPUT_EQUATION), EM_LIMITTEXT, 1000, UNUSED);

        //type=edit,id=ID_INPUT_NUM,act=limit text length
        SendMessageW(GetDlgItem(hWnd, ID_INPUT_NUM), EM_LIMITTEXT, 1000, UNUSED);

        //type=button,id=ID_BUTTON,act=set font
        SendMessageW(GetDlgItem(hWnd, ID_CLICKBUTTON), WM_SETFONT, (WPARAM)FCC.buttonFont, TRUE);
        SendMessageW(GetDlgItem(hWnd, ID_INGREDIENTS_LIST_BUTTON), WM_SETFONT, (WPARAM)FCC.buttonFont, TRUE);
        
        break;
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 分析菜单选择:
        switch (wmId)
        {
        case ID_INPUT_EQUATION:
        case ID_INPUT_NUM: {
            if (IngreBtnAble) {
                MC.clear();
                SetWindowText(GetDlgItem(hWnd, ID_OUTPUT_RESULTVAL), L"");
                IngreBtnAble = false;
            }
            
            RLMInputVisualDealer(hWnd, wmId);
            break;
        }
        case ID_CLICKBUTTON: {
            
            wchar_t* equation = new wchar_t[MAX_READSTRING];
            GetWindowText(GetDlgItem(hWnd, ID_INPUT_EQUATION), equation, MAX_READSTRING);
            std::wstring equaW(equation);
            delete[] equation;

            /*
            get<0>元素对应原子序数列表
            get<1>元素原子个数列表
            get<2>状态（返回值）
            get<3>返回字符串信息
            */
            auto ListGeneratingRet = MC.ListGenerating(equaW);
            
            int stateGet = std::get<2>(ListGeneratingRet);
            IngreBtnAble = false;
            switch (stateGet){
            case SUCCESS: {
                wchar_t* numGet = new wchar_t[MAX_READSTRING];
                int tmpNum = (int)SendMessage(GetDlgItem(hWnd, ID_INPUT_NUM), WM_GETTEXT, MAX_READSTRING, (LPARAM)numGet);
                if (numGet == L"" || !OverStar::isAllDigitsPWCHART(numGet, tmpNum)) {
                    MessageBox(hWnd, L"Error 800: Count error.", L"ChemistryPusher error", MB_OK);
                    break;
                }
                MC.eventualEleListGenerating(std::get<0>(ListGeneratingRet), std::get<1>(ListGeneratingRet));
                SendMessage(GetDlgItem(hWnd, ID_OUTPUT_RESULTVAL),
                    WM_SETTEXT, UNUSED,
                    (LPARAM)MC.fromDigitArrtoOppoWstring(MC.HighAccCalcTimes(MC.eventualTotalMassReturn(),MC.fromWstringtoOppoDigitArr(std::wstring(numGet)))).c_str());
                IngreBtnAble = true;
                delete[] numGet;
                break;
            }
            case MISMATCHED_BRACKETS:
            case RIGHT_BRACKET_RETURN:
                MessageBox(hWnd, L"Error 200: mismatched brackets.", L"ChemistryPusher error", MB_OK);
                break;
            case UNKNOWN_ELE: {
                MessageBox(hWnd, L"Error 300: unknown element exists.", L"ChemistryPusher error", MB_OK);
                break;
            }
            case IS_DIGIT_AFTER_LEFT_BRACKET: {
                MessageBox(hWnd, L"Error 400: there's a digit after the left bracket\nwhich is illegal.", L"ChemistryPusher error", MB_OK);
                break;
            }
            case EMPTY_IN_BRACKET: {
                MessageBox(hWnd, L"Error 500: there's nothing in the bracket.", L"ChemistryPusher error", MB_OK);
                break;
            }
            case UNNOWN_WRITING_GRAMMAR: {
                MessageBox(hWnd, L"Error 600: unknown writing grammar.", L"ChemistryPusher error", MB_OK);
                break;
            }
                
            default:
                break;
            }
            std::vector<int> orderListGet = std::get<0>(ListGeneratingRet);
            std::vector<std::vector<int>> countListGet = std::get<1>(ListGeneratingRet);

            break;
        }
        case ID_INGREDIENTS_LIST_BUTTON: {
            if (!IngreBtnAble)return FALSE;

            listPasser* listTmpDeliver = prelistCalc();

            HWND hIngreDlg = CreateWindow(L"IngredientsDialog", L"Chemistry Ingredients List", WS_SYSMENU | WS_DLGFRAME, CW_USEDEFAULT, 0, 600, 675, hWnd, NULL, hInst, (LPVOID)listTmpDeliver);

            if (!hIngreDlg)return FALSE;

            ShowWindow(hIngreDlg, TRUE);
            UpdateWindow(hIngreDlg);
            
            break;
        }
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case ID_BALANCER:
            MessageBox(hWnd, L"Log: The chemistry balncer is still developing.", L"Chemistry Pusher", MB_OK);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        GetClientRect(hWnd, &g_rect);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_CTLCOLORSTATIC: {
        HDC hh = (HDC)wParam;//设备上下文句柄
        HWND ll = (HWND)lParam;//控件句柄
        if (GetDlgCtrlID(ll) != ID_OUTPUT_RESULTVAL) {//非只读编辑框控件
            SetBkColor(hh, RGB(169, 72, 242));//文字背景色
            return (INT_PTR)FCC.defaultBkColor;
        }
        else {
            SetBkColor(hh, RGB(255, 255, 255));//文字背景色
            return (INT_PTR)FCC.readOnlyBkColor;
        }
        break;
    }
    case WM_GETMINMAXINFO: {
        auto minLimit = (MINMAXINFO*)lParam;
        minLimit->ptMinTrackSize.x = 508;
        minLimit->ptMinTrackSize.y = 100;
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


INT_PTR CALLBACK hIngredient(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE: {
        listPasser* listTmpGetter = (listPasser*)((CREATESTRUCT*)lParam)->lpCreateParams;
        EnableWindow(g_hWnd, FALSE);
        if (listTmpGetter->showMassFraction) {
            HWND FractionStatic = CreateWindow(L"static", L"质量分数保留小数位数：", WS_CHILD | WS_VISIBLE, 50, 40, 180, 20, hDlg, NULL, NULL, NULL);
            onCreateIngreDlgCombobox(hDlg);
            HWND FractionBtn = CreateWindow(L"button", L"确定", WS_CHILD | WS_VISIBLE | BS_CENTER, 300, 38, 55, 24, hDlg, (HMENU)ID_INGREDIENTS_LIST_FRACTION_OK, NULL, NULL);
            SendMessage(FractionStatic, WM_SETFONT, (WPARAM)FCC.FractionFont, TRUE);
            SendMessage(FractionBtn, WM_SETFONT, (WPARAM)FCC.FractionFont, TRUE);
        }
        ListShow(listTmpGetter, hDlg); 
        SetWindowLongPtr(hDlg, GWLP_USERDATA, (LONG_PTR)listTmpGetter);//存储listPasser数据
        break;
    }
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        switch (wmId) {
        case ID_INGREDIENTS_LIST_FRACTION_OK: {
            HWND hCombobox = GetDlgItem(hDlg, ID_INGREDIENTS_LIST_COMBOBOX);
            int chooseIndex = SendMessage(hCombobox, CB_GETCURSEL, UNUSED, UNUSED);
            int textLen = SendMessage(hCombobox, CB_GETLBTEXTLEN, (WPARAM)chooseIndex, (LPARAM)UNUSED);
            wchar_t* chooseNumber = new wchar_t[textLen + 1];
            SendMessage(hCombobox, CB_GETLBTEXT, (WPARAM)chooseIndex, (LPARAM)chooseNumber);
            listPasser* listTmpGetter = (listPasser*)(GetWindowLongPtr(hDlg, GWLP_USERDATA));
            ChangeFractionData(_wtoi(chooseNumber), GetDlgItem(hDlg, ID_INGREDIENTS_LISTVIEW), listTmpGetter);
            delete[] chooseNumber;
            break;
        }
        default:
            break;
        }
        break;
    }
    case WM_CTLCOLORSTATIC: {
        HDC hh = (HDC)wParam;
        SetBkColor(hh, RGB(255, 255, 255));
        return (INT_PTR)FCC.FractionBkColor;
        break;
    }
    case WM_CLOSE: {
        //delete listGetter及其成员
        listPasser* listGetter = (listPasser*)(GetWindowLongPtr(hDlg, GWLP_USERDATA));
        delete listGetter;
        EnableWindow(g_hWnd, TRUE);
        DestroyWindow(hDlg);
        break;
    }
    default:
        return DefWindowProc(hDlg, uMsg, wParam, lParam);
    }
    return 0;
}


//用于WM_COMMAND对输入框内容处理的函数；返回值：是否修改
static bool onUserInputing(std::wstring& inputchar, int len) {
    bool OpenLetter = false;
    bool Changed = false;
    for (int i = 0; i < len; i++) {
        if (!OpenLetter && OverStar::isAlphaWCHART(inputchar[i]))OpenLetter = true;
        else if (OverStar::isDigitWCHART(inputchar[i]) && OpenLetter) {
            inputchar[i] = smaller[inputchar[i]];
            Changed = true;
        }
        else if (inputchar[i] == L'·')OpenLetter = false;
        else if (inputchar[i] == L'`') {
            inputchar[i] = L'·';
            Changed = true;
        }
        else if (OverStar::isSmallWCHART(inputchar[i]) && !OpenLetter) {
            inputchar[i] = bigger[inputchar[i]];
            Changed = true;
        }
    }
    return Changed;
}


//处理RLM输入视觉效果
std::wstring OldEquationChar;
std::wstring OldNumChar;
static void RLMInputVisualDealer(HWND hWnd, int wmId) {
    wchar_t* inputwchart = new wchar_t[MAX_READSTRING];
    int ret = GetWindowText(GetDlgItem(hWnd, wmId), inputwchart, MAX_READSTRING);
    std::wstring inputchar(inputwchart);
    delete[] inputwchart;
    if (ret != 0 && ((wmId == ID_INPUT_EQUATION && inputchar != OldEquationChar)
        || (wmId == ID_INPUT_NUM && inputchar != OldNumChar))) {
        int nowEditLen = SendMessage(GetDlgItem(hWnd, wmId), WM_GETTEXTLENGTH, UNUSED, UNUSED);
        if (wmId == ID_INPUT_EQUATION)OldEquationChar = inputchar;
        else OldNumChar = inputchar;
        bool needReset = onUserInputing(inputchar, nowEditLen);
        if (needReset) {
            int place = HIWORD(SendMessage(GetDlgItem(hWnd, wmId), EM_GETSEL, UNUSED, UNUSED));
            SetWindowText(GetDlgItem(hWnd, wmId), inputchar.c_str());
            SendMessageW(GetDlgItem(hWnd, wmId), EM_SETSEL, place, place);
        }
    }
}


//成分表预先计算
static listPasser* prelistCalc() {
    auto listGet = MC.listDataReturn();
    int listSize = listGet.first.size();
    listPasser* lip = new listPasser(listSize);

    for (int row = 0; row < listSize; row++) {
        std::vector<int> tmp1 = MC.oppo_mass_map[listGet.first.at(row)];
        std::vector<int> tmp2 = listGet.second.at(row);
        lip->massGet[row] = MC.fromDigitArrtoOppoWstring(tmp1);
        lip->numGet[row] = MC.fromDigitArrtoOppoWstring(tmp2);
        lip->elenameGet[row] = MC.ele_map[listGet.first.at(row)];
        lip->eletolmassGet[row] = MC.fromDigitArrtoOppoWstring(MC.HighAccCalcTimes(tmp1, tmp2));
    }

    if (MC.eventualTotalMassReturn().size() <= 300) {
        lip->showMassFraction = true;
        std::wstring totalGet = MC.fromDigitArrtoOppoWstring(MC.eventualTotalMassReturn());
        for (int row = 0; row < listSize; row++) {
            lip->massFractionAcc[row] = _wtof(lip->eletolmassGet[row].c_str()) / _wtof(totalGet.c_str());
        }
    }
    
    return lip;
}


//成分表（视图列表）可视化
static void ListShow(listPasser* listData, HWND hWndParent) {

    HWND hIngreList = CreateWindow(WC_LISTVIEW, L"", WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_EDITLABELS | WS_BORDER, 50, 100, 500, 500, hWndParent, (HMENU)ID_INGREDIENTS_LISTVIEW, NULL, NULL);

    LVCOLUMN lvc;
    lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT;
    lvc.cx = 100;
    lvc.fmt = LVCFMT_CENTER;

    for (int iColumn = 0; iColumn < 4; iColumn++) {
        lvc.pszText = titles[iColumn];
        ListView_InsertColumn(hIngreList, iColumn, &lvc);
    }

    if (listData->showMassFraction) {
        lvc.pszText = titles[4];
        ListView_InsertColumn(hIngreList, 4, &lvc);
    }

    LVITEM lvi;
    lvi.mask = LVIF_TEXT;

    for (int row = 0; row < listData->listSize; row++) {

        lvi.iItem = row;

        lvi.iSubItem = 0;
        lvi.pszText = (LPWSTR)listData->elenameGet[row].c_str();
        ListView_InsertItem(hIngreList, &lvi);

        lvi.iSubItem = 1;
        lvi.pszText = (LPWSTR)listData->massGet[row].c_str();
        ListView_SetItem(hIngreList, &lvi);

        lvi.iSubItem = 2;
        lvi.pszText = (LPWSTR)listData->numGet[row].c_str();
        ListView_SetItem(hIngreList, &lvi);

        lvi.iSubItem = 3;
        lvi.pszText = (LPWSTR)listData->eletolmassGet[row].c_str();
        ListView_SetItem(hIngreList, &lvi);
    }

    if (listData->showMassFraction) {
        lvi.iSubItem = 4;

        for (int row = 0; row < listData->listSize; row++) {
            lvi.iItem = row;
            std::wstring get = MC.toPercentStr(listData->massFractionAcc[row], 1);
            lvi.pszText = (LPWSTR)get.c_str();
            ListView_SetItem(hIngreList, &lvi);
        }
    }
}


//创建成分表组合框控件
static void onCreateIngreDlgCombobox(HWND hDlg) {
    HWND FractionComboBox = CreateWindow(L"ComboBox", L"", CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_HASSTRINGS, 210, 40, 80, 500, hDlg, (HMENU)ID_INGREDIENTS_LIST_COMBOBOX, NULL, NULL);
    SendMessage(FractionComboBox, CB_ADDSTRING, UNUSED, (LPARAM)L"1");
    SendMessage(FractionComboBox, CB_ADDSTRING, UNUSED, (LPARAM)L"2");
    SendMessage(FractionComboBox, CB_ADDSTRING, UNUSED, (LPARAM)L"3");
    SendMessage(FractionComboBox, CB_ADDSTRING, UNUSED, (LPARAM)L"4");
    SendMessage(FractionComboBox, CB_ADDSTRING, UNUSED, (LPARAM)L"5");

    SendMessage(FractionComboBox, CB_SETCURSEL, 0, UNUSED);
}


//显式改变质量分数保留位数
static void ChangeFractionData(int number, HWND hListview, listPasser* listData) {
    
    LVITEM lvi;
    lvi.mask = LVIF_TEXT;
    lvi.iSubItem = 4;
    for (int row = 0; row < listData->listSize; row++) {
        lvi.iItem = row;
        std::wstring get = MC.toPercentStr(listData->massFractionAcc[row], number);
        lvi.pszText = (LPWSTR)get.c_str();
        ListView_SetItem(hListview, &lvi);
    }
    
}

