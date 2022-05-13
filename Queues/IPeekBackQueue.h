#ifndef _IPEEKBACK_PRIORITY_QUEUE_H_
#define _IPEEKBACK_PRIORITY_QUEUE_H_
#include "IterableQueue.h"
#include "PeekBack.h"

namespace exam
{
	template<typename T>
	class IPeekBackQueue : virtual public IterableQueue<T>, public PeekBack<T>
	{
	public:
		IPeekBackQueue()									= default;
		virtual ~IPeekBackQueue()							= default;
		IPeekBackQueue(const IPeekBackQueue&)				= delete;
		IPeekBackQueue& operator=(const IPeekBackQueue&)	= delete;
	};
}
#endif // !_IPEEKBACK_PRIORITY_QUEUE_H_