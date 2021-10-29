//---------------------------------------------------------------------------
// NAME: Mason Manca
// DATE: Fall 2021
// DESC:
//---------------------------------------------------------------------------

#ifndef BINSEARCHMAP_H
#define BINSEARCHMAP_H

#include "map.h"
#include "arrayseq.h"

template <typename K, typename V>
class BinSearchMap : public Map<K, V>
{
public:
    // Returns the number of key-value pairs in the map
    int size() const;

    // Tests if the map is empty
    bool empty() const;

    // Allows values associated with a key to be updated. Throws
    // out_of_range if the given key is not in the collection.
    V &operator[](const K &key);

    // Returns the value for a given key. Throws out_of_range if the
    // given key is not in the collection.
    const V &operator[](const K &key) const;

    // Extends the collection by adding the given key-value
    // pair. Assumes the key being added is not present in the
    // collection. Insert does not check if the key is present.
    void insert(const K &key, const V &value);

    // Shrinks the collection by removing the key-value pair with the
    // given key. Does not modify the collection if the collection does
    // not contain the key. Throws out_of_range if the given key is not
    // in the collection.
    void erase(const K &key);

    // Returns true if the key is in the collection, and false
    // otherwise.
    bool contains(const K &key) const;

    // Returns the keys k in the collection such that k1 <= k <= k2
    ArraySeq<K> find_keys(const K &k1, const K &k2) const;

    // Returns the keys in the collection in ascending sorted order.
    ArraySeq<K> sorted_keys() const;

private:
    // If the key is in the collection, bin_search returns true and
    // provides the key's index within the array sequence (via the index
    // output parameter). If the key is not in the collection,
    // bin_search returns false and provides the last index checked by
    // the binary search algorithm.
    bool bin_search(const K &key, int &index) const;

    // implemented as a resizable array of (key-value) pairs
    ArraySeq<std::pair<K, V>> seq;
};

// TODO: Implement the BinSearchMap functions below. Note that you do
//       not need to implement a default constructor, destructor, copy
//       constructor, copy assignment operator, move constructor, and
//       move assignment operator for this version of Map. Instead,
//       the default C++ implementations are sufficient.

#endif

// Def

// Returns the number of key-value pairs in the map
template <typename K, typename V>
int BinSearchMap<K, V>::size() const
{
    return seq.size();
}

// Tests if the map is empty
template <typename K, typename V>
bool BinSearchMap<K, V>::empty() const
{
    return seq.empty();
}

// Allows values associated with a key to be updated. Throws
// out_of_range if the given key is not in the collection.
template <typename K, typename V>
V &BinSearchMap<K, V>::operator[](const K &key)
{
    int index = 0;
    if (bin_search(key, index))
        return seq[index].second;
    else
    {
        throw std::out_of_range("Out of range in the [] nonconst");
    }
}

// Returns the value for a given key. Throws out_of_range if the
// given key is not in the collection.
template <typename K, typename V>
const V &BinSearchMap<K, V>::operator[](const K &key) const
{
    int index = 0;
    if (bin_search(key, index))
      return seq[index].second;
    else
    {
        throw std::out_of_range("Out of range in the [] nonconst");
    }
}

// Extends the collection by adding the given key-value
// pair. Assumes the key being added is not present in the
// collection. Insert does not check if the key is present.
template <typename K, typename V>
void BinSearchMap<K, V>::insert(const K &key, const V &value)
{
    int index = 0;
    if (!bin_search(key, index))
      seq.insert({key, value}, index);
}

// Shrinks the collection by removing the key-value pair with the
// given key. Does not modify the collection if the collection does
// not contain the key. Throws out_of_range if the given key is not
// in the collection.
template <typename K, typename V>
void BinSearchMap<K, V>::erase(const K &key)
{
    int index = 0;
    if (bin_search(key, index))
      seq.erase(index);
    
    else
    {
        throw std::out_of_range("Out of range in the [] nonconst");
    }
}

// Returns true if the key is in the collection, and false
// otherwise.
template <typename K, typename V>
bool BinSearchMap<K, V>::contains(const K &key) const
{
    for (int i = 0; i < seq.size(); ++i)
    {
        if (seq[i].first == key)
          return true;
    }
    return false;
}

// Returns the keys k in the collection such that k1 <= k <= k2
template <typename K, typename V>
ArraySeq<K> BinSearchMap<K, V>::find_keys(const K &k1, const K &k2) const
{
    ArraySeq<K> new_seq;
    ArraySeq<K> keys = sorted_keys();
    for (int i = 0; i < keys.size(); ++i)
    {
        if (keys[i] >= k1 && keys[i] <= k2)
          new_seq.insert(keys[i], new_seq.size());
    }
    return new_seq;
}

// Returns the keys in the collection in ascending sorted order.
template <typename K, typename V>
ArraySeq<K> BinSearchMap<K, V>::sorted_keys() const
{
    ArraySeq<K> new_seq;
    for (int i = 0; i < seq.size(); ++i)
        new_seq.insert(seq[i].first, new_seq.size());

    return new_seq;
}

// If the key is in the collection, bin_search returns true and
// provides the key's index within the array sequence (via the index
// output parameter). If the key is not in the collection,
// bin_search returns false and provides the last index checked by
// the binary search algorithm.
template <typename K, typename V>
bool BinSearchMap<K, V>::bin_search(const K &key, int &index) const
{
    if (seq.size() == 0)
        return false;

    ArraySeq<K> new_seq = sorted_keys();
    int start = 0;
    int end = new_seq.size() - 1;
    while (start <= end)
    {
        index = (start + end) / 2;                      
        if (start == end)
        {
            if (new_seq[index] == key)
                return true;
            index = start;
            return false;
        }

        if (new_seq[index] == key)
          return true;
        
        if (new_seq[index] < key)
            start = index + 1;

        if (new_seq[index] > key) 
            end = index-1;
    }
    return false;
}