//---------------------------------------------------------------------------
// NAME: Mason Manca
// DATE: Fall 2021
// DESC:
//---------------------------------------------------------------------------

#ifndef LINKEDMAP_H
#define LINKEDMAP_H

#include "map.h"
#include "linkedseq.h"

template <typename K, typename V>
class LinkedMap : public Map<K, V>
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

    // Returns all the keys in the collection
    ArraySeq<K> all_keys() const;

    // Returns the keys in the collection in ascending sorted order.
    ArraySeq<K> sorted_keys() const;

private:
    // implemented as a linked list of (key-value) pairs
    LinkedSeq<std::pair<K, V>> seq;
};

// TODO: Implement the LinkedMap functions below. Note that you do not
//       need to implement a default constructor, destructor, copy
//       constructor, copy assignment operator, move constructor, and
//       move assignment operator for this version of Map. Instead,
//       the default C++ implementations are sufficient.

#endif

// Returns the number of key-value pairs in the map

template <typename K, typename V>
int LinkedMap<K, V>::size() const
{
    return seq.size();
}

// Tests if the map is empty
template <typename K, typename V>
bool LinkedMap<K, V>::empty() const
{
    return seq.empty();
}

// Allows values associated with a key to be updated. Throws
// out_of_range if the given key is not in the collection.
template <typename K, typename V>
V &LinkedMap<K, V>::operator[](const K &key)
{
    if (contains(key))
    {
        for (int i = 0; i < seq.size(); ++i)
        {
            if (seq[i].first == key)
                return seq[i].second;
        }
    }
    else
    {
        throw std::out_of_range("Out of range in the [] nonconst");
    }
}

// Returns the value for a given key. Throws out_of_range if the
// given key is not in the collection.
template <typename K, typename V>
const V &LinkedMap<K, V>::operator[](const K &key) const
{
    if (contains(key))
    {
        for (int i = 0; i < seq.size(); ++i)
        {
            if (seq[i].first == key)
                return seq[i].second;
        }
    }
    else
    {
        throw std::out_of_range("Out of range in the [] nonconst");
    }
}

// Extends the collection by adding the given key-value
// pair. Assumes the key being added is not present in the
// collection. Insert does not check if the key is present.
template <typename K, typename V>
void LinkedMap<K, V>::insert(const K &key, const V &value)
{
    seq.insert({key, value}, seq.size());
}

// Shrinks the collection by removing the key-value pair with the
// given key. Does not modify the collection if the collection does
// not contain the key. Throws out_of_range if the given key is not
// in the collection.
template <typename K, typename V>
void LinkedMap<K, V>::erase(const K &key)
{
    if (contains(key))
    {
        int index = -1;
        for (int i = 0; i < seq.size(); ++i)
        {
            if (seq[i].first == key)
            {
                index = i;
                break;
            }
        }
        seq.erase(index);
    }
    else
    {
        throw std::out_of_range("Out of range in the [] nonconst");
    }
}

// Returns true if the key is in the collection, and false
// otherwise.
template <typename K, typename V>
bool LinkedMap<K, V>::contains(const K &key) const
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
ArraySeq<K> LinkedMap<K, V>::find_keys(const K &k1, const K &k2) const
{
    ArraySeq<K> new_seq;
    ArraySeq<K> keys = all_keys();
    for (int i = 0; i < keys.size(); ++i)
    {
        if (keys[i] >= k1 && keys[i] <= k2)
            new_seq.insert(keys[i], new_seq.size());
    }
    return new_seq;
}

// Returns all the keys in the collection
template <typename K, typename V>
ArraySeq<K> LinkedMap<K, V>::all_keys() const
{
    ArraySeq<K> new_seq;
    for (int i = 0; i < seq.size(); ++i)
        new_seq.insert(seq[i].first, new_seq.size());

    return new_seq;
}

// Returns the keys in the collection in ascending sorted order.
template <typename K, typename V>
ArraySeq<K> LinkedMap<K, V>::sorted_keys() const
{
    ArraySeq<K> new_seq;

    for (int i = 0; i < seq.size(); ++i)
        new_seq.insert(seq[i].first, new_seq.size());
        
    new_seq.merge_sort();
    return new_seq;
}