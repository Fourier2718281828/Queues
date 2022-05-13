#ifndef _ITERABLE_QUEUE_H_
#define _ITERABLE_QUEUE_H_
#include "IQueue.h"
#include "Iterable.h"

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
	class IterableQueue : public IQueue<T>, public Iterable<T>
	{
	public:
		IterableQueue()									= default;
		virtual ~IterableQueue()						= default;
		IterableQueue(const IterableQueue&)				= delete;
		IterableQueue& operator=(const IterableQueue&)	= delete;
	};

	template<typename T>
	inline ostream& operator<<(ostream& o, const IterableQueue<T>& q)
	{
		o << '[';
		auto& itor = q.attach();

		while (!itor.stop())
		{
			o << *itor;
			++itor;
			if (!itor.stop())
				o << ", ";
		}

		delete& itor;

		o << ']' << ':' << q.size();
		if (q.capacity() <= 100000)
			o << '/' << q.capacity();

		return o;
	}
}

#endif // !_ITERABLE_QUEUE_H_