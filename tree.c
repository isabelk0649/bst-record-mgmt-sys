/**
 * -------------------------------------
 * @tree tree.h
 * Tree Header File
 * -------------------------------------
 * @author Isabel Katai, 169020649, kata0649@mylaurier.ca
 *
 * @version 2024-03-01
 *
 * -------------------------------------
 */

#include "queue_stack.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>


/* Compute and return the TPROPS value of a tree.
 * @param root - pointer to the root of a tree
 * @return - number of nodes and height in TPROPS type.
 */

int height (TNODE *root){

    if (root == NULL) {
        return 0;

    } else {
        int left_tree_height = height(root->left);
        int right_tree_height = height(root->right);
        return (left_tree_height > right_tree_height) ? left_tree_height + 1 : right_tree_height + 1;
    }
}

int total_nodes (TNODE *root){

    if (root == NULL) {
        return 0;
    }

    int left_nodes = total_nodes(root->left);
    int right_nodes = total_nodes(root->right);
    return 1 + left_nodes + right_nodes;

}
TPROPS tree_property(TNODE *root){

    TPROPS tree_prop;
    tree_prop.height = height(root);
    tree_prop.order = total_nodes(root);
    return tree_prop;

}

void preorder_aux(TNODE *root){

    if (root == NULL) {
        return;
    }

    printf("%c ", root->data);
    preorder_aux(root->left);
    preorder_aux(root->right);

}

/* Display the node data of the tree in pre-order and format "%c ".
 *
 *  @param root - pointer to the root of a tree
 */
void preorder(TNODE *root){
	preorder_aux(root);

}

void inorder_aux(TNODE *root){

    if (root == NULL) {
        return;
    }

    inorder_aux(root->left);
    printf("%c ", root->data);
    inorder_aux(root->right);

}

/* Display the node data of the tree in in-order and format "%c".
 *
 *  @param root - pointer to the root of a tree
 */
void inorder(TNODE *root){
	inorder_aux(root);
}

/* Display the node data of the tree in post-order and format "%c ".
 *
 *  @param root - pointer to the root of a tree
 */

void postorder_aux(TNODE *root){

	if (root == NULL) {
		return;
	}

	postorder_aux(root->left);
	postorder_aux(root->right);
	printf("%c ", root->data);

}

void postorder(TNODE *root){
	postorder_aux(root);

}

/* Display the node data of the tree in breadth-first-order and format "%c ".
 * Required to use auxiliary queue and iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 */
void bforder(TNODE *root){

    if (root == NULL) {
        return;
    }

    QUEUE queue;
    queue.front = NULL; // Initialize
    queue.rear = NULL;

    enqueue(&queue, root); // Enqueue the root node

    while (queue.front != NULL) { // Check if the queue is not empty

        TNODE *current = dequeue(&queue); // Dequeue a node
        printf("%c ", current->data); // Print its data

        // Enqueue left and right children (if any)
        if (current->left)
            enqueue(&queue, current->left);
        if (current->right)
            enqueue(&queue, current->right);
    }
}

/* Search by key using breadth-first-search algorithm
 * Required to use auxiliary queue and iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 *  @param key -  search key
 *
 *  @return  - the found node pointer if fount, otherwise NULL
 */
TNODE *bfs(TNODE *root, char key){

    if (root == NULL) {
        return NULL;
    }

    QUEUE queue;
    queue.front = NULL; // Initialize
    queue.rear = NULL;

    enqueue(&queue, root); // Enqueue the root node

    while (queue.front != NULL) { // Check if the queue is not empty

        TNODE *current = dequeue(&queue); // Dequeue a node
        if (current->data == key) // Check if the current node's data matches the key
            return current; // Return the current node if found

        // Enqueue left and right children (if any)
        if (current->left)
            enqueue(&queue, current->left);
        if (current->right)
            enqueue(&queue, current->right);
    }

    // Key not found
    return NULL;
}


/* Search by key using depth-first-search algorithm.
 * Required to use auxiliary queue and iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 *  @param key -  search key
 *
 *  @return  - the found node pointer if fount, otherwise NULL
 */
TNODE *dfs(TNODE *root, char key){

    if (root == NULL) {
        return NULL;
    }

    STACK stack;
    stack.top = NULL; // Initialize

    push(&stack, root); // Push the root node onto the stack

    while (stack.top != NULL) { // Check if the stack is not empty

        TNODE *current = pop(&stack); // Pop a node
        if (current->data == key) // Check if the current node's data matches the key
            return current; // Return the current node if found

        // Push right and left children (if any)
        if (current->right)
            push(&stack, current->right);
        if (current->left)
            push(&stack, current->left);
    }

    // Key not found
    return NULL;
}


// the following functions are given, need to add to your program.

TNODE *t_new_node(char val) {
    TNODE *np = (TNODE *) malloc(sizeof(TNODE));
    if (np != NULL) {
        np->data = val;
        np->left = NULL;
        np->right = NULL;
    }
    return np;
}

void clean_tree(TNODE **rootp) {
    TNODE *p = *rootp;
    if (p) {
        if (p->left)
            clean_tree(&p->left);
        if (p->right)
            clean_tree(&p->right);
        free(p);
    }
    *rootp = NULL;
}

void insert_tree(TNODE **rootp, char val) {
    if (*rootp == NULL) {
        *rootp = t_new_node(val);
    } else {
        QUEUE queue = { 0 };
        TNODE *p;
        enqueue(&queue, *rootp);
        while (queue.front) {
            p = dequeue(&queue);
            if (p->left == NULL) {
                p->left = t_new_node(val);
                break;
            } else {
                enqueue(&queue, p->left);
            }

            if (p->right == NULL) {
                p->right = t_new_node(val);
                break;
            } else {
                enqueue(&queue, p->right);
            }
        }
    }
}
