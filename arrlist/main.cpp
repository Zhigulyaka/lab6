#include <iostream>
#include "ArrList.h"

void main()
{
	ArrList<int> l1(3);
	l1.InsFirst(5);
	l1.InsLast(6);
	l1.InsLast(7);
	cout << l1 << endl;
	l1.Rotate();
	cout << "Changed list" << l1 << endl;
}
