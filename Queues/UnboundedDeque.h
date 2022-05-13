#ifndef _UNBOUDED_DEQUE_H_
#define	_UNBOUDED_DEQUE_H_
#include "IDeque.h"
#include "ArrayQueueIterator.h"

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
		explicit UnboundedDeque(const size_t = DEFAULT_CAPACITY);
		virtual ~UnboundedDeque();
		UnboundedDeque(const UnboundedDeque&) = delete;
		UnboundedDeque& operator=(const UnboundedDeque&) = delete;
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
	private:
		inline size_t	next_index	(const size_t) const;
		inline size_t	prev_index	(const size_t) const;
		inline void		resize		(const size_t);
	};

	template<typename T>
	const size_t UnboundedDeque<T>::DEFAULT_CAPACITY = 0;

	template<typename T>
	inline UnboundedDeque<T>::UnboundedDeque(const size_t capacity)
		:	_size(0),
			_capacity(capacity),
			_front(0),
			_back(capacity - 1),
			_allocator(new T[capacity])
	{
	}

	template<typename T>
	inline UnboundedDeque<T>::~UnboundedDeque()
	{
		delete[] _allocator;
		_allocator = nullptr;
		_size = _front = _back = 0;
		return;
	}

	template<typename T>
	inline typename UnboundedDeque<T>::ConstIterator& UnboundedDeque<T>::attach() const
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

	template<typename T>
	inline typename UnboundedDeque<T>::Iterator& UnboundedDeque<T>::attach()
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

	template<typename T>
	inline bool UnboundedDeque<T>::do_empty() const
	{
		return IQueue<T>::size() == 0;
	}

	template<typename T>
	inline bool UnboundedDeque<T>::do_full() const
	{
		return IQueue<T>::size() == IQueue<T>::capacity();
	}

	template<typename T>
	inline const T& UnboundedDeque<T>::do_front() const
	{
		if (IQueue<T>::empty())
		{
			throw IQueue<T>::BadQueue(IQueue<T>::QueueProblem::EMPTY_QUEUE_FRONT);
		}

		return _allocator[_front];
	}

	template<typename T>
	inline const T& UnboundedDeque<T>::do_back() const
	{
		if (IQueue<T>::empty())
		{
			throw IQueue<T>::BadQueue(IQueue<T>::QueueProblem::EMPTY_QUEUE_BACK);
		}

		return _allocator[_back];
	}

	template<typename T>
	inline size_t UnboundedDeque<T>::do_capacity() const
	{
		return _capacity;
	}

	template<typename T>
	inline size_t UnboundedDeque<T>::do_size() const
	{
		return _size;
	}

	template<typename T>
	inline void UnboundedDeque<T>::do_pop_front()
	{
		if (IQueue<T>::empty())
		{
			throw IQueue<T>::BadQueue(IQueue<T>::QueueProblem::EMPTY_QUEUE_POP);
		}

		--_size;
		_front = next_index(_front);

		if (IQueue<T>::size() <= IQueue<T>::capacity() / 4)
		{
			resize(2 * IQueue<T>::size());
		}

		return;
	}

	template<typename T>
	inline void UnboundedDeque<T>::do_pop_back()
	{
		if (IQueue<T>::empty())
		{
			throw IQueue<T>::BadQueue(IQueue<T>::QueueProblem::EMPTY_QUEUE_POP);
		}

		--_size;
		_back = prev_index(_back);

		if (IQueue<T>::size() <= IQueue<T>::capacity() / 4)
		{
			resize(2 * IQueue<T>::size());
		}

		return;
	}

	template<typename T>
	inline void UnboundedDeque<T>::do_put_front(const T& value)
	{
		if (IQueue<T>::full())
		{
			resize(2 * IQueue<T>::capacity() + 1);
		}

		++_size;
		_allocator[_front = prev_index(_front)] = value;
		return;
	}

	template<typename T>
	inline void UnboundedDeque<T>::do_put_back(const T& value)
	{
		if (IQueue<T>::full())
		{
			resize(2 * IQueue<T>::capacity() + 1);
		}

		++_size;
		_allocator[_back = next_index(_back)] = value;
		return;
	}

	template<typename T>
	inline size_t UnboundedDeque<T>::next_index(const size_t i) const
	{
		return (i + 1 < IQueue<T>::capacity()) ? (i + 1) : 0;
	}

	template<typename T>
	inline size_t UnboundedDeque<T>::prev_index(const size_t i) const
	{
		return (i > 0) ? (i - 1) : (IQueue<T>::capacity() - 1);
	}

	template<typename T>
	inline void UnboundedDeque<T>::resize(const size_t new_capacity)
	{
		
		auto& itor_prev = attach();
		T* prev = _allocator;
		_allocator = new T[new_capacity];
		_capacity = new_capacity;
		_front = 0;
		_back = (IQueue<T>::size() ? IQueue<T>::size() : IQueue<T>::capacity()) - 1;
		auto& itor_next = attach();

		while (!itor_prev.stop())
		{
			*itor_next = *itor_prev;
			++itor_next;
			++itor_prev;
		}
		
		delete& itor_prev;
		delete& itor_next;
		delete[] prev;
		prev = nullptr;
		
		return;
	}
}
#endif // !_UNBOUDED_DEQUE_H_