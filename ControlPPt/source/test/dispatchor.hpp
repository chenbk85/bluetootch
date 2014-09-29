#ifndef __DISPATCH_H__
#define __DISPATCH_H__

namespace bluetooch
{
	class dispatchor
	{
	public:
		dispatchor(size_t num_thread);
		~dispatchor(void);
		void bind(void *);
		// ����ɶ˿�Ͷ������
		template<typename HandlerT, typename AllocatorT = std::allocator<char> >
		void post(HandlerT &&, const AllocatorT &allocator = AllocatorT());
		// ֹͣ����
		void stop();	     
	private:
		struct impl;
		boost::unique_ptr<impl> impl_;
	}; 
}
#endif

