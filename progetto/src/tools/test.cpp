#include "../trie.cpp"
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// Custom to_string function
template <typename T>
std::string to_string(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

// ANSI color codes
const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string LIME = "\033[32m";

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
void testMaxFunction();     // forward declaration
void generateRandomTrie(trie<std::string>& node, int depth, int maxDepth); // forward declaration

bool all_tests_passed = true;
std::vector<std::string> passed_tests;
std::vector<std::string> failed_tests;

void check_test(bool condition, const std::string& test_name) {
    if (condition) {
        std::cout << LIME << "OK" << RESET << " - " << test_name << "\n";
        passed_tests.push_back(test_name);
    } else {
        std::cout << RED << "BAD" << RESET << " - " << test_name << "\n";
        failed_tests.push_back(test_name);
        all_tests_passed = false;
    }
}

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

    std::cout << "\n--- Testing max function on a large trie with random weights ---\n\n";
    testMaxFunction();

    std::cout << "\n--- Test Summary ---\n\n";
    std::cout << LIME << "Passed Tests:\n" << RESET;
    for (const auto& test : passed_tests) {
        std::cout << LIME << "OK" << RESET << " - " << test << "\n";
    }

    if (!failed_tests.empty()) {
        std::cout << RED << "\nFailed Tests:\n" << RESET;
        for (const auto& test : failed_tests) {
            std::cout << RED << "BAD" << RESET << " - " << test << "\n";
        }
    }

    if (all_tests_passed) {
        std::cout << LIME << "\nAll tests passed!\n" << RESET;
    } else {
        std::cout << RED << "\nSome tests failed.\n" << RESET;
    }

    return 0;
}

void testBagFunctions() {
    std::cout << "=== TEST BAG FUNCTIONS ===\n";
    bag<int> b1;
    check_test(b1.empty(), "Initial b1.empty()");
    check_test(b1.get_size() == 0, "Initial b1.size()");

    std::cout << "Adding elements to b1...\n";
    for (auto x : {1, 2, 3, 4, 5}) {
        b1 += x;
    }
    b1.print();
    check_test(b1.get_size() == 5, "b1.size() after adding elements");

    std::cout << "Inserting 99 at index 2...\n";
    b1.insert_at(99, 2);
    b1.print();
    check_test(*b1.at(2) == 99, "b1.at(2) after inserting 99");

    std::cout << "Copy-constructing b2 from b1...\n";
    bag<int> b2(b1);
    b2.print();
    check_test(b2.get_size() == b1.get_size(), "b2.size() after copy-construction");

    std::cout << "Assigning b2 to b3...\n";
    bag<int> b3;
    b3 = b2;
    b3.print();
    check_test(b3.get_size() == b2.get_size(), "b3.size() after assignment");
}

void testTrieFunctions() {
    std::cout << "=== TEST TRIE FUNCTIONS ===\n";
    trie<std::string> root;
    root.set_label(new std::string("root"));
    root.set_weight(0.0);

    trie<std::string> child1, child2, grandChild2;
    child1.set_label(new std::string("child1"));
    child1.set_weight(1.0);
    child2.set_label(new std::string("child2"));
    child2.set_weight(0.0);
    grandChild2.set_label(new std::string("grandChild2"));
    grandChild2.set_weight(2.0);

    child2.add_child(grandChild2);
    root.add_child(child1);
    root.add_child(child2);

    std::cout << "Printing root after adding child1 and child2:\n";
    root.print(std::cout);
    std::cout << "\n\n";

    std::cout << "Testing operator== and operator!=...\n";
    trie<std::string> rootCopy(root);
    check_test(root == rootCopy, "root == rootCopy");
    check_test(!(root != rootCopy), "root != rootCopy");

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

    std::cout << "Testing operator[] on root...\n";
    std::cout << "Setting path on {child2, grandChild}...\n";
    std::vector<std::string> path = {"child2", "grandChild"};
    trie<std::string>& result = root[path];
    result.print(std::cout);
    std::cout << "\n";
    child2.print(std::cout);
    std::cout << "\n";
    check_test(result == child2, "root[path] == child2");

    std::cout << "Testing operator[] on root...\n";
    std::cout << "Setting path2 on {child2, grandChild2}...\n";
    std::vector<std::string> path2 = {"child2", "grandChild2"};
    trie<std::string>& result2 = root[path2];
    result2.print(std::cout);
    std::cout << "\n";
    grandChild2.print(std::cout);
    std::cout << "\n";
    check_test(result2 == grandChild2, "root[path2] == grandChild2");

    std::cout << "Testing operator[] on constroot...\n";
    std::cout << "Setting path2 on {child3, grandChild4, child2}...\n";
    const trie<std::string>& constRoot = root;
    std::vector<std::string> path3 = {"child3", "grandChild4", "child2"};
    const trie<std::string>& result3 = constRoot[path3];
    result3.print(std::cout);
    std::cout << "\n";
    root.print(std::cout);
    std::cout << "\n";
    check_test(result3 == root, "root[path3] == root");

    std::cout << "Testing max() on root...\n";
    trie<std::string>& max = root.max();
    max.print(std::cout);
    std::cout << "\n";
    check_test(max == grandChild, "root.max() == grandChild");
}

void testBagEdgeCases() {
    std::cout << "=== TEST BAG EDGE CASES ===\n";

    std::cout << "Testing negative index, large index, and empty bag...\n";
    bag<int> bagEmpty;
    bagEmpty.insert_at(999, -10); // Should do nothing
    check_test(bagEmpty.empty(), "bagEmpty.empty() after invalid inserts");
    check_test(bagEmpty.get_size() == 0, "bagEmpty.size() after invalid inserts");
    bagEmpty.clear();
    int size = bagEmpty.get_size();
    bagEmpty.insert_at(999, 999); // Should also do nothing
    check_test(!bagEmpty.empty(), "!bagEmpty.empty() after out of range inserts");
    check_test(bagEmpty.get_size() == size+1, "bagEmpty.size() after out of range inserts");

    std::cout << "Testing large inserts...\n";
    bag<int> bagLarge;
    for(int i = 0; i < 50; ++i) {
        bagLarge += i;
    }
    bagLarge.print();
    check_test(bagLarge.get_size() == 50, "bagLarge.size() after large inserts");

    std::cout << "\nTesting copy and assignment with large bag...\n";
    bag<int> bagLargeCopy(bagLarge);
    bag<int> bagLargeAssign;
    bagLargeAssign = bagLarge;
    bagLargeCopy.print();
    bagLargeAssign.print();
    check_test(bagLargeCopy.get_size() == bagLarge.get_size(), "bagLargeCopy.size() after copy-construction");
    check_test(bagLargeAssign.get_size() == bagLarge.get_size(), "bagLargeAssign.size() after assignment");

    std::cout << "\nTrying at() with invalid indices...\n";
    check_test(bagLarge.at(-1) == nullptr, "bagLarge.at(-1)");
    check_test(bagLarge.at(9999) == nullptr, "bagLarge.at(9999)");
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

    std::cout << "\nTesting assigning children to its parent...\n";
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
    check_test(!(deep == almostSame), "deep == almostSame");
    check_test(deep != almostSame, "deep != almostSame");

    std::cout << "\nTesting a very, very deep trie of strings...\n";
    trie<std::string> veryDeep;
    veryDeep.set_label(new std::string("root"));
    trie<std::string>* newcurrent = &veryDeep;

    for (int level = 1; level <= 200; ++level) {
        trie<std::string> nextNode;
        nextNode.set_label(new std::string("level_" + to_string(level)));
        newcurrent->add_child(nextNode);
        // For deep chaining:
        auto& children = newcurrent->get_children();
        newcurrent = &(*children.at(children.get_size() - 1));
    }
    veryDeep.print(std::cout);
}

void generateRandomTrie(trie<std::string>& node, int depth, int maxDepth) {
    if (depth >= maxDepth) return;

    int numChildren = std::rand() % 2 + 1; // Random number of children between 0 and 2
    for (int i = 0; i < numChildren; ++i) {
        trie<std::string> child;
        child.set_label(new std::string("level_" + std::to_string(depth) + "_child_" + std::to_string(i)));
        child.set_weight(static_cast<double>(std::rand()) / RAND_MAX);
        node.add_child(child);
        auto& children = node.get_children();
        generateRandomTrie(*children.at(children.get_size() - 1), depth + 1, maxDepth);
    }
}

void testMaxFunction() {
    std::srand(std::time(nullptr)); // Seed for random number generation

    trie<std::string> root;
    root.set_label(new std::string("root"));
    root.set_weight(static_cast<double>(std::rand()) / RAND_MAX);

    // Generate a large trie with random weights
    generateRandomTrie(root, 0, 8);

    // Print the trie
    std::cout << "Trie before finding max:\n";
    root.print(std::cout);
    std::cout << "\n";

    // Find and print the max node
    trie<std::string>& maxNode = root.max();
    std::cout << "Max node weight: " << maxNode.get_weight() << "\n";
    std::cout << "Max node label: " << *maxNode.get_label() << "\n";
}
