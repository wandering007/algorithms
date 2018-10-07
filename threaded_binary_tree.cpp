// Threaded binary tree
// Single Threaded: Where a NULL right pointers is made to point to the inorder
// successor (if successor exists)
// Double Threaded: Where both left and right NULL pointers are made to point to
// inorder predecessor and inorder successor respectively. The predecessor
// threads are useful for reverse inorder traversal and postorder traversal.
// Ref: https://www.geeksforgeeks.org/threaded-binary-tree-insertion/
//      https://www.sanfoundry.com/cpp-program-implement-threaded-binary-tree/
#include <stdio.h>

struct Node {
    struct Node *left, *right;
    int info;

    // True if left pointer points to predecessor
    // in Inorder Traversal
    bool lthread;

    // True if right pointer points to predecessor
    // in Inorder Traversal
    bool rthread;
};

// Returns inorder successor using rthread
struct Node *inorderSuccessor(struct Node *ptr) {
    // If rthread is set, we can quickly find
    if (ptr->rthread == true) return ptr->right;

    // Else return leftmost child of right subtree
    ptr = ptr->right;
    while (ptr->lthread == false) ptr = ptr->left;
    return ptr;
}

// Printing the threaded tree
void inorder(struct Node *root) {
    if (root == NULL) printf("Tree is empty");

    // Reach leftmost node
    struct Node *ptr = root;
    while (ptr->lthread == false) ptr = ptr->left;

    // One by one print successors
    while (ptr != NULL) {
        printf("%d ", ptr->info);
        ptr = inorderSuccessor(ptr);
    }
}

// Insert a Node in Threaded Binary Search Tree
struct Node *insert(struct Node *root, int ikey) {
    // Searching for a Node with given value
    Node *ptr = root;
    Node *parent = NULL;  // Parent of key to be inserted
    while (ptr != NULL) {
        // If key already exists, return
        if (ikey == (ptr->info)) {
            printf("Duplicate Key !\n");
            return root;
        }

        parent = ptr;  // Update parent pointer

        // Moving on left subtree.
        if (ikey < ptr->info) {
            if (ptr->lthread == false)
                ptr = ptr->left;
            else
                break;
        }

        // Moving on right subtree.
        else {
            if (ptr->rthread == false)
                ptr = ptr->right;
            else
                break;
        }
    }

    // Create a new node
    Node *tmp = new Node;
    tmp->info = ikey;
    tmp->lthread = true;
    tmp->rthread = true;

    if (parent == NULL) {
        root = tmp;
        tmp->left = NULL;
        tmp->right = NULL;
    } else if (ikey < (parent->info)) {
        tmp->left = parent->left;
        tmp->right = parent;
        parent->lthread = false;
        parent->left = tmp;
    } else {
        tmp->left = parent;
        tmp->right = parent->right;
        parent->rthread = false;
        parent->right = tmp;
    }

    return root;
}

/* Fuction to delete an element */
void Delete(struct Node *root, int key) {
    Node *dest = root->left, *p = root;
    while (true) {
        if (dest->info < key) {
            /* not found */
            if (dest->rthread) return;
            p = dest;
            dest = dest->right;
        } else if (dest->info > key) {
            /* not found */
            if (dest->lthread) return;
            p = dest;
            dest = dest->left;
        } else {
            /* found */
            break;
        }
    }
    Node *target = dest;
    if (!dest->rthread && !dest->lthread) {
        /* dest has two children*/
        p = dest;
        /* find largest node at left child */
        target = dest->left;
        while (!target->rthread) {
            p = target;
            target = target->right;
        }
        /* using replace mode*/
        dest->info = target->info;
    }
    // update the left/right children of p
    // target is the left child of p
    if (p->info >= target->info) {
        if (target->rthread && target->lthread) {
            p->left = target->left;
            p->lthread = true;
        } else if (target->rthread) {
            Node *largest = target->left;
            while (!largest->rthread) {
                largest = largest->right;
            }
            largest->right = p;
            p->left = target->left;
        } else {
            Node *smallest = target->right;
            while (!smallest->lthread) {
                smallest = smallest->left;
            }
            smallest->left = target->left;
            p->left = target->right;
        }
    } else { // target is the right child of p
        if (target->rthread && target->lthread) {
            p->right = target->right;
            p->rthread = true;
        } else if (target->rthread) {
            Node *largest = target->left;
            while (!largest->rthread) {
                largest = largest->right;
            }
            largest->right = target->right;
            p->right = target->left;
        } else {
            Node *smallest = target->right;
            while (!smallest->lthread) {
                smallest = smallest->left;
            }
            smallest->left = p;
            p->right = target->right;
        }
    }
}
