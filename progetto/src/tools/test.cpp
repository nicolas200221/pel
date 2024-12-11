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
    // Crea due trie vuoti
    trie<int> trie1;
    trie<int> trie2;

    // Confronto tra trie vuoti
    if (trie1 == trie2) {
        std::cout << "Trie vuoti sono uguali!" << std::endl;
    } else {
        std::cout << "Trie vuoti NON sono uguali!" << std::endl;
    }

    // Aggiungi etichette, pesi e figli a trie1
    trie1.set_label(new int(1));
    trie1.set_weight(10.0);
    trie<int> child1;
    child1.set_label(new int(2));
    child1.set_weight(5.0);
    trie1.add_child(child1);

    // Aggiungi etichette, pesi e figli a trie2 (identici a trie1)
    trie2.set_label(new int(1));
    trie2.set_weight(10.0);
    trie<int> child2;
    child2.set_label(new int(2));
    child2.set_weight(5.0);
    trie2.add_child(child2);

    // Confronto tra trie con stessi dati
    if (trie1 == trie2) {
        std::cout << "Trie con stessi dati sono uguali!" << std::endl;
    } else {
        std::cout << "Trie con stessi dati NON sono uguali!" << std::endl;
    }

    // Modifica trie2 per renderlo diverso
    trie2.set_weight(20.0);

    // Confronto tra trie con dati diversi
    if (trie1 == trie2) {
        std::cout << "Trie con dati diversi sono uguali!" << std::endl;
    } else {
        std::cout << "Trie con dati diversi NON sono uguali!" << std::endl;
    }

    return 0;
}
