#ifndef _IPEEKBACK_PRIORITY_QUEUE_H_
#define _IPEEKBACK_PRIORITY_QUEUE_H_
#include "IPriorityQueue.h"
#include "PeekBack.h"

namespace exam
{
	template<typename T>
	class IPeekBackPriorityQueue : virtual public IPriorityQueue<T>, public PeekBack<T>
	{
	public:
		IPeekBackPriorityQueue()											= default;
		virtual ~IPeekBackPriorityQueue()									= default;
		IPeekBackPriorityQueue(const IPeekBackPriorityQueue&)				= delete;
		IPeekBackPriorityQueue& operator=(const IPeekBackPriorityQueue&)	= delete;
	};
}
#endif // !_IPEEKBACK_PRIORITY_QUEUE_H_