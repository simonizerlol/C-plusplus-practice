//Question 2
size_t Heap::lengthOfContent(unsigned long index) const {
    size_t length = content[index].data.length();
    if(!content[index*2+1].data.empty()) {
        length += lengthOfContent(index*2+1);
    }
    if(!content[index*2+2].data.empty()) {
        length += lengthOfContent(index*2+2);
    }
    return length;
}
ostream &operator<<(ostream &out, const Heap& h) {
    auto length = h.content.size();
    int toDo = 1;
    int done = 0;
    for(int i=0; i < length; i++) {
        if(i*2+1 < length) {
            for(int k=0; k < h.lengthOfContent(i*2+1); k++) {
                out << " ";
            }
        }
        out << h.content[i].data;
        if(i*2+2 < length) {
            for(int k=0; k < h.lengthOfContent(i*2+2); k++) out << " ";
        }
        done++;
        if(done == toDo) {
            toDo *= 2;
            done = 0;
            out << "\n";
        }
        else {
            int child = i;
            while(child % 2 == 0) {
                child = (child-1)/2;
            }
            int parent = (child-1)/2;
            for(int k=0; k < h.content[parent].data.size(); k++) {
                out << " ";
            }
        }
    }
    return out;
}