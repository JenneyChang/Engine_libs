#ifndef DLINK_ITERATOR_H
#define DLINK_ITERATOR_H

#include "Iterator.h"

class DLinkIterator : public Iterator
{
public: 
	Node* pHead;
	Node* pCurr;
	bool done;

public: 
	DLinkIterator(const DLinkIterator&) = delete;
	DLinkIterator& operator=(const DLinkIterator&) = delete;

	DLinkIterator();
	virtual ~DLinkIterator() = default;

	Node* Next() override;
	Node* First() override;
	Node* Curr() override;

	bool IsDone() override;

	void ResetIterator(Node* pHead) override;

private: 
	void prClear();


};

#endif // !DLINK_ITERATOR_H
