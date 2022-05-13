#ifndef _ITERABLE_H_
#define _ITERABLE_H_

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