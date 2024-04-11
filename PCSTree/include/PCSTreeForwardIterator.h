#ifndef PCSTREE_FORWARD_ITERATOR_H
#define PCSTREE_FORWARD_ITERATOR_H

#include "PCSTreeIterator.h"

namespace Azul
{
	class PCSTreeForwardIterator : public PCSTreeIterator
	{
	public:
		PCSTreeForwardIterator(PCSNode *rootNode);
		virtual ~PCSTreeForwardIterator() = default;

		virtual PCSNode *First() override;
		virtual PCSNode *Next() override;
		virtual bool IsDone() override;
		virtual PCSNode *CurrentItem() override;


	private:
		PCSNode *root;
		PCSNode *current;

	};
}

#endif

// ---  End of File ---------------
