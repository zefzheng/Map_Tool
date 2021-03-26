/* These two buildTree files are developed by Daniel Zefeng Zheng, Sep 2020
*
* buildTree files are using efficient KD tree to store the input dataset.
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#define CENSUS_YEAR 0
#define BLOCK_ID 1
#define PROPERTY_ID 2
#define BASE_PROPERTY_ID 3
#define CLUE_SMALL_AREA 4
#define TRADING_NAME 5
#define INDUSTRY_CODE 6
#define INDUSTRY_DESCRIPTION 7
#define X_COOR 8
#define Y_COOR 9
#define LOCATION 10

#define ELEMENTS_CHARS 128+1

#define ARGV_NUM 3
#define STAGE_POSI_NUM 0
#define COOR_ELEMENTS 2
#define COOR_ELEMENTS_RADIUS 3
#define POSI_X_COOR 0
#define POSI_Y_COOR 1
#define INITIAL_DEPTH 0


typedef struct info info_t;
struct info{
    char *Census_year;
    char *Block_ID;
    char *Property_ID;
    char *Base_property_ID;
    char *CLUE_small_area;
    char *Trading_name;
    char *Industry_code;
    char *Industry_description;
    char *x_coordinate;
    char *y_coordinate;
    char *Location;
    info_t *next;

};

typedef struct node node_t;
struct node {
    info_t *data;
    node_t *left;
    node_t *right;
    double coordinate[COOR_ELEMENTS];
    node_t *next_inradius_point;
};

typedef struct {
    node_t *root;
} tree_t;

typedef struct list list_t;
struct list{
    int count_comparison;
    char **search_key;
    char *inputRadius;  //FOR STAGE 2 ONLY
    node_t *resultPoint;
    list_t *next;
};

/* build KD tree functions */
tree_t *make_empty_tree(void);
tree_t *insert_into_tree(tree_t *tree, info_t *data);
node_t *recursive_insert(node_t *root, node_t *new, info_t *data, int depth);
int checkSameCoor(node_t *root, node_t *new);
void append_to_link_list(node_t *root, info_t *data);

/* free functions */
void free_tree(tree_t *tree);
void recursive_free_tree(node_t *root);
void free_elements(info_t *data);
void free_list(list_t *list, char *stage_input);
void free_resultPoint(node_t *resultPoint);



void separate_info(int nread, char *line, tree_t *tree, char *buffer);
info_t *convert_struct(char **tmp);
