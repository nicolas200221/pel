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
    m_l = copy.m_l;
    m_w = copy.m_w;
    if (!copy.m_c.empty()) {
        m_c = *copy.m_c;
        for (auto& child : m_c) {
            child.m_p = this;
            child = trie<T>(child);
        }
    } else {
        m_c = bag<trie<T>>();
    }
}

template <typename T>
trie<T>::trie(trie<T>&& rhs)
    : m_p(rhs.m_p), m_l(rhs.m_l), m_c(std::move(rhs.m_c)), m_w(rhs.m_w) {
    rhs.m_p = nullptr;
    rhs.m_l = nullptr;
    rhs.m_w = 0.0;
}

template <typename T>
trie<T>& trie<T>::operator=(trie<T>&& rhs) {
    if (this != &rhs) {
        delete m_l;
        m_c = std::move(rhs.m_c);
        m_p = rhs.m_p;
        m_l = rhs.m_l;
        m_w = rhs.m_w;

        rhs.m_p = nullptr;
        rhs.m_l = nullptr;
        rhs.m_w = 0.0;
    }
    return *this;
}

template <typename T>
trie<T>& trie<T>::operator=(trie<T> const& copy) {
    if (this != &copy) {
        m_l = copy.m_l;
        m_w = copy.m_w;
        if (!copy.m_c.empty()) {
            m_c = *copy.m_c;
            for (auto& child : m_c) {
                child.m_p = this;
                child = trie<T>(child);
            }
        } else {
            m_c = bag<trie<T>>();
        }
    }
    return *this;
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

template <typename T>
void trie<T>::add_child(trie<T> const& c) {
    if (this != &c) {
        trie<T> new_child = c;
        new_child.m_p = this;
        if (m_c.empty()) {
            m_c += new_child;
        } else {
            bool inserted = false;
            for (auto it = m_c.begin(); it != m_c.end(); ++it) {
                if (*(new_child.m_l) < *(it->m_l)) {
                    auto dist = 0;
                    for (auto it2 = m_c.begin(); it2 != it; ++it2) {
                        ++dist;
                    }
                    m_c.insert_at(new_child, dist);
                    inserted = true;
                    break;
                }
            }
            if (!inserted) {
                m_c += new_child;
            }
        }
    }
}

template <typename T>
bool trie<T>::operator==(trie<T> const& copy) const {
    // Check if labels and weights are equal
    if ((m_l == nullptr && copy.m_l != nullptr) || (m_l != nullptr && copy.m_l == nullptr)) return false;
    if (m_l != nullptr && copy.m_l != nullptr && *m_l != *copy.m_l) return false;
    if (m_w != copy.m_w) return false;

    // Check if the number of children is equal
    if (m_c.get_size() != copy.m_c.get_size()) return false;

    // Check if all children are equal
    auto it1 = m_c.begin();
    auto it2 = copy.m_c.begin();
    while (it1 != m_c.end() && it2 != copy.m_c.end()) {
        if (!(*it1 == *it2)) return false;
        ++it1;
        ++it2;
    }

    return true;
}

template <typename T>
trie<T>::node_iterator::node_iterator(trie<T>* trie)
    : m_ptr(trie) {}
template <typename T>
typename trie<T>::node_iterator::reference trie<T>::node_iterator::operator*() const {
    return *m_ptr;
}
template <typename T>
typename trie<T>::node_iterator::pointer trie<T>::node_iterator::operator->() const {
    return m_ptr;
}
template <typename T>
typename trie<T>::node_iterator& trie<T>::node_iterator::operator++() {
    if (m_ptr) m_ptr = m_ptr->next;
    return *this;
}
template <typename T>
typename trie<T>::node_iterator trie<T>::node_iterator::operator++(int) {
    node_iterator temp = *this;
    ++(*this);
    return temp;
}
template <typename T>
bool trie<T>::node_iterator::operator==(node_iterator const& other) const {
    return m_ptr == other.m_ptr;
}
template <typename T>
bool trie<T>::node_iterator::operator!=(node_iterator const& other) const {
    return m_ptr != other.m_ptr;
}

// Const node iterator
template <typename T>
trie<T>::const_node_iterator::const_node_iterator(trie<T> const* ptr)
    : m_ptr(ptr) {}
template <typename T>
typename trie<T>::const_node_iterator::reference trie<T>::const_node_iterator::operator*() const {
    return *m_ptr;
}
template <typename T>
typename trie<T>::const_node_iterator::pointer trie<T>::const_node_iterator::operator->() const {
    return m_ptr;
}
template <typename T>
typename trie<T>::const_node_iterator& trie<T>::const_node_iterator::operator++() {
    if (m_ptr) m_ptr = m_ptr->next;
    return *this;
}
template <typename T>
typename trie<T>::const_node_iterator trie<T>::const_node_iterator::operator++(int) {
    const_node_iterator temp = *this;
    ++(*this);
    return temp;
}
template <typename T>
bool trie<T>::const_node_iterator::operator==(const_node_iterator const& other) const {
    return m_ptr == other.m_ptr;
}
template <typename T>
bool trie<T>::const_node_iterator::operator!=(const_node_iterator const& other) const {
    return m_ptr != other.m_ptr;
}

// Leaf iterator
template <typename T>
trie<T>::leaf_iterator::leaf_iterator(trie<T>* leaf)
    : m_ptr(leaf) {}
template <typename T>
typename trie<T>::leaf_iterator::reference trie<T>::leaf_iterator::operator*() const {
    return *m_ptr;
}
template <typename T>
typename trie<T>::leaf_iterator::pointer trie<T>::leaf_iterator::operator->() const {
    return m_ptr;
}
template <typename T>
typename trie<T>::leaf_iterator& trie<T>::leaf_iterator::operator++() {
    if (m_ptr) m_ptr = m_ptr->next;
    return *this;
}
template <typename T>
typename trie<T>::leaf_iterator trie<T>::leaf_iterator::operator++(int) {
    leaf_iterator temp = *this;
    ++(*this);
    return temp;
}
template <typename T>
bool trie<T>::leaf_iterator::operator==(leaf_iterator const& other) const {
    return m_ptr == other.m_ptr;
}
template <typename T>
bool trie<T>::leaf_iterator::operator!=(leaf_iterator const& other) const {
    return m_ptr != other.m_ptr;
}
template <typename T>
trie<T>::leaf_iterator::operator trie<T>::node_iterator() const {
    return node_iterator(m_ptr);
}
template <typename T>
trie<T>& trie<T>::leaf_iterator::get_leaf() const {
    return *m_ptr;
}

// Const leaf iterator
template <typename T>
trie<T>::const_leaf_iterator::const_leaf_iterator(trie<T> const* ptr)
    : m_ptr(ptr) {}
template <typename T>
typename trie<T>::const_leaf_iterator::reference trie<T>::const_leaf_iterator::operator*() const {
    return *m_ptr;
}
template <typename T>
typename trie<T>::const_leaf_iterator::pointer trie<T>::const_leaf_iterator::operator->() const {
    return m_ptr;
}
template <typename T>
typename trie<T>::const_leaf_iterator& trie<T>::const_leaf_iterator::operator++() {
    if (m_ptr) m_ptr = m_ptr->next;
    return *this;
}
template <typename T>
typename trie<T>::const_leaf_iterator trie<T>::const_leaf_iterator::operator++(int) {
    const_leaf_iterator temp = *this;
    ++(*this);
    return temp;
}
template <typename T>
bool trie<T>::const_leaf_iterator::operator==(const_leaf_iterator const& other) const {
    return m_ptr == other.m_ptr;
}
template <typename T>
bool trie<T>::const_leaf_iterator::operator!=(const_leaf_iterator const& other) const {
    return m_ptr != other.m_ptr;
}
template <typename T>
trie<T>::const_leaf_iterator::operator trie<T>::const_node_iterator() const {
    return const_node_iterator(m_ptr);
}
template <typename T>
trie<T> const& trie<T>::const_leaf_iterator::get_leaf() const {
    return *m_ptr;
}

// Methods to return iterators
template <typename T>
typename trie<T>::leaf_iterator trie<T>::begin() {
    return leaf_iterator(this);
}
template <typename T>
typename trie<T>::leaf_iterator trie<T>::end() {
    return leaf_iterator(nullptr);
}
template <typename T>
typename trie<T>::node_iterator trie<T>::root() {
    return node_iterator(this);
}
template <typename T>
typename trie<T>::const_leaf_iterator trie<T>::begin() const {
    return const_leaf_iterator(this);
}
template <typename T>
typename trie<T>::const_leaf_iterator trie<T>::end() const {
    return const_leaf_iterator(nullptr);
}
template <typename T>
typename trie<T>::const_node_iterator trie<T>::root() const {
    return const_node_iterator(this);
}