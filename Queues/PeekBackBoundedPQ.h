#ifndef _PEEK_BACK_BOUNDED_PQ_H_
#define _PEEK_BACK_BOUNDED_PQ_H_
#include "IPeekBackQueue.h"
#include "BoundedPQ.h"

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
	template<size_t Capacity, typename T>
	class PeekBackBoundedPQ : public BoundedPQ<Capacity, T>, public IPeekBackQueue<T>
	{
	public:
		PeekBackBoundedPQ()										= default;
		virtual ~PeekBackBoundedPQ()							= default;
		PeekBackBoundedPQ(const PeekBackBoundedPQ&)				= delete;
		PeekBackBoundedPQ& operator=(const PeekBackBoundedPQ&)	= delete;
	private:
		virtual inline const T& do_peekback(const size_t) const override;
	};

	template<size_t Capacity, typename T>
	inline const T& PeekBackBoundedPQ<Capacity, T>::do_peekback(const size_t i) const
	{
		if (i >= IQueue<T>::size())
		{
			throw IQueue<T>::BadQueue(IQueue<T>::QueueProblem::PEEKBACK_INDEX_OUT_OF_BOUNDS);
		}
		auto& itor(PeekBackBoundedPQ<Capacity, T>::attach());
		const T& res(*(itor += i));
		delete& itor;
		return res;
	}
}
#endif // !_PEEK_BACK_BOUNDED_PQ_H_