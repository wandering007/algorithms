/* Dynamic programming based algorithm for Largest Independent Set problem in trees */
// Given a binary tree, find size of the largest independent set (LIS) in it. A subset
// of all tree nodes is an independent set if there is no edge between any two nodes
// of the subset.

#include <stdio.h>
#include <stdlib.h>

// A utility function to find max of two integers
int max(int x, int y) { return (x > y) ? x : y; }

/* A binary tree node has data, point to left child and a pointer to right child */
struct node
{
    int data;
    int liss;
    struct node *left, *right;
};

/* A memoization function returns size of the largest independent set in a given
   binary tree */
int LISS(struct node *root)
{
    if (NULL == root)
        return 0;

    if (root->liss > 0)
        return root->liss;

    if (NULL == root->left && NULL == root->right)
        return (root->liss = 1);

    // calculate size excluding the current node
    int liss_excl = LISS(root->left) + LISS(root->right);

    // calculate size including the current node
    int liss_incl = 1;
    if (root->left)
    {
        liss_incl += LISS(root->left->left) + LISS(root->left->right);
    }
    if (root->right)
    {
        liss_incl += LISS(root->right->left) + LISS(root->right->right);
    }

    // Maximum of two sizes is LISS, store it for future uses
    root->liss = max(liss_excl, liss_incl);

    return root->liss;
}