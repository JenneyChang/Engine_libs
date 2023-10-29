#pragma once
#ifndef SLINK_MAN_H
#define SLINK_MAN_H

#include "List.h"
#include "SLink.h"
#include "Iterator.h"

class SLinkMan : public List
{
public:
	SLinkMan(const SLinkMan&) = delete;
	SLinkMan& operator=(const SLinkMan&) = delete;

	SLinkMan();
	virtual ~SLinkMan();

	void AddToFront(Node* pNode) override;
	void AddToEnd(Node* pNode) override;
	void Remove(Node* pNode) override;
	Node* RemoveFromFront() override;

	Iterator* GetIterator() override;

protected:
	SLink* pHead;
	SLink* pTail;
	Iterator* pIterator;

};
#endif // !SLINK_MAN_H
