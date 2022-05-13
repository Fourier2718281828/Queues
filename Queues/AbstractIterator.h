#ifndef _ABSTRACT_ITERATOR_H_
#define	_ABSTRACT_ITERATOR_H_
#include "Conditional.h"
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
	template <bool IsConstant, class T>
	class AbstractIterator
	{
	public:
		using cond_ref = conditional_t<IsConstant, const T&, T&>;
		class BadIterator;
	public:
		AbstractIterator() = default;
		virtual ~AbstractIterator() = default;
		inline AbstractIterator& clone();
		inline void start();
		inline bool stop()										const;
		inline const AbstractIterator& operator++()				const;
		inline const AbstractIterator& operator+=(const size_t)	const;
		inline const T& operator*()								const;
		inline cond_ref operator*();
	private:
		virtual inline AbstractIterator& do_clone() = 0;
		virtual inline void do_start() = 0;
		virtual inline bool do_stop()											const = 0;
		virtual inline const AbstractIterator& do_preincrement()				const = 0;
		virtual inline const AbstractIterator& do_assign_plus(const size_t)		const = 0;
		virtual inline const T& do_operator_star()								const = 0;
		virtual inline cond_ref do_operator_star() = 0;
	protected:
		enum class ItorProblem
		{
			CONTAINER_MODIFIED,
			ITERATOR_HAS_STOPPED,
		};
	};

	template <bool IsConstant, class T>
	inline AbstractIterator<IsConstant, T>& AbstractIterator<IsConstant, T>::clone()
	{
		return do_clone();
	}

	template <bool IsConstant, class T>
	inline void AbstractIterator<IsConstant, T>::start()
	{
		do_start();
		return;
	}

	template <bool IsConstant, class T>
	inline bool AbstractIterator<IsConstant, T>::stop() const
	{
		return do_stop();
	}

	template <bool IsConstant, class T>
	inline const AbstractIterator<IsConstant, T>& AbstractIterator<IsConstant, T>::operator++() const
	{
		return do_preincrement();
	}

	template <bool IsConstant, class T>
	inline const AbstractIterator<IsConstant, T>& AbstractIterator<IsConstant, T>::operator+=(const size_t i) const
	{
		return do_assign_plus(i);
	}
	template <bool IsConstant, class T>
	inline const T& AbstractIterator<IsConstant, T>::operator*() const
	{
		return do_operator_star();
	}
	template <bool IsConstant, class T>
	inline typename AbstractIterator<IsConstant, T>::cond_ref
		AbstractIterator<IsConstant, T>::operator*()
	{
		return do_operator_star();
	}

	template <bool IsConstant, class T>
	class AbstractIterator<IsConstant, T>::BadIterator
	{
	private:
		const std::string _message;

	public:
		BadIterator(const ItorProblem p)
			: _message(to_string(p))
		{
			return;
		}

		~BadIterator()
		{
			return;
		}

		inline void print_diagnosis(ostream& o) const
		{
			o << _message << '\n';
		}
	private:
		inline std::string to_string(const ItorProblem) const;
	};

	template <bool IsConstant, class T>
	inline std::string AbstractIterator<IsConstant, T>::BadIterator::to_string(const ItorProblem problem) const
	{
		switch (problem)
		{
		case ItorProblem::CONTAINER_MODIFIED:
			return "Contaiter's modification during iteration.";
		case ItorProblem::ITERATOR_HAS_STOPPED:
			return "Iteration via expired iterator.";
		default:
			return "The problem was not stated";
		}
	}
}
#endif // !_ABSTRACT_ITERATOR_H_
