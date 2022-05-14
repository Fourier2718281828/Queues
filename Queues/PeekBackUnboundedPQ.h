#ifndef _PEEK_BACK_UNBOUNDED_PQ_
#define _PEEK_BACK_UNBOUNDED_PQ_
#include "IPeekBackQueue.h"
#include "UnboundedPQ.h"

//#############################################################################
//					��ᒺ����-��������� ��������������					   
//												
//		������������� �������� ��� �������� 2 ����� ���������� �����������
//		������������� ����������� �����-����������� ��������
//		�������� �������� 2021-22 ���������� ��
//
//	5.  ��������� ��������� ����������� ���� Deque.
//	6.	��������� ��������� ������������ ����� �� ��� ������.
//	7.	��������� ��������� �������� ������������ ����� �� ��� ������.
//	8.	��������� ��������� ���������� ������������ ����� �� ��� ������.
//	9.	������������� � ���������� ��������� ����� : 
//		���������� �� ������ � ���� �������, � ������� � �������� ����������.
//
//	10*.������������� � ���������� ������� ���� � �����������, 
//		������� �� ���� � �������� ����.
// 
// project : Queues, developed by Ruslan Zymovets (SE-1)
//#############################################################################

namespace exam
{
	template<typename T>
	class PeekBackUnboundedPQ : public UnboundedPQ<T>, public IPeekBackQueue<T>
	{
	public:
		PeekBackUnboundedPQ(const size_t);
		virtual ~PeekBackUnboundedPQ()								= default;
		PeekBackUnboundedPQ(const PeekBackUnboundedPQ&)				= delete;
		PeekBackUnboundedPQ& operator=(const PeekBackUnboundedPQ&)	= delete;
	private:
		virtual inline const T& do_peekback(const size_t) const override;
	};

	template<typename T>
	inline PeekBackUnboundedPQ<T>::PeekBackUnboundedPQ(const size_t capacity)
		:	UnboundedPQ<T>(capacity)
	{
		return;
	}

	template<typename T>
	inline const T& PeekBackUnboundedPQ<T>::do_peekback(const size_t i) const
	{
		if (i >= IQueue<T>::size())
		{
			throw IQueue<T>::BadQueue(IQueue<T>::QueueProblem::PEEKBACK_INDEX_OUT_OF_BOUNDS);
		}
		auto& itor(PeekBackUnboundedPQ<T>::attach());
		const T& res(*(itor += i));
		delete& itor;
		return res;
	}
}
#endif // !_PEEK_BACK_UNBOUNDED_PQ_