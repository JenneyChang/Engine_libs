//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef PCSNODE_H
#define PCSNODE_H

namespace Azul
{
	class PCSNode
	{
	public:
		// Constants for the library
		static const unsigned int NAME_SIZE = 32;
		static const unsigned int MAJOR_VERSION = 3;
		static const unsigned int MINOR_VERSION = 1;

	public:
		// Enums
		enum class Code : uint32_t
		{
			SUCCESS,
			FAIL_NULL_PTR,
			FAIL_RETURN_NOT_INITIALIZED
		};


	public:
		PCSNode();								// constructor
		virtual ~PCSNode();						// destructor
		PCSNode(const PCSNode &in);				// copy constructor
		PCSNode& operator=(const PCSNode& in);	// assignment operator

		// Specialize Constructor
		PCSNode(const char* const pInName);

		PCSNode(PCSNode* const pInParent, PCSNode* const pInChild,
			PCSNode* const pInNextSibling, PCSNode* const pInPrevSibling,
			const char* const pInName);

		// accessors
		void SetParent(PCSNode *const pIn);
		void SetChild(PCSNode *const pIn);
		void SetNextSibling(PCSNode *const pIn);
		void SetPrevSibling(PCSNode *const pIn);
		void SetForward(PCSNode *const pIn);
		void SetReverse(PCSNode *const pIn);

		PCSNode* GetParent(void) const;
		PCSNode* GetChild(void) const;
		PCSNode* GetNextSibling(void) const;
		PCSNode* GetPrevSibling(void) const;
		PCSNode* GetForward(void) const;
		PCSNode* GetReverse(void) const;

		void SetLevel(int level);
		int GetLevel(void) const;

		// name
		PCSNode::Code SetName(const char *const pInName);
		PCSNode::Code GetName(char *const pOutBuffer, unsigned int sizeOutBuffer) const;

		// print
		void PrintNode() const;
		void PrintChildren() const;
		void PrintSiblings() const;

		// get number of children/siblings
		int GetNumSiblings() const;
		int GetNumChildren() const;


	private:
		PCSNode *pParent;
		PCSNode *pChild;
		PCSNode *pNextSibling;
		PCSNode *pPrevSibling;
		PCSNode *pForward;
		PCSNode *pReverse;

		int		level; //cheat
		char    pName[PCSNode::NAME_SIZE];

		void prPrintError(PCSNode::Code code);


	};
}

#endif

// ---  End of File ---
