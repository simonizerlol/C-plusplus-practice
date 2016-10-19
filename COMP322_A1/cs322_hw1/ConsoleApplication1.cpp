#include "heaps.h"
#include <vector> // std::vector

Heap *heapFromArray(string *input, int length) {
	//Write a function that takes as input an array of strings and returns the Heap struct
	//If a node does not have a left or a right child, the pointer that corresponds to the missing child should be equal to null pointer
	//your code here    
	vector <Heap*> temp; //to temporarily keep addresses in order 	
	Heap* biTree, *parent;  //binary tree to store addresses temporarily & "new Heap" to protect content 	
	parent = new Heap;	 //main or first parent/root 	
	int i = 0;
	parent->name = input[0];
	temp.push_back(parent);
	while (!temp.empty()) {
		biTree = temp.front();          //biTree points at same adrdress as temp[0] 		
		temp.erase(temp.begin());

		if (2 * i + 1 == length) { break; }           //parent has one child 			

		Heap* leftChild = new Heap;
		leftChild->name = input[2 * i + 1];       //left child from array 		
		biTree->left = leftChild;
		temp.push_back(biTree->left);   //add address at the end of the vector  		

		if (2 * i + 2 >= length) { break; }              //parent has no child 			

		Heap* rightChild = new Heap;
		rightChild->name = input[2 * i + 2];       //left child from array 		
		biTree->right = rightChild;
		temp.push_back(biTree->right);      //add address at the end of the vector 		
		++i;
	}
	return parent;
}


int numElements(Heap h) {
	//your code here
	int counter = 1;
	if (h.left != nullptr) {
		counter = counter + numElements(*h.left);
		if (h.right != nullptr) {
			counter = counter + numElements(*h.right);
		}
	}
	return counter;

}



/* might want to do this for Q5
Heap **returnAllHeaps(Heap h) {
//your code here
}*/

string *printLinear(Heap h) {
	//your code here
	int l = numElements(h);
	string array[14];
	for (int i = 0; i < l; i++) {
		array[i] = h.name;
		array[2 * 1 + 1] = h.left->name;
		array[2 * 1 + 2] = h.right->name;
	}

	return array;
}



string printPretty(Heap h) {
	//your code here
}