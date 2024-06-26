#include "PCSTreeForwardIterator.h"

namespace Azul
{
	//----------------------------------------------------------------------------------
	//	CONSTRUCTION
	//----------------------------------------------------------------------------------

	PCSTreeForwardIterator::PCSTreeForwardIterator(PCSNode* rootNode)
		: root(rootNode), current(nullptr)
	{ 
		assert(rootNode);
	}


	//----------------------------------------------------------------------------------
	//	PUBLIC METHODS
	//----------------------------------------------------------------------------------

	PCSNode* PCSTreeForwardIterator::First()
	{
		if (this->root != nullptr)
		{
			this->current = this->root;
		}
		else
		{
			this->root = nullptr;
			this->current = nullptr;
		}
		
		return this->current;
	}

	PCSNode* PCSTreeForwardIterator::Next() 
	{ 
		PCSNode* tmp = this->current;
		if (tmp != nullptr)
		{
			tmp = tmp->GetForward();
		}
		this->current = tmp;

		return this->current;
	}

	bool PCSTreeForwardIterator::IsDone()
	{ 
		return (current == nullptr);
	}

	PCSNode* PCSTreeForwardIterator::CurrentItem()
	{
		return this->current;
	}

}
