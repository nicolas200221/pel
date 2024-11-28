#include "trie.hpp"

int main(){
    bag<int> bagint;
    bagint.append(10);
    bagint.print();
    bag<char> bagchar;
    bagchar.append('a');
    bagchar.append('b');
    bagchar.print();
    return 0;
}