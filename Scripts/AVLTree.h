#ifndef HW1_AVLTREE_H
#define HW1_AVLTREE_H
#include <new>
#include "Exception.h"

template <class T>
class AVLTree
{
public:
    /*
     * Constructor of AVLTree class
     * @param - none
     * @return - A new instance of AVLTree
     */
    AVLTree();

    /*
     * Copy Constructor of AVLTree class
     * @param - The AVLTree to be copied
     * @return - A new instance of AVLTree
     */
    AVLTree(const AVLTree &other);

    /*
     * Destructor of AVLTree class
     * @param - none
     * @return - void
     */
    ~AVLTree();

    /*
     * Assignment Operator of AVLTree class
     * @param - The other AVLTree
     * @return - An AVLTree with the same data
     */
    AVLTree &operator=(const AVLTree &other);

    bool insert(T element, const int firstCond, const int secondCond);

    bool remove(const int firstCond, const int secondCond);

    T &findMax() const;
    T &findSecondMax() const;
    T &findThirdMax();
    T &findMin() const;
    T &findSecondMin() const;
    T &findThirdMin();

    T &find(const int firstCond, const int secondCond);

    void getDataInOrder(T *array);

    void eraseData();

    bool updateFirstCondition(const int firstCond, const int secondCond, const int condition);
    void mergeTeams(AVLTree<T> *firstTrees[6], AVLTree<T> *otherTrees[6], int *lengthsFirst, int *lengthsOther, const int id);

private:
    /*
     * Class Node
     * This class is used to represent nodes in the tree.
     */
    class Node
    {
    public:
        /*
         * Constructor of Node class
         * @param - none
         * @return - A new instance of Node
         */
        Node();

        /*
         * Destructor of Node class
         * @param - none
         * @return - void
         */
        ~Node() = default;

        /*
         * Copy Constructor and Assignment Operator of Node class
         */
        Node(const Node &other) = default;
        Node &operator=(const Node &other) = default;

        /*
         * Deletes each node in a subtree
         * @param - a pointer to the root of the subtree
         * @return - void
         */
        void deleteNodeTree(Node *root);

        /*
         * The internal fields of Node:
         *   The data of the node of type T
         *   The first condition for ordering the tree
         *   The second condition for ordering the tree
         *   The height of the subtree of the node
         *   A pointer to the node's right child
         *   A pointer to the node's left child
         *   A pointer to the node's parent
         */
        T m_data;
        int m_firstCond;
        int m_secondCond;
        int m_height;
        Node *m_right;
        Node *m_left;
        Node *m_father;
    };

    /*
     * Constants for the AVL Tree:
     * START:
     * EMPTY_TREE: The
     * CRITICAL_LEFT:
     * CRITICAL_RIGHT:
     * NEED_LR: The balance factor for needing a LR rotation
     * NEED_RL: The balance factor for needing an RL rotation
     */
    static const int START = 0;
    static const int EMPTY_TREE = -1;
    static const int CRITICAL_LEFT = 2;
    static const int CRITICAL_RIGHT = -2;
    static const int NEED_LR = -1;
    static const int NEED_RL = 1;

    /*
     * Helper function for copy constructor of AVLTree:
     * Copy the entire tree
     * @param - The root of the tree to be copied
     * @return - void
     */
    void copyTree(const Node *root);

    /*
     * Inserts a new node into the tree
     * @param - The address of the new node
     * @param - A node to be used as a runner
     * @return - bool - whether or not succeeded
     */
    bool insertIntoTree(Node &newNode, Node &runnerNode);

    /*
     * LR, LL, RR, and RL rotations on the AVL tree
     * @param - The root of the tree
     * @return - void
     */
    void LRRoll(Node *root);
    void LLRoll(Node *root);
    void RRRoll(Node *root);
    void RLRoll(Node *root);

    /*
     * Removes a node from the AVL tree
     * @param - The root of the tree
     * @param - The first condition the tree is sorted by
     * @param - The second condition the tree is sorted by
     * @return - bool - whether or not succeeded
     */
    bool remover(Node *root, const int firstCond, const int secondCond);

    /*
     * Finds the node with the maximum height in the tree
     * @param - The root of the tree
     * @return - int, the height of the node with the highest height
     */
    int max(const Node *root) const;

    /*
     * Finds a node in the tree
     * @param - The root of the tree
     * @param - The first condition the tree is sorted by
     * @param - The second condition the tree is sorted by
     * @return - T, a reference to the data of the desired node
     */
    T &finder(Node *root, const int firstCond, const int secondCond);

    /*
     * Swaps between two nodes
     * @param - The first node to be swapped
     * @param - The second node to be swapped
     * @return - void
     */
    void swap(Node *first, Node *second);

    /*
     * Determines which rotation the tree needs and calls the correct function
     * @param - The root of the tree
     * @return - void
     */
    void doNeededRoll(Node &root);
    /*
     * Merges thre sorted arrays of nodes that are in the given array
     * @param - the three arrays
     * @param - The sizes of the three arrays
     * @return - The size of the merged array
     */
    int mergeSort(Node ***first, int *sizes);
    /*
     * Updates the field m_root
     * @param - none
     * @return - void
     */
    void fixRoot();

    /*
     * Performs an Inorder Walk on the tree
     * @param - The current node
     * @param - Array to put nodes into
     * @param - Current index in the array
     * @return - void
     */
    void inOrderWalk(Node *current, Node **array, int *index) const;

    /*
     * Merges two sorted arrays of nodes
     * @param - The first array of nodes
     * @param - The second array of nodes
     * @param - The array to hold the merged arrays
     * @param - The size of the first array
     * @param - The size of the second array
     * @return - The size of the merged array
     */
    int mergeSort(Node **first, Node **other, Node **merged, int sizeFirst, int sizeOther);

    /*
     * Inserts the sorted and merged array into an AVL tree
     * @param - The merged array of nodes
     * @param -
     * @param -
     * @return - A pointer to the root of the merged tree
     */
    Node *insertSorted(Node **sorted, int left, int right);

    /*
     * Returns the data held by each node in the tree
     * @param - The current node
     * @param - The array to store the data in each node
     * @param - The current index in the array
     * @return - void
     */
    void dataInOrder(Node *current, T *array, int *index);

    /*
     * Erases the tree
     * @param - The current node
     * @return - void
     */
    void erase(Node *currentNode);

    /* The internal field of AVLTree:
     * The root of the tree
     */
    Node *m_root;
};

//------------------------------------------------- Node Class ---------------------------------------------------------

template <class T>
AVLTree<T>::Node::Node() : m_height(1)
{
    m_father = nullptr;
    m_left = nullptr;
    m_right = nullptr;
}

template <class T>
void AVLTree<T>::Node::deleteNodeTree(Node *root)
{
    if (root != nullptr)
    {
        deleteNodeTree(root->m_left);
        deleteNodeTree(root->m_right);
        if (root->m_father != nullptr)
        {
            if (root->m_father->m_left == root)
            {
                root->m_father->m_left = nullptr;
            }
            else if (root->m_father->m_right == root)
            {
                root->m_father->m_right = nullptr;
            }
            root->m_father = nullptr;
        }
        delete root;
    }
}

//---------------------- AVLTree Class Start ---------------------------------------------------------------------------

template <class T>
AVLTree<T>::AVLTree()
{
    try
    {
        this->m_root = new Node();
    }
    catch (const std::bad_alloc &e)
    {
        delete this->m_root;
        throw(std::bad_alloc());
    }
    m_root->m_height = EMPTY_TREE;
}

template <class T>
AVLTree<T>::AVLTree(const AVLTree<T> &other)
{
    try
    {
        this->m_root = new Node;
    }
    catch (const std::bad_alloc &e)
    {
        delete this->m_root;
        throw(std::bad_alloc());
    }
    m_root->m_height = EMPTY_TREE;
    try
    {
        Node *runner = other.m_root;
        copyTree(runner);
    }
    catch (const std::bad_alloc &e)
    {
        this->m_root->deleteNodeTree(m_root);
        throw(e);
    }
}

template <class T>
void AVLTree<T>::copyTree(const Node *root)
{
    if (root->m_left != nullptr)
    {
        copyTree(root->m_left);
    }
    if (root->m_right != nullptr)
    {
        copyTree(root->m_right);
    }
    try
    {
        insert(root->m_data, root->m_firstCond, root->m_secondCond);
    }
    catch (const std::bad_alloc &e)
    {
        throw(e);
    }
}

template <class T>
AVLTree<T>::~AVLTree()
{
    if (this->m_root != nullptr)
    {
        this->m_root->deleteNodeTree(m_root);
    }
}
template <class T>
void AVLTree<T>::eraseData()
{
    Node *runner = this->m_root;
    erase(runner);
}
template <class T>
void AVLTree<T>::erase(Node *currentNode)
{
    if (currentNode != nullptr)
    {
        erase(currentNode->m_left);
        erase(currentNode->m_right);
        delete currentNode->m_data;
    }
}

template <class T>
typename AVLTree<T>::AVLTree &AVLTree<T>::operator=(const AVLTree<T> &other)
{
    if (this == &other)
    {
        return *this;
    }
    AVLTree tempAVLTree(other);
    Node *temp = this->m_root;
    this->m_root = tempAVLTree.m_root;
    tempAVLTree.m_root = temp;
    return *this;
}

template <class T>
bool AVLTree<T>::insert(T element, const int firstCond, const int secondCond)
{
    if (this->m_root->m_height == EMPTY_TREE)
    {
        m_root->m_data = element;
        m_root->m_firstCond = firstCond;
        m_root->m_secondCond = secondCond;
        m_root->m_height = 1;
        return true;
    }
    Node *temp = new Node;
    try
    {
        if (temp == nullptr)
        {
            throw(std::bad_alloc());
        }
    }
    catch (const std::bad_alloc &e)
    {
        delete temp;
        throw(std::bad_alloc());
    }
    temp->m_data = element;
    temp->m_firstCond = firstCond;
    temp->m_secondCond = secondCond;
    Node *runner = this->m_root;
    bool worked = insertIntoTree(*temp, *runner);
    if (!worked)
    {
        delete (temp);
    }
    fixRoot();
    return worked;
}

template <class T>
void AVLTree<T>::swap(AVLTree<T>::Node *first, AVLTree<T>::Node *second)
{
    Node *tempFather = first->m_father;
    second->m_left = first->m_left;
    if (second->m_left != nullptr)
    {
        second->m_left->m_father = second;
    }
    first->m_left = nullptr;
    Node *tempRight = first->m_right;
    first->m_right = second->m_right;
    if (first->m_right != nullptr)
    {
        first->m_right->m_father = first;
    }
    if (second == tempRight)
    {
        second->m_right = first;
    }
    else
    {
        second->m_right = tempRight;
    }
    if (second->m_right != nullptr)
    {
        second->m_right->m_father = second;
    }

    if (second->m_father->m_firstCond == first->m_firstCond && second->m_father->m_secondCond == first->m_secondCond)
    {
        first->m_father = second;
    }
    else
    {
        first->m_father = second->m_father;
    }
    if (first->m_father != nullptr)
    {
        if (first->m_father->m_left != nullptr && first->m_father->m_left->m_firstCond == second->m_firstCond && first->m_father->m_left->m_secondCond == second->m_secondCond)
        {
            first->m_father->m_left = first;
        }
        else
        {
            first->m_father->m_right = first;
        }
    }
    second->m_father = tempFather;
    if (second->m_father != nullptr)
    {
        if (second->m_father->m_left != nullptr && second->m_father->m_left->m_firstCond == first->m_firstCond && second->m_father->m_left->m_secondCond == first->m_secondCond)
        {
            second->m_father->m_left = second;
        }
        else
        {
            second->m_father->m_right = second;
        }
    }
    int temp = first->m_height;
    first->m_height = second->m_height;
    second->m_height = temp;
}

template <class T>
bool AVLTree<T>::insertIntoTree(AVLTree<T>::Node &newNode, AVLTree<T>::Node &runnerNode)
{
    if (newNode.m_firstCond == runnerNode.m_firstCond && newNode.m_secondCond == runnerNode.m_secondCond)
    {
        return false;
    }
    else if (newNode.m_firstCond < runnerNode.m_firstCond)
    {
        if (runnerNode.m_left == nullptr)
        {
            runnerNode.m_left = &newNode;
            newNode.m_father = &runnerNode;
            if (runnerNode.m_right == nullptr)
            {
                runnerNode.m_height++;
            }
            return true;
        }
        bool worked = insertIntoTree(newNode, *(runnerNode.m_left));
        if (worked)
        {
            if (runnerNode.m_height < runnerNode.m_left->m_height + 1)
            {
                runnerNode.m_height = runnerNode.m_left->m_height + 1;
            }
            doNeededRoll(runnerNode);
        }
        return worked;
    }
    else if (newNode.m_firstCond > runnerNode.m_firstCond)
    {
        if (runnerNode.m_right == nullptr)
        {
            runnerNode.m_right = &newNode;
            newNode.m_father = &runnerNode;
            if (runnerNode.m_left == nullptr)
            {
                runnerNode.m_height++;
            }
            return true;
        }
        bool worked = insertIntoTree(newNode, *(runnerNode.m_right));
        if (worked)
        {
            if (runnerNode.m_height < runnerNode.m_right->m_height + 1)
            {
                runnerNode.m_height = runnerNode.m_right->m_height + 1;
            }
            doNeededRoll(runnerNode);
        }
        return worked;
    }
    else
    {
        if (newNode.m_secondCond < runnerNode.m_secondCond)
        {
            if (runnerNode.m_left == nullptr)
            {
                runnerNode.m_left = &newNode;
                newNode.m_father = &runnerNode;
                if (runnerNode.m_right == nullptr)
                {
                    runnerNode.m_height++;
                }
                return true;
            }
            bool worked = insertIntoTree(newNode, *(runnerNode.m_left));
            if (worked)
            {
                if (runnerNode.m_height < runnerNode.m_left->m_height + 1)
                {
                    runnerNode.m_height = runnerNode.m_left->m_height + 1;
                }
                doNeededRoll(runnerNode);
            }
            return worked;
        }
        else
        {
            if (runnerNode.m_right == nullptr)
            {
                runnerNode.m_right = &newNode;
                newNode.m_father = &runnerNode;
                if (runnerNode.m_left == nullptr)
                {
                    runnerNode.m_height++;
                }
                return true;
            }
            bool worked = insertIntoTree(newNode, *(runnerNode.m_right));
            if (worked)
            {
                if (runnerNode.m_height < runnerNode.m_right->m_height + 1)
                {
                    runnerNode.m_height = runnerNode.m_right->m_height + 1;
                }
                doNeededRoll(runnerNode);
            }
            return worked;
        }
    }
}
template <class T>
void AVLTree<T>::fixRoot()
{
    if (this->m_root->m_height == EMPTY_TREE)
    {
        return;
    }
    while (this->m_root->m_father != nullptr)
    {
        this->m_root = this->m_root->m_father;
    }
}

template <class T>
void AVLTree<T>::doNeededRoll(AVLTree<T>::Node &root)
{
    int leftHeight = 0, rightHeight = 0, leftOffspring = 0, rightOffspring = 0;
    if (root.m_left != nullptr)
    {
        leftHeight = root.m_left->m_height;
    }
    if (root.m_right != nullptr)
    {
        rightHeight = root.m_right->m_height;
    }
    if (leftHeight - rightHeight == CRITICAL_LEFT)
    {
        if (root.m_left->m_left != nullptr)
        {
            leftOffspring = root.m_left->m_left->m_height;
        }
        if (root.m_left->m_right != nullptr)
        {
            rightOffspring = root.m_left->m_right->m_height;
        }
        if (leftOffspring - rightOffspring == NEED_LR)
        {
            LRRoll(&root);
        }
        else
        {
            LLRoll(&root);
        }
    }
    if (leftHeight - rightHeight == CRITICAL_RIGHT)
    {
        if (root.m_right->m_left != nullptr)
        {
            leftOffspring = root.m_right->m_left->m_height;
        }
        if (root.m_right->m_right != nullptr)
        {
            rightOffspring = root.m_right->m_right->m_height;
        }
        if (leftOffspring - rightOffspring == NEED_RL)
        {
            RLRoll(&root);
        }
        else
        {
            RRRoll(&root);
        }
    }
}

template <class T>
void AVLTree<T>::LLRoll(AVLTree<T>::Node *root)
{
    Node *b = root->m_left;
    b->m_father = root->m_father;
    if (b->m_father != nullptr)
    {
        if (b->m_father->m_left != nullptr && b->m_father->m_left->m_firstCond == root->m_firstCond && b->m_father->m_left->m_secondCond == root->m_secondCond)
        {
            b->m_father->m_left = b;
        }
        else
        {
            b->m_father->m_right = b;
        }
    }
    root->m_left = b->m_right;
    if (b->m_right != nullptr)
    {
        b->m_right->m_father = root;
    }
    b->m_right = root;
    root->m_father = b;
    root->m_height = max(root) + 1;
    b->m_height = max(b) + 1;
}

template <class T>
void AVLTree<T>::LRRoll(AVLTree<T>::Node *root)
{
    Node *b = root->m_left;
    Node *c = b->m_right;
    c->m_father = root->m_father;
    if (c->m_father != nullptr)
    {
        if (c->m_father->m_left != nullptr && c->m_father->m_left->m_firstCond == root->m_firstCond && c->m_father->m_left->m_secondCond == root->m_secondCond)
        {
            c->m_father->m_left = c;
        }
        else
        {
            c->m_father->m_right = c;
        }
    }
    root->m_left = c->m_right;
    if (c->m_right != nullptr)
    {
        c->m_right->m_father = root;
    }
    b->m_right = c->m_left;
    if (c->m_left != nullptr)
    {
        c->m_left->m_father = b;
    }
    c->m_left = b;
    b->m_father = c;
    c->m_right = root;
    root->m_father = c;
    b->m_height = max(b) + 1;
    root->m_height = max(root) + 1;
    c->m_height = max(c) + 1;
}

template <class T>
void AVLTree<T>::RRRoll(AVLTree<T>::Node *root)
{
    Node *b = root->m_right;
    b->m_father = root->m_father;
    if (b->m_father != nullptr)
    {
        if (b->m_father->m_left != nullptr && b->m_father->m_left->m_firstCond == root->m_firstCond && b->m_father->m_left->m_secondCond == root->m_secondCond)
        {
            b->m_father->m_left = b;
        }
        else
        {
            b->m_father->m_right = b;
        }
    }
    root->m_father = b;
    root->m_right = b->m_left;
    if (b->m_left != nullptr)
    {
        b->m_left->m_father = root;
    }
    b->m_left = root;
    root->m_height = max(root) + 1;
    b->m_height = max(b) + 1;
}

template <class T>
void AVLTree<T>::RLRoll(AVLTree<T>::Node *root)
{
    Node *b = root->m_right;
    Node *c = b->m_left;
    Node *aFather = root->m_father;
    root->m_right = c->m_left;
    if (c->m_left != nullptr)
    {
        c->m_left->m_father = root;
    }
    b->m_left = c->m_right;
    if (c->m_right != nullptr)
    {
        c->m_right->m_father = b;
    }
    c->m_father = aFather;
    if (aFather != nullptr)
    {
        if (aFather->m_left != nullptr && aFather->m_left->m_firstCond == root->m_firstCond && aFather->m_left->m_secondCond == root->m_secondCond)
        {
            c->m_father->m_left = c;
        }
        else
        {
            c->m_father->m_right = c;
        }
    }
    c->m_left = root;
    root->m_father = c;
    c->m_right = b;
    b->m_father = c;
    b->m_height = max(b) + 1;
    root->m_height = max(root) + 1;
    c->m_height = max(c) + 1;
}

template <class T>
int AVLTree<T>::max(const AVLTree<T>::Node *root) const
{
    int leftHeight = 0, rightHeight = 0;
    if (root->m_left != nullptr)
    {
        leftHeight = root->m_left->m_height;
    }
    if (root->m_right != nullptr)
    {
        rightHeight = root->m_right->m_height;
    }
    if (rightHeight >= leftHeight)
    {
        return rightHeight;
    }
    return leftHeight;
}

template <class T>
bool AVLTree<T>::remove(const int firstCond, const int secondCond)
{
    if (this->m_root->m_height == EMPTY_TREE)
    {
        return false;
    }
    Node *runner = this->m_root;
    bool worked = remover(runner, firstCond, secondCond);
    fixRoot();
    return worked;
}

template <class T>
bool AVLTree<T>::remover(AVLTree<T>::Node *root, const int firstCond, const int secondCond)
{
    if (root == nullptr)
    {
        return false;
    }
    bool worked = false;
    if (root->m_firstCond == firstCond && root->m_secondCond == secondCond)
    {
        if (root->m_left != nullptr && root->m_right != nullptr)
        {
            Node *runner = root->m_right;
            while (runner->m_left != nullptr)
            {
                runner = runner->m_left;
            }
            swap(root, runner);
            this->m_root = runner;
        }
        if (root->m_left == nullptr && root->m_right == nullptr)
        {
            if (root->m_father != nullptr)
            {
                if (root->m_father->m_left != nullptr)
                {
                    if (root->m_father->m_left->m_firstCond == firstCond && root->m_father->m_left->m_secondCond == secondCond)
                    {
                        root->m_father->m_left = nullptr;
                    }
                    else
                    {
                        root->m_father->m_right = nullptr;
                    }
                }
                else
                {
                    root->m_father->m_right = nullptr;
                }
            }
            else
            {
                this->m_root->m_height = EMPTY_TREE;
                return true;
            }
        }
        else if (root->m_left != nullptr && root->m_right == nullptr)
        {
            if (root->m_father != nullptr)
            {
                if (root->m_father->m_left != nullptr)
                {
                    if (root->m_father->m_left->m_firstCond == firstCond && root->m_father->m_left->m_secondCond == secondCond)
                    {
                        root->m_father->m_left = root->m_left;
                    }
                    else
                    {
                        root->m_father->m_right = root->m_left;
                    }
                    if (root->m_left != nullptr)
                    {
                        root->m_left->m_father = root->m_father;
                    }
                }
                else
                {
                    root->m_father->m_right = root->m_left;
                    if (root->m_right != nullptr)
                    {
                        root->m_right->m_father = root->m_father;
                    }
                }
            }
            else
            {
                this->m_root = root->m_left;
                root->m_left->m_father = nullptr;
            }
        }
        else
        {
            if (root->m_father != nullptr)
            {
                if (root->m_father->m_right != nullptr)
                {
                    if (root->m_father->m_right->m_firstCond == firstCond && root->m_father->m_right->m_secondCond == secondCond)
                    {
                        root->m_father->m_right = root->m_right;
                    }
                    else
                    {
                        root->m_father->m_left = root->m_right;
                    }
                    if (root->m_right != nullptr)
                    {
                        root->m_right->m_father = root->m_father;
                    }
                }
                else
                {
                    root->m_father->m_left = root->m_right;
                    if (root->m_right != nullptr)
                    {
                        root->m_right->m_father = root->m_father;
                    }
                }
            }
            else
            {
                this->m_root = root->m_right;
                root->m_right->m_father = nullptr;
            }
        }
        delete (root);
        return true;
    }
    else if (firstCond < root->m_firstCond)
    {
        worked = remover(root->m_left, firstCond, secondCond);
    }
    else if (firstCond > root->m_firstCond)
    {
        worked = remover(root->m_right, firstCond, secondCond);
    }
    else
    {
        if (secondCond < root->m_secondCond)
        {
            worked = remover(root->m_left, firstCond, secondCond);
        }
        else
        {
            worked = remover(root->m_right, firstCond, secondCond);
        }
    }
    if (worked)
    {
        root->m_height = max(root) + 1;
        doNeededRoll(*root);
    }
    return worked;
}

template <class T>
T &AVLTree<T>::findMax() const
{
    if (this->m_root->m_height == EMPTY_TREE)
    {
        throw EmptyTree();
    }
    Node *nodeRunner = this->m_root;
    while (nodeRunner->m_right != nullptr)
    {
        nodeRunner = nodeRunner->m_right;
    }
    return nodeRunner->m_data;
}

template <class T>
T &AVLTree<T>::findMin() const
{
    if (this->m_root->m_height == EMPTY_TREE)
    {
        throw EmptyTree();
    }
    Node *nodeRunner = this->m_root;
    while (nodeRunner->m_left != nullptr)
    {
        nodeRunner = nodeRunner->m_left;
    }
    return nodeRunner->m_data;
}

template <class T>
T &AVLTree<T>::find(const int firstCond, const int secondCond)
{
    if (this->m_root->m_height == EMPTY_TREE)
    {
        throw EmptyTree();
    }
    Node *runner = this->m_root;
    return finder(runner, firstCond, secondCond);
}

template <class T>
T &AVLTree<T>::finder(AVLTree<T>::Node *root, const int firstCond, const int secondCond)
{
    if (root == nullptr)
    {
        throw(NodeNotFound());
    }
    if (root->m_firstCond == firstCond && root->m_secondCond == secondCond)
    {
        return root->m_data;
    }
    if (firstCond < root->m_firstCond)
    {
        return finder(root->m_left, firstCond, secondCond);
    }
    else if (firstCond > root->m_firstCond)
    {
        return finder(root->m_right, firstCond, secondCond);
    }
    else
    {
        if (secondCond < root->m_secondCond)
        {
            return finder(root->m_left, firstCond, secondCond);
        }
        else
        {
            return finder(root->m_right, firstCond, secondCond);
        }
    }
}
template <class T>
void AVLTree<T>::mergeTeams(AVLTree<T> *firstTrees[6], AVLTree<T> *otherTrees[6], int *lengthsFirst, int *lengthsOther, const int id)
{
    int sizeFirst = 0, sizeOther = 0;
    for (int i = 0; i < 3; i++)
    {
        sizeFirst += lengthsFirst[i];
        sizeOther += lengthsOther[i];
    }
    if (sizeFirst == 0)
    {
        for (int i = 0; i < 6; i++)
        {
            AVLTree<T> *temp = firstTrees[i];
            firstTrees[i] = otherTrees[i];
            otherTrees[i] = temp;
        }
        for (int i = 0; i < 3; i++)
        {
            lengthsFirst[i] = lengthsOther[i];
            lengthsOther[i] = 0;
        }
        return;
    }
    if (sizeOther == 0)
    {
        return;
    }
    AVLTree<T>::Node **firstId = (Node **)malloc(sizeof(Node *) * sizeFirst);
    AVLTree<T>::Node **secondId = (Node **)malloc(sizeOther * sizeof(Node *));
    AVLTree<T>::Node **mergedId = (Node **)malloc((sizeOther + sizeFirst) * sizeof(Node *));
    AVLTree<T>::Node **firstStrength = (Node **)malloc(sizeof(Node *) * sizeFirst);
    AVLTree<T>::Node **secondStrength = (Node **)malloc(sizeOther * sizeof(Node *));
    AVLTree<T>::Node **mergedStrength = (Node **)malloc((sizeOther + sizeFirst) * sizeof(Node *));
    if (firstId == nullptr || secondId == nullptr || mergedId == nullptr || firstStrength == nullptr || secondStrength == nullptr || mergedStrength == nullptr)
    {
        free(firstId);
        free(secondId);
        free(mergedId);
        free(firstStrength);
        free(secondStrength);
        free(mergedStrength);
        throw(BadAllocation());
    }
    int indexFirstId = 0, indexOtherId = 0, indexFirstStrength = 0, indexOtherStrength = 0;
    for (int i = 0; i < 3; i++)
    {
        if (lengthsFirst[i] != 0)
        {
            AVLTree<T>::Node *runner = firstTrees[i + 3]->m_root;
            inOrderWalk(runner, firstStrength, &indexFirstStrength);
            runner = firstTrees[i]->m_root;
            inOrderWalk(runner, firstId, &indexFirstId);
        }
        if (lengthsOther[i] != 0)
        {
            AVLTree<T>::Node *runner = otherTrees[i + 3]->m_root;
            inOrderWalk(runner, secondStrength, &indexOtherStrength);
            runner = otherTrees[i]->m_root;
            inOrderWalk(runner, secondId, &indexOtherId);
        }
    }
    try
    {
        mergeSort(&firstStrength, lengthsFirst);
        mergeSort(&secondStrength, lengthsOther);
    }
    catch (const std::exception &e)
    {
        free(firstId);
        free(secondId);
        free(mergedId);
        free(firstStrength);
        free(secondStrength);
        free(mergedStrength);
        throw(BadAllocation());
    }

    int size = mergeSort(firstId, secondId, mergedId, sizeFirst, sizeOther);
    int index = 0, sizeOfFirst = 0, sizeOfSecond = 0, sizeOfThird = 0;
    for (int i = 0; i < (size / 3); i++)
    {
        mergedId[i]->m_data->setTree(0);
        index++;
        sizeOfFirst++;
    }
    for (int i = index; i < ((2 * size) / 3); i++)
    {
        mergedId[i]->m_data->setTree(1);
        index++;
        sizeOfSecond++;
    }
    for (int i = index; i < size; i++)
    {
        mergedId[i]->m_data->setTree(2);
        index++;
        sizeOfThird++;
    }

    mergeSort(firstStrength, secondStrength, mergedStrength, sizeFirst, sizeOther);
    AVLTree<T>::Node **firstTree = (Node **)malloc(sizeof(Node *) * sizeOfFirst);
    AVLTree<T>::Node **secondTree = (Node **)malloc(sizeOfSecond * sizeof(Node *));
    AVLTree<T>::Node **thirdTree = (Node **)malloc(sizeOfThird * sizeof(Node *));
    if (firstTree == nullptr || secondTree == nullptr || thirdTree == nullptr)
    {
        free(firstId);
        free(secondId);
        free(mergedId);
        free(firstStrength);
        free(secondStrength);
        free(mergedStrength);
        free(firstTree);
        free(secondTree);
        free(thirdTree);
        throw(BadAllocation());
    }
    if (lengthsFirst[0] == 0)
    {
        delete firstTrees[0]->m_root;
        delete firstTrees[3]->m_root;
    }
    if (lengthsFirst[1] == 0)
    {
        delete firstTrees[1]->m_root;
        delete firstTrees[4]->m_root;
    }
    if (lengthsFirst[2] == 0)
    {
        delete firstTrees[2]->m_root;
        delete firstTrees[5]->m_root;
    }
    firstTrees[0]->m_root = insertSorted(mergedId, 0, (size / 3) - 1);
    firstTrees[0]->m_root->m_father = nullptr;
    firstTrees[1]->m_root = insertSorted(mergedId, (size / 3), ((2 * size) / 3) - 1);
    firstTrees[1]->m_root->m_father = nullptr;
    firstTrees[2]->m_root = insertSorted(mergedId, ((2 * size) / 3), size - 1);
    firstTrees[2]->m_root->m_father = nullptr;

    int firstIndex = 0, secondIndex = 0, thirdIndex = 0;
    for (int i = 0; i < size; i++)
    {
        if (mergedStrength[i]->m_data->getTree() == 0)
        {
            firstTree[firstIndex++] = mergedStrength[i];
        }
        else if (mergedStrength[i]->m_data->getTree() == 1)
        {
            secondTree[secondIndex++] = mergedStrength[i];
        }
        else
        {
            thirdTree[thirdIndex++] = mergedStrength[i];
        }
    }
    firstTrees[3]->m_root = insertSorted(firstTree, 0, firstIndex - 1);
    firstTrees[3]->m_root->m_father = nullptr;
    firstTrees[4]->m_root = insertSorted(secondTree, 0, secondIndex - 1);
    firstTrees[4]->m_root->m_father = nullptr;
    firstTrees[5]->m_root = insertSorted(thirdTree, 0, thirdIndex - 1);
    firstTrees[5]->m_root->m_father = nullptr;
    free(firstId);
    free(secondId);
    free(mergedId);
    free(firstStrength);
    free(secondStrength);
    free(mergedStrength);
    free(firstTree);
    free(secondTree);
    free(thirdTree);
    lengthsFirst[0] = firstIndex;
    lengthsFirst[1] = secondIndex;
    lengthsFirst[2] = thirdIndex;
    for (int i = 0; i < 3; i++)
    {
        if (lengthsOther[i] != 0)
        {
            AVLTree temp = AVLTree(), temp2 = AVLTree();
            otherTrees[i]->m_root = temp.m_root;
            otherTrees[i + 3]->m_root = temp2.m_root;
            temp.m_root = nullptr;
            temp2.m_root = nullptr;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        lengthsOther[i] = 0;
    }
}

template <class T>
int AVLTree<T>::mergeSort(AVLTree<T>::Node ***first, int *sizes)
{
    int size = 0;
    for (int i = 0; i < 3; i++)
    {
        size += sizes[i];
    }
    AVLTree<T>::Node **temp = (Node **)malloc(size * sizeof(Node *));
    AVLTree<T>::Node **temp2 = (Node **)malloc(size * sizeof(Node *));
    if (temp == nullptr)
    {
        free(temp);
        throw(BadAllocation());
    }
    size = mergeSort(*first, *first + sizes[0], temp, sizes[0], sizes[1]);
    size = mergeSort(temp, *first + sizes[0] + sizes[1], temp2, size, sizes[2]);
    Node **temp3 = *first;
    *first = temp2;
    temp2 = temp3;
    free(temp2);
    free(temp);
    return size;
}

template <class T>
void AVLTree<T>::getDataInOrder(T *array)
{
    if (this->m_root->m_height == EMPTY_TREE)
    {
        return;
    }
    Node *runner = this->m_root;
    int index = 0;
    dataInOrder(runner, array, &index);
}
template <class T>
void AVLTree<T>::dataInOrder(AVLTree<T>::Node *current, T *array, int *index)
{
    if (current == nullptr)
    {
        return;
    }
    dataInOrder(current->m_left, array, index);
    array[*index] = current->m_data;
    *index = *index + 1;
    dataInOrder(current->m_right, array, index);
}

template <class T>
void AVLTree<T>::inOrderWalk(AVLTree<T>::Node *current, AVLTree<T>::Node **array, int *index) const
{
    if (current == nullptr)
    {
        return;
    }
    inOrderWalk(current->m_left, array, index);
    array[*index] = current;
    *index = *index + 1;
    inOrderWalk(current->m_right, array, index);
}

template <class T>
int AVLTree<T>::mergeSort(AVLTree<T>::Node **first, AVLTree<T>::Node **other, AVLTree<T>::Node **merged, int sizeFirst, int sizeOther) //, const int id)
{
    int size = sizeFirst + sizeOther;
    int firstIndex = 0, otherIndex = 0, mergedIndex = 0;
    while (firstIndex < sizeFirst && otherIndex < sizeOther)
    {
        if (first[firstIndex]->m_firstCond < other[otherIndex]->m_firstCond)
        {
            merged[mergedIndex++] = first[firstIndex++];
        }
        else if (first[firstIndex]->m_firstCond > other[otherIndex]->m_firstCond)
        {

            merged[mergedIndex++] = other[otherIndex++];
        }
        else
        {
            if (first[firstIndex]->m_secondCond < other[otherIndex]->m_secondCond)
            {
                merged[mergedIndex++] = first[firstIndex++];
            }
            else if (first[firstIndex]->m_secondCond > other[otherIndex]->m_secondCond)
            {

                merged[mergedIndex++] = other[otherIndex++];
            }
            else
            {
                delete other[otherIndex];
                merged[mergedIndex++] = first[firstIndex++];
                otherIndex++;
                size--;
            }
        }
    }
    while (firstIndex < sizeFirst)
    {
        merged[mergedIndex++] = first[firstIndex++];
    }
    while (otherIndex < sizeOther)
    {

        merged[mergedIndex++] = other[otherIndex++];
    }
    return size;
}

template <class T>
typename AVLTree<T>::Node *AVLTree<T>::insertSorted(AVLTree<T>::Node **sorted, int left, int right)
{
    if (left > right)
    {
        return nullptr;
    }
    int middle = (left + right) / 2;
    Node *current = sorted[middle];
    Node *leftTree = insertSorted(sorted, left, middle - 1);
    Node *rightTree = insertSorted(sorted, middle + 1, right);
    current->m_left = leftTree;
    current->m_right = rightTree;
    current->m_height = max(current) + 1;
    if (rightTree != nullptr)
    {
        rightTree->m_father = current;
    }
    if (leftTree != nullptr)
    {
        leftTree->m_father = current;
    }

    return current;
}

template <class T>
T &AVLTree<T>::findSecondMax() const
{
    Node *runner = this->m_root;
    while (runner->m_right != nullptr)
    {
        runner = runner->m_right;
    }
    if (runner->m_left != nullptr)
    {
        return runner->m_left->m_data;
    }
    if (runner->m_father != nullptr)
    {
        return runner->m_father->m_data;
    }
    throw NodeNotFound();
}
template <class T>
T &AVLTree<T>::findThirdMax()
{
    Node *runner = this->m_root;
    while (runner->m_right != nullptr)
    {
        runner = runner->m_right;
    }
    if (runner->m_father == nullptr)
    {
        throw NodeNotFound();
    }
    runner = runner->m_father;
    if (runner->m_left != nullptr)
    {
        runner = runner->m_left;
        while (runner->m_right != nullptr)
        {
            runner = runner->m_right;
        }
        return runner->m_data;
    }
    if (runner->m_father == nullptr)
    {
        throw NodeNotFound();
    }
    return runner->m_father->m_data;
}
template <class T>
T &AVLTree<T>::findSecondMin() const
{
    Node *runner = this->m_root;
    while (runner->m_left != nullptr)
    {
        runner = runner->m_left;
    }
    if (runner->m_right != nullptr)
    {
        return runner->m_right->m_data;
    }
    if (runner->m_father == nullptr)
    {
        throw NodeNotFound();
    }
    return runner->m_father->m_data;
}
template <class T>
T &AVLTree<T>::findThirdMin()
{
    Node *runner = this->m_root;
    while (runner->m_left != nullptr)
    {
        runner = runner->m_left;
    }
    if (runner->m_father == nullptr)
    {
        throw NodeNotFound();
    }
    runner = runner->m_father;
    if (runner->m_right != nullptr)
    {
        runner = runner->m_right;
        while (runner->m_left != nullptr)
        {
            runner = runner->m_left;
        }
        return runner->m_data;
    }
    if (runner->m_father == nullptr)
    {
        throw NodeNotFound();
    }
    return runner->m_father->m_data;
}
template <class T>
bool AVLTree<T>::updateFirstCondition(const int firstCond, const int secondCond, const int condition)
{
    if (this->m_root->m_height == EMPTY_TREE)
    {
        return false;
    }
    T element;
    try
    {
        element = this->find(firstCond, secondCond);
    }
    catch (const std::exception &e)
    {
        return false;
    }
    if (!this->remove(firstCond, secondCond))
    {
        return false;
    }
    return this->insert(element, condition, secondCond);
}
//---------------------- AVLTree Class End -----------------------------------------------------------------------------
#endif // HW1_AVLTREE_H