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
    bagint.prepend(10);
    bagint.prepend(5);
    bagint.append(30);
    bagint.append(35);
    bagint.print();
    bag<int> bagintcopy(bagint);
    cout<<"bagintcopy(2) = "<<*(bagintcopy.at(2))<<endl;
    bagintcopy.append_at(50, 2);
    cout<<"bagintcopy(3) = "<<*(bagintcopy.at(3))<<endl;
    cout<<"bagintcopy(0) = "<<*(bagintcopy.at(0))<<endl;
    cout<<"bagintcopy(15) = "<<(bagintcopy.at(15) ? *(bagintcopy.at(15)) : -16384)<<endl;
    cout<<"bagintcopy(-3) = "<<(bagintcopy.at(-3) ? *(bagintcopy.at(-3)) : -16384)<<endl;
    bagintcopy.append_at(500, -2);
    bagintcopy.append_at(50, 29);
    bagintcopy.print();
    return 0;
} 