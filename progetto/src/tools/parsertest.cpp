#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include "../trie.cpp"
using namespace std;

void trie_char();
void trie_string();
void trie_int();
void trie_double();
void trie_bool();

int main() {
    cout<<"***TRIE CHAR***"<<endl;
    trie_char();
    cout<<endl<<endl;
    cout<<"***TRIE STRING***"<<endl;
    trie_string();
    cout<<endl<<endl;
    cout<<"***TRIE INT***"<<endl;
    trie_int();
    cout<<endl<<endl;
    cout<<"***TRIE DOUBLE***"<<endl;
    trie_double();
    cout<<endl<<endl;
    cout<<"***TRIE BOOL***"<<endl;
    trie_bool();

    return 0;
}

void trie_char(){
    std::ifstream in("datasets/trie_char1.tr");
    if (!in.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
    }
    cout<<"Parsing trie<char> from file: datasets/trie_char1.tr"<<endl;

    trie<char> t;
    try {
        in >> t;
        std::cout << "Parsed trie: " << t << std::endl << std::endl;
    } catch (const parser_exception& e) {
        std::cerr << "Parser exception: " << e.what() << std::endl << std::endl;
    }
    in.close();
    

    for(int i = 1; i <= 5; i++){
        std::ifstream in_error("datasets/trie_char_error" + to_string(i) + ".tr");
        if (!in_error.is_open()) {
            std::cerr << "Unable to open file" << std::endl;
        }
        cout<<"Parsing trie<char> from file: datasets/trie_char_error" + to_string(i) + ".tr"<<endl;

        try {
            in_error >> t;
            std::cout << "Parsed trie: " << t << std::endl << std::endl;
        } catch (const parser_exception& e) {
            std::cerr << "Parser exception: " << e.what() << std::endl << std::endl;
        }
        in_error.close();
    }
}

void trie_string(){
    std::ifstream in("datasets/trie_string.tr");
    if (!in.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
    }
    cout<<"Parsing trie<string> from file: datasets/trie_string.tr"<<endl;

    trie<string> t;
    try {
        in >> t;
        std::cout << "Parsed trie: " << t << std::endl << std::endl;
    } catch (const parser_exception& e) {
        std::cerr << "Parser exception: " << e.what() << std::endl << std::endl;
    }
    in.close();
    

    for(int i = 1; i <= 4; i++){
        std::ifstream in_error("datasets/trie_string_error" + to_string(i) + ".tr");
        if (!in_error.is_open()) {
            std::cerr << "Unable to open file" << std::endl;
        }
        cout<<"Parsing trie<string> from file: datasets/trie_string_error" + to_string(i) + ".tr"<<endl;

        try {
            in_error >> t;
            std::cout << "Parsed trie: " << t << std::endl << std::endl;
        } catch (const parser_exception& e) {
            std::cerr << "Parser exception: " << e.what() << std::endl << std::endl;
        }
        in_error.close();
    }
}

void trie_int(){
    std::ifstream in("datasets/trie_int.tr");
    if (!in.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
    }
    cout<<"Parsing trie<int> from file: datasets/trie_int.tr"<<endl;

    trie<int> t;
    try {
        in >> t;
        std::cout << "Parsed trie: " << t << std::endl << std::endl;
    } catch (const parser_exception& e) {
        std::cerr << "Parser exception: " << e.what() << std::endl << std::endl;
    }
    in.close();
    

    for(int i = 1; i <= 5; i++){
        std::ifstream in_error("datasets/trie_int_error" + to_string(i) + ".tr");
        if (!in_error.is_open()) {
            std::cerr << "Unable to open file" << std::endl;
        }
        cout<<"Parsing trie<int> from file: datasets/trie_int_error" + to_string(i) + ".tr"<<endl;

        try {
            in_error >> t;
            std::cout << "Parsed trie: " << t << std::endl << std::endl;
        } catch (const parser_exception& e) {
            std::cerr << "Parser exception: " << e.what() << std::endl << std::endl;
        }
        in_error.close();
    }
}

void trie_double(){
    std::ifstream in("datasets/trie_double.tr");
    if (!in.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
    }
    cout<<"Parsing trie<double> from file: datasets/trie_double.tr"<<endl;

    trie<double> t;
    try {
        in >> t;
        std::cout << "Parsed trie: " << t << std::endl << std::endl;
    } catch (const parser_exception& e) {
        std::cerr << "Parser exception: " << e.what() << std::endl << std::endl;
    }
    in.close();
    

    for(int i = 1; i <= 5; i++){
        std::ifstream in_error("datasets/trie_double_error" + to_string(i) + ".tr");
        if (!in_error.is_open()) {
            std::cerr << "Unable to open file" << std::endl;
        }
        cout<<"Parsing trie<double> from file: datasets/trie_double_error" + to_string(i) + ".tr"<<endl;

        try {
            in_error >> t;
            std::cout << "Parsed trie: " << t << std::endl << std::endl;
        } catch (const parser_exception& e) {
            std::cerr << "Parser exception: " << e.what() << std::endl << std::endl;
        }
        in_error.close();
    }
}

void trie_bool(){
    std::ifstream in("datasets/trie_bool.tr");
    if (!in.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
    }
    cout<<"Parsing trie<bool> from file: datasets/trie_bool.tr"<<endl;

    trie<bool> t;
    try {
        in >> t;
        std::cout << "Parsed trie: " << std::boolalpha << t << std::endl << std::endl;
    } catch (const parser_exception& e) {
        std::cerr << "Parser exception: " << e.what() << std::endl << std::endl;
    }
    in.close();
    

    for(int i = 1; i <= 5; i++){
        std::ifstream in_error("datasets/trie_bool_error" + to_string(i) + ".tr");
        if (!in_error.is_open()) {
            std::cerr << "Unable to open file" << std::endl;
        }
        cout<<"Parsing trie<double> from file: datasets/trie_bool_error" + to_string(i) + ".tr"<<endl;

        try {
            in_error >> t;
            std::cout << "Parsed trie: " << std::boolalpha << t << std::endl << std::endl;
        } catch (const parser_exception& e) {
            std::cerr << "Parser exception: " << e.what() << std::endl << std::endl;
        }
        in_error.close();
    }
}