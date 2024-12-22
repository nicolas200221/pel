#include "../trie.cpp"

//test bag.
int main(){
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
}

/* int main() {
    return 0;
} */
