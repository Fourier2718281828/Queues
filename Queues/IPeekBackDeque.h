#ifndef _IPEEK_BACK_DEQUE_H
#define _IPEEK_BACK_DEQUE_H
#include "IDeque.h"
#include "PeekBack.h"

namespace exam
{
	template<typename T>
	class IPeekBackDeque : virtual public IDeque<T>, public PeekBack<T>
	{
	public:
		IPeekBackDeque()									= default;
		virtual ~IPeekBackDeque()							= default;
		IPeekBackDeque(const IPeekBackDeque&)				= delete;
		IPeekBackDeque& operator=(const IPeekBackDeque&)	= delete;
	};
}
#endif // !_IPEEK_BACK_DEQUE_H