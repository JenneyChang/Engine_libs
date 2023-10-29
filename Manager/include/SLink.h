#pragma once
#ifndef SLINK_H
#define SLINK_H

#include "Node.h"

class SLink : public Node
{
public:
	SLink* pNext;

	SLink(const SLink&) = delete;
	SLink& operator=(const SLink&) = delete;

	SLink();
	virtual ~SLink() = default;

	//mandatory overloads
	void ResetLink() override;
	void PrintLink() override;


};
#endif // !SLINK_H
