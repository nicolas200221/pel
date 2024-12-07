#include "trie.hpp"

int main(){
    bag<char> bagchar;
    bagchar.append('a');
    bagchar.append('b');
    bagchar.print();
    bag<int> bagint;
    bagint.append(15);
    bagint.append(20);
    bagint.append(25);
    bagint.append(30);
    bagint.append(35);
    bagint.print();
    bag<int> bagintcopy(bagint);
    cout<<"bagintcopy(2) = "<<bagintcopy.at(2)<<endl;
    bagintcopy.append_at(50, 2);
    cout<<"bagintcopy(2) = "<<bagintcopy.at(2)<<endl;
    bagintcopy.print();
    return 0;
} 