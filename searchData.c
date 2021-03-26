#include "read_CSV.h"
#include "buildTree.h"
#include "searchData.h"

/* main searching function of the nearest coordinate for map1 */
list_t *map1_searchRecord(tree_t *tree) {
    int i;
    list_t *outcome_list = NULL;
    char **search_key;
    search_key = (char **)malloc(sizeof(char *) * COOR_ELEMENTS);
    assert(search_key);

    for (i = 0; i < COOR_ELEMENTS; i++) {
        search_key[i] = (char *)malloc(sizeof(char) * DIGIT_NUM);
        assert(search_key[i]);
    }

    /* scanf two coordinates from key.txt */
    while((fscanf(stdin,"%s %s", search_key[POSI_X_COOR], search_key[POSI_Y_COOR])) == COOR_ELEMENTS){

        int depth = 0, count_comparsion = 0;
        double nearestRadius;
        node_t *nearestNode = NULL;

        /* recursive search the coordinates in tree */
        map1_recursiveSearch(tree->root, search_key, depth, &count_comparsion, &nearestNode, &nearestRadius);

        /* store into the outcome list to print out */
        outcome_list = map1_store_into_list(count_comparsion, search_key, nearestNode, outcome_list);

        nearestNode = NULL;

    }
    for (i = 0; i < COOR_ELEMENTS; i++){
        free(search_key[i]);
    }
    free(search_key);
    return outcome_list;
}

/* recursive searching function of the nearest coordinate for map1 */
void map1_recursiveSearch(node_t *root, char **search_key, int depth, int *count_comparsion, node_t **nearestNode, double *nearestRadius) {
    if (root == NULL){
        return;
    }

    int cd = depth % 2;
    double distance = calculateDistance(root, search_key[cd], cd);
    double radius = calculateRadius(root, search_key);

    *count_comparsion = *count_comparsion + 1;
    /* find the nearest Node*/
    if (*nearestNode == NULL) {
        *nearestNode = root;
        *nearestRadius = radius;
    } else if (radius < *nearestRadius) {
        *nearestNode = root;
        *nearestRadius = radius;
    }

    if (*nearestRadius == 0) {
        return;
    }

    /* searching the target in KD tree */
    if((distance < radius) || (distance == radius)) {
        map1_recursiveSearch(root->left, search_key, depth + 1, count_comparsion, nearestNode, nearestRadius);
        map1_recursiveSearch(root->right, search_key, depth + 1, count_comparsion, nearestNode, nearestRadius);
    }
    else{
        if (atof(search_key[cd]) < root->coordinate[cd]) {
            map1_recursiveSearch(root->left, search_key, depth + 1, count_comparsion, nearestNode, nearestRadius);
        }
        else{
            map1_recursiveSearch(root->right, search_key, depth + 1, count_comparsion, nearestNode, nearestRadius);
        }
    }
}

/* store the outcome into the outcome list for Map1 */
list_t *map1_store_into_list(int count_comparsion, char **search_key, node_t *nearestNode, list_t *outcome_list){

    list_t *new;
    new = (list_t *)malloc(sizeof(list_t));
    assert(new);

    new->count_comparison = count_comparsion;
    insert_key(new, search_key);
    new->resultPoint = nearestNode;
    new->inputRadius = NULL;

    new->next = outcome_list;
    outcome_list = new;

    return outcome_list;
}


/* main searching function of the coordinates in the radius for map2 */
list_t *map2_searchRecord(tree_t *tree) {
    int i;
    char **search_key;
    search_key = (char **)malloc(sizeof(char *) * COOR_ELEMENTS);
    assert(search_key);
    list_t *outcome_list = NULL;

    for (i = 0; i < COOR_ELEMENTS; i++) {
        search_key[i] = (char *)malloc(sizeof(char) * DIGIT_NUM);
        assert(search_key[i]);
    }

    char *inputRadius;
    inputRadius = (char *)malloc(sizeof(char) * DIGIT_NUM);
    assert(inputRadius);

    /* scanf two coordinates from key.txt */
    while((fscanf(stdin,"%s %s %s", search_key[POSI_X_COOR], search_key[POSI_Y_COOR], inputRadius)) == COOR_ELEMENTS_RADIUS){
        int depth = 0, count_comparsion = 0;
        node_t *satisfyCoorNode = NULL;

        /* recursive search the coordinates in tree */
        map2_recursiveSearch(tree->root, search_key, depth, &count_comparsion, &satisfyCoorNode, inputRadius);

        /* store into the outcome list to print out */
        outcome_list = map2_store_into_list(count_comparsion, search_key, satisfyCoorNode, inputRadius, outcome_list);

    }
    for (i = 0; i < COOR_ELEMENTS; i++){
        free(search_key[i]);
    }
    free(search_key);
    free(inputRadius);
    return outcome_list;
}

/* recursive searching function of the coordinates in the radius for map2 */
void map2_recursiveSearch(node_t *root, char **search_key, int depth, int *count_comparsion, node_t **satisfyCoorNode, char *inputRadius) {
    if (root == NULL){
        return;
    }

    int cd = depth % 2;
    double distance = calculateDistance(root, search_key[cd], cd);
    double radius = calculateRadius(root, search_key);

    *count_comparsion = *count_comparsion + 1;

    /* searching the target in KD tree */
    if (radius <= atof(inputRadius)){
        node_t *new_node;
        new_node = (node_t *)malloc(sizeof(node_t));
        assert(new_node);
        new_node->data = root->data;
        new_node->next_inradius_point = *satisfyCoorNode;
        *satisfyCoorNode = new_node;

        map2_recursiveSearch(root->left, search_key, depth + 1, count_comparsion, satisfyCoorNode, inputRadius);
        map2_recursiveSearch(root->right, search_key, depth + 1, count_comparsion, satisfyCoorNode, inputRadius);
    }
    /* normal comparsion in KD tree (same as Map1)*/
    else {
        if((distance < radius) || (distance == radius)) {
            map2_recursiveSearch(root->left, search_key, depth + 1, count_comparsion, satisfyCoorNode, inputRadius);
            map2_recursiveSearch(root->right, search_key, depth + 1, count_comparsion, satisfyCoorNode, inputRadius);
        }
        else{
            if (atof(search_key[cd]) < root->coordinate[cd]) {
                map2_recursiveSearch(root->left, search_key, depth + 1, count_comparsion, satisfyCoorNode, inputRadius);
            }
            else{
                map2_recursiveSearch(root->right, search_key, depth + 1, count_comparsion, satisfyCoorNode, inputRadius);
            }
        }
    }
}

/* store the outcome into the outcome list for Map2 */
list_t *map2_store_into_list(int count_comparsion, char **search_key, node_t *satisfyCoorNode, char *inputRadius, list_t *outcome_list) {

    list_t *new;
    new = (list_t *)malloc(sizeof(list_t));
    assert(new);

    new->resultPoint = satisfyCoorNode;
    new->count_comparison = count_comparsion;

    insert_key(new, search_key);
    new->inputRadius = (char *)malloc(sizeof(char) * strlen(inputRadius)+1);
    strcpy(new->inputRadius, inputRadius);

    new->next = outcome_list;
    outcome_list = new;

    return outcome_list;
}



/* calculate the distance/radius between searching coordinate and dataset coordinate */
double calculateRadius(node_t *root, char **search_key) {
    double radius;
    double node_x = root->coordinate[POSI_X_COOR];
    double node_y = root->coordinate[POSI_Y_COOR];
    double query_x = atof(search_key[POSI_X_COOR]);
    double query_y = atof(search_key[POSI_Y_COOR]);
    
    radius = sqrt(pow(node_x - query_x, 2.0) + pow(node_y - query_y, 2.0));
    return radius;
}

/* calculate the distance between searching coordinate and perpendicular of the dataset point */
double calculateDistance(node_t *root, char *search_coor, int cd) {
    double distance;
    distance = fabs(root->coordinate[cd] - atof(search_coor));
    return distance;
}

/* insert the outcome key with efficient memory allocation */
void insert_key(list_t *new, char **key) {
    new->search_key = (char **)malloc(sizeof(char *) * COOR_ELEMENTS);
    assert(new->search_key);
    for (int i = 0; i < COOR_ELEMENTS; i++) {
        new->search_key[i] = (char *)malloc(sizeof(char) * strlen(key[i]) + 1);
        assert(new->search_key[i]);
        strcpy(new->search_key[i], key[i]);
    }
}
