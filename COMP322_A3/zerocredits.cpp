
HuffmanTree::HuffmanHeap::HuffmanHeap(istream &instr) {
    // start with an empty map
    map<string, unsigned int> associate;
    // ----
    // use a the input stream with a string to read every word one by one
    string g;
    // read every word one by one
    while(instr >> g) {
        // if the word was already seen, increment the count. Otherwise, initialized it at 1
        if (associate.find(g) != associate.end()) {
            associate[g]++;
        }else {
            associate[g] = 1;
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

