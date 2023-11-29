#pragma once

#include <Windows.h>
#include <string>
#include <regex>



struct AppLocation
{
	LPCWSTR DCAS		= L"C:\\Windows\\system32\\dsac.exe";
	LPCWSTR DSA			= L" C:\\Windows\\system32\\DSA.msc";
};

struct UserAccount
{
	std::wstring Username;
	std::wstring Domain;
};


enum App
{
	DSAC,
	DSA
};

enum AppType
{
	MMC,
	EXE
};

class Tool
{

private:
	static LPCWSTR ReturnPath(App Application);
	static void BreakUPN(LPCWSTR UPN, UserAccount* &IntUseracc);

public:
	static bool StartApplication(App Application, AppType Type, LPCWSTR UPN, LPCWSTR Password);

};