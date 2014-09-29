#ifndef __DISPATCH_H__
#define __DISPATCH_H__
#include <boost/interprocess/smart_ptr/unique_ptr.hpp>
namespace bluetooch
{
	class dispatchor
	{
	public:
		dispatchor(size_t num_thread);
		~dispatchor(void);
		void bind(void *);
		// ����ɶ˿�Ͷ������
		template<typename HandlerT>
		void dispatchor::post(HandlerT& handle);
		// ֹͣ����
		void stop();	     
	private:
		struct impl;
		boost::unique_ptr<impl> impl_;
	}; 
}
#endif

