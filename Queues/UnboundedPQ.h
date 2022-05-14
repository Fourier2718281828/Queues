#ifndef _UBOUNDED_PQ_H
#define _UBOUNDED_PQ_H
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
	template<typename T>
	class UnboundedPQ : virtual public IterableQueue<T>
	{
	public:
		using Iterator = ArrayQueueIterator<false, T>;
		using ConstIterator = ArrayQueueIterator<true, T>;
	private:
		size_t _size;
		size_t _capacity;
		T* _allocator;
		static const size_t DEFAULT_CAPACITY;
		static const size_t FRONT;
	public:
		explicit UnboundedPQ(const size_t = DEFAULT_CAPACITY);
		virtual ~UnboundedPQ();
		UnboundedPQ(const UnboundedPQ&)				= delete;
		UnboundedPQ& operator=(const UnboundedPQ&)	= delete;
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
		inline void resize(const size_t);
		inline void emerge(const size_t);
		inline void plunge(const size_t);
	};

	template<typename T>
	const size_t UnboundedPQ<T>::DEFAULT_CAPACITY = 0;

	template<typename T>
	const size_t UnboundedPQ<T>::FRONT = 1;

	template<typename T>
	inline UnboundedPQ<T>::UnboundedPQ(const size_t capacity)
		:	_size(0),
			_capacity(capacity),
			_allocator(new T[capacity + 1])
	{
		return;
	}

	template<typename T>
	inline UnboundedPQ<T>::~UnboundedPQ()
	{
		_size = 0;
		delete[] _allocator;
		_allocator = nullptr;
		return;
	}

	template<typename T>
	inline typename UnboundedPQ<T>::ConstIterator& UnboundedPQ<T>::attach() const
	{
		return *(
			new ConstIterator
			(
				&_allocator[0],
				&_allocator[1],
				&_allocator[IQueue<T>::size()],
				IQueue<T>::size(),
				IQueue<T>::capacity() + 1
			)
			);
	}

	template<typename T>
	inline typename UnboundedPQ<T>::Iterator& UnboundedPQ<T>::attach()
	{
		return *(
			new Iterator
			(
				&_allocator[0],
				&_allocator[1],
				&_allocator[IQueue<T>::size()],
				IQueue<T>::size(),
				IQueue<T>::capacity() + 1)
			);
	}

	template<typename T>
	inline bool UnboundedPQ<T>::do_empty() const
	{
		return IQueue<T>::size() == 0;
	}

	template<typename T>
	inline bool UnboundedPQ<T>::do_full() const
	{
		return IQueue<T>::capacity() == IQueue<T>::size();
	}

	template<typename T>
	inline const T& UnboundedPQ<T>::do_front() const
	{
		if (IQueue<T>::empty())
			throw IQueue<T>::BadQueue(IQueue<T>::QueueProblem::EMPTY_QUEUE_FRONT);
		return _allocator[FRONT];
	}

	template<typename T>
	inline size_t UnboundedPQ<T>::do_capacity() const
	{
		return _capacity;
	}

	template<typename T>
	inline size_t UnboundedPQ<T>::do_size() const
	{
		return _size;
	}

	template<typename T>
	inline void UnboundedPQ<T>::do_pop_front()
	{
		if (IQueue<T>::empty())
		{
			throw IQueue<T>::BadQueue(IQueue<T>::QueueProblem::EMPTY_QUEUE_POP);
		}

		std::swap(_allocator[1], _allocator[_size--]);
		plunge(1);

		if (IQueue<T>::size() <= IQueue<T>::capacity() / 4)
		{
			resize(2 * IQueue<T>::size());
		}

		return;
	}

	template<typename T>
	inline void UnboundedPQ<T>::do_put_back(const T& value)
	{
		if (IQueue<T>::full())
		{
			resize(2 * IQueue<T>::capacity() + 1);
		}
		_allocator[++_size] = value;
		emerge(_size);
		return;
	}

	template<typename T>
	inline void UnboundedPQ<T>::resize(const size_t new_capacity)
	{
		auto& itor_prev = attach();
		T* prev = _allocator;
		_allocator = new T[new_capacity + 1];
		_capacity = new_capacity;
		auto& itor_next = attach();

		while (!itor_prev.stop())
		{
			*itor_next = std::move(*itor_prev);
			++itor_next;
			++itor_prev;
		}

		delete& itor_prev;
		delete& itor_next;
		delete[] prev;
		prev = nullptr;

		return;
	}
	template<typename T>
	inline void UnboundedPQ<T>::emerge(const size_t i0)
	{
		size_t i = i0;

		while ((i / 2) && _allocator[i / 2] < _allocator[i])
		{
			std::swap(_allocator[i / 2], _allocator[i]);
			i /= 2;
		}

		return;
	}
	template<typename T>
	inline void UnboundedPQ<T>::plunge(const size_t i0)
	{
		size_t i = i0;
		while (2 * i <= IQueue<T>::size())
		{
			size_t j = 2 * i;
			j += j < IQueue<T>::size() && _allocator[j] < _allocator[j + 1];
			if (!(_allocator[i] < _allocator[j]))
				break;
			std::swap(_allocator[i], _allocator[j]);
			i = j;
		}

		return;
	}
}

#endif // !_BOUNDED_PQ_H
