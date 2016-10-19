//COMP322 A3
//NAME: SIMON HSU
//ID: 260610820
#include "huffman.h"
#include <iostream>
#include <sstream>

//QUESTION 1 - 0 credit

HuffmanTree::HuffmanHeap::HuffmanHeap(istream &instr) {
    // start with an empty map
    map<string, unsigned int> associate;
    // ----
    // use a the input stream with a string to read every word one by one
    string word;
    // read every word one by one
    while(instr >> word) {
        // if the word was already seen, increment the count. Otherwise, initialized it at 1
        if (associate.find(word) != associate.end()) {
            associate[word]++;
        }else {
            associate[word] = 1;
        }
    }

    // insert every word in the heap
    for(auto &ada : associate) {
        auto tn = new TreeNode(ada.first);
        this->push(tn, ada.second);
    }
}

void HuffmanTree::HuffmanHeap::pop() {
    if(content.size() <= 1) return;
    auto newpriority = content[0]->priority;
    auto tn1 = *(content[0]->data);
    Heap::pop();
    newpriority += content[0]->priority;
    auto tn2 = *(content[0]->data);
    Heap::pop();
    auto tn = new TreeNode(tn1, tn2);
    Heap::push(tn, newpriority);
}

// QUESTION 2
/*
    Retreving huffman codes from huffman trees
    DFS: go down the branches of the tree until a leaf is encountered,
    while keeping track of the path that has been taken.
        When such a node is reached save the association in the HuffmanCode,
        which happens to be a map.
*/
void HuffmanTree::dfs(HuffmanCode& hc, TreeNode *tn, string &s) {
    //hc is the map that stores all code associations
    //tn is a pointer to the TreeNode that is investigated
    //s is a string of 0s and 1s that keeps track of the path from the root to the node tn.

    //if tn has a word associated with it,
    //if node is leaf, add code to map
    if(tn->word != nullptr) {
        //string w = *(tn->word);
        //hc[w] = s;
        hc[*(tn->word)] = s;
    }

    //if tn is not a leaf, then investigate the child associated to 0.
    //if node is not leaf (does not have an item)
    else if(tn->word == nullptr) {
        //initialize string to build code sequence
        string code;

        //if node has left child, append '0' to code and recurse on left child
        if(tn->children[0] != nullptr) {
            code = s+"0";
            HuffmanTree::dfs(hc, tn->children[0], code);
        }

        //do the same for the right child
        //if node has right child, append '1' to code and recurse on right child
        if(tn->children[1] != nullptr) {
            code = s+"1";
            HuffmanTree::dfs(hc, tn->children[1], code);
        }
    }
}

//QUESTION 3
/*
    Retrieving Huffman Codes from a source input stream
    assume that the input stream (whether a file or not) stores on each line two works:
    first a vocabulary word and second the sequence of 0s and 1s associated with this word.
*/
HuffmanCode::HuffmanCode(istream &input) {
    /*
        EXCEPTION: The method should throw 0 if the stream is not in the proper format,
        for example if a line has more than two words, or the second word is not a sequence of 0s and 1s.
    */
    string word, code; //first word, second code
    while(input >> word, input >> code) {
        //i am not using regex i think it was causing compile error
        //input>>code;
        //regex e("[01]*");
        //bool match = regex_exp(code, e)
        //if (match == false) throw 0;
        this->insert(make_pair(word,code)); //insert word and its code in map
    }
}

//QUESTION 4
/*
    Retreving Huffman Trees from Huffman Codes
    Given a HuffmanCode, implement a methods that builds a Huffman Tree.
    Based on all the words in the HuffmanCode object, and their corresponding codes,
    build a tree that has all the paths of 0s and 1s,
    and all the words at the leafs of this tree.
*/
HuffmanTree::HuffmanTree(const HuffmanCode &hc) {
    /*
        EXCEPTION: The method should throw 1 if the code is not a prefix code.
        EXCEPTION: The method should throw 2 if the codes are not all sequences of 0s and 1s.
    */
    this->root = new TreeNode(); //initialize root

    //loop for each pair in HuffmanCode
    for(auto& p: hc) {
        string *word = new string(p.first); //initialize word
        string code = p.second; //initialize code
        //start from root
        resetIterator();

        //loop through each char in code
        for(int i=0; i<(code.length()); i++) {
            if(iter->word != nullptr) throw 1;
            //descend tree according to arrangement of code
            if(code[i] == '0') {
                //if current node does not have left child, add one and modeDownonZero, else just moveDownOnZero
                if(iter->children[0] == nullptr) {
                    //if on last char of code, add node with word
                    iter->children[0] = new TreeNode();
                }
                moveDownOnZero();
            }
            else if(code[i] == '1') {
                //if current node does not have right child, add one and moveDownOnOne, else just moveDownOnOne
                if(iter->children[1] == nullptr) {
                //if on last char of code, add node with word

                    iter->children[1] = new TreeNode();
                }
                    moveDownOnOne();
            }
            //throw 2 if the codes are not all sequences of 0s and 1s.
            else throw 2;
            }
            iter->word = word; //add word to leaf
        }
    }

// QUESTION 5
/*
    Encoding an inout stream to an ouput stream
    given a huffmanCode, implement the encoding method, which takes as parameters two streams:
    an input stream that contains words in a dictionary,and an output stream which will contain only 0s and 1s.
    The method read each word one by one and push to the output stream all corresponding codes.
*/
void HuffmanEncoder::encode(istream &fin, ostream &fout) const {
    /*
        EXCEPTION: The method should throw 1 if fin contains words that are not in the dictionary of code.
    */
    string ip; //initialize input
    while(fin >> ip) {
        //if word is not in dictionary, throw 1
        if(code.find(ip) == code.end()) {
                throw 1;
        }
        else {
            fout << code.find(ip)->second;
        }
    }
}

//QUESTION 6
/*
    Decoding an encoded message
    this method takes an input stream and decodes all the words corresponding to the
    sequence of 0s and 1s that it reads from the stream.
    The method should add all these items to the queue of savedWords,
    which is a private member of the class HuffmanDecoder.
*/
void HuffmanDecoder::push(istream &f) {
    /*
        EXCEPTION: The method should throw 0 if the sequence has characters other than 0 and 1.
        EXCEPTION: The method should throw 1 if the last word was not fully completed.
    */
    char c; //initialize c to read word
    resetIterator();
    //for each c in f
    while(f.get(c)) {
            if(c == '0') {
                try {
                    //if left child exists, move iter left
                    moveDownOnZero();
                    try {
                        //if left child is leaf, push it into queue saveWords and reset
                        savedWords.push(getWordFromIter());
                        resetIterator();
                    }
                    catch (double d) {} //catches exception where tree node has no item
                }
                catch (int i) {throw 1; } //catches exception where left or right child does not exist, word was not fully completed
            }
            else if(c == '1') {
                try {
                    //if right child exists, move iter right
                    moveDownOnOne();
                    try {
                        //if right child is leaf, push it into queue saveWords and reset
                        savedWords.push(getWordFromIter());
                        resetIterator();
                    }
                    catch (double d) { } //catches exception where tree node has no item
                }
                catch (int i) {throw 1;} //catches exception where left or right child does not exist, word was not fully completed
            }
            else throw 0; //catches exception where the sequence has characters other than 0 and 1.
        }
    }
