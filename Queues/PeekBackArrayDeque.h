#ifndef _PEEK_BACK_ARRAY_DEQUE_H_
#define _PEEK_BACK_ARRAY_DEQUE_H_
#include "IPeekBackDeque.h"
#include "ArrayDeque.h"

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
	class PeekBackArrayDeque : public ArrayDeque<Capacity, T>, public IPeekBackDeque<T>
	{
	public:
		PeekBackArrayDeque()										= default;
		virtual ~PeekBackArrayDeque()								= default;
		PeekBackArrayDeque(const PeekBackArrayDeque&)				= delete;
		PeekBackArrayDeque& operator=(const PeekBackArrayDeque&)	= delete;
	private:
		virtual inline const T& do_peekback(const size_t) const override;
	};

	template<size_t Capacity, typename T>
	inline const T& PeekBackArrayDeque<Capacity, T>::do_peekback(const size_t i) const
	{
		if (i >= IQueue<T>::size())
		{
			throw IQueue<T>::BadQueue(IQueue<T>::QueueProblem::PEEKBACK_INDEX_OUT_OF_BOUNDS);
		}
		auto& itor(ArrayDeque<Capacity, T>::attach());
		const T& res(*(itor += i));
		delete& itor;
		return res;
	}
}
#endif // !_PEEK_BACK_ARRAY_DEQUE_H_