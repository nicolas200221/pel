#include "trie.hpp"

int main(){
    bag<char> bagchar;
    bagchar.insert('a');
    bagchar.insert('z');
    bagchar.insert('b');
    bagchar.insert('h');
    bagchar.insert('g');
    bagchar.insert('l');
    bagchar.insert('e');
    bagchar.print();
    bag<int> bagint;
    bagint.insert(20);
    bagint.insert(35);
    bagint.insert(10);
    bagint.insert(15);
    bagint.insert(5);
    bagint.insert(42);
    bagint.insert(35);
    bagint.print();
    bag<int> bagintcopy(bagint);
    cout<<"bagintcopy(2) = "<<*(bagintcopy.at(2))<<endl;
//    bagintcopy.append_at(50, 2);
    cout<<"bagintcopy(3) = "<<*(bagintcopy.at(3))<<endl;
    cout<<"bagintcopy(0) = "<<*(bagintcopy.at(0))<<endl;
    cout<<"bagintcopy(15) = "<<(bagintcopy.at(15) ? *(bagintcopy.at(15)) : -16384)<<endl;
    cout<<"bagintcopy(-3) = "<<(bagintcopy.at(-3) ? *(bagintcopy.at(-3)) : -16384)<<endl;
//    bagintcopy.append_at(500, -2);
//    bagintcopy.append_at(50, 29);
    bagintcopy.print();
    bagintcopy.insert(500);
    bagintcopy.print();
    bag<string> bagstring;
    bagstring.insert("ciao");
    bagstring.insert("prova");
    bagstring.insert("11!");
    bagstring.insert("xd");
    bagstring.insert("diocan");
    bagstring.insert("lol");
    bagstring.insert("zzzzz");
    bagstring.print();
    return 0;
} 