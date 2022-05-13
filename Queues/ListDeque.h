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
	class ListDeque : virtual public IDeque<T>
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
		ListDeque();
		virtual ~ListDeque();
		ListDeque(const ListDeque&) = delete;
		ListDeque& operator=(const ListDeque&) = delete;
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
	};

	template<typename T>
	inline ListDeque<T>::ListDeque()
		:	_front(nullptr),
			_back(nullptr),
			_size(0)
	{
		return;
	}

	template<typename T>
	inline ListDeque<T>::~ListDeque()
	{
		Node<T>* prev;
		while (_front)
		{
			prev = _front;
			_front = _front->_next;
			delete prev;
		}

		_back = nullptr;
		_size = 0;

		return;
	}

	template<typename T>
	inline typename ListDeque<T>::ConstIterator& ListDeque<T>::attach() const
	{
		return *(new ConstIterator(_front));
	}

	template<typename T>
	inline typename ListDeque<T>::Iterator& ListDeque<T>::attach()
	{
		return *(new Iterator(_front));
	}

	template<typename T>
	inline bool ListDeque<T>::do_empty() const
	{
		return _front == nullptr;
	}

	template<typename T>
	inline bool ListDeque<T>::do_full() const
	{
		return false;
	}

	template<typename T>
	inline const T& ListDeque<T>::do_front() const
	{
		if (IQueue<T>::empty())
			throw IQueue<T>::BadQueue(QueueProblem::EMPTY_QUEUE_FRONT);
		return _front->_value;
	}
	template<typename T>
	inline const T& ListDeque<T>::do_back() const
	{
		if (IQueue<T>::empty())
			throw IQueue<T>::BadQueue(QueueProblem::EMPTY_QUEUE_BACK);
		return _back->_value;
	}
	template<typename T>
	inline size_t ListDeque<T>::do_capacity() const
	{
		return -1;
	}

	template<typename T>
	inline size_t ListDeque<T>::do_size() const
	{
		return _size;
	}

	template<typename T>
	inline void ListDeque<T>::do_pop_front()
	{
		if (IQueue<T>::empty())
			throw IQueue<T>::BadQueue(QueueProblem::EMPTY_QUEUE_POP);
		--_size;
		Node<T>* old_front = _front;
		_front = _front->_next;
		delete old_front;

		return;
	}

	template<typename T>
	inline void ListDeque<T>::do_pop_back()
	{
		if (IQueue<T>::empty())
			throw IQueue<T>::BadQueue(QueueProblem::EMPTY_QUEUE_POP);
		--_size;
		Node<T>* old_back = _back;
		_back = _back->_prev;
		delete old_back;

		return;
	}

	template<typename T>
	inline void ListDeque<T>::do_put_front(const T& value)
	{
		++_size;

		if (IQueue<T>::empty())
		{
			_back = _front = new Node<T>(value, nullptr, nullptr);
			return;
		}

		_front = _front->_prev = new Node<T>(value, _front, nullptr);

		return;
	}

	template<typename T>
	inline void ListDeque<T>::do_put_back(const T& value)
	{
		++_size;

		if (IQueue<T>::empty())
		{
			_back = _front = new Node<T>(value, nullptr, nullptr);
			return;
		}

		_back = _back->_next = new Node<T>(value, nullptr, _back);

		return;
	}
}
#endif // !_LIST_DEQUE_H_
