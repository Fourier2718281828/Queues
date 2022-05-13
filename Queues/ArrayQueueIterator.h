#ifndef _ARRAY_QUEUE_ITERATOR_
#define _ARRAY_QUEUE_ITERATOR_
#include "AbstractIterator.h"

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
	template<bool IsConstant, typename T>
	class ArrayQueueIterator : public AbstractIterator<IsConstant, T>
	{
	private:
		using AbstractIterator<IsConstant, T>::ItorProblem;
		using AbstractIterator<IsConstant, T>::BadIterator;
	public:
		using cond_ref = conditional_t<IsConstant, const T&, T&>;
		using cond_ptr = conditional_t<IsConstant, const T*, T*>;
		using cond_const_ptr = conditional_t<IsConstant, const T* const, T* const>;
	private:
		cond_const_ptr		_array_begining;
		cond_const_ptr		_start;
		cond_const_ptr		_end;
		mutable cond_ptr	_current;
		const size_t		_size;
		const size_t		_capacity;
	public:
		ArrayQueueIterator(cond_const_ptr, cond_const_ptr, cond_const_ptr, const size_t, const size_t);
		ArrayQueueIterator(const ArrayQueueIterator&);
		virtual ~ArrayQueueIterator() = default;
	private:
		virtual inline ArrayQueueIterator& do_clone()									override;
		virtual inline void do_start()													override;
		virtual inline bool do_stop()											const	override;
		virtual inline const ArrayQueueIterator& do_preincrement()				const	override;
		virtual inline const ArrayQueueIterator& do_assign_plus(const size_t)	const 	override;
		virtual inline const T& do_operator_star()								const	override;
		virtual inline cond_ref do_operator_star()										override;
	private:
		inline cond_const_ptr	step_forward(cond_const_ptr, const size_t)		const;
	};

	template<bool IsConstant, typename T>
	inline ArrayQueueIterator<IsConstant, T>::ArrayQueueIterator
	(
		ArrayQueueIterator<IsConstant, T>::cond_const_ptr array_beginning,
		ArrayQueueIterator<IsConstant, T>::cond_const_ptr start,
		ArrayQueueIterator<IsConstant, T>::cond_const_ptr end,
		const size_t size,
		const size_t capacity
	)
		: _array_begining(array_beginning),
		_start(start),
		_end(end),
		_current(size ? start : nullptr),
		_size(size),
		_capacity(capacity)
	{
		return;
	}

	template<bool IsConstant, typename T>
	inline ArrayQueueIterator<IsConstant, T>::ArrayQueueIterator(const ArrayQueueIterator& itor)
		: _array_begining(itor._array_begining),
		_start(itor._start),
		_end(itor._end),
		_current(itor._current),
		_size(itor._size),
		_capacity(itor._capacity)
	{
		return;
	}

	template<bool IsConstant, typename T> inline
		typename ArrayQueueIterator<IsConstant, T>& ArrayQueueIterator<IsConstant, T>::do_clone()
	{
		return *(new ArrayQueueIterator(*this));
	}

	template<bool IsConstant, typename T>
	inline void ArrayQueueIterator<IsConstant, T>::do_start()
	{
		_current = _start;
		return;
	}

	template<bool IsConstant, typename T>
	inline bool ArrayQueueIterator<IsConstant, T>::do_stop() const
	{
		return nullptr == _current;
	}

	template<bool IsConstant, typename T>
	inline const typename ArrayQueueIterator<IsConstant, T>&
		ArrayQueueIterator<IsConstant, T>::do_preincrement() const
	{
		return do_assign_plus(1);
	}

	template<bool IsConstant, typename T>
	inline const typename ArrayQueueIterator<IsConstant, T>&
		ArrayQueueIterator<IsConstant, T>::do_assign_plus(const size_t i) const
	{
		if (do_stop())
		{
			throw BadIterator(ItorProblem::ITERATOR_HAS_STOPPED);
		}

		_current = step_forward(_current, i);

		return *this;
	}

	template<bool IsConstant, typename T>
	inline const T& ArrayQueueIterator<IsConstant, T>::do_operator_star() const
	{
		return *_current;
	}

	template<bool IsConstant, typename T>
	inline typename ArrayQueueIterator<IsConstant, T>::cond_ref
		ArrayQueueIterator<IsConstant, T>::do_operator_star()
	{
		return *_current;
	}

	template<bool IsConstant, typename T>
	inline typename ArrayQueueIterator<IsConstant, T>::cond_const_ptr
		ArrayQueueIterator<IsConstant, T>::step_forward
		(
			ArrayQueueIterator<IsConstant, T>::cond_const_ptr curr,
			const size_t steps
		)	const
	{
		if (_end == _current)
		{
			return nullptr;
		}

		size_t sum = _current - _array_begining + steps;
		size_t next_index = _capacity == 0 ? 0 : sum % _capacity;
		auto next_position = _array_begining + next_index;

		if
			(
				(_start <= _end && next_position >= _start && next_position <= _end)
				||
				(_start > _end && (next_position >= _start || next_position <= _end))
				)
		{
			return next_position;
		}

		return nullptr;
	}
}
#endif // !_ARRAY_QUEUE_ITERATOR_ 