#pragma once

#include "resource.h"
#include "windows.h"
#include <string>
#include <iostream>
#include <codecvt>
#include "framework.h"
#include "Tools.h"

//definitions here
#define MAX_LOADSTRING 100




class MainProgram
{
public:
	// Global Variables:
	WCHAR szTitle[MAX_LOADSTRING];										// The title bar text
	WCHAR szWindowClass[MAX_LOADSTRING];								// the main window class name

	//function declarations for the primary program loop
	ATOM MyRegisterClass(HINSTANCE hInstanceMain/*, HINSTANCE hInstanceMenu*/);
	BOOL InitInstance(HINSTANCE, /*HINSTANCE,*/ int);
	static LRESULT CALLBACK MainWnd(HWND, UINT, WPARAM, LPARAM);


};

class UserAccountDialog
{
public:
	static int WeHaveSetTheseAlready;
	static LPCWSTR UPN;
	static LPCWSTR Password;


	static INT_PTR CALLBACK UserAccount(HWND, UINT, WPARAM);
};


class AboutDialog
{
public:
	static INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
};


class HelperFunctions
{
public:
};