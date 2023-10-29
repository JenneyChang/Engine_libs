#pragma once
#ifndef SLINK_ITERATOR_H
#define SLINK_ITERATOR_H

#include "Iterator.h"

class SLinkIterator : public Iterator
{
public:
	Node* pHead;
	Node* pCurr;
	bool done;

	//deleted 
	SLinkIterator(const SLinkIterator&) = delete;
	SLinkIterator& operator=(const SLinkIterator&) = delete;

	SLinkIterator();
	virtual ~SLinkIterator() = default;

	Node* Next() override;
	Node* First() override;
	Node* Curr() override;

	bool IsDone() override;

	void ResetIterator(Node* pHead) override;


private:
	void prClear();


};
#endif // !SLINK_ITERATOR_H
