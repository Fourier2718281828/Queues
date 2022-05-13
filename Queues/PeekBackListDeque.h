#ifndef _PEEK_BACK_LIST_DEQUE_H_
#define _PEEK_BACK_LIST_DEQUE_H_
#include "IPeekBackDeque.h"
#include "ListDeque.h"

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
	class PeekBackListDeque : public ListDeque<T>, public IPeekBackDeque<T>
	{
	public:
		PeekBackListDeque()										= default;
		virtual ~PeekBackListDeque()							= default;
		PeekBackListDeque(const PeekBackListDeque&)				= delete;
		PeekBackListDeque& operator=(const PeekBackListDeque&)	= delete;
	private:
		virtual inline const T& do_peekback(const size_t) const override;
	};

	template<typename T>
	inline const T& PeekBackListDeque<T>::do_peekback(const size_t i) const
	{
		if (i >= IQueue<T>::size())
		{
			throw IQueue<T>::BadQueue(IQueue<T>::QueueProblem::PEEKBACK_INDEX_OUT_OF_BOUNDS);
		}
		auto& itor(ListDeque<T>::attach());
		const T& res(*(itor += i));
		delete& itor;
		return res;
	}
}
#endif // !_PEEK_BACK_LIST_DEQUE_H_