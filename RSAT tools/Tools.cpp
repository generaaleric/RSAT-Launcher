#include "Tools.h"

//internal Function variables are prefixed by Int (in case of possible confusion)


LPCWSTR Tool::ReturnPath(App Application)
{
	AppLocation* Location = new AppLocation;
	switch (Application)
	{
	case DSAC:
		return Location->DCAS;
		delete Location;
		break;
	case DSA:
		return Location->DSA;
		delete Location;
		break;
	};
}


void Tool::BreakUPN(LPCWSTR UPN, UserAccount*& IntUseracc)
{
	//init a bunch of stuff
	std::wstring IntUPN = UPN;
	std::wstring AtUPN = L"@";
	std::wstring SlashUPN = L"\\";
	std::wstring IntUsername;
	std::wstring IntDomain;
	size_t pos = 0;

	
	if ((pos = IntUPN.find(AtUPN)) != std::wstring::npos)
	{
		//find the right position of the strings and split them at the @ sign IE:
		//Johndoe@contonso.com becomes (username) Johndoe, (domain) contonso.com
		IntUsername = IntUPN.substr(0, IntUPN.find(AtUPN));
		IntDomain = IntUPN.erase(0, IntUPN.find(AtUPN) + AtUPN.length());
	
		//set the iternal strings to
		IntUseracc->Username = IntUsername;
		IntUseracc->Domain = IntDomain;
		return;
	}
	else if ((pos = IntUPN.find(SlashUPN)) != std::wstring::npos)
	{
		//find the right position of the strings and split them at the @ sign IE:
		//cotonso\johndoe becomes (username) Johndoe, (domain) contonso.com
		IntDomain = IntUPN.substr(0, IntUPN.find(SlashUPN));
		IntUsername = IntUPN.erase(0, IntUPN.find(SlashUPN) + SlashUPN.length());

		IntUseracc->Username = IntUsername;
		IntUseracc->Domain = IntDomain;
		return;
	}
	else
	{
		//we have no domain just a username
		IntUseracc->Username = UPN;
		IntUseracc->Domain = nullptr;
		return;
	};
}

bool Tool::StartApplication(App Application, AppType Type, LPCWSTR UPN, LPCWSTR Password)
{
	//debug variables
	int error;
	//initialise a bunch of variables
	UserAccount* IntUseracc = new UserAccount;
	bool applicationStartedSuccessfully = false;
	LPCWSTR EXEApp = new wchar_t;
	LPWSTR MMCApp = new wchar_t;
	PROCESS_INFORMATION BlankProcInfo{};
	STARTUPINFOW BlankStartInfo;

	ZeroMemory(&BlankStartInfo, sizeof(BlankStartInfo));
	BlankStartInfo.cb = sizeof(BlankStartInfo);
	ZeroMemory(&BlankProcInfo, sizeof(BlankProcInfo));

	//do a bunch of setup for a couple of our variables
	Tool::BreakUPN(UPN, IntUseracc);

	switch (Type)
	{
	case EXE:
		EXEApp = Tool::ReturnPath(Application);
		applicationStartedSuccessfully = CreateProcessWithLogonW(IntUseracc->Username.c_str(), IntUseracc->Domain.c_str(), Password, LOGON_WITH_PROFILE, EXEApp, nullptr, 0, nullptr, nullptr, &BlankStartInfo, &BlankProcInfo);
		error = GetLastError();
		break;
	case MMC:
		MMCApp = const_cast<LPWSTR>(Tool::ReturnPath(Application));
		applicationStartedSuccessfully = CreateProcessWithLogonW(IntUseracc->Username.c_str(), IntUseracc->Domain.c_str(), Password, LOGON_WITH_PROFILE, L"C:\\Windows\\System32\\mmc.exe", MMCApp, 0, nullptr, nullptr, &BlankStartInfo, &BlankProcInfo);
		error = GetLastError();
		break;
	}
	return applicationStartedSuccessfully;
}
