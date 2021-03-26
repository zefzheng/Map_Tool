/* These two searchData files are developed by Daniel Zefeng Zheng, Sep 2020
*
*  searchData files are to search in dataset tree.
*/


#define DIGIT_NUM 12

/* function for map1 */
list_t *map1_searchRecord(tree_t *tree);
void map1_recursiveSearch(node_t *root, char **search_key, int depth, int *count_comparsion, node_t **nearestNode, double *nearestRadius);
list_t *map1_store_into_list(int count_comparsion, char **search_key, node_t *nearestNode, list_t *outcome_list);

/* function for map2 */
list_t *map2_searchRecord(tree_t *tree);
void map2_recursiveSearch(node_t *root, char **search_key, int depth, int *count_comparsion, node_t **satisfyCoorNode, char *inputRadius);
list_t *map2_store_into_list(int count_comparsion, char **search_key, node_t *satisfyCoorNode, char *inputRadius, list_t *outcome_list);

/* general function */
double calculateRadius(node_t *root, char **search_key);
double calculateDistance(node_t *root, char *search_coor, int cd);
void insert_key(list_t *new, char **key);
