#pragma region test //delete this section

#include <iostream>
using namespace std;

#pragma endregion
/*
 * Your implementation of the container bag<Val>.
 * Write both the declaration and definition of the
 * container in this file.
 */

template <typename T> class bag {
    class iterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = T;
            using pointer = T*;
            using reference = T&;

            iterator(bag<T>*);
            reference operator*() const;
            pointer operator->() const;
            iterator& operator++();
            iterator operator++(int);
            bool operator==(iterator const&) const;
            bool operator!=(iterator const&) const;
        
        private:
            typename bag<T>::Pcell current;
    };

    public:
        bag();
        bag(bag<T> const&);
        ~bag();

        void append(T val);

        #pragma region test // delete this section

        void print();

        #pragma endregion

    private:
        struct Cell {
            T val;
            Cell* next;
        };
        typedef Cell* Pcell;

        struct Impl;
        Impl* Pimpl;
};

#pragma region test //delete this section
template <typename T>
void bag<T>::print(){
    cout<<"bag:{\n";
    for(Pcell i = Pimpl->head; i; i = i->next)
        cout<<"\t[\n\t\tvalue: "<<i->val<<"\n\t\tnext: "<<i->next<<"\n\t],\n";
    cout<<"};\n";
}
#pragma endregion

template <typename T>
bag<T>::iterator::iterator(bag<T>* bag)
    : current(bag) {}

template <typename T>
typename bag<T>::iterator::reference bag<T>::iterator::operator*() const{
    return current->val;
}

template <typename T>
typename bag<T>::iterator::pointer bag<T>::iterator::operator->() const{
    return &(current->val);
}

template <typename T>
typename bag<T>::iterator& bag<T>::iterator::operator++(){
    if(current) current = current->next;
    return *this;
}

template <typename T>
typename bag<T>::iterator bag<T>::iterator::operator++(int n){
    bag<T>::iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
bool bag<T>::iterator::operator==(bag<T>::iterator const& other) const{
    return current == other.current;
}

template <typename T>
bool bag<T>::iterator::operator!=(bag<T>::iterator const& other) const{
    return current != other.current;
}

template <typename T>
struct bag<T>::Impl{
    Pcell head;
    Pcell tail;
    void destroy(Pcell head) const;
};

template <typename T>
void bag<T>::Impl::destroy(Pcell head) const{
    if(head){
        destroy(head->next);
        delete head;
    }
}

template <typename T>
bag<T>::bag(){
    Pimpl = new Impl();
    Pimpl->head = nullptr;
    Pimpl->tail = nullptr;
}

template <typename T>
bag<T>::bag(const bag<T>& copy) {
    Pimpl = new Impl();
    Pimpl->head = nullptr;
    Pimpl->tail = nullptr;

    Pcell src = copy.Pimpl->head;
    while (src) {
        this->append(src->val);
        src = src->next;
    }
}

template <typename T>
bag<T>::~bag(){
    Pimpl->destroy(Pimpl->head);
    delete Pimpl;
}

template <typename T>
void bag<T>::append(T val) {
    Pcell newCell = new Cell{val, nullptr};
    if (Pimpl->tail) {
        Pimpl->tail->next = newCell;
        Pimpl->tail = newCell;
    } else {
        Pimpl->head = Pimpl->tail = newCell;
    }
}