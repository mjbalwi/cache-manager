/**
 * @author Majeed Balwi
 * @file cache_manager.cpp
 * @brief CacheManager implementation used for managing a cache with a hash table and FIFO list.
 *
 * @date 2026-03-17 - initial creation and comments
 */

#include "cache_manager.h"
#include "milestone3.h"

/**
 * @brief Returns a pointer to the internal hash table.
 * @return Pointer to the HashTable object.
 */
HashTable *CacheManager::getTable()
{
    return hashTable;
}

/**
 * @brief Returns a pointer to the internal FIFO list.
 * @return Pointer to the DoublyLinkedList object.
 */
DoublyLinkedList *CacheManager::getList()
{
    return doublyLinkedList;
}

/**
 * @brief Gets the current number of items in the cache.
 * @return Number of items in the cache.
 */
int CacheManager::getSize()
{
    return hashTable->getNumberOfItems();
}

/**
 * @brief Checks whether the cache is empty.
 * @return True if the cache has no entries, false otherwise.
 */
bool CacheManager::isEmpty()
{
    return hashTable->isEmpty();
}

/**
 * @brief Adds a node to the cache, evicting the least recently used if >= Max Cache Size
 * @param curKey Key associated with the node.
 * @param myNode Pointer to the node to be added.
 * @return True if the operation succeeds, false otherwise.
 */
bool CacheManager::add(int curKey, DllNode *myNode)
{
    // add to FIFO list

    if (getSize() >= getMaxCacheSize())
    {
        // remove least recently used in hashTable & Dll
        if (doublyLinkedList->tail != nullptr)
        {
            hashTable->remove(doublyLinkedList->tail->key);
            doublyLinkedList->removeTailNode();
        }
    }

    // add node
    doublyLinkedList->insertAtHead(curKey, myNode);
    HashNode *myHashNode = new HashNode(curKey, myNode); // note to self: for some reason with *, new is requried, but w/o * new doesnt work.
    myHashNode->next = nullptr;
    myHashNode->prev = nullptr;
    hashTable->add(curKey, myHashNode);

    return true;
}

/**
 * @brief Removes a node from the cache based on the key.
 * @param curKey Key of the node to be removed.
 * @return True if the operation succeeds, false otherwise.
 */
bool CacheManager::remove(int curKey)
{
    if (!hashTable->contains(curKey))
    {
        return false;
    }

    hashTable->remove(curKey);
    doublyLinkedList->remove(curKey);

    return true;
}

/**
 * @brief Clears all entries from the cache.
 */
void CacheManager::clear()
{
    if (hashTable != nullptr)
    {
        hashTable->clear();
    }
    if (doublyLinkedList != nullptr)
    {
        doublyLinkedList->clear();
    }
    
}

/**
 * @brief Retrieves a node from the cache.
 * @param curKey Key of the node to retrieve.
 * @return Pointer to the DllNode if found, nullptr otherwise.
 */
DllNode *CacheManager::getItem(int curKey)
{
    HashNode *node = hashTable->getItem(curKey);

    if (node == nullptr)
    {
        return nullptr;
    }

    return node->getFifoNode();
}

/**
 * @brief Gets the maximum cache size.
 * @return Maximum number of entries the cache can hold.
 */
int CacheManager::getMaxCacheSize()
{
    return maxCacheSize;
}

/**
 * @brief Checks if a specific key exists in the cache.
 * @param curKey Key to check.
 * @return True if the key exists in the cache, false otherwise.
 */
bool CacheManager::contains(int curKey)
{
    return hashTable->contains(curKey);
}

/**
 * @brief Prints the current contents of the cache to console and output file.
 */
void CacheManager::printCache()
{
    logToFileAndConsole("\nPrinting out the cache contents");
    doublyLinkedList->printList();
    hashTable->printTable();
}