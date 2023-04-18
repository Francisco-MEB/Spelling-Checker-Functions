#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <string_view>

#define LENGTH 45

struct node
{
    std::string word{};
    node* next{};
};

namespace hashTable
{
constexpr inline unsigned int size = 200; // number of buckets in hash table
node* table[size];
}

bool check(std::string_view word);
unsigned int hash(std::string_view word);
bool load(std::string_view dictionary);
unsigned int size(void);
bool unload();
std::string lowercaseConversion(std::string& word);


#endif
