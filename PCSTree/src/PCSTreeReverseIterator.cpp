#include "PCSTreeReverseIterator.h"
#include "PCSTree.h"

namespace Azul
{
	//----------------------------------------------------------------------------------
	//	CONSTRUCTION
	//----------------------------------------------------------------------------------

	Azul::PCSTreeReverseIterator::PCSTreeReverseIterator(PCSNode* rootNode)
		: root(rootNode), current(nullptr), prevNode(nullptr)
	{ 
		assert(rootNode != nullptr);
	}


	//----------------------------------------------------------------------------------
	//	PUBLIC METHODS
	//----------------------------------------------------------------------------------

	PCSNode* PCSTreeReverseIterator::First()
	{
		if (root != nullptr)
		{
			/*this->current = GetTail();*/
			this->current = PCSTree::pTail;
		}
		else
		{
			this->root = nullptr;
			this->current = nullptr;
		}

		return current;
	}

	PCSNode* PCSTreeReverseIterator::Next()
	{
		prevNode = this->current;
		if (prevNode != nullptr)
		{
			current = prevNode->GetReverse();
		}

		return current;
	}

	bool PCSTreeReverseIterator::IsDone()
	{
		return (current == nullptr);
	}

	PCSNode* PCSTreeReverseIterator::CurrentItem()
	{
		return current;
	}

}