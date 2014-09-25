#ifndef __COMMAND_UTILS_H__
#define __COMMAND_UTILS_H__
#include <Windows.h>

namespace CommandUtils
{
	void SetF5()
	{
		keybd_event(VK_F5,0,0,0);
		keybd_event(VK_F5,0,KEYEVENTF_KEYUP,0);
	}
	void SetLeft()
	{
		keybd_event(VK_LEFT,0,0,0);
		keybd_event(VK_LEFT,0,KEYEVENTF_KEYUP,0);
	}
	void SetRight()
	{
		keybd_event(VK_RIGHT,0,0,0);
		keybd_event(VK_RIGHT,0,KEYEVENTF_KEYUP,0);
	}
	void SetEsc()
	{	
		keybd_event(VK_ESCAPE,0,0,0);
		keybd_event(VK_ESCAPE,0,KEYEVENTF_KEYUP,0);
	}
	void SetShiltF5()
	{
		keybd_event(VK_SHIFT,0,0,0);                                     //ģ���Ȱ���Shift��
		keybd_event(VK_F5,0,0,0);                                               // ��û�е�����������°�����̵����֡�2������
		keybd_event(VK_F5,0,KEYEVENTF_KEYUP,0);          //Ȼ���ɿ�����
		keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);//Ȼ���ɿ�����
	}
}
#endif // !__COMMAND_UTILS_H__
