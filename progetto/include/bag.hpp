#pragma region test //delete this section

#include <iostream>
using namespace std;

#pragma endregion
/*
 * Your implementation of the container bag<Val>.
 * Write both the declaration and definition of the
 * container in this file.
 */

template <typename T> class bag{
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
    Pimpl->head = new Cell{ T(), nullptr };
    Pimpl->tail = Pimpl->head;
}

template <typename T>
bag<T>::bag(const bag& copy){
    Pimpl = new Impl();
    Pimpl->head = nullptr;
    Pimpl->tail = nullptr;

    Pcell src = Pimpl->head;
    Pcell dest = copy.Pimpl->head;
    while(dest){
        this->append(dest->key, dest->val);
        dest = dest->next;
    }
}

template <typename T>
bag<T>::~bag(){
    Pimpl->destroy(Pimpl->head);
    delete Pimpl;
}

template <typename T>
void bag<T>::append(T val){
    if(Pimpl->head == Pimpl->tail){
        Pimpl->head->val = val;
        Pimpl->head->next = nullptr;
    } else {
        Pimpl->tail->next = new Cell;
        Pimpl->tail = Pimpl->tail->next;
        Pimpl->tail->val = val;
        Pimpl->tail->next = nullptr;
    }
}