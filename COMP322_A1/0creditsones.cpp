 Heap *heapFromArray(string *input, int length) {     
 vector <Heap*> temp; //to temporarily keep addresses in order 	
 Heap* biTree,*parent;  //binary tree to store addresses temporarily & "new Heap" to protect content 	
 parent = new Heap;	 //main or first parent/root 	
 int i =0; 	
 parent->name = input[0]; 	
 temp.push_back(parent);    
 while (!temp.empty()){ 		
 biTree = temp.front();          //biTree points at same adrdress as temp[0] 		
 temp.erase(temp.begin()); 		
 if (2*i+1==length){             //parent has one child 			
 break; 		} 		
 Heap* leftChild = new Heap; 		
 leftChild->name = input[2*i+1];       //left child from array 		
 biTree->left = leftChild; 		
 temp.push_back(biTree->left);   //add address at the end of the vector  		
 if (2*i+2>=length){             //parent has no child 			
 break; 		} 		
 Heap* rightChild = new Heap; 		
 rightChild->name = input[2*i+2];       //left child from array 		
 biTree->right = rightChild; 		
 temp.push_back(biTree->right);      //add address at the end of the vector 		
 ++i; 		} 		
 return parent; }
