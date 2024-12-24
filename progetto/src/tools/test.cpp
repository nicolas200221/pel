#include "../trie.cpp"
#include <sstream>

// Custom to_string function
template <typename T>
std::string to_string(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

void set_and_print(trie<std::string>& trie, const std::string& label, double weight = 0.0) {
    trie.set_label(new std::string(label));
    trie.set_weight(weight);
    trie.print();
    std::cout << std::endl;
}

void testBagFunctions();    // forward declaration
void testTrieFunctions();   // forward declaration
void testBagEdgeCases();    // forward declaration
void testTrieEdgeCases();   // forward declaration

//test trie.
int main() {
    std::cout << "\n--- Running Extended Tests ---\n\n";
    testBagFunctions();
    std::cout << "\n";
    testTrieFunctions();

    std::cout << "\n--- Stress Tests: Bag & Trie Edge Cases ---\n\n";
    testBagEdgeCases();
    std::cout << "\n";
    testTrieEdgeCases();

    return 0;
}

void testBagFunctions() {
    std::cout << "=== TEST BAG FUNCTIONS ===\n";
    bag<int> b1;
    std::cout << "Initial b1.empty() = " << b1.empty() << ", b1.size() = " << b1.get_size() << "\n";

    std::cout << "Adding elements to b1...\n";
    for (auto x : {1, 2, 3, 4, 5}) {
        b1 += x;
    }
    b1.print();
    std::cout << "b1.size() = " << b1.get_size() << "\n\n";

    std::cout << "Inserting 99 at index 2...\n";
    b1.insert_at(99, 2);
    b1.print();

    std::cout << "Copy-constructing b2 from b1...\n";
    bag<int> b2(b1);
    b2.print();
    std::cout << "b2.size() = " << b2.get_size() << "\n";

    std::cout << "Assigning b2 to b3...\n";
    bag<int> b3;
    b3 = b2;
    b3.print();
    std::cout << "b3.size() = " << b3.get_size() << "\n\n";
}

void testTrieFunctions() {
    std::cout << "=== TEST TRIE FUNCTIONS ===\n";
    trie<std::string> root;
    root.set_label(new std::string("root"));
    root.set_weight(0.0);

    trie<std::string> child1, child2;
    child1.set_label(new std::string("child1"));
    child1.set_weight(1.0);
    child2.set_label(new std::string("child2"));
    child2.set_weight(2.0);

    root.add_child(child1);
    root.add_child(child2);

    std::cout << "Printing root after adding child1 and child2:\n";
    root.print(std::cout);
    std::cout << "\n\n";

    std::cout << "Testing operator== and operator!=...\n";
    trie<std::string> rootCopy(root);
    std::cout << "root == rootCopy? " << (root == rootCopy) << "\n";
    std::cout << "root != rootCopy? " << (root != rootCopy) << "\n";

    std::cout << "\nAdding a grandchild to child1...\n";
    trie<std::string> grandChild;
    grandChild.set_label(new std::string("grandChild"));
    grandChild.set_weight(3.0);
    child1.add_child(grandChild); // This won't affect root's structure unless we do it directly on root's child
    child1.print(std::cout);

    std::cout << "\n(For demonstration, if needed, add child1 again to root)\n";
    root.add_child(child1);
    root.print(std::cout);
    std::cout << "\n";
}

void testBagEdgeCases() {
    std::cout << "=== TEST BAG EDGE CASES ===\n";

    std::cout << "Testing negative index, large index, and empty bag...\n";
    bag<int> bagEmpty;
    bagEmpty.insert_at(999, -10); // Should do nothing
    bagEmpty.insert_at(999, 999); // Should also do nothing
    std::cout << "bagEmpty.empty() = " << bagEmpty.empty()
              << ", bagEmpty.size() = " << bagEmpty.get_size() << "\n\n";

    std::cout << "Testing large inserts...\n";
    bag<int> bagLarge;
    for(int i = 0; i < 50; ++i) {
        bagLarge += i;
    }
    bagLarge.print();

    std::cout << "\nTesting copy and assignment with large bag...\n";
    bag<int> bagLargeCopy(bagLarge);
    bag<int> bagLargeAssign;
    bagLargeAssign = bagLarge;
    bagLargeCopy.print();
    bagLargeAssign.print();

    std::cout << "\nTrying at() with invalid indices...\n";
    std::cout << "bagLarge.at(-1) = " << (bagLarge.at(-1) ? *bagLarge.at(-1) : -9999) << "\n";
    std::cout << "bagLarge.at(9999) = " << (bagLarge.at(9999) ? *bagLarge.at(9999) : -9999) << "\n";
}

void testTrieEdgeCases() {
    std::cout << "=== TEST TRIE EDGE CASES ===\n";

    std::cout << "Constructing a trie of bool...\n";
    trie<bool> boolTrie;
    boolTrie.set_label(new bool(true));
    boolTrie.set_weight(3.14);

    trie<bool> childTrue, childFalse;
    childTrue.set_label(new bool(true));
    childFalse.set_label(new bool(false));
    boolTrie.add_child(childTrue);
    boolTrie.add_child(childFalse);
    boolTrie.print(std::cout);

    std::cout << "\nTesting a very deep trie of strings...\n";
    trie<std::string> deep;
    deep.set_label(new std::string("root"));
    trie<std::string> current(deep);

    for (int level = 1; level <= 5; ++level) {
        trie<std::string> nextNode;
        nextNode.set_label(new std::string("level_" + to_string(level)));
        current.add_child(nextNode);
        // For deep chaining:
        auto& children = current.get_children();
        current = *children.at(children.get_size() - 1);
    }
    deep.print(std::cout);

    std::cout << "\nTrying operator== and operator!= on partially-similar tries...\n";
    trie<std::string> almostSame(deep);
    almostSame.set_label(new std::string("almostRoot"));
    std::cout << "deep == almostSame? " << (deep == almostSame) << "\n";
    std::cout << "deep != almostSame? " << (deep != almostSame) << "\n";
}
