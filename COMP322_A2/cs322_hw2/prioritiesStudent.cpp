//COMP322 A2
//NAME: SIMON HSU
//ID: 260610820
#include "priorities.h"
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
//QUESTION 1
Heap::Heap(const vector<string> & dataToAdd) {
    
    //initialize temp node
    
    Node n;
    
    
    
    //iterate for each index in dataToAdd
    
    for(int i = 0; i < dataToAdd.size(); i++) {
        
        //set attribuets to n
        
        n.priority = i;
        
        n.data = dataToAdd[i];
        
        
        
        //add n to contents
        
        this->content.push_back(n);
        
        
        
    }
    
}
Heap::Heap(const Heap& h) {
    
    //new node to add to content vector
    
    Node n;
    
    
    
    //iterate for each node in h.contents
    
    for(int i = 0; i < h.content.size(); i++) {
        
        
        
        //copy priority and data from h to n
        
        n.data = h.content[i].data;
        
        n.priority = h.content[i].priority;
        
        
        
        //add n to contents
        
        this->content.push_back(n);
        
    }
    
}
//Question 2
size_t Heap::lengthOfContent(unsigned long index) const {
    
    //add length of current node
    
    size_t len = this->content[index].data.length();
    
    auto length = this->content.size();
    
    
    
    //if there is a left child, recurse
    
    if(index*2+1 < length) {
        
        len += lengthOfContent(index*2+1);
        
    }
    
    //if there is a right child, recurse
    
    if(index*2+2 < length) {
        
        len += lengthOfContent(index*2+2);
        
    }
    
    return len;
    
}
ostream &operator<<(ostream &out, const Heap& h) {
    
    //100% readapated from A1Q6 answer
    
    auto length = h.content.size();
    
    
    
    //counters
    
    int elemPerRowToDo = 1;
    
    int elemPerRowDone = 0;
    
    
    
    //iterate through each node
    
    for(int i=0; i < length; i++) {
        
        //print whitespace on left if left child exists
        
        if(i*2+1 < length) {
            
            for(int j=0; j < h.lengthOfContent(i*2+1); j++) out << " ";
            
        }
        
        
        
        //print current node
        
        out << h.content[i].data;
        
        
        
        //print whitespace on right
        
        if(i*2+2 < length) {
            
            for(int j=0; j < h.lengthOfContent(i*2+2); j++) out << " ";
            
        }
        
        
        
        //count element printed
        
        elemPerRowDone++;
        
        
        
        //new line/level control
        
        if(elemPerRowDone == elemPerRowToDo) {
            
            //elements in next row is double of current
            
            elemPerRowToDo *= 2;
            
            //reset counter to zero
            
            elemPerRowDone = 0;
            
            //and move to next line
            
            out << "\n";
            
        }
        
        //find appropriate white space to print
        
        else {
            
            int child = i;
            
            while(child % 2 == 0) {
                
                child = (child-1)/2;
                
            }
            
            int parent = (child-1)/2;
            
            for(int j=0; j < h.content[parent].data.size(); j++) {
                
                out << " ";
                
            }
            
        }
        
    }
    
    return out;
    
}


//QUESTION 3
//the function go over the elements in content and create a string in the format(name, priority) 
//and add it to a vector of strings, which you have to return.
vector<string> Heap::printLinear() const{
    string s = "";
    int tmp;
    vector<string> toReturn;
    for(int i=0; i < content.size(); i++) {
        s = "";
        s += "(";
        s += content[i].data;
        s += ", ";
		tmp = content[i].priority;
        ostringstream convert;
        convert << tmp;
        s += convert.str();
        s += ")";
		toReturn.push_back(s);
    }
    return toReturn;
}

//QUESTION 4
//the element access operator gives the priority of an item using the square bracket notation.
unsigned int Heap::operator[](string s) const{
    int toReturn = 0;
    //iterate through the heap content to check if matches
    for(int i=0; i < content.size(); i++) { 
		//if matches, return node priority
        if(s == content[i].data) {
            return content[i].priority;
        }
    }
    return toReturn;
}

//QUESTION 5
//the function inserts an element in the heap.
//compare the item with the parent, and swap if necessary. 
//continue swapping up until the item inserted is at
//its rightful place(i.e.it has no priority over its parent).
void Heap::heapifyUp(unsigned long index) {
    if(content[(index-1)/2].priority > content[index].priority) { 
        swap(content[(index-1)/2],content[index]);
        heapifyUp((index-1)/2);
    }
}

void Heap::push(string data, unsigned int priority) {
    //initialize node n
    Node n;
    //iterate through the contents to check existing data
    for(int i=0; i < content.size(); i++) {
		//if matches, terminate the program
        if(data == content[i].data) {
            return;
        }
    }
    //set attribuets to n
    n.data = data;
    n.priority = priority;
    //push n to contents
    content.push_back(n);
    //heapify up using index
    heapifyUp(content.size()-1);
}

Heap& Heap::operator+=(const Heap& h) {
	//iterate through the contents to check existing data and push
    for(int i=0; i < h.content.size(); i++) { 
      push(h.content[i].data, h.content[i].priority);
    }
    return *this;
}

// QUESTION 6
//the function removes the top element in the heap.
//compare the item with its children, and swap the item with the child that has priority over all three items
//(parent, left child, and right child) if necessary.
//continue swapping down until the item falls at its rightful place(i.e.it has priority over its children).
void Heap::heapifyDown(unsigned long index) {

	if (this->content.size() > 0) {
		int current = this->content[index].priority;
		if (2 * index + 2 <= this->content.size())
		{
			int leftChild = this->content[2 * index + 1].priority;
			int rightChild = this->content[2 * index + 2].priority;
			if (current > leftChild && current < rightChild) {
				swap(this->content[index], this->content[2 * index + 1]);
				heapifyDown(2 * index + 1);
			}
			else if (current > rightChild && current < leftChild)
			{
				swap(this->content[index], this->content[2 * index + 2]);
				heapifyDown(2 * index + 2);
			}
			else if (current > rightChild && current > leftChild)
			{
				swap(this->content[index], this->content[2 * index + 1]);
				heapifyDown(2 * index + 1);
			}
			else
			{
				return;
			}
		}
	}
}

string Heap::pop() {
	string s = this->content[0].data;
	swap(this->content[0], this->content[this->content.size() - 1]);
	this->content.pop_back();
	heapifyDown(0);
	return s;
}

// QUESTION 7
//the function creates a heap based on the frequency of words coming from an istream.
//1. Create a map that keeps a count of the words in the input stream.
//2. Read word by word the input stream and update the counts as you do that.
//   A word is any sequence of characters separated by white spaces
//3. Find the word that occurs the most times in the stream. Save this value into max.
//4.Insert every word in the heap with priority max - count, such that the word that is most frequent has priority
//  value 0, and all words that are less frequent have higher and higher priority values.
Heap::Heap(istream &in) {
	map<string, int > myMap; 
	int count, max = 0;
	string s;
	in >> s;
	while (in >> s) {
		//if the word is not in myMap 
		if (myMap.count(s) < 1) {
			count = 1;
			myMap.insert(pair<string, int>(s, 1)); //add the word to map and its count
		}
		//if the word is in the map
		else {
			myMap[s] = myMap[s] + 1; //increase its count by one
			count = myMap[s];        //assign the frequency of the word to count
		}
		if (count > max) {            //if count is greater than max
			max = count;			  //assign count to max
		}
	}
	for (map<string, int>::iterator it = myMap.begin(); it != myMap.end(); ++it) {
		int m;        //to keep count from myMap
		Node n;       //initialize node n to be added to content vector
		n.data = it->first;      //assign myMap string to Node data
		m = it->second;
		n.priority = max - m;    //let n.priority = maximum - count
		content.push_back(n);    //add n to content
	}
	//set n in the order of heap according to their priroties
	for (int n = 0; n < content.size(); n++) { 
		heapifyDown(n);
	}
}