#pragma region delete

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
    //constructors
        bag();
        bag(bag<T> const&);
        ~bag();
    
    //insertion methods
        void insert(T);
        #pragma region delete
        //void insert_at(T, int);
        //void append_at(T, int);
        #pragma endregion

    //get element
        T* at(int);

        #pragma region delete

        void print();

        #pragma endregion
    
    private:
        struct Cell {
            T val;
            Cell* prev;
            Cell* next;
        };
        typedef Cell* Pcell;

        struct Impl;
        Impl* Pimpl;

        void append(T);
        void prepend(T);
};

#pragma region delete
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
    if (Pimpl->tail) {
        Pimpl->tail->next = new Cell { val, Pimpl->tail, nullptr };
        Pimpl->tail = Pimpl->tail->next;
    } else {
        Pimpl->head = Pimpl->tail = new Cell { val, nullptr, nullptr };
    }
}

template <typename T>
void bag<T>::prepend(T val) {
    Pcell newCell = new Cell { val, nullptr };
    if (Pimpl->head) {
        Pimpl->head->prev = new Cell { val, nullptr, Pimpl->head };
        Pimpl->head = Pimpl->head->prev;
    } else {
        Pimpl->head = Pimpl->tail = new Cell { val, nullptr, nullptr };
    }
}

template <typename T>
void bag<T>::insert(T val) {
    Pcell cell = Pimpl->head;
    bool found = false;
    int index = 0;
    while(cell && !found){
        if(cell->val <= val){
            cell = cell->next;
            index++;
        }
        else found = true;
    }
    if(!cell) append(val);
    else if(index == 0) prepend(val);
    else{
        Pcell new_cell = new Cell { val, cell->prev, cell };
        cell->prev->next = new_cell;
        cell->prev = new_cell;
    }
}

#pragma region delete
/* template <typename T>
void bag<T>::insert_at(T val, int index) {
    if(index < 0) return;
    if(index == 0){
        this->append(val);
        return;
    }
    int i = 0;
    Pcell cell = Pimpl->head;
    while(i < index && cell){
        cell = cell->next;
        i++;
    }
    if(!cell) return;
    Pcell tmp = cell;
    cell = new Cell { val, tmp->prev, new Cell { tmp->val, cell, tmp->next } };
    tmp->prev->next = cell;
}

template <typename T>
void bag<T>::append_at(T val, int index) {
    if(index < 0) return;
    if(index == 0){
        this->append(val);
        return;
    }
    int i = 0;
    Pcell cell = Pimpl->head;
    while(i < index && cell){
        cell = cell->next;
        i++;
    }
    if(!cell) return;
    Pcell tmp = cell->next;
    cell->next = new Cell { val, cell, tmp };
} */
#pragma endregion

template <typename T>
T* bag<T>::at(int index) {
    if (index < 0) return nullptr;
    if (index == 0) return &Pimpl->head->val;
    int i = 0;
    Pcell cell = Pimpl->head;
    while (i < index && cell) {
        cell = cell->next;
        i++;
    }
    if (!cell) return nullptr;
    return &cell->val;
}
