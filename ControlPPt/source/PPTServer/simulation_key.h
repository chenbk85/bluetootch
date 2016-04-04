#ifndef __SIMMULATION_KEY_H__
#define __SIMMULATION_KEY_H__
#include <string>

const std::string cmd_next = "next";
const std::string cmd_pre = "pre";
const std::string cmd_exit = "esc";
const std::string cmd_start = "start";
const std::string cmd_stop = "stop";
class SimulationKey
{
public:
	SimulationKey();
	~SimulationKey();
	//��ͷ��ʼ����
	void SetF5();
	//��һҳ
	void SetLeft();
	//��һҳ
	void SetRight();
	//�Ƴ���ӳ
	void SetEsc();
	//�ӵ�ǰҳ��ʼ����
	void SetShiltF5();

	std::wstring SetWindowsWnd(const std::wstring& wnd_class);
private:
	HWND ppt_windows_handle_;
};
#endif
