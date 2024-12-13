#include "../trie.cpp"

/* int main(){
    bag<char> bagchar;
    for(auto record : { 'a', 'z', 'b', 'h', 'g', 'l', 'e' })
        bagchar.insert(record);
    bagchar.print();
    bag<int> bagint;
    for(auto record : { 20, 35, 10, 15, 5, 42, 37 })
        bagint.insert(record);
    bagint.print();
    bag<int> bagintcopy(bagint);
    cout<<"bagintcopy(2) = "<<*(bagintcopy.at(2))<<endl;
//    bagintcopy.append_at(50, 2);
    cout<<"bagintcopy(3) = "<<*(bagintcopy.at(3))<<endl;
    cout<<"bagintcopy(0) = "<<*(bagintcopy.at(0))<<endl;
    cout<<"bagintcopy(15) = "<<(bagintcopy.at(15) ? *(bagintcopy.at(15)) : -16384)<<endl;
    cout<<"bagintcopy(-3) = "<<(bagintcopy.at(-3) ? *(bagintcopy.at(-3)) : -16384)<<endl;
//    bagintcopy.append_at(500, -2);
//    bagintcopy.append_at(50, 29);
    bagintcopy.insert(500);
    bagintcopy += 25;
    bagintcopy.print();
    bag<string> bagstring;
    for(auto record : { "ciao", "prova", "11!", "xd", "diocan", "lol", "zzzzz" })
        bagstring.insert(record);
    bagstring.print();
    return 0;
}  */

int main() {
    
    // Test bag<char>
    bag<char> bagchar;
    for (auto record : { 'a', 'z', 'b', 'h', 'g', 'l', 'e' })
        bagchar += record;
    bagchar.print();

    // Test bag<int>
    bag<int> bagint;
    for (auto record : { 20, 35, 10, 15, 5, 42, 37 })
        bagint += record;
    bagint.print();

    // Test copy constructor and at() method
    bag<int> bagintcopy(bagint);
    cout << "bagintcopy(2) = " << *(bagintcopy.at(2)) << endl;
    cout << "bagintcopy(3) = " << *(bagintcopy.at(3)) << endl;
    cout << "bagintcopy(0) = " << *(bagintcopy.at(0)) << endl;
    cout << "bagintcopy(15) = " << (bagintcopy.at(15) ? *(bagintcopy.at(15)) : -16384) << endl;
    cout << "bagintcopy(-3) = " << (bagintcopy.at(-3) ? *(bagintcopy.at(-3)) : -16384) << endl;

    // Test insert and operator+=
    bagintcopy += 500;
    bagintcopy += 25;
    bagintcopy.print();

    // Test bag<string>
    bag<string> bagstring;
    for (auto record : { "ciao", "prova", "11!", "xd", "diocan", "lol", "zzzzz" })
        bagstring += record;
    bagstring.print();

    // Test trie<int>
    trie<int> trieint;
    trieint.set_weight(1.5);
    int label = 10;
    trieint.set_label(&label);
    trie<int> child1;
    child1.set_weight(2.5);
    int child1_label = 20;
    child1.set_label(&child1_label);
    trieint.add_child(child1);
    trie<int> child2;
    child2.set_weight(3.5);
    int child2_label = 30;
    child2.set_label(&child2_label);
    trieint.add_child(child2);

    cout << "Trie root weight: " << trieint.get_weight() << endl;
    cout << "Trie root label: " << *(trieint.get_label()) << endl;
    cout << "Trie children count: " << trieint.get_children().get_size() << endl;

    for (auto it = trieint.begin(); it != trieint.end(); ++it) {
        cout << "Child weight: " << it.get_leaf().get_weight() << endl;
        cout << "Child label: " << *(it.get_leaf().get_label()) << endl;
    }
    return 0;
}
