#include "AVLTree.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <vector>
#include <climits>

void test_integration();
void test_boundary_conditions();

int main()
{
    srand(time(0)); // Seed the random number generator with the current time
    bool notFound = false;
    AVLTree<int> tree; // Create an instance of your AVL tree

    // Insert 100 random numbers into the tree
    for (int i = 0; i < 100; ++i)
    {
        int num = rand() % 1000; // Generate a random number between 0 and 999
        tree.insert(num, num,num);
        if (!(*tree.find(num,num) == num))
        {
            std::cout << "Tree should contain " << num << " after insertion, but it does not.\n";
            return 1; // Return an error code
        }
    }

    // Print the tree in order for debugging
    tree.printTree();

    // Remove 50 random numbers from the tree
    for (int i = 0; i < 50; ++i)
    {
        int num = rand() % 1000; // Generate a random number between 0 and 999
        tree.remove(num,num);
        try
        {
            tree.find(num,num);
        }
        catch (...)
        {
            notFound = true;
        }

        if (!notFound)
        {
            std::cout << "Tree should not contain " << num << " after removal, but it does.\n";
            return 1; // Return an error code
        }
    }

    // Print the tree in order for debugging
    tree.printTree();

    AVLTree<int> t1;
    t1.insert(5, 5,5);
    printf("One node with '5': \n");
    t1.printTree();
    printf("\n");

    t1.insert(20, 20,20);
    t1.insert(-14, -14,-14);
    t1.insert(50, 50,50);
    t1.insert(2, 2,2);
    t1.insert(2, 2,2);
    t1.insert(3, 3,3);
    t1.insert(4, 4,4);
    t1.insert(3, 3,2);
    t1.insert(4, 4,5);
    printf("finding three max:\n");
    printf("max is %d\n", *(t1.findMax()));
    printf("second max is %d\n", *(t1.findSecondMax()));
    printf("third max is %d\n", *(t1.findThirdMax()));
    printf("finding three min:\n");
    printf("min is %d\n", *(t1.findMin()));
    printf("second min is %d\n", *(t1.findSecondMin()));
    printf("third min is %d\n", *(t1.findThirdMin()));
    printf("Original Tree:\n");
    t1.printTree();
    printf("\n");

    t1.remove(20,20);
    printf("Removal of 20:\n");
    t1.printTree();
    printf("\n");

    t1.remove(2,2);
    printf("Removal of 2:\n");
    t1.printTree();
    printf("\n");

    if (t1.remove(70,70))
    {
        printf("oh No! removed 70!\n");
    }
    else
    {
        printf("Couldn't remove 70!\n");
    }

    // int i = t1.insert(5,5);
    // printf("Added 5 again: %d\n",i);

    t1.remove(3,3);
    printf("Removed 3,3:\n");
    t1.printTree();
    printf("\n");
    t1.remove(4,5);
    printf("Removed 4,5:\n");
    t1.printTree();
    printf("\n");

    AVLTree<int> t2 = t1;
    printf("Print 'operation=' tree:\n");
    t2.printTree();
    printf("\n");

    AVLTree<int> t3(t1);
    printf("Print copied tree:\n");
    t3.printTree();
    printf("\n");

    AVLTree<int> t4;
    t4.insert(16, 16,16);
    t4.insert(1, 1,1);
    t4.printTree();
    t1.mergeTree(t4, 2, 5);
    printf("Print merged tree:\n");
    t1.printTree();
    printf("\n");
    // Test Right-Right (RR) Rotation
    AVLTree<int> t5;
    t5.insert(30, 30,30);
    t5.insert(20, 20,20);
    t5.insert(10, 10,10);
    std::cout << "Testing RR Rotation" << std::endl;
    t5.printTree();

    // Test Left-Left (LL) Rotation
    AVLTree<int> t6;
    t6.insert(10, 10,10);
    t6.insert(20, 20,20);
    t6.insert(30, 30,30);
    std::cout << "Testing LL Rotation" << std::endl;
    t6.printTree();

    // Test Left-Right (LR) Rotation:
    AVLTree<int> t7;
    t7.insert(30, 30,30);
    t7.insert(10, 10,10);
    t7.insert(20, 20,20);
    std::cout << "Testing LR Rotation" << std::endl;
    t7.printTree();
    // Test Right-Left (RL)
    AVLTree<int> t8;
    t8.insert(10, 10,10);
    t8.insert(30, 30,30);
    t8.insert(20, 20,20);
    std::cout << "Testing RL Rotation" << std::endl;
    t8.printTree();

    test_integration();
    test_boundary_conditions();
    std::cout << "All tests passed!\n";
};

void test_boundary_conditions()
{
    AVLTree<int> tree;
    bool notFound = false;
    // Test inserting the minimum and maximum int values
    tree.insert(INT_MIN, INT_MIN,INT_MIN);
    tree.insert(INT_MAX, INT_MAX,INT_MAX);
    assert(*tree.find(INT_MIN,INT_MIN) == INT_MIN);
    assert(*tree.find(INT_MAX,INT_MAX) == INT_MAX);
    assert(tree.treeIsBalanced());

    // Test removing the minimum and maximum int values
    tree.remove(INT_MIN,INT_MIN);
    tree.remove(INT_MAX,INT_MAX);
    try
    {
        tree.find(INT_MIN,INT_MIN);
        tree.find(INT_MAX,INT_MAX);
    }
    catch (...)
    {
        notFound = true;
    }

    if (!notFound)
    {
        std::cout << "found something that shouldnt be found" << std::endl;
        notFound = false;
    }
    assert(tree.treeIsBalanced());

    // Test inserting a large number of elements
    for (int i = 0; i < 10000; i++)
    {
        tree.insert(i, i,i);
        assert(*tree.find(i,i) == i);
    }
    assert(tree.treeIsBalanced());

    // Test removing a large number of elements
    for (int i = 0; i < 10000; i++)
    {
        tree.remove(i,i);
        try
        {
            tree.find(i,i);
        }
        catch (...)
        {
            notFound = true;
        }

        if (!notFound)
        {
            std::cout << "found something that shouldnt be found" << std::endl;
            notFound = false;
        }
    }
    assert(tree.treeIsBalanced());
}

void test_integration()
{
    AVLTree<int> tree;
    std::vector<int> elements = {30, 20, 40, 10, 50};
    bool notFound = false;
    // Insert elements and check balance
    for (int el : elements)
    {
        tree.insert(el, el,el);
        assert(tree.find(el,el) != nullptr);
        assert(tree.treeIsBalanced());
    }

    // Check the height of the tree
    assert(tree.height() == 3);

    // Remove elements and check balance
    for (int el : elements)
    {
        tree.remove(el,el);
        try
        {
            tree.find(el,el);
        }
        catch (...)
        {
            notFound = true;
        }

        if (!notFound)
        {
            std::cout << "found something that shouldnt be found" << std::endl;
            notFound = false;
        }
        assert(tree.treeIsBalanced());
    }

    // Check the height of the tree
    assert(tree.height() == 0);
}
