#include "Poly.h"
#include <iostream>
#include <math.h>

using namespace std;

Poly::Poly()
{
	head = new PolyNode(-1, 0, NULL);
    size = 0;
    degree = -1;
}

Poly::Poly(const std::vector<int>& deg, const std::vector<double>& coeff)
{
    head = new PolyNode(-1, 0, NULL);
    if (deg.size() == 0) {
        degree = -1;
    }
    else {
        degree = deg[0];
        PolyNode* currentPtr = head;
        PolyNode* prevPtr = head;

        for (int i = 0; i < deg.size(); i++) {
            currentPtr = new PolyNode(deg[i], coeff[i], NULL);
            prevPtr->next = currentPtr;
            prevPtr = currentPtr;
            size++;
        }
    }
}

Poly::~Poly()
{
    PolyNode* ptr = head;
    PolyNode* nextPtr = NULL;
    while (ptr != NULL) {
        nextPtr = ptr->next;
        delete ptr;
        ptr = nextPtr;
    }
}

// time complexity is O(n/2) because on average you need to insert at the halfway point
// and must move through each node one at a time to find the insertion place
// space complexity is S(c), since only 2 pointers need to be stored
void Poly::addMono(int i, double c)
{
//    for (PolyNode* ptr = head; ptr!=NULL; ptr++) {
//        cout << ptr->deg << endl;
//    }
	PolyNode* ptr = head->next;
    PolyNode* prevPtr = head;
    while (ptr != NULL) {
        if (i > ptr->deg) {

            // insert new node before current node
            prevPtr->next = new PolyNode(i, c, ptr);

            size++;
            // increase the degree if the input mono is higher degree than any other terms
            if (degree < i) {
                degree = i;
            }
            return;
        }
        else if (i == ptr->deg) {
            ptr->coeff += c;
            // in the case that the addition results in the coeff being 0
            if (ptr->coeff == 0) {

                // in the case where the two largest terms cancel
                if (degree == i) {
                    if (ptr->next != NULL) {
                        degree = ptr->next->deg;
                    }
                    // in the case where the only term is cancelled out
                    else {
                        degree = -1;
                    }
                }

                // now delete the term
                prevPtr->next = ptr->next;
                delete ptr;
                size--;
            }
            return;
        }
        else {
            prevPtr = ptr;
            ptr = ptr->next;
        }

    }
    // add mono to end
    prevPtr->next = new PolyNode(i, c, NULL);
    size++;


}

// time complexity is O(n) because one operation is done for every term in the input
// space complexity is S(n), since we can assume that each term takes up its own node
void Poly::addPoly(const Poly& p)
{
    if (p.head->next != NULL) {
        degree = max(p.head->next->deg, degree);
    }

    PolyNode* currentPtr = head;
    currentPtr = currentPtr->next;
    PolyNode* prevPtr = head;
    PolyNode* inputPtr = p.head->next;
    int counter = 0;
    while (inputPtr != NULL) {
        counter++;
        if (counter > 1000) {
            cout << "infinite loop";
            return;
        }
//    cout << inputPtr->deg << endl;
        // once the end of the current list is reached, simply append to the end
        if (currentPtr == NULL) {
            prevPtr->next = new PolyNode(inputPtr->deg, inputPtr->coeff, NULL);
            prevPtr = prevPtr->next;
            inputPtr = inputPtr->next;
            size++;
        }
        else {
            // input node is a lower degree, cannot be added to list, move forward
            if (currentPtr->deg > inputPtr->deg) {
                prevPtr = currentPtr;
                currentPtr = currentPtr->next;
            }
            else if (currentPtr->deg < inputPtr->deg) {
                // previous pointer points to new node, and the new node points to the current pointer
                // this inserts the new node in between previous and current
                prevPtr->next = new PolyNode(inputPtr->deg, inputPtr->coeff, currentPtr);
                prevPtr = prevPtr->next;
                inputPtr = inputPtr->next;
                size++;
                // do not step forward
            }
            // in the case where the degrees are the same
            else {

                currentPtr->coeff += inputPtr->coeff;

                if (currentPtr->coeff == 0) {
                    // case where the 2 largest terms cancel
                    if (degree == currentPtr->deg) {
                        // case where the only 2 terms cancel
                        if (currentPtr->next == NULL && inputPtr->next == NULL) {
                            degree = -1;
                        }
                        // end of current list, degree is next highest term in input
                        else if (currentPtr->next == NULL) {
                            degree = inputPtr->next->deg;
                        }
                        // end of input list, degree is next highest term in current
                        else if (inputPtr->next == NULL) {
                            degree = currentPtr->next->deg;
                        }
                        // degree is the highest power between the next term in current and next in input
                        else {
                            degree = max(currentPtr->next->deg, inputPtr->next->deg);
                        }
                    }
                    // skip over the current pointer, do not move previous pointer
                    prevPtr->next = currentPtr->next;
//                    delete currentPtr;
                    size--;

                }
                else {
                    prevPtr = currentPtr;
                }
                //move forward
                currentPtr = currentPtr->next;
                inputPtr = inputPtr->next;
            }
        }
    }

}

// time complexity is O(n) because each term must be multiplied by the monomial
// so the entire list must be iterated through
// space complexity is S(c), since only 1 pointer need to be stored
void Poly::multiplyMono(int i, double c)
{
    PolyNode* ptr = head->next;
    // if multiplied by 0, set to the empty list
	if (c == 0) {

        head->next = NULL;
        degree = -1;
        size = 0;
        // *** Known issue: memory leak here ***

//        PolyNode* nextPtr;
//        while (ptr != NULL) {
//            nextPtr = ptr->next;
//            delete ptr;
//            ptr = nextPtr;
//        }
        return;
    }

    // multiplying a term by cX^i adds i to the power and multiplies the coefficient by c
    while (ptr != NULL) {
        ptr->deg += i;
        ptr->coeff *= c;
        ptr = ptr->next;
    }
    degree = head->next->deg;
}

void Poly::multiplyPoly(const Poly& p)
{

}

// time complexity is O(n + m) where n in the input size and m is the current size
// since n iterations are needed to first clear the input followed by m insertions
// space complexity is S(c), since only 3 pointers need to be stored
void Poly::duplicate(Poly& outputPoly)
{
	PolyNode* currentPtr = head->next;

    // *** Known issue: memory leak here ***
    //takes the first non-dummy node
//    PolyNode* inputPtr = outputPoly.head->next;
//    PolyNode* nextPtr;
//    // clear outputPoly first
//    while (inputPtr != NULL) {
//        nextPtr = inputPtr->next;
//        delete inputPtr;
//        inputPtr = nextPtr;
//    }
    outputPoly.head->next = NULL;

    PolyNode* inputPtr = outputPoly.head;

    // add each node from this to the end
    while (currentPtr != NULL) {
        inputPtr->next = new PolyNode(currentPtr->deg, currentPtr->coeff, NULL);
        currentPtr = currentPtr->next;
        inputPtr = inputPtr->next;
        outputPoly.size++;
    }
    if (outputPoly.head->next != NULL) {
        outputPoly.degree = outputPoly.head->next->deg;
    }
}

// time complexity is O(1) since this is a simple retrieval
// space complexity is S(1), since only 1 value needs to be stored
int Poly::getDegree()
{
	return degree;
}

// time complexity is O(1) since this is a simple retrieval
// space complexity is S(1), since only 1 value needs to be stored
int Poly::getTermsNo()
{
	return size;
}

double Poly::evaluate(double x)
{
	double sum = 0;
    PolyNode* ptr = head->next;

    while (ptr != NULL) {
        // add to the sum x raised to the deg-th power times the coefficient
        sum += ptr->coeff * pow(x, ptr->deg);
        ptr = ptr->next;
    }
	return sum;
}

std::string Poly::toString()
{
	string outputStr = "";
    outputStr += ("degree=" + to_string(degree));

    PolyNode* ptr = head->next;
    while (ptr != NULL) {
        outputStr += (" a(" + to_string(ptr->deg) + ")=" + to_string(ptr->coeff) +";");
        ptr = ptr->next;
    }
	return outputStr;//change this after completing this function
}
