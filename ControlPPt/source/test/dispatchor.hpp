#ifndef __DISPATCH_H__
#define __DISPATCH_H__
#include <boost/scoped_ptr.hpp>
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
		void post(HandlerT& handle);
		// ֹͣ����
		void stop();	     
	private:
		struct impl;
		boost::scoped_ptr<impl> impl_;
	}; 
}
#endif

