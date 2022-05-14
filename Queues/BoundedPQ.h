#ifndef _BOUNDED_PQ_H
#define _BOUNDED_PQ_H
#include "IterableQueue.h"

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
	class BoundedPQ : virtual public IterableQueue<T>
	{
	public:
		using Iterator = ArrayQueueIterator<false, T>;
		using ConstIterator = ArrayQueueIterator<true, T>;
	private:
		size_t _size;
		size_t _front;
		size_t _back;
		T _allocator[Capacity];
	public:
		BoundedPQ();
		virtual ~BoundedPQ();
		BoundedPQ(const BoundedPQ&) = delete;
		BoundedPQ& operator=(const BoundedPQ&) = delete;
	public:
		virtual inline ConstIterator& attach()	const;
		virtual inline Iterator& attach();
	private:
		virtual inline bool		do_empty()			const		override;
		virtual inline bool		do_full()			const		override;
		virtual inline const T& do_front()			const		override;
		virtual inline size_t	do_capacity()		const		override;
		virtual inline size_t	do_size()			const		override;
		virtual inline void		do_pop_front()					override;
		virtual inline void		do_put_back(const T& value)		override;
	private:
		inline size_t next_index(const size_t) const;
		inline size_t prev_index(const size_t) const;
	};

	template<typename T>
	class BoundedPQ<0, T>;

		template<size_t Capacity, typename T>
	inline BoundedPQ<Capacity, T>::BoundedPQ()
		: _size(0), _front(0), _back(-1)
	{
		return;
	}

	template<size_t Capacity, typename T>
	inline BoundedPQ<Capacity, T>::~BoundedPQ()
	{
		_size = _front = _back = 0;
		return;
	}

	template<size_t Capacity, typename T>
	inline typename BoundedPQ<Capacity, T>::ConstIterator& BoundedPQ<Capacity, T>::attach() const
	{
		return *(
			new ConstIterator
			(
				&_allocator[0],
				&_allocator[_front],
				&_allocator[_back],
				IQueue<T>::size(),
				IQueue<T>::capacity()
			)
			);
	}

	template<size_t Capacity, typename T>
	inline typename BoundedPQ<Capacity, T>::Iterator& BoundedPQ<Capacity, T>::attach()
	{
		return *(
			new Iterator
			(
				&_allocator[0],
				&_allocator[_front],
				&_allocator[_back],
				IQueue<T>::size(),
				IQueue<T>::capacity())
			);
	}

	template<size_t Capacity, typename T>
	inline bool BoundedPQ<Capacity, T>::do_empty() const
	{
		return IQueue<T>::size() == 0;
	}

	template<size_t Capacity, typename T>
	inline bool BoundedPQ<Capacity, T>::do_full() const
	{
		return IQueue<T>::size() == IQueue<T>::capacity();
	}

	template<size_t Capacity, typename T>
	inline const T& BoundedPQ<Capacity, T>::do_front() const
	{
		if (IQueue<T>::empty())
			throw IQueue<T>::BadQueue(IQueue<T>::QueueProblem::EMPTY_QUEUE_FRONT);
		return _allocator[_front];
	}

	template<size_t Capacity, typename T>
	inline size_t BoundedPQ<Capacity, T>::do_capacity() const
	{
		return Capacity;
	}

	template<size_t Capacity, typename T>
	inline size_t BoundedPQ<Capacity, T>::do_size() const
	{
		return _size;
	}

	template<size_t Capacity, typename T>
	inline void BoundedPQ<Capacity, T>::do_pop_front()
	{
		if (IQueue<T>::empty())
			throw IQueue<T>::BadQueue(IQueue<T>::QueueProblem::EMPTY_QUEUE_POP);
		--_size;
		_front = next_index(_front);
	}

	template<size_t Capacity, typename T>
	inline void BoundedPQ<Capacity, T>::do_put_back(const T& value)
	{
		if (IQueue<T>::full())
			throw IQueue<T>::BadQueue(IQueue<T>::QueueProblem::FULL_QUEUE_PUT);
		++_size;
		_allocator[_back = next_index(_back)] = value;

		for (size_t i = _back; i != _front; i = prev_index(i))
		{
			if (_allocator[prev_index(i)] < _allocator[i])
				std::swap(_allocator[prev_index(i)], _allocator[i]);
		}
	}

	template<size_t Capacity, typename T>
	inline size_t BoundedPQ<Capacity, T>::next_index(const size_t i) const
	{
		return (i + 1 < IQueue<T>::capacity()) ? (i + 1) : 0;
	}

	template<size_t Capacity, typename T>
	inline size_t BoundedPQ<Capacity, T>::prev_index(const size_t i) const
	{
		return (i > 0) ? (i - 1) : (IQueue<T>::capacity() - 1);
	}
}
#endif // !_BOUNDED_PQ_H