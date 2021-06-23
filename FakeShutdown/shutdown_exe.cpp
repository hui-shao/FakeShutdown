#include "shutdown_exe.h"

static const char* msg[] = {
	"���� ? ���ƺ��㵽��ʲô...",
	"emm���������ˣ��ǹػ���ť��",
	"But...�ػ��Ĺ����ƺ����˵�����",
	"����ϵͳ������⵽��;�˴��...���Ѿ���ǰ����....",
	"�����ĵ��Ի�û�йػ����벻Ҫ���š�",
	"��Ϊ��ĵ������ڲ���ػ�",
	"����Ҳ�ǿ������Լ����뷨��!"
};

bool system_shutdown()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;

	// ��ȡtoken
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		MessageBox(NULL, "��ȡtokenʧ��", "������Ȩʧ��", MB_OK | MB_ICONERROR);
		return false;
	}

	// ��ȡ SE_SHUTDOWN_NAME Ȩ�޵�LUID 
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// ��ȡ SE_SHUTDOWN_NAME Ȩ��
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
	if (GetLastError() != ERROR_SUCCESS) {
		MessageBox(NULL, "��ȡ SE_SHUTDOWN_NAME Ȩ��ʧ��", "������Ȩʧ��", MB_OK | MB_ICONERROR);
		return false;
	}

	// ʵʩ�ػ�
	// ��ʹ�� InitiateSystemShutdown ��ԭ����Ϊ��֧�� Win XP
	if (!ExitWindowsEx(EWX_SHUTDOWN , SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_MINOR_UPGRADE | SHTDN_REASON_FLAG_PLANNED)) {
		MessageBox(NULL, "ִ�йػ�ʧ��", "���󣺲���ʧ��", MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}

void main() {

	// ���ؿ���̨
	SetConsoleTitle("shutdown");
	HWND hwnd;
	hwnd = FindWindow("ConsoleWindowClass",NULL);
	if (hwnd) {
		ShowWindow(hwnd, SW_HIDE);
	}

	// ��Ϣ��
	int i = 0;
	for (i; i < sizeof(msg) / sizeof(msg[0]); i++) {
		MessageBox(NULL, msg[i], "Windows��ܰ��ʾ", MB_OK | MB_ICONINFORMATION);
	}
	Sleep(8912);

	// �ػ�ȷ��
	if (MessageBox(NULL, "���Ҫ�ػ����� QAQ", "����ȷ��...", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES) {
		system_shutdown();
	}
}