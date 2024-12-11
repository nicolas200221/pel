#include "trie.hpp"

int main(){
    bag<char> bagchar;
    for(auto record : { 'a', 'z', 'b', 'h', 'g', 'l', 'e' })
        bagchar.insert(record);
    bagchar.print();
    bag<int> bagint;
    for(auto record : { 20, 35, 10, 15, 5, 42, 37 })
        bagint.insert(record);
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
    bagintcopy.insert(500);
    bagintcopy += 25;
    bagintcopy.print();
    bag<string> bagstring;
    for(auto record : { "ciao", "prova", "11!", "xd", "diocan", "lol", "zzzzz" })
        bagstring.insert(record);
    bagstring.print();
    return 0;
} 