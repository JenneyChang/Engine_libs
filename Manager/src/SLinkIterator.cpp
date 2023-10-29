#include "SLinkIterator.h"
#include "SLink.h"

SLinkIterator::SLinkIterator() : Iterator()
{
	this->prClear();
}

Node* SLinkIterator::Next()
{
	SLink* temp = (SLink*)this->pCurr;

	if (temp != nullptr)
	{
		temp = temp->pNext;
	}
	this->pCurr = temp;

	if (this->pCurr == nullptr)
	{
		this->done = true;
	}
	else
	{
		this->done = false;
	}

	return this->pCurr;

}
Node* SLinkIterator::First()
{
	if (this->pHead != nullptr)
	{
		this->done = false;
		this->pCurr = this->pHead;
	}
	else
	{
		this->prClear();
	}

	return this->pCurr;
}
Node* SLinkIterator::Curr()
{
	return this->pCurr;
}

bool SLinkIterator::IsDone()
{
	return this->done;
}

void SLinkIterator::ResetIterator(Node* Head)
{
	if (Head != nullptr)
	{
		this->done = false;
		this->pHead = Head;
		this->pCurr = Head;
	}
	else
	{
		this->prClear();
	}
}

void SLinkIterator::prClear()
{
	this->pHead = nullptr;
	this->pCurr = nullptr;
	this->done = true;
}