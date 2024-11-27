#include "trie.hpp"  // It is forbidden to include other libraries!

template <typename T>
trie<T>::trie(){
    m_p = nullptr;
    m_l = nullptr;
    m_c = T();
    m_w = 0.0;
}

int main(){
    bag<int> bag;
    bag.append(10);
    bag.print();
    return 0;
}