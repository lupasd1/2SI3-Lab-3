#include "BST.h"
#include <iostream>
#include <math.h>

using namespace std;

BST::BST()
{
	root = new BSTNode(-1, 0, NULL, NULL);
}

BST::BST(int d, double c)
{
    root = new BSTNode(d, c, NULL, NULL);
}

BST::~BST()
{
//    PolyNode* ptr = head;
//    PolyNode* nextPtr = NULL;
//    while (ptr != NULL) {
//        nextPtr = ptr->next;
//        delete ptr;
//        ptr = nextPtr;
//    }
}

void BST::addMono(int i, double c)
{
//    for (PolyNode* ptr = head; ptr!=NULL; ptr++) {
//        cout << ptr->deg << endl;
//    }
	BSTNode* ptr = root;

    while (ptr != NULL) {
        if (i > ptr->deg) {
            if (ptr->right == NULL) {
                ptr->right = new BSTNode(i, c, NULL, NULL);
                return;
            }
            else {
                ptr = ptr->right;
            }
        }
        else if (i < ptr->deg) {
            if (ptr->left == NULL) {
                ptr->left = new BSTNode(i, c, NULL, NULL);
                return;
            }
            else {
                ptr = ptr->left;
            }
        }
        else {
            ptr->coeff += c;
            return;
        }
    }

}
//std::vector<PolyNode> BST::output() {
//
//};
//std::string Poly::toString()
//{
//	string outputStr = "";
//    outputStr += ("degree=" + to_string(degree));
//
//    PolyNode* ptr = head->next;
//    while (ptr != NULL) {
//        outputStr += (" a(" + to_string(ptr->deg) + ")=" + to_string(ptr->coeff) +";");
//        ptr = ptr->next;
//    }
//	return outputStr;//change this after completing this function
//}
