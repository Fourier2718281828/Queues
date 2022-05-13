#ifndef _ITERABLE_H_
#define _ITERABLE_H_

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
	class Iterable
	{
	public:
		using Iterator = AbstractIterator<false, T>;
		using ConstIterator = AbstractIterator<true, T>;
	public:
		Iterable() = default;
		virtual ~Iterable() = default;
		/*Iterable(const Iterable&)				= delete;
		Iterable& operator=(const Iterable&)	= delete;*/ //?????
	public:
		virtual inline	ConstIterator& attach()	const	= 0;
		virtual inline	Iterator& attach()				= 0;
	};
}

#endif // !_ITERABLE_H_