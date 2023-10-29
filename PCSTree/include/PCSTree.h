//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef PCSTREE_H
#define PCSTREE_H

namespace Azul
{
	// forward declare
	class PCSNode;

	// PCSTree class 
	class PCSTree
	{
	public:
		// Simple data structure
		struct Info
		{
			int currNumNodes;
			int maxNumNodes;
			int currNumLevels;
			int maxNumLevels;
		};

		static PCSNode* pTail;


	public:
		PCSTree(const PCSTree& in) = delete;				// copy constructor 
		PCSTree& operator = (const PCSTree& in) = delete;	// assignment operator

		PCSTree();	// constructor
		~PCSTree();	// destructor

		// get Root
		PCSNode *GetRoot() const;

		// insert
		void Insert(PCSNode *const pInNode, PCSNode *const pParent);

		// remove
		void Remove(PCSNode *const pInNode);

		// get info
		void GetInfo(Info &info);
		void Print() const;


	private:
		// Data
		Info	mInfo;
		PCSNode *pRoot;

		int counter;	//used to update level count

		// update info
		void privInfoAddNode();
		void privInfoRemoveNode();
		void privInfoRemoveNewLevel(PCSNode* const inNode);
		void prInfoAddLevel(PCSNode* const inNode);

		// safety (TODO: change to iterative approach)
		void privDepthFirst(PCSNode *tmp);
		void privPrintHelper(PCSNode* node) const;

		void prFindForward(PCSNode* inNode);
		void prFindReverse(PCSNode* parent);

	};

}

#endif

// ---  End of File ---
