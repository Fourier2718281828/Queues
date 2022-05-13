#ifndef _LIST_DEQUE_H_
#define	_LIST_DEQUE_H_
#include "IDeque.h"
#include "ListQueueIterator.h"

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
	class ListQueue : virtual public IDeque<T>
	{
	private:
		using IQueue<T>::QueueProblem;
	public:
		using Iterator = ListQueueIterator<false, T>;
		using ConstIterator = ListQueueIterator<true, T>;
	private:
		Node<T>* _front;
		Node<T>* _back;
		size_t	 _size;
	public:
		ListQueue();
		virtual ~ListQueue();
		ListQueue(const ListQueue&) = delete;
		ListQueue& operator=(const ListQueue&) = delete;
	public:
		virtual inline ConstIterator& attach()	const;
		virtual inline Iterator& attach();
	private:
		virtual inline bool		do_empty()			const;
		virtual inline bool		do_full()			const;
		virtual inline const T& do_front()			const;
		virtual inline const T& do_back()			const;
		virtual inline size_t	do_capacity()		const;
		virtual inline size_t	do_size()			const;
		virtual inline void		do_pop();
		virtual inline void		do_pop_back();
		virtual inline void		do_put(const T& value);
		virtual inline void		do_put_back(const T& value);
	};
}
#endif // !_LIST_DEQUE_H_
