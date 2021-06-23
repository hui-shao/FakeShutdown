#include "shutdown_exe.h"

static const char* msg[] = {
	"啊嘞 ? 你似乎点到了什么...",
	"emm，想起来了，是关机按钮！",
	"But...关机的过程似乎出了点意外",
	"部分系统程序侦测到在途核打击...现已经提前躲起....",
	"如果你的电脑还没有关机，请不要慌张。",
	"因为你的电脑现在不想关机",
	"电脑也是可以有自己的想法的!"
};

bool system_shutdown()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;

	// 获取token
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		MessageBox(NULL, "获取token失败", "错误：提权失败", MB_OK | MB_ICONERROR);
		return false;
	}

	// 获取 SE_SHUTDOWN_NAME 权限的LUID 
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// 获取 SE_SHUTDOWN_NAME 权限
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
	if (GetLastError() != ERROR_SUCCESS) {
		MessageBox(NULL, "获取 SE_SHUTDOWN_NAME 权限失败", "错误：提权失败", MB_OK | MB_ICONERROR);
		return false;
	}

	// 实施关机
	// 不使用 InitiateSystemShutdown 的原因是为了支持 Win XP
	if (!ExitWindowsEx(EWX_SHUTDOWN , SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_MINOR_UPGRADE | SHTDN_REASON_FLAG_PLANNED)) {
		MessageBox(NULL, "执行关机失败", "错误：操作失败", MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}

void main() {

	// 隐藏控制台
	SetConsoleTitle("shutdown");
	HWND hwnd;
	hwnd = FindWindow("ConsoleWindowClass",NULL);
	if (hwnd) {
		ShowWindow(hwnd, SW_HIDE);
	}

	// 消息框
	int i = 0;
	for (i; i < sizeof(msg) / sizeof(msg[0]); i++) {
		MessageBox(NULL, msg[i], "Windows温馨提示", MB_OK | MB_ICONINFORMATION);
	}
	Sleep(8912);

	// 关机确认
	if (MessageBox(NULL, "真的要关机了吗？ QAQ", "最后的确认...", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES) {
		system_shutdown();
	}
}