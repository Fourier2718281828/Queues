#ifndef _ITERABLE_QUEUE_H_
#define _ITERABLE_QUEUE_H_
#include "IQueue.h"
#include "Iterable.h"

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