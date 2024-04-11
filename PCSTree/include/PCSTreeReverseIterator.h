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
		PCSNode *root;		//basically end of rev tree
		PCSNode *current;
		PCSNode *prevNode;

	};

}

#endif

// ---  End of File ---------------
