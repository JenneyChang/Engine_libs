#include "PCSNode.h"

namespace Azul
{
	//----------------------------------------------------------------------------------
	//	CONSTRUCTION
	//----------------------------------------------------------------------------------

	Azul::PCSNode::PCSNode()
		: pParent(nullptr), pChild(nullptr), pNextSibling(nullptr), pPrevSibling(nullptr),
		  pForward(nullptr), pReverse(nullptr), level(-1), pName{0}
	{ }

	Azul::PCSNode::~PCSNode()
	{ }

	Azul::PCSNode::PCSNode(const PCSNode& in)
		: pParent(in.pParent), pChild(in.pChild), pNextSibling(in.pNextSibling),
		  pPrevSibling(in.pPrevSibling), pForward(in.pForward), pReverse(in.pReverse), level(-1)
	{ 
		PCSNode::Code result = this->SetName(in.pName);
		if (result != Code::SUCCESS)
		{
			Trace::out("\nCopy Constructor: \n");
			prPrintError(result);
		}
	}

	PCSNode& Azul::PCSNode::operator=(const PCSNode& in)
	{
		if (this != &in)
		{
			this->pParent = in.pParent;
			this->pChild = in.pChild;
			this->pNextSibling = in.pNextSibling;
			this->pPrevSibling = in.pPrevSibling;
			this->pForward = in.pForward;
			this->pReverse = in.pReverse;
			this->level = -1;

			PCSNode::Code result = this->SetName(in.pName);
			if (result != Code::SUCCESS)
			{
				Trace::out("\nAssignment operator: \n");
				prPrintError(result);
			}
		}

		return *this;
	}

	Azul::PCSNode::PCSNode(const char* const pInName)
		: pParent(nullptr), pChild(nullptr), pNextSibling(nullptr), pPrevSibling(nullptr),
		  pForward(nullptr), pReverse(nullptr), level(-1)
	{
		PCSNode::Code result = this->SetName(pInName);
		if (result != Code::SUCCESS)
		{
			Trace::out("\nSpecialized constructor: \n");
			prPrintError(result);
		}
	}

	Azul::PCSNode::PCSNode(PCSNode* const pInParent, PCSNode* const pInChild, PCSNode* const pInNextSibling, PCSNode* const pInPrevSibling, const char* const pInName)
		: pParent(pInParent), pChild(pInChild), pNextSibling(pInNextSibling), 
		  pPrevSibling(pInPrevSibling), level(-1)
	{
		PCSNode::Code result = this->SetName(pInName);
		if (result != Code::SUCCESS)
		{
			Trace::out("\nSpecialized constructor: \n");
			prPrintError(result);
		}
	}


	//----------------------------------------------------------------------------------
	//	ACCESSORS
	//----------------------------------------------------------------------------------

	void Azul::PCSNode::SetParent(PCSNode* const pIn)		{ this->pParent = pIn; }
	void Azul::PCSNode::SetChild(PCSNode* const pIn)		{ this->pChild = pIn; }
	void Azul::PCSNode::SetNextSibling(PCSNode* const pIn)	{ this->pNextSibling = pIn; }
	void Azul::PCSNode::SetPrevSibling(PCSNode* const pIn)	{ this->pPrevSibling = pIn; }
	void Azul::PCSNode::SetForward(PCSNode* const pIn)		{ this->pForward = pIn; }
	void Azul::PCSNode::SetReverse(PCSNode* const pIn)		{ this->pReverse = pIn; }

	PCSNode* Azul::PCSNode::GetParent(void) const	{ return this->pParent; }
	PCSNode* Azul::PCSNode::GetChild(void) const	{ return this->pChild; }
	PCSNode* Azul::PCSNode::GetNextSibling(void) const { return this->pNextSibling; }
	PCSNode* PCSNode::GetPrevSibling(void) const { return this->pPrevSibling; }
	PCSNode* Azul::PCSNode::GetForward(void) const { return this->pForward; }
	PCSNode* Azul::PCSNode::GetReverse(void) const { return this->pReverse; }

	void Azul::PCSNode::SetLevel(int _level) { this->level = _level; }
	int Azul::PCSNode::GetLevel(void) const { return this->level; }

	PCSNode::Code Azul::PCSNode::SetName(const char* const pInName)
	{
		PCSNode::Code code = PCSNode::Code::FAIL_RETURN_NOT_INITIALIZED;

		if (pInName == nullptr)
		{
			code = PCSNode::Code::FAIL_NULL_PTR;
		}
		else
		{
			//make sure its clear
			memset(this->pName, 0, PCSNode::NAME_SIZE);

			//copy over name
			memcpy_s(this->pName, PCSNode::NAME_SIZE - 1, pInName, PCSNode::NAME_SIZE - 1);
			code = PCSNode::Code::SUCCESS;
		}

		return code;
	}

	PCSNode::Code Azul::PCSNode::GetName(char* const pOutBuffer, unsigned int sizeOutBuffer) const
	{
		PCSNode::Code code = PCSNode::Code::FAIL_RETURN_NOT_INITIALIZED;

		if (pOutBuffer == nullptr)
		{
			code = PCSNode::Code::FAIL_NULL_PTR;
		}
		else
		{
			//clear out buffer
			unsigned int buffSize = 0;
			memset(pOutBuffer, 0, sizeOutBuffer);

			//out buffer smaller name size
			if (sizeOutBuffer < PCSNode::NAME_SIZE)
			{
				buffSize = sizeOutBuffer - 1;
			}
			else
			{
				buffSize = PCSNode::NAME_SIZE - 1;
			}

			memcpy_s(pOutBuffer, sizeOutBuffer, this->pName, buffSize);
			code = PCSNode::Code::SUCCESS;
		}

		return code;
	}


	//----------------------------------------------------------------------------------
	//	PRINT FUNCTIONS
	//----------------------------------------------------------------------------------

	void Azul::PCSNode::PrintNode() const
	{
		Trace::out("\n        Node: %s (%p)\n", this->pName, this);

		//Parent
		if (this->pParent == nullptr)
		{
			Trace::out("      Parent: nullptr\n");
		}
		else
		{
			Trace::out("      Parent: %s (%p)\n", this->pParent->pName, this->pParent);
		}

		//Child
		if (this->pChild == nullptr)
		{
			Trace::out("       Child: nullptr\n");
		}
		else
		{
			Trace::out("       Child: %s (%p)\n", this->pChild->pName, this->pChild);
		}

		//Next Sibling
		if (this->pNextSibling == nullptr)
		{
			Trace::out("Next Sibling: nullptr\n");
		}
		else
		{
			Trace::out("Next Sibling: %s (%p)\n", this->pNextSibling->pName, this->pNextSibling);
		}

		//Prev Sibling
		if (this->pPrevSibling == nullptr)
		{
			Trace::out("Prev Sibling: nullptr\n");
		}
		else
		{
			Trace::out("Prev Sibling: %s (%p)\n", this->pPrevSibling->pName, this->pPrevSibling);
		}

		//Forward
		if (this->pForward == nullptr)
		{
			Trace::out("     Forward: nullptr\n");
		}
		else
		{
			Trace::out("     Forward: %s (%p)\n", this->pForward->pName, this->pForward);
		}

		//Reverse
		if (this->pReverse == nullptr)
		{
			Trace::out("     Reverse: nullptr\n");
		}
		else
		{
			Trace::out("     Reverse: %s (%p)\n\n", this->pReverse->pName, this->pReverse);
		}
	}

	void Azul::PCSNode::PrintChildren() const
	{
		Trace::out("\nPrinting Children (%s): \n", this->pName);

		PCSNode* child = this->GetChild();
		while (child != nullptr)
		{
			child->PrintNode();
			child = child->GetNextSibling();
		}
	}

	void Azul::PCSNode::PrintSiblings() const
	{
		Trace::out("\nPrinting Siblings (%s): \n", this->pName);

		PCSNode* parent = this->GetParent();
		PCSNode* tmp = parent->GetChild();
		while (tmp != nullptr)
		{
			tmp->PrintNode();
			tmp = tmp->GetNextSibling();
		}
	}


	//----------------------------------------------------------------------------------
	//	STAT FUNCTIONS
	//----------------------------------------------------------------------------------

	int Azul::PCSNode::GetNumSiblings() const
	{
		//count curr node (same level as siblings)
		int count = 0;
		PCSNode* parent = this->GetParent();
		if (parent == nullptr)
		{
			//root
			count++;
		}
		else
		{
			//get first child
			PCSNode* tmp = parent->GetChild();
			while (tmp != nullptr)
			{
				count++;
				tmp = tmp->GetNextSibling();
			}
		}

		return count;
	}
	
	int Azul::PCSNode::GetNumChildren() const
	{
		int count = 0;

		//get first child
		PCSNode* tmp = this->GetChild();
		while (tmp != nullptr)
		{
			count++;
			tmp = tmp->GetNextSibling();
		}

		return count;
	}


	//----------------------------------------------------------------------------------
	//	PRIVATE FUNCTIONS
	//----------------------------------------------------------------------------------

	void Azul::PCSNode::prPrintError(PCSNode::Code code)
	{
		if (PCSNode::Code::FAIL_RETURN_NOT_INITIALIZED == code)
		{
			Trace::out("Error: Fail Return Not Initialized\n");
		}
		else if (PCSNode::Code::FAIL_NULL_PTR == code)
		{
			Trace::out("Error: Fail Null Pointer\n");
		}
	}


}