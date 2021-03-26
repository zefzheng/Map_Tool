#include "buildTree.h"

/* create an empyty tree to store the info */
tree_t
*make_empty_tree() {
    tree_t *tree;
    tree = malloc(sizeof(*tree));
    assert(tree!=NULL);
    /* initialize tree to empty */
    tree->root = NULL;
    return tree;
}

/* adding info to the dataset tree */
tree_t
*insert_into_tree(tree_t *tree, info_t *data) {
    node_t *new;
    new = (node_t *)malloc(sizeof(node_t));
    assert(tree!=NULL && new!=NULL);

    new->data = data;
    new->coordinate[POSI_X_COOR] = atof(data->x_coordinate);
    new->coordinate[POSI_Y_COOR] = atof(data->y_coordinate);
    new->left = new->right = NULL;
    new->next_inradius_point = NULL;

    tree->root = recursive_insert(tree->root, new, data, INITIAL_DEPTH);

    return tree;
}

/* recursive adding info to the dataset tree */
node_t
*recursive_insert(node_t *root, node_t *new, info_t *data, int depth) {
    /* To use the reminder to count the depth of the tree. */
    int cd = depth % 2;

    if (root==NULL) {
        return new;
    } else if (checkSameCoor(root, new)) {
        append_to_link_list(root, data);
        free(new);
    } else if (new->coordinate[cd] < (root->coordinate[cd])) {
        root->left = recursive_insert(root->left, new, data, depth + 1);
    } else {
        root->right = recursive_insert(root->right, new, data, depth + 1);
    }
    return root;
}

/* Checking whether it is the same coordinate */
int checkSameCoor(node_t *root, node_t *new) {
    int i;
    for (i = 0; i < COOR_ELEMENTS; i++){
        if (root->coordinate[i] != new->coordinate[i]){
            return 0;
        }
    }
    return 1;
}

/* if it is the same coordinate, append into a list */
void append_to_link_list(node_t *root, info_t *data){
    data->next = root->data;
    root->data = data;
}

/* main function of freeing KD tree */
void
free_tree(tree_t *tree) {
    assert(tree!=NULL);
    recursive_free_tree(tree->root);
    free(tree);
}

/* recursive function of freeing KD tree */
void
recursive_free_tree(node_t *root) {
    if (root) {
        recursive_free_tree(root->left);
        recursive_free_tree(root->right);
        free_elements(root->data);
        free(root);
    }
}

/* free all the attributes/elements of memory space */
void
free_elements(info_t *data) {
    if (data->next != NULL){
        free_elements(data->next);
    }

    free(data->Census_year);
    free(data->Block_ID);
    free(data->Property_ID);
    free(data->Base_property_ID);
    free(data->CLUE_small_area);
    free(data->Trading_name);
    free(data->Industry_code);
    free(data->Industry_description);
    free(data->x_coordinate);
    free(data->y_coordinate);
    free(data->Location);
    free(data);
}

/* free database list */
void
free_list(list_t *list, char *stage_input) {
    if (list->next != NULL) {
           free_list(list->next, stage_input);
    }
    int i;
    for (i = 0; i < 2; i++){
        free(list->search_key[i]);
    }

    /* extra free for map2 attributes */
    if (strcmp(stage_input, "./map1")) {
        free_resultPoint(list->resultPoint);
        free(list->inputRadius);
    }

    free(list->search_key);
    free(list);
}

/* free result point */
void free_resultPoint(node_t *resultPoint) {
    if (resultPoint != NULL){
        free_resultPoint(resultPoint->next_inradius_point);
        free(resultPoint);
    }
}
