#include "DLink.h"

DLink::DLink()
{ 
	this->pNext = nullptr;
	this->pPrev = nullptr;
}

void DLink::ResetLink()
{
	this->pNext = nullptr;
	this->pPrev = nullptr;
}

void DLink::PrintLink()
{
	if (this->pPrev == nullptr)
	{
		Trace::out("\t prev: nullptr\n");
	}
	else
	{
		Trace::out("\t prev: %s (%p)\n", pPrev->GetName(), pPrev);
	}

	if (this->pNext == nullptr)
	{
		Trace::out("\t next: nullptr\n");
	}
	else
	{
		Trace::out("\t next: %s (%p)\n", pNext->GetName(), pNext);
	}
}