#ifndef NODE_H
#define NODE_H

class Node
{
public:
	Node() = default;
	virtual ~Node() = default;
	Node(const Node&) = delete;
	Node& operator=(const Node&) = delete;

	virtual void ResetLink(void) = 0;
	virtual bool Compare(Node* pNode) = 0;
	virtual void PrintLink(void) = 0;

	virtual bool ComparePriority(Node* pNode) { AZUL_UNUSED_VAR(pNode); return false; }
	virtual char* GetName() { return nullptr; }


};
#endif // !NODE_H
