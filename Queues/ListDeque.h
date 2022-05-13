#ifndef _LIST_DEQUE_H_
#define	_LIST_DEQUE_H_
#include "IDeque.h"
#include "ListQueueIterator.h"

//#############################################################################
//					“Об’єктно-орієнтоване програмування”					   
//												
//		Екзаменаційне завдання для студентів 2 курсу факультету інформатики
//		Національного університету “Києво-Могилянська академія”
//		Весняний триместр 2021-22 навчальний рік
//
//	5.  Визначити інтерфейс двосторонніх черг Deque.
//	6.	Визначити реалізацію двосторонньої черги на базі списку.
//	7.	Визначити реалізацію обмеженої двосторонньої черги на базі масиву.
//	8.	Визначити реалізацію необмеженої двосторонньої черги на базі масиву.
//	9.	Запропонувати і реалізувати пріоритетні черги : 
//		вилучається не перший в черзі елемент, а елемент з найвищим пріоритетом.
//
//	10*.Запропонувати і реалізувати варіанти черг з підгляданням, 
//		виділити їм місце в ієрархії черг.
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
