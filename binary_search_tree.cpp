

#include "binary_search_tree.h"
#include "milestone4.h"
#include <algorithm>
#include <queue>

BinarySearchTree::BinarySearchTree() { root = nullptr; }

BinarySearchTree::~BinarySearchTree()
{
    deleteTree(root);
}

/**
 * @brief Adds a node with specifed to key
 *
 * @param key The key to be added to the tree
 */
void BinarySearchTree::addToTree(int key)
{
    TreeNode *node = new TreeNode(key);
    TreeNode *curr = root;

    if (curr != nullptr)
    {
        while (curr != nullptr)
        {
            if (node->key > curr->key)
            { // compare keys
                if (curr->right != nullptr)
                { // check if right is nullptr
                    curr = curr->right;
                }
                else
                {
                    curr->right = node;
                    break;
                }
            }
            else
            {
                if (curr->left != nullptr)
                {
                    curr = curr->left;
                }
                else
                {
                    curr->left = node;
                    break;
                }
            }
        }
    }
    else
    {
        root = node;
    }
}

/**
 * @brief Removes a node with the specified key from the tree.
 *
 * @param key The key of the node to remove.
 * @return True if the node was removed, false if the key wasn't found.
 */
bool BinarySearchTree::removeNode(int key)
{
    TreeNode *curr = root;
    TreeNode *parent = root;

    while (curr != nullptr)
    {
        if (curr->key == key)
        {
            // ============================================================
            // Leaf case
            // ============================================================
            if (curr->left == nullptr && curr->right == nullptr)
            {
                if (curr == root)
                {
                    delete root;
                    return true;
                }
                if (parent->right == curr)
                {

                    parent->right = nullptr;
                    delete curr;
                    return true;
                }
                else if (parent->left == curr)
                {
                    parent->left = nullptr;
                    delete curr;
                    return true;
                }
            }

            // ============================================================
            // 1 Child Case
            // ============================================================

            // --- Left Child ----
            if (curr->right == nullptr)
            {
                if (parent->left == curr)
                {
                    parent->left = curr->left;
                    delete curr;
                    return true;
                }
                if (parent->right == curr)
                {
                    parent->right = curr->left;
                    delete curr;
                    return true;
                }
            }
            // --- Right Child ----
            if (curr->left == nullptr)
            {
                if (parent->left == curr)
                {
                    parent->left = curr->right;
                    delete curr;
                    return true;
                }
                if (parent->right == curr)
                {
                    parent->right = curr->right;
                    delete curr;
                    return true;
                }
            }

            // ============================================================
            // 2 Child Case
            // ============================================================
            TreeNode *node = curr->right;
            parent = node;
            while (node->left != nullptr)
            {
                parent = node;
                node = node->left;
            }

            curr->key = node->key;
            parent->left = nullptr;
            delete node;
            return true;
        }
        else if (curr->key > key)
        {
            parent = curr;
            curr = curr->left;
        }
        else
        {
            parent = curr;
            curr = curr->right;
        }
    }
    return false;
}

/**
 * @brief Gets the height of the tree.
 *
 * The height of the tree is defined as the length of the longest path from
 * the root to a leaf node.
 *
 * @return The height of the tree.
 */
int BinarySearchTree::getHeightOfTree() const
{
    return getHeight(root);
}

/**
 * @brief Gets the number of nodes in the tree.
 *
 * This function uses getNodeCount to recursively find number of nodes in tree
 *
 * @return The number of nodes in the tree.
 */
int BinarySearchTree::getNumberOfTreeNodes() const
{
    return getNodeCount(root);
}

/**
 * @brief Helper function for recursive count for getNumberOfTreeNodes
 *
 * @param node a pointer to node from which to begin recursive count
 */
int BinarySearchTree::getNodeCount(TreeNode *node) const
{
    if (node != nullptr)
    {
        int left = getNodeCount(node->left);
        int right = getNodeCount(node->right);

        return 1 + left + right;
    }
    return 0;
}

/**
 * @brief Checks if the tree contains a node with the specified key.
 *
 * @param key The key to search for in the tree.
 * @return True if the key exists in the tree, false otherwise.
 */
bool BinarySearchTree::contains(int key) const
{
    TreeNode *curr = root;

    while (curr != nullptr)
    {
        if (curr->key == key)
        {
            return true;
        }
        else if (curr->key > key)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }

    return false;
}

/**
 * @brief Gets root node of tree
 *
 * @return a pointer to the root node of tree
 */
TreeNode *BinarySearchTree::getRoot() const { return root; }

/**
 * @brief Checks if the tree is empty.
 *
 * @return True if the tree is empty, false otherwise.
 */
bool BinarySearchTree::isEmpty() const
{
    if (root == nullptr)
    {
        return true;
    }

    return false;
}

/**
 * @brief Clears the entire tree.
 *
 * Deletes all the nodes in the tree, freeing up memory.
 */
void BinarySearchTree::clear()
{
    deleteTree(root);
    root = nullptr;
}

/**
 * @brief Deletes the tree starting from the specified node.
 *
 * Recursively deletes all nodes in the tree.
 *
 * @param node The starting node to begin deleting the tree.
 */
void BinarySearchTree::deleteTree(TreeNode *node)
{
    if (node != nullptr)
    {
        deleteTree(node->right);
        deleteTree(node->left);
        delete node;
    }
}

/**
 * @brief Prints the data of a specific node.
 *
 * This function prints the key, number of nodes in the subtree, and height of the given node.
 *
 * @param node A pointer to the node whose data is to be printed.
 */
void BinarySearchTree::printNodeFromTree(TreeNode *node) const
{
    if (node != nullptr)
    {
        logToFileAndConsole("Node key: " + std::to_string(node->key));
    }
}

/**
 * @brief Performs an in-order traversal of the tree and prints the nodes.
 *
 * In-order traversal visits the left subtree, the node, and then the right subtree.
 */
void BinarySearchTree::printInOrder() const
{
    logToFileAndConsole("Performing In-order traversal");
    printInOrderHelper(root);
}

/**
 * @brief Helper function for recursive In-order traversal.
 *
 * This function is called recursively to perform a In-order traversal starting from the given node.
 *
 * @param node A pointer to the node from which to begin the In-order traversal.
 */
void BinarySearchTree::printInOrderHelper(TreeNode *node) const
{
    if (node != nullptr)
    {
        printInOrderHelper(node->left);
        printNodeFromTree(node);
        printInOrderHelper(node->right);
    }
}

/**
 * @brief Performs an in-order traversal of the tree and prints the nodes.
 *
 * In-order traversal visits the left subtree, the node, and then the right subtree.
 */
void BinarySearchTree::printPreOrder() const
{
    logToFileAndConsole("Performing Pre-order traversal");
    printPreOrderHelper(root);
}

/**
 * @brief Helper function for recursive pre-order traversal.
 *
 * This function is called recursively to perform a pre-order traversal starting from the given node.
 *
 * @param node A pointer to the node from which to begin the pre-order traversal.
 */
void BinarySearchTree::printPreOrderHelper(TreeNode *node) const
{
    if (node != nullptr)
    {
        printNodeFromTree(node);
        printPreOrderHelper(node->left);
        printPreOrderHelper(node->right);
    }
}

/**
 * @brief Performs an in-order traversal of the tree and prints the nodes.
 *
 * In-order traversal visits the left subtree, the node, and then the right subtree.
 */
void BinarySearchTree::printPostOrder() const
{
    logToFileAndConsole("Performing Post-order traversal");
    printPostOrderHelper(root);
}

/**
 * @brief Helper function for recursive Post-order traversal.
 *
 * This function is called recursively to perform a Post-order traversal starting from the given node.
 *
 * @param node A pointer to the node from which to begin the Post-order traversal.
 */
void BinarySearchTree::printPostOrderHelper(TreeNode *node) const
{
    if (node != nullptr)
    {
        printPostOrderHelper(node->left);
        printPostOrderHelper(node->right);
        printNodeFromTree(node);
    }
}

/**
 * @brief Performs a depth-first traversal (same as pre-order traversal) and prints the nodes.
 *
 * Depth-first traversal visits the node first, then the left subtree, and then the right subtree.
 */
void BinarySearchTree::printDepthFirst() const
{
    logToFileAndConsole("Performing Depth First via PreOrder traversal");
    logToFileAndConsole("Performing Pre-order traversal");
    printPreOrderHelper(root);
}

/**
 * @brief Performs a breadth-first traversal of the tree and prints the nodes.
 *
 * Breadth-first traversal visits nodes level by level, from left to right.
 */
void BinarySearchTree::printBreadthFirst() const
{
    logToFileAndConsole("Performing Breadth First traversal");
    if (root != nullptr)
    {
        std::queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            TreeNode *curr = q.front();
            q.pop();
            printNodeFromTree(curr);
            if (curr->left != nullptr)
            {
                q.push(curr->left);
            }

            if (curr->right != nullptr)
            {
                q.push(curr->right);
            }
        }
    }
}

/**
 * @brief Helper function to calculate the height of a node.
 *
 * This function is used by `getHeightOfTree` to calculate the height of the tree.
 *
 * @param node A pointer to the node whose height is to be calculated.
 * @return The height of the given node.
 */
int BinarySearchTree::getHeight(TreeNode *node) const
{
    if (node != nullptr)
    {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        return 1 + std::max(leftHeight, rightHeight);
    }
    return 0;
}
