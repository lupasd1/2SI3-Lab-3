#ifndef BSTNODE_H_
#define BSTNODE_H_

class BSTNode
{
public:
	int deg;
	double coeff;
	BSTNode* left;
	BSTNode* right;

	BSTNode(int d, double c, BSTNode* l, BSTNode* r) {
		deg = d;
		coeff = c;
		left = l;
        right = r;
	}
};

#endif /* BSTNODE_H_ */
