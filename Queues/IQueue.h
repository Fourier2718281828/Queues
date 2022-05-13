#ifndef _IQUEUE_
#define _IQUEUE_
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
	template <typename T>
	class IQueue
	{
	public:
		class BadQueue;
	public:
		IQueue() = default;
		virtual ~IQueue() = default;
		IQueue(const IQueue&) = delete;
		IQueue& operator=(const IQueue&) = delete;
		inline bool		empty()			const;
		inline bool		full()			const;
		inline const T& front()			const;
		inline size_t	capacity()		const;
		inline size_t	size()			const;
		inline void		pop_back();
		inline void		put_front(const T& value);
	private:
		virtual inline bool		do_empty()			const		= 0;
		virtual inline bool		do_full()			const		= 0;
		virtual inline const T& do_front()			const		= 0;
		virtual inline size_t	do_capacity()		const		= 0;
		virtual inline size_t	do_size()			const		= 0;
		virtual inline void		do_pop_back()					= 0;
		virtual inline void		do_put_front(const T& value)	= 0;
	protected:
		enum class QueueProblem
		{
			EMPTY_QUEUE_FRONT,
			EMPTY_QUEUE_POP,
			FULL_QUEUE_PUT,
			//PEEKBACK_INDEX_OUT_OF_BOUNDS,  ??
		};
	};

	template<typename T>
	inline bool IQueue<T>::empty() const
	{
		return do_empty();
	}

	template<typename T>
	inline bool IQueue<T>::full() const
	{
		return do_full();
	}

	template<typename T>
	inline const T& IQueue<T>::front() const
	{
		return do_front();
	}

	template<typename T>
	inline size_t IQueue<T>::capacity() const
	{
		return do_capacity();
	}

	template<typename T>
	inline size_t IQueue<T>::size() const
	{
		return do_size();
	}

	template<typename T>
	inline void IQueue<T>::pop_back()
	{
		do_pop_back();
		return;
	}

	template<typename T>
	inline void IQueue<T>::put_front(const T& value)
	{
		do_put_front(value);
		return;
	}

	template<typename T>
	class IQueue<T>::BadQueue
	{
	private:
		const std::string _message;

	public:
		BadQueue(const QueueProblem p)
			: _message(to_string(p))
		{
			return;
		}

		~BadQueue()
		{
			return;
		}

		inline void print_diagnosis(ostream& o) const
		{
			o << _message << '\n';
		}
	private:
		inline std::string to_string(const QueueProblem) const;
	};

	template<typename T>
	inline std::string IQueue<T>::BadQueue::to_string(const QueueProblem problem) const
	{
		switch (problem)
		{
		case QueueProblem::EMPTY_QUEUE_FRONT:
			return "Empty queue has no front.";
		case QueueProblem::EMPTY_QUEUE_POP:
			return "Cannot pop from an empty queue.";
		case QueueProblem::FULL_QUEUE_PUT:
			return "Cannot put to a full queue.";
		/*case QueueProblem::PEEKBACK_INDEX_OUT_OF_BOUNDS:
			return "The non-existent element cannot be peeked.";*/
		default:
			return "The problem wasn not stated";
		}
	}
}
#endif // !_IQUEUE_