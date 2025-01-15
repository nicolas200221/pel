#include "trie.hpp"  // It is forbidden to include other libraries!

template <typename T>
int constructor(const std::string&, trie<T>&);

template <typename T>
T parser_set_label(size_t*, size_t*, size_t, int, std::string);

template <typename T>
bool misspell(std::string);

template <typename T>
std::ostream& operator<<(std::ostream& os, trie<T> const& t) {
    if(t.get_label() != nullptr) os << *t.get_label() << " children={ ";
    else os << "children={ ";
    const auto& children = t.get_children();
    size_t count = 0;
    for (const auto& child : children) {
        if (!child.get_children().empty()) {
            os << child;
        } else {
            os << *child.get_label() << " ";
            if(child.get_weight() != 0.0) os << child.get_weight() << " ";
            os << "children={}";
        }
        if (++count != children.get_size()) {
            os << ", ";
        }
    }
    os << "}";
    return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, trie<T>& t) {
    t = trie<T>(); // Reset the trie

    std::string input;
    std::string line;

    // Read the entire file content
    while (std::getline(is, line)) {
        // Manually remove spaces, tabs, and newlines
        std::string cleaned_line;
        std::string buffer = "";
        int label = 0;
        int weight = 0;
        for (char c : line) {
            if (!std::isspace(static_cast<unsigned char>(c))) {
                cleaned_line += c;
                buffer += c;
            } else {
                bool is_weight = ((buffer.size() == 3) && (isdigit(buffer[0]) && buffer[1] == '.' && isdigit(buffer[2])));
                bool is_valid = true;
                if constexpr (!((std::is_same<T, double>::value) || (std::is_same<T, float>::value))) {
                    for(char b : buffer){
                        if(!isalnum(b)) {
                            is_valid = false;
                            break;
                        }
                    }
                } else is_valid = is_weight;
                if(!buffer.empty() && !is_weight && is_valid && (buffer != "children")){
                    if(label == 1) {
                        if (misspell<T>(buffer)) throw parser_exception("Syntax error, found \"" + buffer + "\" did you mean \"children\"?");
                        else throw parser_exception(" Only one label is allowed");
                    } else label = 1;
                } else if(is_weight){
                    if(is_valid){
                        if(label == 2) throw parser_exception("Only one label is allowed");
                        else label++;
                    } else {
                        if(weight == 1) throw parser_exception("Only one weight is allowed");
                        else weight++;
                    }
            } else {
                label = 0;
                weight = 0;
            }
            buffer = "";
            }
        }
        input += cleaned_line;
    }



    // Parse the input string
    if (input.substr(0, 8) != "children") throw parser_exception("Expected 'children' keyword at the beginning of the file");
    if (input.size() < 10 || input[8] != '=' || input[9] != '{') throw parser_exception("Expected '={}' after 'children' keyword");
    if (input.back() != '}') throw parser_exception("Expected '}' at the end of the file");

    std::cout<<"input: "<<input<<std::endl;
    constructor(input.substr(10, input.size() - 11), t);

    return is;
}

//check if children keyword is misspelled by checking how far is from the original
template <typename T>
bool misspell(std::string s){
    std::string children = "children";
    int match = 0;
    int next = 0;
    int pos = 0;
    for(char c : children){
        size_t found = s.find(c);
        if(found != std::string::npos){
            if(found == (pos + 1)) next++;
            match++;
            pos = found;
        }
    }
    if(match >= 3 && next >= 3) return true;
    else return false;
}

template <typename T>
int constructor(const std::string& s, trie<T>& t) {
    bool is_leaf = false;
    int pos = 0;
    while(pos < s.size() - 1) {
        T label;
        double weight = 0.0;
        trie<T> child;
        const size_t WEIGHT_SIZE = 3;
        size_t label_weight_size;
        size_t label_size = 0;
        //fix position if there were multiple node closing brackets before this one.
        while(!isalpha(s[pos]) && s[pos - 1] == '}') pos++;
        
        label = parser_set_label<T>(&label_size, &label_weight_size, WEIGHT_SIZE, pos, s);

        std::string weightstr = s.substr(pos + label_size, 3);

        //check if leaf
        if(isdigit(weightstr[0]) && weightstr[1] == '.' && isdigit(weightstr[2])){
            const std::string LEAF_END = s.substr(pos + label_weight_size, 12);
            bool not_last_child = (LEAF_END == "children={},");
            bool last_child = (LEAF_END == "children={}}");
            bool only_child = (LEAF_END == s.substr(pos + label_weight_size));
            if(not_last_child || last_child || only_child){
                is_leaf = true;
                weight = stod(weightstr);
                child.set_label(new T(label));
                child.set_weight(weight);
                t.add_child(child);
            }
            else if(s.substr(pos + label_weight_size, 11) == "children={}") throw parser_exception("Missing ',' after childs list");
            else throw parser_exception("Syntax error on leaf definition, expected 'children={}', but found: " + s.substr(pos + label_weight_size, 11));
        } else {
            //check if node
            if(s.substr(pos + label_size, 11) == "children={}")
                throw parser_exception("Missing weight on leaf");
            else {
                if(s.substr(pos + label_size, 10) == "children={"){
                    is_leaf = false;
                    child.set_label(new T(label));
                } else throw parser_exception("Syntax error on node definition, expected 'children={...}', but found: " + s.substr(pos + label_size, 10));
            }
        }
        //if node is a leaf, skip to the next node, else call recursively constructor on the node to add its child.
        if(is_leaf) pos += label_weight_size + 12; // 12("children={}," lenght).
        else{
            const int ENTIRE_CHILDREN = pos + label_size + 10; // 10("children={" lenght).
            int temp_pos = ENTIRE_CHILDREN;
            int nodes_encountered = 0;
            std::string eof = std::string(s.size() - temp_pos, '}');
            while((temp_pos < s.size()) && (s.substr(temp_pos) != eof) && nodes_encountered >= 0){
                if(s[temp_pos] == '{' && s[temp_pos + 1] != '}') nodes_encountered++;
                if(s[temp_pos] == '}'){
                    if(s[temp_pos + 1] != '}'){
                        if(s[temp_pos + 1] != ',')
                            throw parser_exception("Missing ',' after childs list");
                        if (!isalnum(s[temp_pos + 2])) throw parser_exception("Found illegal character at the end of trie<char> definition");
                    }
                }
                if(s[temp_pos] == '}' && s[temp_pos + 1] == '}') nodes_encountered--;
                else if(s[temp_pos] == '}' && s[temp_pos + 1] != ',') throw parser_exception("Missing ',' after childs list");
                temp_pos++;
                eof = std::string(s.size() - temp_pos, '}');
            }
            if(nodes_encountered >= 0){
                if(s[temp_pos - 1] == '{') temp_pos++;
                temp_pos += nodes_encountered;
                if (s[temp_pos + 1] == ',') throw parser_exception("Found illegal character at the end of trie<char> definition");
                pos += constructor(s.substr(ENTIRE_CHILDREN, (s.size() - 1) - (ENTIRE_CHILDREN)), child) + (label_size + 10); 
                t.add_child(child);
            } else {
                if(isalpha(s[temp_pos + 1])) throw parser_exception("Missing ',' after childs list");
                pos += constructor(s.substr(ENTIRE_CHILDREN, temp_pos - (ENTIRE_CHILDREN)), child) + (label_size + 10);
                t.add_child(child);
            }
        }
    }
    return pos;
}

template <typename T>
T parser_set_label(size_t* label_size, size_t* label_weight_size, size_t WEIGHT_SIZE, int pos, std::string s){
    //extract label from string
    auto extract_label = [=](std::string s, int pos) -> std::string {
        int temp_pos = pos;
        std::string label_temp = "";
        std::string weight = "";
        bool is_weight = false;
        bool is_valid = false;
        if constexpr ((std::is_same<T, double>::value) || (std::is_same<T, float>::value)){
            weight = s.substr(temp_pos + 3, 3);
            is_weight = (temp_pos + 5 < s.size()) && (isdigit(weight[0]) && weight[1] == '.' && isdigit(weight[2]));
            if(is_weight) {
                (*label_size) = 3;
                return s.substr(temp_pos, 3);
            } else if (s.substr(temp_pos + 3, 8) == "children") {
                (*label_size) = 3;
                return s.substr(temp_pos, 3);;
            }
            is_valid = isalnum(s[temp_pos]);
        } else {
            if constexpr (std::is_same<T, std::string>::value) is_valid = !isdigit(s[temp_pos]);
            else is_valid = isalnum(s[temp_pos]);
            weight = s.substr(temp_pos, 3);
            is_weight = (temp_pos + 2 < s.size()) && (isdigit(weight[0]) && weight[1] == '.' && isdigit(weight[2]));
        }
        while(is_valid && !is_weight && (s.substr(temp_pos, 8) != "children")){
            label_temp += s[temp_pos];
            (*label_size)++;
            temp_pos++;
            if constexpr ((std::is_same<T, double>::value) || (std::is_same<T, float>::value)){
                weight = s.substr(temp_pos + 3, 3);
                is_weight = (temp_pos + 5 < s.size()) && (isdigit(weight[0]) && weight[1] == '.' && isdigit(weight[2]));
            } else {
                weight = s.substr(temp_pos, 3);
                is_weight = (temp_pos + 2 < s.size()) && (isdigit(weight[0]) && weight[1] == '.' && isdigit(weight[2]));
            }
        }
        return label_temp;
    };

    //check if children keyword is misspelled
    auto children_misspell = [=](std::string s, int pos) -> void {
        //try to extract children keyword from string
        auto extract_children_keyword = [&](std::string s, int& pos, bool& delimiter, bool& is_weight) -> std::string {
            std::string children_temp = "";
            std::string children_check = s.substr(pos, 8);
            bool end_children = false;
            while((pos < s.size()) && !delimiter && !is_weight && (children_check != "children")){
                std::string weight = "";
                if constexpr ((std::is_same<T, double>::value) || (std::is_same<T, float>::value)){
                    if (!end_children && (s[pos+3] != '=' && s[pos+3] != '{' && s[pos+3] != '}' && s[pos+3] != ',')){
                        weight = s.substr(pos + 3, 3);
                        is_weight = (pos + 5 < s.size()) && (isdigit(weight[0]) && weight[1] == '.' && isdigit(weight[2]));
                    } else end_children = true;
                } else {
                    weight = s.substr(pos, 3);
                    is_weight = (pos + 2 < s.size()) && (isdigit(weight[0]) && weight[1] == '.' && isdigit(weight[2]));
                }
                if(!is_weight){
                    if (s[pos] == '=' || s[pos] == '{' || s[pos] == '}' || s[pos] == ',')
                        delimiter = true;
                    else {
                        children_temp += s[pos];
                        pos++;
                        children_check = s.substr(pos, 8);
                    }
                }
            }
            if(children_check == "children") return children_check;
            else return children_temp;
        };

        const std::string children = "children";
        bool delimiter = false;
        bool is_weight = false;
        std::string children_temp = "";
        children_temp = extract_children_keyword(s, pos, delimiter, is_weight);
        //if there is a weight, check again skipping the weight
        if(is_weight){
            delimiter = false;
            is_weight = false;
            pos += 3;
            children_temp = extract_children_keyword(s, pos, delimiter, is_weight);
            if(children_temp != children)
                throw parser_exception("Syntax error, found \"" + children_temp + "\" did you mean \"" + children + "\"?");
        } else {
            std::string extracted_keyword = "";
            if(children_temp.size() >= children.size())
                extracted_keyword = children_temp.substr(children_temp.size() - children.size(), children.size());
            else extracted_keyword = children_temp;
            if(extracted_keyword != children)
                throw parser_exception("Syntax error, found \"" + extracted_keyword + "\" did you mean \"" + children + "\"?");
        }
    };

    if constexpr (std::is_same<T, char>::value){
        (*label_size) = 0;
        children_misspell(s, pos);
        std::string label_temp = extract_label(s, pos);
        *label_weight_size = (*label_size) + WEIGHT_SIZE;
        if ((*label_size) == 1) {
            if(!isalpha(label_temp[0]))
                throw parser_exception("Label on trie<char> should be a letter, but found: " + label_temp);
            else return label_temp[0];
        } else 
            throw parser_exception("Label on trie<char> should be a single letter, but found: " + label_temp);
    }

    if constexpr (std::is_same<T, std::string>::value){
        (*label_size) = 0;
        children_misspell(s, pos);
        std::string label_temp = extract_label(s, pos);
        (*label_weight_size) = (*label_size) + WEIGHT_SIZE;
        return label_temp; 
    }

    if constexpr ((std::is_same<T, int>::value) || (std::is_same<T, bool>::value)){
        (*label_size) = 0;
        children_misspell(s, pos);
        std::string label_temp = extract_label(s, pos);
        *label_weight_size = *label_size + WEIGHT_SIZE;
        if ((*label_size) == 1) {
            if(!isdigit(label_temp[0]))
                throw parser_exception("Label on trie<int> should be a digit, but found: " + label_temp);
            else return (label_temp[0] - 48);
        } else 
            throw parser_exception("Label on trie<int> should be a single digit, but found: " + label_temp);
    }

    if constexpr ((std::is_same<T, double>::value) || (std::is_same<T, float>::value)) {
        *label_size = 0;
        children_misspell(s, pos);
        std::string label_temp = extract_label(s, pos);
        *label_weight_size = *label_size + WEIGHT_SIZE;
        if((*label_size) == 3){
            if(!isdigit(label_temp[0]) || label_temp[1] != '.' || !isdigit(label_temp[2]))
                throw parser_exception("Syntax error on trie<double> definition, label should be a double, but found: " + label_temp);
            else return stod(label_temp);
        } else 
            throw parser_exception("Label on trie<double> should be of format \"x.x\", but found: " + label_temp);
    }
}

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

        // Check for duplicate labels among sibling nodes
        for (const auto& child : m_c) {
            if (*(new_child.m_l) == *(child.m_l)) {
                std::cout << "Duplicate label found:" << std::endl;
                std::cout << "new child:" << std::endl << new_child << std::endl;
                std::cout << "Existing child:" << std::endl << child << std::endl;
                throw parser_exception("Duplicate label found in sibling nodes");
            }
        }

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

template <typename T>
trie<T>& trie<T>::max() {
    if (m_c.empty()) return *this;
    trie<T>* max_node = this;
    for (auto it = m_c.begin(); it != m_c.end(); ++it) {
        if (!it->m_c.empty()) {
            trie<T>& child_max = it->max();
            if (child_max.m_w > max_node->m_w) {
                max_node = &child_max;
            }
        } else if (it->m_w > max_node->m_w) {
            max_node = &(*it);
        }
    }
    return *max_node;
}

template <typename T>
trie<T> const& trie<T>::max() const {
    if (m_c.empty()) return *this;
    trie<T> const* max_node = this;
    for (auto it = m_c.begin(); it != m_c.end(); ++it) {
        if (!it->m_c.empty()) {
            trie<T> const& child_max = it->max();
            if (child_max.m_w > max_node->m_w) {
                max_node = &child_max;
            }
        } else if (it->m_w > max_node->m_w) {
            max_node = &(*it);
        }
    }
    return *max_node;
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