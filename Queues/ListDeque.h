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
		virtual inline bool		do_empty()			const		override;
		virtual inline bool		do_full()			const		override;
		virtual inline const T& do_front()			const		override;
		virtual inline const T& do_back()			const		override;
		virtual inline size_t	do_capacity()		const		override;
		virtual inline size_t	do_size()			const		override;
		virtual inline void		do_pop_front()					override;
		virtual inline void		do_pop_back()					override;
		virtual inline void		do_put_front(const T& value)	override;
		virtual inline void		do_put_back(const T& value)		override;
	};
}
#endif // !_LIST_DEQUE_H_
