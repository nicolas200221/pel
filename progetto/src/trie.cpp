#include "trie.hpp"  // It is forbidden to include other libraries!

template <typename T>
trie<T>::trie(){
    m_p = nullptr;
    
}

int main(){
    bag<int> bag;
    bag.append(10);
    bag.print();
    return 0;
}