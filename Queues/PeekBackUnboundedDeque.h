#ifndef _PEEK_BACK_UNBOUNDED_DEQUE_H_
#define _PEEK_BACK_UNBOUNDED_DEQUE_H_
#include "IPeekBackDeque.h"
#include "UnboundedDeque.h"

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
	class PeekBackUnboundedDeque : public UnboundedDeque<T>, public IPeekBackDeque<T>
	{
	public:
		PeekBackUnboundedDeque(const size_t = 0);
		virtual ~PeekBackUnboundedDeque()									= default;
		PeekBackUnboundedDeque(const PeekBackUnboundedDeque&)				= delete;
		PeekBackUnboundedDeque& operator=(const PeekBackUnboundedDeque&)	= delete;
	private:
		virtual inline const T& do_peekback(const size_t) const override;
	};

	template<typename T>
	inline PeekBackUnboundedDeque<T>::PeekBackUnboundedDeque(const size_t capacity)
		: UnboundedDeque<T>(capacity)
	{
		return;
	}

	template<typename T>
	inline const T& PeekBackUnboundedDeque<T>::do_peekback(const size_t i) const
	{
		if (i >= IQueue<T>::size())
		{
			throw IQueue<T>::BadQueue(IQueue<T>::QueueProblem::PEEKBACK_INDEX_OUT_OF_BOUNDS);
		}
		auto& itor(UnboundedDeque<T>::attach());
		const T& res(*(itor += i));
		delete& itor;
		return res;
	}
}
#endif // !_PEEK_BACK_UNBOUNDED_DEQUE_H_