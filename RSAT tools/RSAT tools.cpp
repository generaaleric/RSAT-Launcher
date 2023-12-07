// RSAT tools.cpp : Defines the entry point for the application.
//
//internal Function variables are prefixed by Int (in case of possible confusion)
#include "RSAT tools.h"

// a couple variables to be accesible for everyone regardless of class or what ever... hopefully
HINSTANCE hInst; // current instance
int FirstInit;
HMENU Menu;
bool AppStartFailure;
LPWSTR UserAccountDialog::UPN = new WCHAR[1000];
LPWSTR UserAccountDialog::Password = new WCHAR[1000];
bool UserAccountSet = false;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    
    MainProgram* Main = new MainProgram;

    LoadStringW(hInstance, IDS_APP_TITLE, Main->szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDD_RSATTOOLS_MainWindow, Main->szWindowClass, MAX_LOADSTRING);
    Main->MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!Main->InitInstance (hInstance,  nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RSATTOOLS));

    MSG msg;

    // Main message loop:
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

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MainProgram::MyRegisterClass(HINSTANCE hInstance)
{
    //register the main window
    WNDCLASSEXW wcex{};
    

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS;
    wcex.lpfnWndProc    = MainProgram::MainWnd;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RSATTOOLS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+0);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_RSATTOOLS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return (RegisterClassExW(&wcex));
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL MainProgram::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store main instance handle in our global variable

   HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_TILEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr);
   if (!hWnd)
   {
      return FALSE;
   }
   CreateDialogA(hInst, MAKEINTRESOURCEA(IDD_FORMVIEW_MAINWINDOW),hWnd, MainWnd);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT MainProgram::MainWnd(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, (DLGPROC)AboutDialog::About, lParam);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDM_UserAccount:
            DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_UserAccount), hWnd, (DLGPROC)UserAccountDialog::UserAccount, lParam);
            break;
        case IDC_DSAC:
            if (UserAccountSet == false)
            {
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_ErrNoAccount), hWnd, (DLGPROC)NoAccountError::ErrNoAcc, lParam);
                break;
            };
            AppStartFailure = Tool::StartApplication( DSAC, EXE, UserAccountDialog::UPN, UserAccountDialog::Password);
            if (AppStartFailure == false)
                break;
            break;
        case IDC_DSA:
            if (UserAccountSet == false)
            {
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_ErrNoAccount), hWnd, (DLGPROC)NoAccountError::ErrNoAcc, lParam);
                break;
            };
            AppStartFailure = Tool::StartApplication(DSA, MMC, UserAccountDialog::UPN, UserAccountDialog::Password);
                if (AppStartFailure == false)
                    break;
                break;
        case IDC_DSSITE:
            if (UserAccountSet == false)
            {
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_ErrNoAccount), hWnd, (DLGPROC)NoAccountError::ErrNoAcc, lParam);
                break;
            };
            AppStartFailure = Tool::StartApplication(DSSITE, MMC, UserAccountDialog::UPN, UserAccountDialog::Password);
            if (AppStartFailure == false)
                break;
            break;
        case IDC_Domain:
            if (UserAccountSet == false)
            {
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_ErrNoAccount), hWnd, (DLGPROC)NoAccountError::ErrNoAcc, lParam);
                break;
            };
            AppStartFailure = Tool::StartApplication(Domain, MMC, UserAccountDialog::UPN, UserAccountDialog::Password);
            if (AppStartFailure == false)
                break;
            break;
        case IDC_ADSIEDIT:
            if (UserAccountSet == false)
            {
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_ErrNoAccount), hWnd, (DLGPROC)NoAccountError::ErrNoAcc, lParam);
                break;
            };
            AppStartFailure = Tool::StartApplication(ADSIEDIT, MMC, UserAccountDialog::UPN, UserAccountDialog::Password);
            if (AppStartFailure == false)
                break;
            break;
        case IDC_CertServ:
            if (UserAccountSet == false)
            {
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_ErrNoAccount), hWnd, (DLGPROC)NoAccountError::ErrNoAcc, lParam);
                break;
            };
            AppStartFailure = Tool::StartApplication(CertServ, MMC, UserAccountDialog::UPN, UserAccountDialog::Password);
            if (AppStartFailure == false)
                break;
            break;
        case IDC_CLUSTERUPDATE:
            if (UserAccountSet == false)
            {
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_ErrNoAccount), hWnd, (DLGPROC)NoAccountError::ErrNoAcc, lParam);
                break;
            };
            AppStartFailure = Tool::StartApplication(CLUSTERUPDATE, EXE, UserAccountDialog::UPN, UserAccountDialog::Password);
            if (AppStartFailure == false)
                break;
            break;
        case IDC_DFSMGMT:
            if (UserAccountSet == false)
            {
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_ErrNoAccount), hWnd, (DLGPROC)NoAccountError::ErrNoAcc, lParam);
                break;
            };
            AppStartFailure = Tool::StartApplication(DFSMGMT, MMC, UserAccountDialog::UPN, UserAccountDialog::Password);
            if (AppStartFailure == false)
                break;
            break;
        case IDC_DHCP:
            if (UserAccountSet == false)
            {
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_ErrNoAccount), hWnd, (DLGPROC)NoAccountError::ErrNoAcc, lParam);
                break;
            };
            AppStartFailure = Tool::StartApplication(DHCP, MMC, UserAccountDialog::UPN, UserAccountDialog::Password);
            if (AppStartFailure == false)
                break;
            break;
        case IDC_DNS:
            if (UserAccountSet == false)
            {
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_ErrNoAccount), hWnd, (DLGPROC)NoAccountError::ErrNoAcc, lParam);
                break;
            };
            AppStartFailure = Tool::StartApplication(DNS, MMC, UserAccountDialog::UPN, UserAccountDialog::Password);
            if (AppStartFailure == false)
                break;
            break;
        case IDC_CLUADMIN:
            if (UserAccountSet == false)
            {
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_ErrNoAccount), hWnd, (DLGPROC)NoAccountError::ErrNoAcc, lParam);
                break;
            };
            AppStartFailure = Tool::StartApplication(CLUADMIN, MMC, UserAccountDialog::UPN, UserAccountDialog::Password);
            if (AppStartFailure == false)
                break;
            break;
        case IDC_FSRM:
            if (UserAccountSet == false)
            {
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_ErrNoAccount), hWnd, (DLGPROC)NoAccountError::ErrNoAcc, lParam);
                break;
            };
            AppStartFailure = Tool::StartApplication(FSRM, MMC, UserAccountDialog::UPN, UserAccountDialog::Password);
            if (AppStartFailure == false)
                break;
            break;
        case IDC_GPMC:
            if (UserAccountSet == false)
            {
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_ErrNoAccount), hWnd, (DLGPROC)NoAccountError::ErrNoAcc, lParam);
                break;
            };
            AppStartFailure = Tool::StartApplication(GPMC, MMC, UserAccountDialog::UPN, UserAccountDialog::Password);
            if (AppStartFailure == false)
                break;
            break;
        case IDC_OCSP:
            if (UserAccountSet == false)
            {
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_ErrNoAccount), hWnd, (DLGPROC)NoAccountError::ErrNoAcc, lParam);
                break;
            };
            AppStartFailure = Tool::StartApplication(OCSP, MMC, UserAccountDialog::UPN, UserAccountDialog::Password);
            if (AppStartFailure == false)
                break;
            break;
        case IDC_RAMGMTUI:
            if (UserAccountSet == false)
            {
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_ErrNoAccount), hWnd, (DLGPROC)NoAccountError::ErrNoAcc, lParam);
                break;
            };
            AppStartFailure = Tool::StartApplication(RAMGMTUI, EXE, UserAccountDialog::UPN, UserAccountDialog::Password);
            if (AppStartFailure == false)
                break;
            break;
        case IDC_RRAS:
            if (UserAccountSet == false)
            {
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_ErrNoAccount), hWnd, (DLGPROC)NoAccountError::ErrNoAcc, lParam);
                break;
            };
            AppStartFailure = Tool::StartApplication(RRAS, MMC, UserAccountDialog::UPN, UserAccountDialog::Password);
            if (AppStartFailure == false)
                break;
            break;
        case IDC_VMW:
            if (UserAccountSet == false)
            {
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_ErrNoAccount), hWnd, (DLGPROC)NoAccountError::ErrNoAcc, lParam);
                break;
            };
            AppStartFailure = Tool::StartApplication(VMW, EXE, UserAccountDialog::UPN, UserAccountDialog::Password);
            if (AppStartFailure == false)
                break;
            break;

        //why the hell one would still use this is beyond me but its part of the RSAT tools soooo....
        case IDC_WSUS:
            if (UserAccountSet == false)
            {
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_ErrNoAccount), hWnd, (DLGPROC)NoAccountError::ErrNoAcc, lParam);
                break;
            };
            AppStartFailure = Tool::StartApplication(WSUS, MMC, UserAccountDialog::UPN, UserAccountDialog::Password);
            if (AppStartFailure == false)
                break;
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


// Message handler for about box.
INT_PTR CALLBACK AboutDialog::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


//The Username and password box
INT_PTR CALLBACK UserAccountDialog::UserAccount(HWND hDlg, UINT message, WPARAM wParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            GetDlgItemText(hDlg, IDC_UserName, UserAccountDialog::UPN, 1000);
            GetDlgItemText(hDlg, IDC_Password, UserAccountDialog::Password, 1000);
            UserAccountSet = true;

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        };
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        case IDC_ClearAndExit:
                delete[] UPN;
                delete[] Password;
                UserAccountSet = false;
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
                break;
        };
    }
    return (INT_PTR)FALSE;

}

INT_PTR NoAccountError::ErrNoAcc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            EndDialog(hDlg, LOWORD(wParam));
            DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_UserAccount), hDlg, (DLGPROC)UserAccountDialog::UserAccount, lParam);
            return (INT_PTR)TRUE;
            break;
        }
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        };
    }
    return (INT_PTR)FALSE;
}