// QUESTION 2
void HuffmanTree::dfs(HuffmanCode& hc, TreeNode *tn, string &s) {
    //if node is leaf, add code to map
    if(tn->word != nullptr) {
        string key = *(tn->word);
        hc[key] = s;
    }

    //if node is not leaf
    else if(tn->word == nullptr) {
        //initialize string to build code sequence
        string str;
        
        //if node has left child, append '0' to code and recurse on left child
        if(tn->children[0] != nullptr) {
            str = s+"0";
            HuffmanTree::dfs(hc, tn->children[0], str);
        }
        
        //if node has right child, append '1' to code and recurse on right child
        if(tn->children[1] != nullptr) {
            str = s+"1";
            HuffmanTree::dfs(hc, tn->children[1], str);
        }
    }
}

// QUESTION 4
void HuffmanEncoder::encode(istream &fin, ostream &fout) const {
    string input, output;
    while(fin >> input) {
        //if word is not in dictionary, throw 1
        if(code.find(input) == code.end()) throw 1;
        else {
            output << code.find(s)->second;
            fout << output;
        }
    }
}

//QUESTION 5
HuffmanTree::HuffmanTree(const HuffmanCode &hc) {
    //initialize root
    root = new TreeNode();
    
    //loop for each pair in HuffmanCode
    for(auto& h_code : hc) {
        string key = h_code.first;
        string code = h_code.second;
        
        //start from root
        resetIterator();
        
        //loop through each char in code
        for(int i=0; i<(code.length()); i++) {
            
            //descend tree according to arrangement of code
            if(code[i] == '0') {

                //if current node does not have left child, add one and modeDownonZero, else just moveDownOnZero
                if(iter->children[0] == nullptr) {
                    //if on last char of code, add node with word
                    if(i == code.length()-1) {
                        auto leaf = new TreeNode(key);
                        iter->children[0] = leaf;
                    } else {
                        auto tn = new TreeNode();
                        iter->children[0] = tn;
                    }
                    moveDownZero();
                } else moveDownZero();
            }
            else if(code[i] == '1') {

                //if current node does not have right child, add one and moveDownOnOne, else just moveDownOnOne
                if(iter->children[1] == nullptr) {

                //if on last char of code, add node with word
                    if(i == code.length()-1) {
                        auto leaf = new TreeNode(key);
                        iter->children[1] = leaf;
                    } else {
                        auto tn = new TreeNode();
                        iter->children[1] = tn;
                    }
                    moveDownOnOne();
                } else moveDownOnOne();
            }

            //throw 2 if sequence does not contain 0 or 1
            else throw 2;
        }
    }
}

