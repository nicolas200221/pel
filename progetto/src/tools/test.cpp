#include "../trie.cpp"

//test bag.
/* int main(){
    bag<char> bagchar;
    for(auto record : { 'a', 'z', 'b', 'h', 'g', 'l', 'e' })
        bagchar += record;
    bagchar.print();
    bag<int> bagint;
    for(auto record : { 20, 35, 10, 15, 5, 42, 37 })
        bagint += record;
    bagint.print();
    bag<int> bagintcopy(bagint);
    cout<<"bagintcopy(2) = "<<*(bagintcopy.at(2))<<endl;
    cout<<"bagintcopy(3) = "<<*(bagintcopy.at(3))<<endl;
    cout<<"bagintcopy(0) = "<<*(bagintcopy.at(0))<<endl;
    cout<<"bagintcopy(15) = "<<(bagintcopy.at(15) ? *(bagintcopy.at(15)) : -16384)<<endl;
    cout<<"bagintcopy(-3) = "<<(bagintcopy.at(-3) ? *(bagintcopy.at(-3)) : -16384)<<endl;
    bagintcopy += 500;
    bagintcopy += 25;
    bagintcopy.print();
    bag<string> bagstring;
    for(auto record : { "ciao", "prova", "11!", "xd", "diocan", "lol", "zzzzz" })
        bagstring += record;
    bagstring.print();
    cout<<"bagstring.empty() = "<<bagstring.empty()<<endl;
    cout<<"bagstring.get_size() = "<<bagstring.get_size()<<endl;
    bagstring.insert_at("2", 2);
    bagstring.print();
    cout<<"bagstring.empty() = "<<bagstring.empty()<<endl;
    cout<<"bagstring.get_size() = "<<bagstring.get_size()<<endl;
    bag<bool> bagbool;
    bagbool.print();
    cout<<"bagbool.empty() = "<<bagbool.empty()<<endl;
    cout<<"bagbool.get_size() = "<<bagbool.get_size()<<endl;
    bagbool.insert_at(true, 15);
    bagbool.insert_at(false, -3);
    return 0;
} */

//test trie.
int main() {
    trie<string> triestring;
    trie<string> triestring2;
    trie<string> triestring3;
    trie<string> triestring4;
    trie<string> triestring5;
    trie<string> triestring6;

    triestring2.set_label(new string("ciao"));
    triestring2.print();
    
    triestring3.set_label(new string("prova"));
    triestring3.set_weight(0.5);
    triestring3.print();

    triestring4.set_label(new string("11!"));
    triestring4.print();
    
    triestring5.set_label(new string("xd"));
    triestring5.print();

    triestring6.set_label(new string("diocan"));
    triestring6.set_weight(5.0);
    triestring6.print();

    triestring5.add_child(triestring6);
    triestring5.print();

    triestring4.add_child(triestring5);
    triestring4.print();

    triestring2.add_child(triestring3);
    triestring2.print();

    triestring2.add_child(triestring4);
    triestring2.print();

    triestring.add_child(triestring2);
    triestring.print();
    return 0;
}
