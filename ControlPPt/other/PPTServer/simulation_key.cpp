#include "stdafx.h"
#include <Windows.h>
#include "simulation_key.h"

SimulationKey::SimulationKey():
ppt_windows_handle_(nullptr){

}
SimulationKey::~SimulationKey(){

}
void SimulationKey::SetF5(){
	keybd_event(VK_F5, 0, 0, 0);
	keybd_event(VK_F5, 0, KEYEVENTF_KEYUP, 0);
}
void SimulationKey::SetLeft(){
		
	keybd_event(VK_LEFT, 0, 0, 0);
	keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
}
	void SimulationKey::SetRight(){

	keybd_event(VK_RIGHT, 0, 0, 0);
	keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
}
void SimulationKey::SetEsc(){
	keybd_event(VK_ESCAPE, 0, 0, 0);
	keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0);
}
void SimulationKey::SetShiltF5(){

	keybd_event(VK_SHIFT, 0, 0, 0);                                     //ģ���Ȱ���Shift��
	keybd_event(VK_F5, 0, 0, 0);                                               // ��û�е�����������°�����̵����֡�2������
	keybd_event(VK_F5, 0, KEYEVENTF_KEYUP, 0);          //Ȼ���ɿ�����
	keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);//Ȼ���ɿ�����
}
