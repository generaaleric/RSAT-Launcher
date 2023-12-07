#pragma once

#include <Windows.h>
#include <string>
#include <regex>



struct AppLocation
{
	LPCWSTR DCAS			= L"C:\\Windows\\system32\\dsac.exe";
	LPCWSTR DSA				= L" C:\\Windows\\system32\\DSA.msc";
	LPCWSTR DSSITE			= L" C:\\Windows\\system32\\dssite.msc";
	LPCWSTR Domain			= L" C:\\Windows\\system32\\domain.msc";
	LPCWSTR ADSIEDIT		= L" C:\\Windows\\system32\\adsiedit.msc";
	LPCWSTR CertServ		= L" C:\\Windows\\system32\\certsrv.msc";
	LPCWSTR CLUSTERUPDATE	= L"C:\\Windows\\system32\\ClusterUpdateUI.exe";
	LPCWSTR DFSMGMT			= L" C:\\Windows\\system32\\dfsmgmt.msc";
	LPCWSTR DHCP			= L" C:\\Windows\\system32\\dhcpmgmt.msc";
	LPCWSTR DNS				= L" C:\\Windows\\system32\\dnsmgmt.msc";
	LPCWSTR CLUADMIN		= L" C:\\Windows\\system32\\Cluadmin.msc";
	LPCWSTR FSRM			= L" C:\\Windows\\system32\\fsrm.msc";
	LPCWSTR GPMC			= L" C:\\Windows\\system32\\gpmc.msc";
	LPCWSTR OCSP			= L" C:\\Windows\\system32\\ocsp.msc";
	LPCWSTR RAMGMTUI		= L"C:\\Windows\\system32\\RAMgmtUI.exe";
	LPCWSTR RRAS			= L" C:\\Windows\\system32\\rrasmgmt.msc";
	LPCWSTR VMW				= L"C:\\Windows\\system32\\vmw.exe";
	LPCWSTR WSUS			= L" C:\\Program Files\\Update Services\\AdministrationSnapin\\wsus.msc";
};

struct UserAccount
{
	std::wstring Username;
	std::wstring Domain;
};


enum App
{
	DSAC, DSA, DSSITE, Domain,
	ADSIEDIT, CertServ, CLUSTERUPDATE, DFSMGMT,
	DHCP, DNS, CLUADMIN, FSRM,
	GPMC, OCSP, RAMGMTUI, RRAS,
	VMW, WSUS
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