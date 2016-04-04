#ifndef __SOCKET_SESSION_H__
#define __SOCKET_SESSION_H__

#include <WinSock2.h>
#include <thread>
#include <memory>
#include <atomic>
class ControlCenter;
class SocketSession : 
	public std::enable_shared_from_this<SocketSession> {
public:
	SocketSession(const SOCKET& socket, std::shared_ptr<ControlCenter>& cc);
	~SocketSession();
	bool Start();
	void Stop();
	//Ϊ���ڱ���ֳɰ��Լ�ɱ��
	void NotifyClose();
private:
	void Close();
	void Run();
	SOCKET socket_;
	std::atomic_bool is_stop_;
	std::shared_ptr<std::thread> thread_;
	std::weak_ptr<ControlCenter> control_center_;
};
#endif