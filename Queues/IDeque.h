#ifndef _IDEQUE_H_
#define _IDEQUE_H_
#include "IterableQueue.h"
#include <ostream>
using std::ostream;

//#############################################################################
//					��ᒺ����-��������� ��������������					   
//												
//		������������� �������� ��� �������� 2 ����� ���������� �����������
//		������������� ����������� �����-����������� ��������
//		�������� �������� 2021-22 ���������� ��
//
//	5.  ��������� ��������� ����������� ���� Deque.
//	6.	��������� ��������� ������������ ����� �� ��� ������.
//	7.	��������� ��������� �������� ������������ ����� �� ��� ������.
//	8.	��������� ��������� ���������� ������������ ����� �� ��� ������.
//	9.	������������� � ���������� ��������� ����� : 
//		���������� �� ������ � ���� �������, � ������� � �������� ����������.
//
//	10*.������������� � ���������� ������� ���� � �����������, 
//		������� �� ���� � �������� ����.
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
		inline void pop_front();
		inline void put_back(const T& value);
	private:
		virtual inline const T& do_back()	const			= 0;
		virtual inline void do_pop_front()					= 0;
		virtual inline void do_put_back(const T& value)		= 0;
	};

	template<typename T>
	inline const T& IDeque<T>::back() const
	{
		return do_back();
	}

	template<typename T>
	inline void IDeque<T>::pop_front()
	{
		return do_pop_front();
	}

	template<typename T>
	inline void IDeque<T>::put_back(const T& value)
	{
		return do_put_back(value);
	}
}
#endif // !_IDEQUE_H_