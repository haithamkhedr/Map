
#ifndef STACK_h
#define STACK_h
#include "dbc.h"
#include "LinkedList.h"

using namespace std;

 template <class Item>
 class Stack
	{
	public:
		void push(const Item &item);
		Item pop();
		Item getTopItem()const;
		int getNumberOfItems();
		bool isEmpty();
	private:
		LinkedList<Item> stack;
	};


 

 template <class Item> void  Stack<Item>::push(const Item &item)
{
	int oldNumberOfItems;
	//invariant
	INVARIANT0(getNumberOfItems()>=0);
	//precondition
	REQUIRE0((oldNumberOfItems=getNumberOfItems()) || 1);

	//Implementation
	stack.addAtFront(item);

	//postcondition
	ENSURE0(getNumberOfItems()==oldNumberOfItems+1);
	//invariant
	INVARIANT0(getNumberOfItems()>=0);
}

template <class Item> Item Stack<Item>::pop()
{
	int oldNUmberOfItems;
	//invariant
	INVARIANT0(getNumberOfItems()>=0);
	//precondition
	REQUIRE0(getNumberOfItems()>0);
	REQUIRE0((oldNUmberOfItems=getNumberOfItems()) ||1);

	//Implementation
	Item temp=stack.getFirst();
	stack.removeFirst();

	//postcondition
	ENSURE0(getNumberOfItems()==(oldNUmberOfItems-1));
	//invariant
	INVARIANT0(getNumberOfItems() >= 0);
	return temp;

}
template <class Item> Item Stack<Item>::getTopItem() const
{
	return stack.getFirst();
}
template <class Item> int Stack<Item>::getNumberOfItems()
{
	return stack.getNumberOfItems();
}

template <class Item> bool Stack<Item>::isEmpty()
{
	return getNumberOfItems()==0;

}

#endif 