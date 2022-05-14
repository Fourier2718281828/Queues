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
#include <cstdlib>
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

template<typename T>
void testDeque(IDeque<T>& d)
{
	cout << typeid(d).name() << endl;

	cout << d << endl;
	try
	{
		cout << "front or back :" << endl;
		cout << "front = " << d.front() << ", back = " << d.back() << endl;
	}
	catch (const IDeque<int>::BadQueue& bq)
	{
		bq.print_diagnosis(cout);
	}

	for (int i = 0; i < 4; ++i)
	{
		d.put_front(i);
		cout << "put_front(" << i << ") : " << d << endl;
		d.put_back(i);
		cout << "put_back(" << i << ") : " << d << endl;
		cout << "front = " << d.front() << ", back = " << d.back() << endl;
	}

	try
	{
		while (!d.empty())
		{
			d.pop_front();
			cout << "pop_front() : " << d << endl;
			if (!d.empty())
			{
				d.pop_back();
				cout << "pop_back() : " << d << endl;
			}
			if (d.empty()) break;
			cout << "front = " << d.front() << ", back = " << d.back() << endl;
		}
	}
	catch (const IDeque<int>::BadQueue& bq)
	{
		bq.print_diagnosis(cout);
	}

	cout << "When pop_back or pop_front on an empty queue : " << endl;

	try
	{
		d.pop_front();
	}
	catch (const IDeque<int>::BadQueue& bq)
	{
		bq.print_diagnosis(cout);
	}

	try
	{
		d.pop_back();
	}
	catch (const IDeque<int>::BadQueue& bq)
	{
		bq.print_diagnosis(cout);
	}
	cout << "--------------------------------------------------------------------------" << endl;
}

template<typename T>
void testPeekBackDeque(IPeekBackDeque<T>& d)
{
	cout << typeid(d).name() << endl;

	for (int i = 0; i < 4; ++i)
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

	cout << "When exceeded the limits : " << endl;
	try
	{
		d.peekback(d.size());
	}
	catch (const IPeekBackDeque<T>::BadQueue& bq)
	{
		bq.print_diagnosis(cout);
	}

	cout << "--------------------------------------------------------------------------" << endl;
}

template<typename T>
void testIterableQueue(IterableQueue<T>& d)
{
	cout << typeid(d).name() << endl;
	srand(time(NULL));
	size_t r = 0;
	cout << "Filling with random numbers : " << endl;
	for (size_t i = 0u; i < 7; ++i)
	{
		r = rand() % 20 + 1;
		d.put_back(r);
		cout << "put_back(" << r << ") : " << d << endl;
		cout << "front (max) = " << d.front() << endl;
	}

	cout << "Popping and getting a sorted array : " << endl;
	const size_t size = d.size();
	int* arr = new int[size];

	cout << d << endl;
	
	for (size_t i = 0u; !d.empty(); ++i)
	{
		arr[i] = d.front();
		d.pop_front();
		cout << d << endl;
	}

	cout << "The resulting array : ";
	for (size_t i = 0u; i < size; ++i)
	{
		cout << arr[i] << (i == size - 1 ? "" : ", ");
	}
	cout << endl;

	delete[] arr; arr = nullptr;

	cout << "--------------------------------------------------------------------------" << endl;
}

template<typename T>
void testPeekBackQueue(IPeekBackQueue<T>& d)
{
	cout << typeid(d).name() << endl;
	srand(time(NULL));
	size_t r = 0;
	cout << "Filling with random numbers : " << endl;
	for (size_t i = 0u; i < 7; ++i)
	{
		r = rand() % 20 + 1;
		d.put_back(r);
		cout << "put_back(" << r << ") : " << d << endl;
		cout << "front (max) = " << d.front() << endl;
	}
	cout << "Print the queue using peekback method (not necessarily sorted): " << endl;
	for(size_t i = 0u; i < d.size(); ++i)
	{
		cout << d.peekback(i) << (i == d.size() - 1 ? "" : ", ");
	}
	cout << endl;
	cout << "--------------------------------------------------------------------------" << endl;
}


int main(void)
{
	cout << "##########################################################################" << endl;
	cout << "Testing Deques" << endl;
	cout << "ArrayDeque \t- deque implementation on cyclic array" << endl;
	cout << "ListDeque \t- deque implementation on list" << endl;
	cout << "UnboundedDeque \t- deque implementation on resizable cyclic array" << endl;
	cout << "--------------------------------------------------------------------------" << endl;

	ArrayDeque<11, int> ad;
	ListDeque<int> ld;
	UnboundedDeque<int> ud;
	testDeque(ad);
	testDeque(ld);
	testDeque(ud);

	cout << "##########################################################################" << endl;
	cout << "Testing Deques" << endl;
	cout << "PeekBackArrayDeque \t- peek-back deque impl. on cyclic array" << endl;
	cout << "PeekBackListDeque \t- peek-back deque impl. on list" << endl;
	cout << "PeekBackUnboundedDeque \t- peek-back deque impl. on resizable cyclic array" << endl;
	cout << "--------------------------------------------------------------------------" << endl;

	PeekBackArrayDeque<11, int> pad;
	PeekBackListDeque<int> pld;
	PeekBackUnboundedDeque<int> pud;
	testPeekBackDeque(pad);
	testPeekBackDeque(pld);
	testPeekBackDeque(pud);


	cout << "##########################################################################" << endl;
	cout << "Testing Priority Queues" << endl;
	cout << "BoundedPQ \t- pq implementation on sorted array" << endl;
	cout << "UnboundedPQ \t- pq implementation on binary heap (array not sorted!)" << endl;
	cout << "--------------------------------------------------------------------------" << endl;


	BoundedPQ<11, int> bpq;
	UnboundedPQ<int> ubpq;

	testIterableQueue(bpq);
	testIterableQueue(ubpq);

	cout << "##########################################################################" << endl;
	cout << "Testing Priority Queues" << endl;
	cout << "PeekBackBoundedPQ   - peek-back pq impl. on sorted array" << endl;
	cout << "PeekBackUnboundedPQ - peek-back pq impl. on bin. heap (array not sorted!)" << endl;
	cout << "--------------------------------------------------------------------------" << endl;

	PeekBackBoundedPQ<11, int> pbpq;
	PeekBackUnboundedPQ<int> pupq;

	testPeekBackQueue(pbpq);
	testPeekBackQueue(pupq);

	return 0;
}