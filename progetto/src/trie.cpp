#include "trie.hpp"  // It is forbidden to include other libraries!

template <typename T>
trie<T>::trie() 
    : m_p(nullptr), m_l(nullptr), m_c(), m_w(0.0) {}

template <typename T>
trie<T>::~trie() {
    for (auto& child : m_c) {
        child.m_p = nullptr; // Avoid double deletion
    }
    delete m_l;
}

template <typename T>
trie<T>::trie(double w)
    : m_p(nullptr), m_l(nullptr), m_c(), m_w(w) {}

template <typename T>
trie<T>::trie(trie<T> const& other) {
    m_p = other.m_p;
    m_l = other.m_l ? new T(*other.m_l) : nullptr;
    m_w = other.m_w;

    // Deep copy of children
    for (const auto& child : other.m_c) {
        trie<T> new_child(child);
        new_child.m_p = this; // Set the parent of the new child
        m_c += new_child;
    }
}

template <typename T>
trie<T>::trie(trie<T>&& other) {
    m_p = other.m_p;
    m_l = other.m_l;
    m_w = other.m_w;
    m_c = std::move(other.m_c);

    // Update parent pointers of the children
    for (auto& child : m_c) {
        child.m_p = this;
    }

    // Prevent the other node from deleting the moved resources
    other.m_l = nullptr;
    other.m_c.clear();
}

template <typename T>
trie<T>& trie<T>::operator=(trie<T> const& other) {
    if (this != &other) {
        // Create a temporary copy of the other node
        trie<T> temp(other);

        // Clean up existing resources
        delete m_l;
        m_c.clear();

        // Move data from the temporary copy to this node
        m_p = nullptr; // The parent will be set when the node is added to a new parent
        m_l = temp.m_l;
        m_w = temp.m_w;
        m_c = std::move(temp.m_c);

        // Update parent pointers of the children
        for (auto& child : m_c) {
            child.m_p = this;
        }

        // Prevent the temporary copy from deleting the moved resources
        temp.m_l = nullptr;
        temp.m_c.clear();
    }
    return *this;
}

template <typename T>
trie<T>& trie<T>::operator=(trie<T>&& other) {
    if (this != &other) {
        // Clean up existing resources
        delete m_l;
        m_c.clear();

        // Move data from other to this node
        m_p = nullptr; // The parent will be set when the node is added to a new parent
        m_l = other.m_l;
        m_w = other.m_w;
        m_c = std::move(other.m_c);

        // Update parent pointers of the children
        for (auto& child : m_c) {
            child.m_p = this;
        }

        // Prevent the other node from deleting the moved resources
        other.m_l = nullptr;
        other.m_c.clear();
    }
    return *this;
}

template <typename T>
void trie<T>::set_weight(double w) {
    this->m_w = w;
}

template <typename T>
double trie<T>::get_weight() const { return this->m_w; }

template <typename T>
void trie<T>::set_label(T* l) {
    delete this->m_l;
    m_l = l;
}

template <typename T>
T const* trie<T>::get_label() const { return this->m_l; }
template <typename T>
T* trie<T>::get_label() { return this->m_l; }

template <typename T>
void trie<T>::set_parent(trie<T>* p) { 
    delete this->m_p;
    this->m_p = p;
}

template <typename T>
trie<T> const* trie<T>::get_parent() const { return this->m_p; }
template <typename T>
trie<T>* trie<T>::get_parent() { return this->m_p; }

template <typename T>
bag<trie<T>> const& trie<T>::get_children() const { return this->m_c; }
template <typename T>
bag<trie<T>>& trie<T>::get_children() { return this->m_c; }

template <typename T>
void trie<T>::add_child(trie<T> const& c) {
    if (this != &c) {
        // Create a deep copy of the subtree
        trie<T> new_child(c);
        new_child.set_parent(this); // Set the parent of the new child

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
bool trie<T>::operator!=(trie<T> const& other) const {
    return !(*this == other);
}

template <typename T>
trie<T>& trie<T>::operator[](std::vector<T> const& v) {
    if(v.empty()) return *this;
    for(auto it = m_c.begin(); it != m_c.end(); ++it) {
        if(*(it->m_l) == v[0]) {
            std::vector<T> new_v(v.begin() + 1, v.end());
            return it->operator[](new_v);
        }
    }
    return *this;
}

template <typename T>
trie<T> const& trie<T>::operator[](std::vector<T> const& v) const {
    if(v.empty()) return *this;
    for(auto it = m_c.begin(); it != m_c.end(); ++it) {
        if(*(it->m_l) == v[0]) {
            std::vector<T> new_v(v.begin() + 1, v.end());
            return it->operator[](new_v);
        }
    }
    return *this;
}

// node_iterator
template <typename T>
trie<T>::node_iterator::node_iterator(trie<T>* ptr)
    : m_ptr(ptr) {}

template <typename T>
typename trie<T>::node_iterator::reference trie<T>::node_iterator::operator*() const {
    static T default_value; // Default value for root node
    if (m_ptr->m_l == nullptr) {
        return default_value; // Return default value for root node
    }
    return *(m_ptr->m_l);
}

template <typename T>
typename trie<T>::node_iterator::pointer trie<T>::node_iterator::operator->() const {
    if (m_ptr->m_l == nullptr) {
        return nullptr; // Return nullptr for root node
    }
    return m_ptr->m_l;
}

template <typename T>
typename trie<T>::node_iterator& trie<T>::node_iterator::operator++() {
    if (m_ptr) {
        m_ptr = m_ptr->m_p; // Move to parent node
    }
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

// leaf_iterator
template <typename T>
trie<T>::leaf_iterator::leaf_iterator(trie<T>* leaf)
    : m_ptr(leaf) {}

template <typename T>
typename trie<T>::leaf_iterator::reference trie<T>::leaf_iterator::operator*() const {
    static T default_value; // Default value for root node
    if (m_ptr->m_l == nullptr) {
        return default_value; // Return default value for root node
    }
    return *(m_ptr->m_l);
}

template <typename T>
typename trie<T>::leaf_iterator::pointer trie<T>::leaf_iterator::operator->() const {
    if (m_ptr->m_l == nullptr) {
        return nullptr; // Return nullptr for root node
    }
    return m_ptr->m_l;
}

template <typename T>
typename trie<T>::leaf_iterator& trie<T>::leaf_iterator::operator++() {
    if (m_ptr) {
        auto it = m_ptr->m_c.begin();
        if (it != m_ptr->m_c.end()) {
            m_ptr = &(*it);
        } else {
            m_ptr = nullptr;
        }
    }
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
    static T default_value; // Default value for root node
    if (m_ptr->m_l == nullptr) {
        return default_value; // Return default value for root node
    }
    return *(m_ptr->m_l);
}

template <typename T>
typename trie<T>::const_leaf_iterator::pointer trie<T>::const_leaf_iterator::operator->() const {
    if (m_ptr->m_l == nullptr) {
        return nullptr; // Return nullptr for root node
    }
    return m_ptr->m_l;
}

template <typename T>
typename trie<T>::const_leaf_iterator& trie<T>::const_leaf_iterator::operator++() {
    if (m_ptr) {
        auto it = m_ptr->m_c.begin();
        if (it != m_ptr->m_c.end()) {
            m_ptr = &(*it);
        } else {
            m_ptr = nullptr;
        }
    }
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
    // Find the first leaf in lexicographical order
    trie<T>* current = this;
    while (!current->m_c.empty()) {
        current = &(*current->m_c.begin());
    }
    return leaf_iterator(current);
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
    // Find the first leaf in lexicographical order
    const trie<T>* current = this;
    while (!current->m_c.empty()) {
        current = &(*current->m_c.begin());
    }
    return const_leaf_iterator(current);
}

template <typename T>
typename trie<T>::const_leaf_iterator trie<T>::end() const {
    return const_leaf_iterator(nullptr);
}

template <typename T>
typename trie<T>::const_node_iterator trie<T>::root() const {
    return const_node_iterator(this);
}