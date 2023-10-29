#ifndef ITERATOR_H
#define ITERATOR_H

#include "Node.h"

class Iterator
{
public: 
	Iterator() = default;
	virtual ~Iterator() = default;

	virtual Node* Next() = 0;
	virtual Node* First() = 0;
	virtual Node* Curr() = 0;

	virtual bool IsDone() = 0;

	virtual void ResetIterator(Node* pHead) = 0;
};

#endif // !ITERATOR_h
