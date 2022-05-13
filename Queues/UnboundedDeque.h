#ifndef _UNBOUDED_DEQUE_H_
#define	_UNBOUDED_DEQUE_H_
#include "IDeque.h"
#include "ArrayQueueIterator.h"

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
	class UnboundedDeque : virtual public IDeque<T>
	{
	private:
		using IQueue<T>::QueueProblem;
	public:
		using Iterator = ArrayQueueIterator<false, T>;
		using ConstIterator = ArrayQueueIterator<true, T>;
	private:
		size_t _size;
		size_t _capacity;
		size_t _front;
		size_t _back;
		T* _allocator;
		static const size_t DEFAULT_CAPACITY;
	public:
		UnboundedDeque();
		virtual ~UnboundedDeque();
		UnboundedDeque(const UnboundedDeque&) = delete;
		UnboundedDeque& operator=(const UnboundedDeque&) = delete;
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

	template<typename T>
	const size_t UnboundedDeque<T>::DEFAULT_CAPACITY = 0;
}
#endif // !_UNBOUDED_DEQUE_H_