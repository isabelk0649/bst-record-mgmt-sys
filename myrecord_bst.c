/**
 * -------------------------------------
 * @myrecord_bst.c  myrecord_bst.c
 * Assignment 7 Source Code File
 * -------------------------------------
 * @author Isabel Katai, 169020649, kata0649@mylaurier.ca
 *
 * @version 2024-03-01
 *
 * -------------------------------------
 */

#include <stdio.h>
#include <math.h>
#include "queue_stack.h"
#include "bst.h"
#include "tree.h"
#include "myrecord_bst.h"

/* Add a record data into the BSTDS and update its stats info incrementally.
 *
 * @parame ds - pointer to the BSTDS.
 * @parama record - RECORD data to be added.
 */

float calculate_mean(BSTNODE *root) {

    float sum = 0.0;
    int count = 0;

    void inorder_traversal(BSTNODE *node) {

        if (node != NULL) {
            inorder_traversal(node->left);
            sum += node->data.score;
            count++;
            inorder_traversal(node->right);
        }
    }

    inorder_traversal(root);
    float mean = (count > 0) ? (sum / count) : 0.0;

    return mean;
}


float calculate_stddev(BSTNODE *root) {

    float mean = calculate_mean(root);

    float squared_diff_sum = 0.0;
    int count = 0;

    void inorder_traversal(BSTNODE *node) {

        if (node != NULL) {
            inorder_traversal(node->left);
            squared_diff_sum += pow(node->data.score - mean, 2);
            count++;
            inorder_traversal(node->right);
        }
    }

    inorder_traversal(root);
    float standard_deviation = (count > 0) ? sqrt(squared_diff_sum / count) : 0.0;

    return standard_deviation;

}
void add_record(BSTDS *tree, RECORD record) {

	if (tree == NULL) {
		return;
	}

	BSTNODE *np = b_new_node(record);
	bst_insert(&(tree->root), np->data);

	tree->count++;
	tree->mean = calculate_mean(tree->root);
	tree->stddev = calculate_stddev(tree->root);

}

/* Delete a record of the given name from the BST tree of BSTDS
 * and update its stats info incrementally.
 * @parame ds - pointer to the BSTDS.
 * @parama record - RECORD data to be added.
 */
void remove_record(BSTDS *tree, char *key) {

	if (tree == NULL || tree->root == NULL){
		return;
	}

	bst_delete(&(tree->root), key);
	tree->count--;
	tree->mean = calculate_mean(tree->root);
	tree->stddev = calculate_stddev(tree->root);

}

void clean_bstds(BSTDS *ds) {
  clean_bst(&ds->root);
  ds->count = 0;
  ds->mean = 0;
  ds->stddev = 0;
}
