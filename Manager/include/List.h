#ifndef LIST_H
#define LIST_H

#include "Node.h"
#include "Iterator.h"

class List
{
public: 
	List() = default;
	List(const List&) = delete;
	List& operator=(const List&) = delete;
	virtual ~List() = default;

	virtual void AddToFront(Node* pNode) = 0;
	virtual void AddToEnd(Node* pNode) = 0;
	virtual void Remove(Node* pNode) = 0;
	virtual Node* RemoveFromFront() = 0;

	virtual Iterator* GetIterator() = 0;

	virtual void AddByPriority(Node* pNode) { AZUL_UNUSED_VAR(pNode); assert(false); }

};

#endif // !LIST_H
