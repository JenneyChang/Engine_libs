//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef PCSTREE_REVERSE_ITERATOR_H
#define PCSTREE_REVERSE_ITERATOR_H

#include "PCSTreeIterator.h"

namespace Azul
{
	class PCSTreeReverseIterator : public PCSTreeIterator
	{
	public:
		PCSTreeReverseIterator(PCSNode *rootNode);
		virtual ~PCSTreeReverseIterator() = default;

		virtual PCSNode *First() override;
		virtual PCSNode *Next() override;
		virtual bool IsDone() override;
		virtual PCSNode *CurrentItem() override;

	private:
		// YOU can store what you want... here
		// these were my variables...
		PCSNode *root;		//basically end of rev tree
		PCSNode *current;
		PCSNode *prevNode;

	};

}

#endif

// ---  End of File ---------------