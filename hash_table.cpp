/**
 *  @author Majeed Balwi
 *
 *  hash_table.cpp: hash table that contains the method definitions of header file hash_node.h
 *
 *  4/26/2026 - initial creation and comments
 *  5/26/2026 - full implementation
 */

#include "hash_table.h"
#include "milestone5.h"
// Default constructor
HashTable::HashTable()
{
    table = nullptr;
    numberOfItems = 0;
    numberOfBuckets = 0;
}

/**
 *
 * getTable
 *
 * Method to return the hash table
 *
 * @param    none
 *
 * @return   pointer to the hash table array
 */
HashNode **HashTable::getTable()
{
    return table;
}

/**
 *
 * getSize
 *
 * Method to return the size of the hash table
 *
 * @param    none
 *
 * @return	size of the hash table array
 */
int HashTable::getSize()
{
    return numberOfBuckets;
}

/**
 *
 * calculateHashCode
 *
 * Method to calculate the hashCode
 *
 * @param    currentKey     hash table size
 *
 * @return   hashcode for currentKey
 */
int HashTable::calculateHashCode(int currentKey)
{
    if (numberOfBuckets != 0)
    {
        return currentKey % numberOfBuckets;
    }

    return -1;
}

/**
 *
 * isEmpty
 *
 * Method to check if HashTable is empty
 *
 * @param    none
 *
 * @return   true if the table has zero entries, false otherwise
 */
bool HashTable::isEmpty()
{
    return table == nullptr;
}

/**
 *
 * getNumberOfItems
 *
 * Method to return number of items in the hash table
 *
 * @param    none
 *
 * @return   number of items in the table
 */
int HashTable::getNumberOfItems()
{
    return numberOfItems;
}

/**
 *
 * add
 *
 * Method to add a node to the hash table
 *
 * @param    curKey    key for this node
 * @param    myNode    new node to add to the table
 *
 * @return   true if success, false otherwise
 */
bool HashTable::add(int curKey, HashNode *myNode)
{
    int hashCode = calculateHashCode(curKey);
    myNode->hashCode = hashCode;
    HashNode *bucket = table[hashCode];

    if (bucket == nullptr)
    {
        table[hashCode] = myNode;
        numberOfItems++;
        return true;
    }
    else
    {
        while (bucket != nullptr)
        {
            if (bucket->next == nullptr)
            {
                bucket->next = myNode;
                myNode->prev = bucket;
                numberOfItems++;
                return true;
            }
            bucket = bucket->next;
        }
    }

    return false;
}

/**
 *
 * remove
 *
 * Method to remove node with curKey
 *
 * @param    key     key of node to remove
 *
 * @return   true if success, false otherwise
 */
bool HashTable::remove(int curKey)
{
    int hashCode = calculateHashCode(curKey);
    HashNode *bucket = table[hashCode];

    while (bucket != nullptr)
    {
        if (bucket->key == curKey)
        {
            if (bucket->next != nullptr)
            {
                bucket->next->prev = bucket->prev;
            }
            if (bucket->prev != nullptr)
            {
                bucket->prev->next = bucket->next;
            }
            else
            {
                table[hashCode] = bucket->next;
            }
            delete bucket;
            numberOfItems--;
            return true;
        }
        bucket = bucket->next;
    }

    return false;
}

/**
 *
 * clear
 *
 * Method to remove all entries from the table
 *
 * @param    none
 *
 * @return   nothing, but will delete all entries from the table
 */
void HashTable::clear()
{
    for (int i = 0; i < numberOfBuckets; i++)
    {
        HashNode *bucket = table[i];
        while (bucket != nullptr)
        {
            HashNode *temp = bucket->next;
            delete bucket;
            bucket = temp;
        }
        table[i] = nullptr;
    }

    numberOfItems = 0;
}

/**
 *
 * getItem
 *
 * Method to retrieve item from the hash table
 *
 * @param    curKey  retrieve node from hash table with curKey value
 *
 * @return   pointer to the HashNode
 */
HashNode *HashTable::getItem(int curKey)
{
    int hashCode = calculateHashCode(curKey);

    HashNode *bucket = table[hashCode];

    while (bucket != nullptr)
    {
        if (bucket->key == curKey)
        {
            return bucket;
        }
        bucket = bucket->next;
    }

    return nullptr;
}

/**
 *
 * contains
 *
 * Method to verify if a key is in the hash table
 *
 * @param    curKey  check key for hash table with curKey value
 *
 * @return   true if found, false otherwise
 */
bool HashTable::contains(int curKey)
{
    int hashCode = calculateHashCode(curKey);

    HashNode *bucket = table[hashCode];

    while (bucket != nullptr)
    {
        if (bucket->key == curKey)
        {
            return true;
        }
        bucket = bucket->next;
    }

    return false;
}

/**
 *
 * printTable
 *
 * Method to print out the contents of table
 *
 * @param    none
 *
 * @return   nothing, but output is sent to console and to file
 */
void HashTable::printTable()
{
    logToFileAndConsole("\nHere are the Hash Table contents (" + std::to_string(numberOfItems) + " entries):");

    for (int i = 0; i < numberOfBuckets; i++)
    {
        HashNode *bucket = table[i];

        if (bucket == nullptr)
        {
            logToFileAndConsole("Bucket " + std::to_string(i) + ": Empty");
        }
        else
        {
            while (bucket != nullptr)
            {
                logToFileAndConsole("Bucket " + std::to_string(i) + ": ");
                bucket->fifoNode->printNode();
                bucket = bucket->next;
            }
        }
    }
    logToFileAndConsole("End of table");
}
