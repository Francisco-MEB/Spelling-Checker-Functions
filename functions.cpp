#include "Header.h"

#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <cctype>


bool check(std::string& word)
{
    int hashValue = hash(word);
    
    node *n = hashTable::table[hashValue];
    
    std::string wordCopy = lowercaseConversion(word);
    
    while (n != NULL)
    {
        std::string nextWord = lowercaseConversion(n->word);
        if (word == nextWord)
        {
            return true;
        }
        
        n = n->next;
    }
    
    return false;
}

unsigned int hash(std::string_view word)
{
    unsigned int hashValue = 0;
    for (int i = 0, wordLength = static_cast<int>(word.length()); i < wordLength; i++)
    {
        char letter = word[i];
        if (isupper(letter) != 0)
        {
            letter = tolower(letter);
        }
        int asciiConversion = letter;
        hashValue += asciiConversion;
        hashValue = hashValue * asciiConversion % hashTable::size;
    }
    
    return hashValue;
}

bool load(std::string_view dictionary, unsigned int& dictSize)
{
    std::ifstream dictFile{dictionary};
    if (!dictFile)
    {
        std::cerr << dictionary << " could not be opened for reading.\n";
        return false;
    }
    
    std::string word{};
    while (!dictFile.eof())
    {
        node* tmp = new node;
        if (!tmp)
        {
            return false;
        }
        
        tmp->word = word;
        
        int hashValue = hash(tmp->word);
        
        tmp->next = hashTable::table[hashValue];
        hashTable::table[hashValue] = tmp;
        
        dictSize++;
    }
    
    dictFile.close();
    
    return true;
}

bool unload()
{
    for (int i = 0; i < hashTable::size; i++)
    {
        node *ptr = hashTable::table[i];
        
        while (!ptr)
        {
            node *tmp = ptr;
            ptr = ptr->next;
            delete tmp;
        }
        
        if (!ptr && i == hashTable::size - 1)
        {
            return true;
        }
    }
    
    return false;
}

std::string lowercaseConversion(std::string& word)
{
    std::string tmp = word;
    for (int i = 0; i < word.length(); i++)
    {
        if (isupper(word[i]) != 0)
        {
            tmp[i] = tolower(tmp[i]);
        }
    }
    
    return tmp;
}

