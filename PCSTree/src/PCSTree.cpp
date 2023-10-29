#include "PCSTree.h"
#include "PCSNode.h"

namespace Azul
{
	PCSNode* PCSTree::pTail = nullptr;

	//----------------------------------------------------------------------------------
	//	CONSTRUCTION
	//----------------------------------------------------------------------------------

	Azul::PCSTree::PCSTree()
		: mInfo{0}, pRoot(nullptr), counter(0)
	{ }

	Azul::PCSTree::~PCSTree()
	{ }


	//----------------------------------------------------------------------------------
	//	PUBLIC CLASS METHODS
	//----------------------------------------------------------------------------------

	PCSNode* Azul::PCSTree::GetRoot() const
	{
		return this->pRoot;
	}

	void Azul::PCSTree::Insert(PCSNode* const pInNode, PCSNode* const pParent)
	{
		if (this->pRoot == nullptr)
		{
			//Tree is empty, add as root
			this->pRoot = pInNode;
			this->pRoot->SetParent(pParent);
			this->pRoot->SetLevel(1);

			//update tree stats
			this->mInfo.currNumLevels++;
			this->mInfo.maxNumLevels++;
			this->privInfoAddNode();
		}
		else if (pParent->GetChild() != nullptr)
		{
			//parent has a child, insert in front 
			pInNode->SetParent(pParent);
			
			pInNode->SetPrevSibling(nullptr);
			pInNode->SetNextSibling(pParent->GetChild());
			pInNode->GetNextSibling()->SetPrevSibling(pInNode);
			
			pParent->SetChild(pInNode);
			pInNode->SetLevel(pInNode->GetNextSibling()->GetLevel());

			//set forward /reverse
			pParent->SetForward(pInNode);
			pInNode->SetReverse(pParent);	//opposite of forward
			prFindForward(pInNode);

			//update tree stats
			this->privInfoAddNode();
		}
		else
		{
			//insert below a node
			pInNode->SetParent(pParent);
			pParent->SetChild(pInNode);

			//set forward
			pParent->SetForward(pInNode);
			pInNode->SetReverse(pParent);	//opposite of forward
			prFindForward(pInNode);

			//update tree stats
			this->privInfoAddNode();
			this->prInfoAddLevel(pInNode);
		}

		//save ref to last node
		if (pInNode->GetForward() == nullptr)
		{
			PCSTree::pTail = &*pInNode;
		}
	}

	void Azul::PCSTree::Remove(PCSNode* const pInNode)
	{
		//if node has no children
		if (pInNode->GetChild() == nullptr)
		{
			//last node on level
			if (pInNode->GetNextSibling() == nullptr)
			{
				//grab parent
				PCSNode* parent = pInNode->GetParent();
				if (parent == nullptr)
				{
					//removing root
					this->pRoot = nullptr;
				}
				else
				{
					//grab first child
					PCSNode* tmp = parent->GetChild();
					if (tmp->GetNextSibling() == nullptr)
					{
						//disconnect first child
						parent->SetChild(nullptr);
					}
					else
					{
						//disconnect node
						pInNode->GetPrevSibling()->SetNextSibling(nullptr);
					}
				}

				//update tree stats
				this->privInfoRemoveNewLevel(pInNode);
			}
			else
			{
				//grab parent
				PCSNode* parent = pInNode->GetParent();
				assert(parent != nullptr);

				//grab first child
				PCSNode* child = parent->GetChild();
				assert(child != nullptr);

				if (child == pInNode)
				{
					//remove first child w/ sibling
					//update parent point next child
					parent->SetChild(child->GetNextSibling());

					if (child->GetNextSibling() != nullptr)
					{
						//disconnect from sibling
						child->GetNextSibling()->SetPrevSibling(nullptr);
					}
				}
				else
				{
					//remove level middle node
					pInNode->GetPrevSibling()->SetNextSibling(pInNode->GetNextSibling());
					if (pInNode->GetNextSibling() != nullptr)
					{
						pInNode->GetNextSibling()->SetPrevSibling(pInNode->GetPrevSibling());
					}
				}
			}

			//fix links
			pInNode->SetPrevSibling(nullptr);
			pInNode->SetNextSibling(nullptr);
			pInNode->SetChild(nullptr);
			pInNode->SetParent(nullptr);

			this->privInfoRemoveNode();
			return;
		}
		else
		{
			//recursive remove children
			PCSNode* child = pInNode->GetChild();
			if (child != nullptr)
			{
				this->Remove(child);
				this->Remove(pInNode);
			}
		}
	}

	void Azul::PCSTree::GetInfo(Info& info)
	{
		info = this->mInfo;
	}

	void Azul::PCSTree::Print() const
	{
		this->privPrintHelper(this->pRoot);
	}


	//----------------------------------------------------------------------------------
	//	PRIVATE CLASS METHODS
	//----------------------------------------------------------------------------------

	void Azul::PCSTree::privInfoAddNode()
	{
		//increment node count
		this->mInfo.currNumNodes++;

		//update max nodes
		if (mInfo.currNumNodes > mInfo.maxNumNodes)
		{
			this->mInfo.maxNumNodes++;
		}
	}

	void Azul::PCSTree::privInfoRemoveNode()
	{
		this->mInfo.currNumNodes--;
	}

	void Azul::PCSTree::prInfoAddLevel(PCSNode* const inNode)
	{
		int lvlcount = 0;
		PCSNode* tmp = inNode;
		
		//find what level new node is at
		while (tmp != nullptr)
		{
			//count levels (bottom --> top)
			lvlcount++;
			tmp = tmp->GetParent();
		}
		inNode->SetLevel(lvlcount);
		
		//update stats
		if (lvlcount > mInfo.currNumLevels)
		{
			mInfo.currNumLevels = lvlcount;
		}

		if (mInfo.currNumLevels > mInfo.maxNumLevels)
		{
			this->mInfo.maxNumLevels++;
		}
	}

	void Azul::PCSTree::privInfoRemoveNewLevel(PCSNode* const inNode)
	{
		//grab parent
		PCSNode* parent = inNode->GetParent();
		if (parent != nullptr)
		{
			//are there still children?
			PCSNode* child = parent->GetChild();
			if (child == nullptr)
			{
				//recalculate tree...
				privDepthFirst(this->pRoot);
			}
			else
			{
				//do nothing, level still exists
				return;
			}
		}
		else
		{
			//we are at root, do nothing
		}

		//update tree stat before leaving...
		if (counter < mInfo.currNumLevels)
		{
			mInfo.currNumLevels--;
		}
		//reset counter
		counter = 0;
	}

	void Azul::PCSTree::privDepthFirst(PCSNode* root)
	{
		PCSNode* pChild = nullptr;
		if (root->GetChild() != nullptr)
		{
			pChild = root->GetChild();
			while (pChild != nullptr)
			{
				//keep largest level count
				if (counter < pChild->GetLevel())
				{
					counter = pChild->GetLevel();
				}

				privDepthFirst(pChild);
				pChild = pChild->GetNextSibling();
			}
		}
	}

	void Azul::PCSTree::privPrintHelper(PCSNode* node) const
	{
		//print current node
		node->PrintNode();

		PCSNode* pChild = nullptr;
		if(node->GetChild() != nullptr)
		{
			pChild = node->GetChild();

			//print children
			while (pChild != nullptr)
			{
				privPrintHelper(pChild);
				pChild = pChild->GetNextSibling();
			}
		}
	}

	void Azul::PCSTree::prFindForward(PCSNode* inNode)
	{
		//do we have child?
		if (inNode->GetChild())
		{
			inNode->SetForward(inNode->GetChild());
			inNode->GetChild()->SetReverse(inNode);
		}
		//do we have a sibling?
		else if (inNode->GetNextSibling())
		{
			inNode->SetForward(inNode->GetNextSibling());
			inNode->GetNextSibling()->SetReverse(inNode);
		}
		else
		{
			//lets go up a level(s)
			PCSNode* parent = inNode->GetParent();
			PCSNode* prev = nullptr;
			while (parent->GetNextSibling() == nullptr)
			{
				//find parent with viable sibling
				prev = parent;
				parent = parent->GetParent();

				//have we hit root? (aka end of tree)
				if (parent == nullptr)
				{
					if (prev == pRoot)
					{
						inNode->SetForward(nullptr);
					}

					return;
				}
			}

			//else we have a valid sibling
			inNode->SetForward(parent->GetNextSibling());
			parent->GetNextSibling()->SetReverse(inNode);
		}
	}

	void Azul::PCSTree::prFindReverse(PCSNode* parent)
	{
		//is there prev sibling (another node on same level)
		if (parent->GetPrevSibling())
		{
			parent->SetReverse(parent->GetPrevSibling());
		}
		//
	}

}