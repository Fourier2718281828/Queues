#ifndef _PEEK_BACK_ARRAY_DEQUE_H_
#define _PEEK_BACK_ARRAY_DEQUE_H_
#include "IPeekBackDeque.h"
#include "ArrayDeque.h"

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