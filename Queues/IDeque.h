#ifndef _IDEQUE_H_
#define _IDEQUE_H_
#include "IterableQueue.h"
#include <ostream>
using std::ostream;

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
	class IDeque : public IterableQueue<T>
	{
	public:
		IDeque()							= default;
		virtual ~IDeque()					= default;
		IDeque(const IDeque&)				= delete;
		IDeque& operator=(const IDeque&)	= delete;
	public:
		inline const T& back()		const;
		inline void pop_back();
		inline void put_front(const T& value);
	private:
		virtual inline const T& do_back()	const			= 0;
		virtual inline void do_pop_back()					= 0;
		virtual inline void do_put_front(const T& value)	= 0;
	};

	template<typename T>
	inline const T& IDeque<T>::back() const
	{
		return do_back();
	}

	template<typename T>
	inline void IDeque<T>::pop_back()
	{
		return do_pop_back();
	}

	template<typename T>
	inline void IDeque<T>::put_front(const T& value)
	{
		return do_put_front(value);
	}
}
#endif // !_IDEQUE_H_