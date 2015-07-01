#ifndef __TIMER_BASIC_TIMER_HPP
#define __TIMER_BASIC_TIMER_HPP

#include <chrono>
#include <limits>
#include <memory>
#include "timer_service.hpp"
#include "timer_impl.hpp"

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

	// ---------------------------------------
	// class basic_timer_t
class basic_timer_t;
typedef timer_service_t<waitable_timer_t>	win_timer_service_t;
typedef std::shared_ptr<basic_timer_t>		timer_handle_ptr;

	class basic_timer_t
	{
	public:
		explicit basic_timer_t():id_(0)
		{}
		// ���ܻص���������ע��һ��Timer
		template < typename HandlerT >
		basic_timer_t()
			:id_(0)
		{
		}
		~basic_timer_t()
		{
			if( id_ != 0 )
				service_.erase_timer(id_);
		}
	private:
		basic_timer_t(const basic_timer_t &);
		basic_timer_t &operator=(const basic_timer_t &);
	public:
		explicit operator bool() const
		{
			return id_ != 0;
		}
		// ����ʱ����
		// period ʱ����
		// delay �ӳ�ʱ��
		void set_timer(long period, long delay = 0)
		{
			assert(id_ != 0);
			service_.set_timer(id_, period, delay);
		}
		bool start()
		{
			return service_.start();
		}
		// ȡ��Timer
		void cancel()
		{
			assert(id_ != 0);
			service_.erase_timer(id_);
			id_ = 0;
		}
		// �첽�ȴ�
		void async_wait()
		{
			assert(id_ != 0);
			service_.async_wait(id_);
		}

		template < typename HandlerT >
		void async_wait(HandlerT &&handler, const std::chrono::milliseconds& duration_time, const std::chrono::milliseconds &delay_time = std::chrono::milliseconds(0))
		{
			assert(duration_time.count() <= std::numeric_limits<long>::max());
			assert(-(delay_time.count() * 10000) >= std::numeric_limits<long long>::min());
			if( id_ == 0 )
			{
				id_ = service_.add_timer(
					static_cast<long>(duration_time.count()), 
					static_cast<long>(delay_time.count()), 
					std::forward<HandlerT>(handler));
			}
			async_wait();
		}
		template < typename HandlerT, typename ClockT, typename DurationT >
		void async_wait(HandlerT && handler, const std::chrono::milliseconds& duration_time, const std::chrono::time_point<ClockT, DurationT>& abs_time)
		{
			if( id_ == 0 )
			{
				std::chrono::milliseconds real_time = std::chrono::duration_cast<std::chrono::milliseconds>(abs_time - ClockT::now());
				id_ = service_.add_timer(static_cast<long>(duration_time.count()),
					static_cast<long>(real_time.count()), 
					std::forward<HandlerT>(handler));
			}
			async_wait();
		}
	private:
		win_timer_service_t service_;		// service
		std::uint32_t id_;
	};
#endif