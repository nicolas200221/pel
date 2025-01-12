template <typename T> class bag {
    class iterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = T;
            using pointer = T*;
            using reference = T&;

            iterator(typename bag<T>::Pcell cell) : current(cell) {}
            reference operator*() const;
            pointer operator->() const;
            iterator& operator++();
            iterator operator++(int);
            bool operator==(iterator const& other) const;
            bool operator!=(iterator const& other) const;

        private:
            typename bag<T>::Pcell current;
    };

    class const_iterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = T;
            using pointer = const T*;
            using reference = const T&;

            const_iterator(typename bag<T>::Pcell cell) : current(cell) {}
            reference operator*() const;
            pointer operator->() const;
            const_iterator& operator++();
            const_iterator operator++(int);
            bool operator==(const_iterator const& other) const;
            bool operator!=(const_iterator const& other) const;

        private:
            typename bag<T>::Pcell current;
    };

    public:
    //constructors
        bag();
        bag(bag<T> const&);
        ~bag();

        void operator+=(T);
        void operator=(bag<T> const&);
        bag<T>& operator*() const;
        bool empty() const;
        int get_size() const;
        void clear();

    //insertion methods
        void insert_at(T, int);

    //get element
        T* at(int);

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
    
    private:
        int size;

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
    size = 0;
}

template <typename T>
bag<T>::bag(const bag<T>& copy) {
    Pimpl = new Impl();
    Pimpl->head = nullptr;
    Pimpl->tail = nullptr;
    size = 0;

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
void bag<T>::operator+=(T value) {
    this->append(value);
}

template <typename T>
void bag<T>::operator=(const bag<T>& copy) {
    if (this != &copy) {
        Pimpl->destroy(Pimpl->head);
        Pimpl->head = nullptr;
        Pimpl->tail = nullptr;
        size = 0;

        Pcell src = copy.Pimpl->head;
        while (src) {
            this->append(src->val);
            src = src->next;
        }
    }
}

template <typename T>
bag<T>& bag<T>::operator*() const {
    return *const_cast<bag<T>*>(this);
}

template <typename T>
bool bag<T>::empty() const {
    return !size;
}

template<typename T>
int bag<T>::get_size() const {
    return size;
}

template <typename T>
void bag<T>::clear() {
    Pimpl->destroy(Pimpl->head);
    Pimpl->head = nullptr;
    Pimpl->tail = nullptr;
    size = 0;
}

template <typename T>
void bag<T>::append(T val) {
    if (size > 0) {
        Pimpl->tail->next = new Cell { val, Pimpl->tail, nullptr };
        Pimpl->tail = Pimpl->tail->next;
        size++;
    } else {
        Pimpl->head = Pimpl->tail = new Cell { val, nullptr, nullptr };
        size++;
    }
}

template <typename T>
void bag<T>::prepend(T val) {
    Pcell newCell = new Cell { val, nullptr };
    if (size > 0) {
        Pimpl->head->prev = new Cell { val, nullptr, Pimpl->head };
        Pimpl->head = Pimpl->head->prev;
        size++;
    } else {
        Pimpl->head = Pimpl->tail = new Cell { val, nullptr, nullptr };
        size++;
    }
    delete newCell;
}

template <typename T>
void bag<T>::insert_at(T val, int index) {
    if (index < 0) return;
    if (index == 0) {
        prepend(val);
        return;
    }
    int i = 0;
    Pcell cell = Pimpl->head;
    while (i < index && cell) {
        cell = cell->next;
        i++;
    }
    if (!cell) {
        append(val);
        return;
    }
    Pcell new_cell = new Cell { val, cell->prev, cell };
    if (cell->prev) {
        cell->prev->next = new_cell;
    }
    cell->prev = new_cell;
    size++;
}

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

template <typename T>
typename bag<T>::iterator::reference bag<T>::iterator::operator*() const {
    return current->val;
}
template <typename T>
typename bag<T>::iterator::pointer bag<T>::iterator::operator->() const {
    return &(current->val);
}
template <typename T>
typename bag<T>::iterator& bag<T>::iterator::operator++() {
    if (current) 
        current = current->next;
    return *this;
}
template <typename T>
typename bag<T>::iterator bag<T>::iterator::operator++(int) {
    iterator tmp = *this;
    ++(*this);
    return tmp;
}
template <typename T>
bool bag<T>::iterator::operator==(const iterator& other) const {
    return current == other.current;
}
template <typename T>
bool bag<T>::iterator::operator!=(const iterator& other) const {
    return current != other.current;
}
template <typename T>
typename bag<T>::iterator bag<T>::begin() {
    return iterator(Pimpl->head);
}
template <typename T>
typename bag<T>::iterator bag<T>::end() {
    return iterator(nullptr);
}

template <typename T>
typename bag<T>::const_iterator::reference bag<T>::const_iterator::operator*() const {
    return current->val;
}
template <typename T>
typename bag<T>::const_iterator::pointer bag<T>::const_iterator::operator->() const {
    return &(current->val);
}
template <typename T>
typename bag<T>::const_iterator& bag<T>::const_iterator::operator++() {
    if (current) 
        current = current->next;
    return *this;
}
template <typename T>
typename bag<T>::const_iterator bag<T>::const_iterator::operator++(int) {
    const_iterator tmp = *this;
    ++(*this);
    return tmp;
}
template <typename T>
bool bag<T>::const_iterator::operator==(const const_iterator& other) const {
    return current == other.current;
}
template <typename T>
bool bag<T>::const_iterator::operator!=(const const_iterator& other) const {
    return current != other.current;
}
template <typename T>
typename bag<T>::const_iterator bag<T>::begin() const {
    return const_iterator(Pimpl->head);
}
template <typename T>
typename bag<T>::const_iterator bag<T>::end() const {
    return const_iterator(nullptr);
}