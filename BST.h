#ifndef BST_H_
#define BST_H_

#include "BSTNode.h"
#include "PolyNode.h"
#include <vector>
#include <string>

class BST
{
private:
	// must contain this private field, and you can define other private fields
	BSTNode* root = NULL;


public:
	BST();
	BST(int d, double c);
//	BST(const std::vector<int>& deg, const std::vector<double>& coeff);
	~BST();

	void addMono(int i, double c);
//	std::vector<PolyNode> output();
    BSTNode* getRoot() {return root;};

};

#endif /* BST_H_ */
