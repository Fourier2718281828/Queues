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