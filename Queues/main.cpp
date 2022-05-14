#include "ArrayDeque.h"
#include "ListDeque.h"
#include "UnboundedDeque.h"
#include "BoundedPQ.h"
#include "UnboundedPQ.h"
#include "PeekBackArrayDeque.h"
#include "PeekBackListDeque.h"
#include "PeekBackUnboundedDeque.h"
#include "PeekBackBoundedPQ.h"
#include "PeekBackUnboundedPQ.h"
#include <iostream>
using namespace exam;
using std::cout;
using std::endl;

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

void testDeque(IDeque<int>& d)
{
	cout << typeid(d).name() << endl;

	for (int i = 0; i < 5; ++i)
	{
		cout << d << endl;
		d.put_front(i);
		d.put_back(i);
	}

	cout << d << endl;

	while (!d.empty())
	{
		d.pop_front();
		cout << d << endl;
	}

	cout << "----------------------------------------------------" << endl;
}

void testPeekBackDeque(IPeekBackDeque<int>& d)
{
	cout << typeid(d).name() << endl;

	for (int i = 0; i < 5; ++i)
	{
		cout << d << endl;
		d.put_front(i);
		d.put_back(i);
	}

	cout << d << endl;

	cout << "Using peekback :" << endl;
	
	for (size_t i = 0u; i < d.size(); ++i)
	{
		cout << d.peekback(i) << ' ';
	}

	cout << endl;

	cout << "----------------------------------------------------" << endl;
}

int main(void)
{
	/*ArrayDeque<11, int> ad;
	ListDeque<int> ld;
	UnboundedDeque<int> ud;
	testDeque(ad);
	testDeque(ld);
	testDeque(ud);

	PeekBackArrayDeque<11, int> pad;
	PeekBackListDeque<int> pld;
	PeekBackUnboundedDeque<int> pud;
	testPeekBackDeque(pad);
	testPeekBackDeque(pld);
	testPeekBackDeque(pud);*/

	UnboundedPQ<int> q;
	cout << q << endl;
	q.put_front(5);
	cout << q << endl;
	q.put_front(4);
	cout << q << endl;
	q.put_front(10);
	cout << q << endl;
	q.put_front(8);
	cout << q << endl;
	q.pop_back();
	cout << q << endl;
	q.put_front(7);
	cout << q << endl;
	q.put_front(1);
	cout << q << endl;
	q.put_front(1);
	q.put_front(1);
	q.put_front(1);
	cout << q << endl;
	q.put_front(0);
	cout << q << endl;

	return 0;
}