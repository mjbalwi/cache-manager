/**
 * @author - Majeed Balwi
 * @file doubly_linked_list.cpp -  This file contains the method definitions of the header file doubly_linked_list.h
 *   it is the FIFO list of the cache manager
 *
 * 4/25/2026 - Initial creation and comments
 * 4/26/2026 - finished all the method implementations
 *
 */

#include "doubly_linked_list.h"
#include "milestone5.h"

/**
 *  DoublyLinkedList
 *
 *  default constructor for DoublyLinkedList, creates an empty list
 *
 */
DoublyLinkedList::DoublyLinkedList()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

/**
 *  ~DoublyLinkedList
 *
 *
 *  Desconstructor, deletes entire list
 */
DoublyLinkedList::~DoublyLinkedList()
{
    clear();
}

/**
 * getSize
 *
 * retrieves the number of nodes in list
 *
 * @param: nothing
 *
 * @return the number of nodes in the list
 */
int DoublyLinkedList::getSize()
{
    return size;
}

/** isEmpty
 *
 * Checks if list is empty or not
 *
 * @param: nothing
 *
 * @return true if list empty, false otherwise
 */
bool DoublyLinkedList::isEmpty()
{
    return head == nullptr;
}

/**
 * insertAtHead
 *
 * inserts new node at the beginning of list
 *
 * @param key     the int key for new node
 * @param newNode the new dllnode
 *
 * @return nothing: updates dll and size
 */
void DoublyLinkedList::insertAtHead(int key, DllNode *newNode)
{
    if (newNode != nullptr)
    {
        newNode->key = key;
        if (isEmpty())
        {
            head = tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    size++;
}

/**
 * insertAtTail
 *
 * inserts new node at the end of list
 *
 * @param key     the int for new node
 * @param newNode the new dll node
 *
 * @return nothing: updates dll and size
 */
void DoublyLinkedList::insertAtTail(int key, DllNode *newNode)
{
    if (newNode != nullptr)
    {
        newNode->key = key;

        if (isEmpty())
        {
            head = tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    size++;
}

/**
 *
 * remove
 *
 * Method to remove a node with a specific value from the list
 *
 * @param: key
 *
 * @return: nothing; updates doubly linked list
 */
void DoublyLinkedList::remove(int key)
{
    DllNode *cur = head;

    if (!isEmpty())
    {
        while (cur != nullptr)
        {
            if (cur->key == key)
            {
                // middle node case
                if (cur->prev != nullptr)
                {
                    cur->prev->next = cur->next;
                }
                else
                {
                    head = cur->next;
                }
                if (cur->next != nullptr)
                {
                    cur->next->prev = cur->prev;
                }
                else
                {
                    tail = cur->prev;
                }
                delete cur;
                size--;
                break;
            }
            cur = cur->next;
        }
    }
}

/**
 *
 * removeHeaderNode
 *
 * Method to remove the header node (first node)
 *
 * @param: none
 *
 * @return: nothing; updates doubly linked list and size
 */
void DoublyLinkedList::removeHeaderNode()
{
    DllNode *cur = head;
    if (!isEmpty())
    {
        if (head->next == nullptr)
        {
            head = tail = nullptr;
        }
        else
        {
            head = head->next;
            head->prev = nullptr;
        }
        size--;
        delete cur;
    }
}

/**
 *
 * removeTailNode
 *
 * Method to remove the tail node (last node)
 *
 * @param: none
 *
 * @return: nothing; updates doubly linked list
 */
void DoublyLinkedList::removeTailNode()
{
    DllNode *cur = tail;

    if (!isEmpty())
    {
        if (tail->prev == nullptr)
        {
            head = tail = nullptr;
        }
        else
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete cur;
        size--;
    }
}

/**
 *
 * moveNodeToHead
 *
 * Method to move a specific node to the head of the list
 *
 * @param: key
 *
 * @return: nothing; updates doubly linked list
 */
void DoublyLinkedList::moveNodeToHead(int key)
{
    DllNode *cur = head;
    if (!isEmpty())
    {
        while (cur != nullptr)
        {
            if (cur->key == key)
            {
                if (cur->prev != nullptr)
                {
                    cur->prev->next = cur->next;
                }
                else
                {
                    return;
                }
                if (cur->next != nullptr)
                {
                    cur->next->prev = cur->prev;
                }
                else
                {
                    cur->prev->next = nullptr;
                }

                head->prev = cur;
                cur->next = head;
                cur->prev = nullptr;
                head = cur;
                break;
            }

            cur = cur->next;
        }
    }
}

/**
 * @brief Moves the node with the given key to the tail of the list.
 * @param key Key of the node to move.
 */
void DoublyLinkedList::moveNodeToTail(int key)
{
    DllNode *current = head;
    if (!isEmpty())
    {
        while (current != nullptr)
        {
            if (current->key == key)
            {
                if (current->prev != nullptr)
                {
                    current->prev->next = current->next;
                }
                else if (head == tail)
                {
                    return;
                }
                else
                {
                    head = current->next;
                    head->prev = nullptr;
                }
                if (current->next != nullptr)
                {
                    current->next->prev = current->prev;
                }
                else
                {
                    return;
                }
                tail->next = current;
                current->prev = tail;
                current->next = nullptr;
                tail = current;
                return;
            }
            current = current->next;
        }
    }
}

/**
 * @brief Clears the list by deleting all nodes.
 */
void DoublyLinkedList::clear()
{
    DllNode *current = head;
    DllNode *temp = head;

    while (current != nullptr)
    {
        current = current->next;
        delete temp;
        temp = current;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

/**
 * @brief Prints the list from head to tail to the console and output file.
 */
void DoublyLinkedList::printList()
{
    DllNode *current = head;

    logToFileAndConsole("\nHere are the FIFO List contents: ");

    while (current != nullptr)
    {
        logToFileAndConsole("FIFO Node contents-> Key: " + std::to_string(current->key) +
                            ", fullName: " + current->fullName +
                            ", address: " + current->address +
                            ", city: " + current->city +
                            ", state: " + current->state +
                            ", zip: " + current->zip + " ");

        current = current->next;
    }

    logToFileAndConsole("End of FIFO List");
}

/**
 * @brief Prints the list from tail to head to the console and output file.
 */
void DoublyLinkedList::reversePrintList()
{
    DllNode *current = tail;

    logToFileAndConsole("\nHere are the List contents reversed:");

    while (current != nullptr)
    {

        logToFileAndConsole("FIFO Node key: " + current->key);
        current = current->prev;
    }

    logToFileAndConsole("End of FIFO List");
}