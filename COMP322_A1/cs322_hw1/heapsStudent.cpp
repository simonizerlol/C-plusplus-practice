#include "heaps.h"
#include <vector> // std::vector
//0 credits q2
Heap *heapFromArray(string *input, int length) {
	//Write a function that takes as input an array of strings and returns the Heap struct
	//If a node does not have a left or a right child, the pointer that corresponds to the missing child should be equal to null pointer
 	vector <Heap*> tmp; //to temporarily keep addresses in order 	
 	Heap* t,*p;  //initialize binary tree to store addresses temporarily and "new Heap" to protect content 	
 	p = new Heap;	 //initialize parent for the heap	
 	int i =0; 	
 	p->name = input[0]; 	
	tmp.push_back(p);    
	while (!tmp.empty()){ 		
	 	t = tmp.front();          //biTree points at same adrdress as temp[0] 		
	 	tmp.erase(tmp.begin());
	  		
 	if (2*i+1==length){ break; }           //parent has one child 			
				
 	Heap* leftC = new Heap; 		
 	leftC->name = input[2*i+1];       //left child from array 		
	t->left = leftC; 		
 	tmp.push_back(t->left);   //add address at the end of the vector  		
 	
	if (2*i+2>=length){break;}              //parent has no child 			
 			
 	Heap* rightC = new Heap; 		
 	rightC->name = input[2*i+2];       //left child from array 		
 	t->right = rightC; 		
 	tmp.push_back(t->right);      //add address at the end of the vector 		
 	++i; } 		
 return p; }

//Q3
int numElements(Heap h) { 
    //takes as input a Heap struct and 
	//returns the number of elements in that heap
  	int c = 1; //initialize a counter
    if(h.left != nullptr) {
        c = c + numElements(*h.left);
        if(h.right != nullptr) {
            c = c + numElements(*h.right);
        }
    }
    return c;
}
//Q4
size_t lengthOfContent(Heap h) {
    long l = h.name.length(); //initialize the length
    if(h.left != nullptr){
        l = l + lengthOfContent(*h.left);
        if(h.right != nullptr){
            l = l + lengthOfContent(*h.right);
        }
    }
    return l;
}
//Q5
Heap **returnAllHeaps(Heap h) {
    Heap **array=new Heap*;
    vector <Heap*> tmp;
    int i= 0;
    while(!tmp.empty()){
    	Heap *hp = new Heap;
    	hpt = tmp.front();
    	array[i] = hp;
    	if(hp->left!=nullptr){
    		tmp.push_back(hp->left);
		}
		if(hp->right!=nullptr){
			tmp.push_back(hp->right);
			++i;
		}
		return array;
		delete array;
	}
}

string *printLinear(Heap h) {
    int num = numElements(h);
    string *array = new string[num];
    Heap **returnArray;
    Heap* parent=&h;
    returnArray = returnAllHeaps(parent);
    for(int i=0; i < num; i++) {
    	Heap *h = returnArray[i];
    	str[i] = h->left name;
	}
    return array;
    delete [] array;
}



string printPretty(Heap h) {
    //your code here
}
