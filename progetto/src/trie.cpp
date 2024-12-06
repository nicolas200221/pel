#include "trie.hpp"  // It is forbidden to include other libraries!

template <typename T>
trie<T>::trie() 
    : m_p(nullptr), m_l(nullptr), m_c(), m_w(0.0) {}

template <typename T>
trie<T>::~trie() {
    for (auto& child : m_c){
        delete &child;
    }
    delete m_l;
}

template <typename T>
trie<T>::trie(double w)
    : m_p(nullptr), m_l(nullptr), m_c(), m_w(w) {}

template <typename T>
trie<T>::trie(trie<T> const& copy) {
    for(auto& x : copy.m_c) {
        this->m_l = copy.m_l;
        this->m_w = copy.m_w;
        this->m_c = new bag<trie<T>>;
        this = this->m_c;
    }
}

template <typename T>
trie<T>::trie(trie<T>&& rhs){
    m_l = rhs.m_l;
    m_c = std::move(rhs.m_c);
    m_w = rhs.m_w;

    rhs.m_p = nullptr;
    rhs.m_l = nullptr;
    rhs.m_c = bag<trie<T>>();
    rhs.m_w = 0;
}

template <typename T>
trie<T>& trie<T>::operator=(trie<T> const& copy){
    for(auto& x : copy.m_c) {
        this->m_l = copy.m_l;
        this->m_w = copy.m_w;
        this->m_c = new bag<trie<T>>;
        this = this->m_c;
    }
}

template <typename T>
trie<T>& trie<T>::operator=(trie<T>&& rhs){
    m_l = rhs.m_l;
    m_c = std::move(rhs.m_c);
    m_w = rhs.m_w;

    rhs.m_p = nullptr;
    rhs.m_l = nullptr;
    rhs.m_c = bag<trie<T>>();
    rhs.m_w = 0;
}