#ifndef DLINK_MAN_H
#define DLINK_MAN_H

#include "List.h"
#include "DLink.h"
#include "Iterator.h"


class DLinkMan : public List
{
protected:
	DLink* pHead;
	DLink* pTail;

	Iterator* pIterator;

public:
	DLinkMan(const DLinkMan&) = delete;
	DLinkMan& operator=(const DLinkMan&) = delete;

	DLinkMan();
	virtual ~DLinkMan();

	void AddToFront(Node* pNode) override;
	void AddToEnd(Node* pNode) override;
	void Remove(Node* pNode) override;
	Node* RemoveFromFront() override;

	Iterator* GetIterator() override;

	void AddByPriority(Node* pNode) override;


};

#endif