#include "BinarySearchT.h"
#include <stdlib.h>
#include <stdio.h>

DSNode_t *bst_create(int* data, size_t tree_lenght) 
{ 
    if(data == NULL || tree_lenght == 0) return NULL;
    DSNode_t* root = NULL;
    for(size_t i = 0; i < tree_lenght;++i)
    {
        root = bst_insert(root,data[i]);
    }
    return root; 
}

DSNode_t *bst_insert(DSNode_t *root, int data) 
{ 
    if(root == NULL)
    {
        DSNode_t* new_root = malloc(sizeof(DSNode_t));
        if(new_root == NULL)
        {
            fprintf(stderr,"BST_insert : failed alloc\n");
            exit(EXIT_FAILURE);
        }
        new_root->data = data;
        new_root->left = NULL;
        new_root->right = NULL;
        return new_root;
    }
    // insert left
    if(data <= root->data)
    {
        root->left = bst_insert(root->left,data);
    }
    else
    {
        root->right = bst_insert(root->right,data);
    }
    return root; 
}

DSNode_t *bst_search(DSNode_t *root, int target) 
{ 
    if(root == NULL ||root->data == 0) return NULL;
    if(target < root->data)
    {
        return bst_search(root->left,target);
    }
    else
    {
        return bst_search(root->right,target);
    }
}

void bst_delete(DSNode_t *root, int target) 
{
    DSNode_t* result = bst_search(root,target);
    if(result == NULL)
    {
        fprintf(stderr,"bst_delete : item not found in tree\n");
        return;
    }
    // TODO : continue deletion
}

int bst_height(DSNode_t *tree) 
{ 
    if(tree == NULL) return -1;
    int left = bst_height(tree->left);
    int right = bst_height(tree->right);
    return 1 + (left > right? left:right); 
}

bool bst_is_balanced(DSNode_t *root) 
{ 
    if(root == NULL) return false;
    int left = bst_height(root->left);
    int right = bst_height(root->right);
    return abs(left-right) <= 1 && 
            bst_is_balanced(root->left) &&
            bst_is_balanced(root->right); 
}

size_t bst_count_nodes(DSNode_t *tree) 
{ 
    if(tree == NULL) return 0;
    return 1 + bst_count_nodes(tree->left)+bst_count_nodes(tree->right);
}

void bst_fill_ordered(DSNode_t *tree, int* data, size_t *index) 
{
    if(tree == NULL) return;
    bst_fill_ordered(tree->left,data,index);
    data[(*index)++] = tree->data;
    bst_fill_ordered(tree->right,data,index);
}

int *bst_sorted_data(DSNode_t *tree) 
{ 
    if(tree == NULL) return NULL;
    size_t num_nodes = bst_count_nodes(tree);
    int* sorted_data = malloc(sizeof(int)*num_nodes);
    if(sorted_data == NULL)
    {
        fprintf(stderr,"bst_sorted_data : failed to alloc\n");
        exit(EXIT_FAILURE);
    }
    size_t index = 0;
    bst_fill_ordered(tree,sorted_data,&index);
    return sorted_data; 
}

void bst_destroy(DSNode_t *tree) 
{
    if(tree == NULL) return;
    bst_destroy(tree->left);
    bst_destroy(tree->right);
    free(tree);
}

void bst_print(DSNode_t *tree, int depth) 
{
    if (tree == NULL) return;
    bst_print(tree->right, depth + 1);
    for (int i = 0; i < depth; ++i) printf("    ");
    printf("%d\n", tree->data);
    bst_print(tree->left, depth + 1);
}

void bst_test() {
  int values[] = {5, 3, 7, 2, 4, 6, 8};
  size_t length = sizeof(values) / sizeof(values[0]);

  DSNode_t *tree = bst_create(values, length);

  printf("Tree structure:\n");
  bst_print(tree, 0);

  printf("\nTree is %sbalanced\n", bst_is_balanced(tree) ? "" : "not ");

  printf("Sorted values:\n");
  int *sorted = bst_sorted_data(tree);
  for (size_t i = 0; i < length; ++i) {
    printf("%d ", sorted[i]);
  }
  printf("\n");
  free(sorted);

  int search_value = 4;
  DSNode_t *found = bst_search(tree, search_value);
  printf("Search for %d: %s\n", search_value, found ? "Found" : "Not found");

  bst_destroy(tree);
}
