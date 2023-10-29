#include "SLink.h"

SLink::SLink()
{
	this->pNext = nullptr;
}

void SLink::ResetLink()
{
	this->pNext = nullptr;
}

void SLink::PrintLink()
{
	if (this->pNext == nullptr)
	{
		Trace::out("\t next: nullptr\n");
	}
	else
	{
		Trace::out("\t next: %s (%p)\n", pNext->GetName(), pNext);
	}
}