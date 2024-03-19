
#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Search the BST by search key matching with data.name
 *
 * @param root - pointer to tree root.
 * @param key - string of search key
 *
 * @return - pointer to matched node if found, otherwise NULL
 */

BSTNODE *bst_search_aux(BSTNODE *root, char *key){

	if (root == NULL) {
		return NULL;
	}

    if (strcmp(key, root->data.name) == 0) { // Compare strings using strcmp
        return root;

    } else if (strcmp(key, root->data.name) < 0) { // Compare strings using strcmp
        return bst_search_aux(root->left, key);

    } else {
        return bst_search_aux(root->right, key);
    }

}
BSTNODE *bst_search(BSTNODE *root, char *key){

	return bst_search_aux(root, key);

}

/* Insert a node of given record data into BST.
 *
 * @param rootp - pointer of pointer to tree root.
 * @param data  -  record data for the new node.
 *
 */

void bst_insert_aux(BSTNODE **rootp, RECORD data){

	if (*rootp == NULL) {
		*rootp = b_new_node(data);
		return;
	}

    if (strcmp(data.name, (*rootp)->data.name) < 0) {
        bst_insert_aux(&(*rootp)->left, data);

    } else {
        bst_insert_aux(&(*rootp)->right, data);
	}


}
void bst_insert(BSTNODE **rootp, RECORD data){
	bst_insert_aux(rootp, data);

}

/* Delete a node of data.name matched with given key.
 *
 * @param rootp - pointer of pointer to tree root.
 * @param key -   key to match with data.name for deletion.
 */

void bst_delete_aux(BSTNODE **rootp, char *key){

	if (*rootp == NULL) {
		return;
	}

	if (strcmp(key, (*rootp)->data.name) < 0) {
        bst_delete_aux(&(*rootp)->left, key);

    } else if (strcmp(key, (*rootp)->data.name) > 0) {
        bst_delete_aux(&(*rootp)->right, key);

	} else {

        if ((*rootp)->left == NULL) { //no child, or only one
            BSTNODE *temp = *rootp;
            *rootp = (*rootp)->right;
            free(temp);

        } else if ((*rootp)->right == NULL) {
            BSTNODE *temp = *rootp;
            *rootp = (*rootp)->left;
            free(temp);

        } else { // two children
            BSTNODE *temp = extract_smallest_node(&(*rootp)->right);
            (*rootp)->data = temp->data;
            free(temp);
        }
	}
}

void bst_delete(BSTNODE **rootp, char *key){
	bst_delete_aux(rootp, key);

}


// Following functions are given in a7 help.

/* This function creates BSTNODE node with given RECORD data
 * using malloc() and return the new node pointer.
 */

BSTNODE *b_new_node(RECORD data) {
    BSTNODE *np = (BSTNODE *) malloc(sizeof(BSTNODE));
    if (np) {
        memcpy(np, &data, sizeof(BSTNODE));
        np->left = NULL;
        np->right = NULL;
    }
    return np;
}

BSTNODE *extract_smallest_node(BSTNODE **rootp) {
    BSTNODE *p = *rootp, *parent = NULL;
    if (p) {
        while (p->left) {
            parent = p;
            p = p->left;
        }

        if (parent == NULL)
            *rootp = p->right;
        else
            parent->left = p->right;

        p->left = NULL;
        p->right = NULL;
    }

    return p;
}

void clean_bst(BSTNODE **rootp) {
    BSTNODE *root = *rootp;
    if (root) {
        if (root->left)
            clean_bst(&root->left);
        if (root->right)
            clean_bst(&root->right);
        free(root);
    }
    *rootp = NULL;
}
