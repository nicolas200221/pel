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

template <typename T>
void trie<T>::set_weight(double w){ this->m_w = w; }

template <typename T>
double trie<T>::get_weight() const { return this->m_w; }

template <typename T>
void trie<T>::set_label(T* l) { this->m_l = l; }

template <typename T>
T const* trie<T>::get_label() const { return this->m_l; }

template <typename T>
void trie<T>::set_parent(trie<T>* p) { this->m_p = p; }

template <typename T>
trie<T> const* trie<T>::get_parent() const { return this->m_p; }

template <typename T>
bag<trie<T>> const& trie<T>::get_children() const { return this->m_c; }

//implementa anche prepend per l'ordinamento, oltre all'operator <;
template <typename T>
void trie<T>::add_child(trie<T> const& c) {
    this->m_w = 0.0;
    this->m_c += c;
}