#ifndef __ASYNC_SOCKET_SOCKET_OPTION_HPP
#define __ASYNC_SOCKET_SOCKET_OPTION_HPP

#include <MSTcpIP.h>
#include "../service/exception.hpp"


namespace async { namespace network {

	// ----------------------------------------------
	// ����bool����socket���Եİ�����

	template<int _Level, int _Name>
	class boolean_t
	{
	private:
		int value_;

	public:
		explicit boolean_t(bool val)
			: value_(val ? 1 : 0)
		{}
		boolean_t &operator=(const boolean_t &rhs)
		{
			value_	 = rhs.value_;
			return *this;
		}	
		boolean_t &operator=(bool val)
		{
			value_ = val ? 1 : 0;
		}

	public:
		bool value() const
		{
			return !!value_;
		}

		// bool ת��
		operator bool() const
		{
			return !!value_;
		}

		bool operator!() const
		{
			return !value_;
		}

		// ��ȡSocket levalѡ��ֵ
		int level() const
		{
			return _Level;
		}

		// ��ȡSocket name
		int name() const
		{
			return _Name;
		}	

		// ��ȡSocketֵ
		char *data()
		{
			return reinterpret_cast<char *>(&value_);
		}
		const char *data() const
		{
			return reinterpret_cast<const char *>(&value_);
		}

		// ��ȡֵ��С
		size_t size() const
		{
			return sizeof(value_);
		}


		// ����boolean�Ĵ�С
		void resize(size_t nSize)
		{
			// ��ĳЩƽ̨��getsockopt����һ��sizeof(bool)--1�ֽڡ�	
			// 
			switch(nSize)
			{
			case sizeof(char):
				value_ = *reinterpret_cast<char *>(&value_) ? 1 : 0;
				break;
			case sizeof(value_):
				break;
			default:
				throw exception::exception_base("bool socket opetion resize");
			}
		}
	};


	// ----------------------------------------------------------
	// ����int����socket���Եİ�����

	template<int _Level, int _Name>
	class integer_t
	{
	private:
		int value_;

	public:
		integer_t()
			: value_(0)
		{}
		explicit integer_t(int val)
			: value_(val)
		{}
		integer_t &operator=(const integer_t &rhs)
		{
			value_	 = rhs.value_;
			return *this;
		}	
		integer_t &operator=(int val)
		{
			value_ = val;
		}

	public:
		bool value() const
		{
			return !!value_;
		}

		// ��ȡSocket levalѡ��ֵ
		int level() const
		{
			return _Level;
		}

		// ��ȡSocket name
		int name() const
		{
			return _Name;
		}	

		// ��ȡSocketֵ
		char *data()
		{
			return reinterpret_cast<char *>(&value_);
		}
		const char *data() const
		{
			return (const char *)&value_;
		}

		// ��ȡֵ��С
		size_t size() const
		{
			return sizeof(value_);
		}


		// ����int�Ĵ�С
		void resize(size_t nSize)
		{
			if( nSize != sizeof(value_) )
				throw service::network_exception("Integer socket option resize");
		}
	};


	// -----------------------------------------------------------------
	// class Linger ѡ�����ð�����

	// SO_LINGER���ڿ��Ƶ�δ���͵��������׽������Ŷ�ʱ��һ��ִ����closesocket�󣬸ò�ȡ���ֶ���
	// ���������ʱ����δ���ͺͽ��ܵ����ݶ��ᶪ����ͬʱ����Է�������
	// Ҳ����ͨ������SO_DONTLINGER������

	template< >
	class integer_t<SOL_SOCKET, SO_LINGER>
	{
	private:
		::linger value_;


	public:
		integer_t()
		{
			value_.l_linger = 0;	// option on/off
			value_.l_onoff	= 0;	// linger time
		}
		integer_t(bool bOn, int nTime)
		{
			enabled(bOn);
			timeout(nTime);
		}


	public:
		// �򿪻�ر�lingerѡ��
		void enabled(bool val)
		{
			value_.l_onoff = val ? 1 : 0;
		}

		bool enabled() const
		{
			return value_.l_onoff != 0;
		}

		void timeout(int val)
		{
			value_.l_linger = static_cast<u_short>(val);
		}
		int timeout() const
		{
			return static_cast<int>(value_.l_linger);
		}

		// ��ȡSocket levalѡ��ֵ
		int level() const
		{
			return SOL_SOCKET;
		}

		// ��ȡSocket name
		int name() const
		{
			return SO_LINGER;
		}	

		// ��ȡSocketֵ
		char *data()
		{
			return reinterpret_cast<char *>(&value_);
		}
		const char *data() const
		{
			return reinterpret_cast<const char *>(&value_);
		}

		// ��ȡֵ��С
		size_t size() const
		{
			return sizeof(value_);
		}

		// ����int�Ĵ�С
		void resize(size_t nSize)
		{
			if( nSize != sizeof(value_) )
				throw service::network_exception("Linger socket option resize");
		}

	};






	typedef u_long IoctlArgType;


	template < size_t _CMD >
	class io_control_t;

	template <>
	class io_control_t<FIONBIO>
	{
		u_long enable_;

	public:
		io_control_t(bool enable)
			: enable_(enable ? 1 : 0)
		{}

		u_long cmd() const
		{
			return FIONBIO;
		}

		void *in_buffer()
		{
			return &enable_;
		}

		size_t in_buffer_size() const
		{
			return sizeof(enable_);
		}

		void *out_buffer()
		{
			return 0;
		}

		size_t out_buffer_size() const
		{
			return 0;
		}
	};

	template <>
	class io_control_t<SIO_KEEPALIVE_VALS>
	{
		tcp_keepalive inAlive_;
		tcp_keepalive outAlive_;

	public:
		io_control_t(u_long inTime)
		{
			if( inTime != 0 )
				inAlive_.onoff = 1;
			else
				inAlive_.onoff = 0;

			inAlive_.keepalivetime = inTime * 1000;
			inAlive_.keepaliveinterval = 2 * 1000;

			inAlive_.onoff = 0;
			outAlive_.keepalivetime = 0;
			outAlive_.keepaliveinterval = 0;
		}

		u_long cmd() const
		{
			return SIO_KEEPALIVE_VALS;
		}

		void *in_buffer()
		{
			return &inAlive_;
		}

		size_t in_buffer_size() const
		{
			return sizeof(inAlive_);
		}

		void *out_buffer()
		{
			return &outAlive_;
		}

		size_t out_buffer_size() const
		{
			return sizeof(outAlive_);
		}
	};

	template <>
	class io_control_t<SIO_GET_EXTENSION_FUNCTION_POINTER>
	{
		GUID guid_;
		LPVOID func_;

	public:
		io_control_t(const GUID &guid, LPVOID func)
			: guid_(guid)
			, func_(func)
		{}

		u_long cmd() const
		{
			return SIO_GET_EXTENSION_FUNCTION_POINTER;
		}

		void *in_buffer()
		{
			return &guid_;
		}

		size_t in_buffer_size() const
		{
			return sizeof(guid_);
		}

		LPVOID out_buffer()
		{
			return func_;
		}

		size_t out_buffer_size() const
		{
			return sizeof(func_);
		}
	};


	//----------------------------------

	/*
	Example:

	tcp::socket sock(io);
	SocketBase::Broadcast opt(true);
	socket.SetOption(opt);
	*/

	typedef boolean_t<SOL_SOCKET, SO_BROADCAST>				broadcast;
	typedef boolean_t<SOL_SOCKET, SO_CONDITIONAL_ACCEPT>	conditional_accept;
	typedef boolean_t<SOL_SOCKET, SO_DEBUG>					debug;
	typedef boolean_t<SOL_SOCKET, SO_DONTROUTE>				dont_route;
	typedef boolean_t<SOL_SOCKET, SO_DONTLINGER>			dont_linger;
	typedef boolean_t<SOL_SOCKET, SO_KEEPALIVE>				keep_alive;
	typedef boolean_t<SOL_SOCKET, SO_REUSEADDR>				reuse_addr;
	typedef boolean_t<IPPROTO_TCP, TCP_NODELAY>				no_delay;


	typedef integer_t<SOL_SOCKET, SO_SNDBUF>				send_buffer_size;
	typedef integer_t<SOL_SOCKET, SO_SNDLOWAT>				send_low_water_mark;
	typedef integer_t<SOL_SOCKET, SO_RCVBUF>				recv_buffer_size;
	typedef integer_t<SOL_SOCKET, SO_RCVLOWAT>				recv_low_water_mark;
	typedef integer_t<SOL_SOCKET, SO_SNDTIMEO>				send_time_out;
	typedef integer_t<SOL_SOCKET, SO_RCVTIMEO>				recv_time_out;
	typedef integer_t<SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT> update_accept_context;
	typedef integer_t<SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT> update_connect_context;
	typedef integer_t<SOL_SOCKET, SO_LINGER>				linger;



	// io_ctrl

	typedef io_control_t<FIONBIO>							non_blocking_io;
	//typedef IOCtrl<FIONREAD>					BytesReadable;
	typedef io_control_t<SIO_KEEPALIVE_VALS>				io_keepalive;
	typedef io_control_t<SIO_GET_EXTENSION_FUNCTION_POINTER> extension_function;
}
}





#endif