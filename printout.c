#include "buildTree.h"
#include "printout.h"

/* print out the Map1 outcome list  */
void map1_printout_to_file(FILE *output_file, list_t *outcome_list) {
    list_t *node = outcome_list;
    /* print out the nearest point to file*/
    while(node != NULL) {
        info_t *info = node->resultPoint->data;
        while (info) {
            fprintf(output_file, "%s %s %s", node->search_key[0], node->search_key[1], "-->");
            fprintf(output_file, "%s %s %s ", "Census year:", info->Census_year, "||");
            fprintf(output_file, "%s %s %s ", "Block ID:", info->Block_ID, "||");
            fprintf(output_file, "%s %s %s ", "Property ID:", info->Property_ID, "||");
            fprintf(output_file, "%s %s %s ", "Base property ID:", info->Base_property_ID, "||");
            fprintf(output_file, "%s %s %s ", "CLUE small area:", info->CLUE_small_area, "||");
            fprintf(output_file, "%s %s %s ", "Trading name:", info->Trading_name, "-->");
            fprintf(output_file, "%s %s %s ", "Industry (ANZSIC4) code:", info->Industry_code, "||");
            fprintf(output_file, "%s %s %s ", "Industry (ANZSIC4) description:", info->Industry_description, "||");
            fprintf(output_file, "%s %s %s ", "x coordinate:", info->x_coordinate, "||");
            fprintf(output_file, "%s %s %s ", "y coordinate:", info->y_coordinate, "||");
            fprintf(output_file, "%s %s %s \n", "Location:", info->Location, "||");
            info = info->next;
        }
        /* print out the count comparsion numnber */
        printf("%s %s -- > %d\n",node->search_key[0], node->search_key[1], node ->count_comparison);
        node = node->next;
    }
}

/* print out the Map2 outcome list */
void map2_printout_to_file(FILE *output_file, list_t *outcome_list) {
    list_t *node = outcome_list;

    /* no point is in the radius */
    while(node != NULL){
        node_t *one_point = node->resultPoint;
        if (one_point == NULL) {
            fprintf(output_file, "%s %s %s %s %s\n", node->search_key[0], node->search_key[1], node->inputRadius, "-->", "NOTFOUND");
        }
        /* print out the points in the radius to file*/
        else {
            while(one_point != NULL){
                info_t *info = one_point->data;
                while (info != NULL) {
                    fprintf(output_file, "%s %s %s %s", node->search_key[0], node->search_key[1], node->inputRadius, "-- >");
                    fprintf(output_file, "%s %s %s ", "Census year:", info->Census_year, "||");
                    fprintf(output_file, "%s %s %s ", "Block ID:", info->Block_ID, "||");
                    fprintf(output_file, "%s %s %s ", "Property ID:", info->Property_ID, "||");
                    fprintf(output_file, "%s %s %s ", "Base property ID:", info->Base_property_ID, "||");
                    fprintf(output_file, "%s %s %s ", "CLUE small area:", info->CLUE_small_area, "||");
                    fprintf(output_file, "%s %s %s ", "Trading name:", info->Trading_name, "-->");
                    fprintf(output_file, "%s %s %s ", "Industry (ANZSIC4) code:", info->Industry_code, "||");
                    fprintf(output_file, "%s %s %s ", "Industry (ANZSIC4) description:", info->Industry_description, "||");
                    fprintf(output_file, "%s %s %s ", "x coordinate:", info->x_coordinate, "||");
                    fprintf(output_file, "%s %s %s ", "y coordinate:", info->y_coordinate, "||");
                    fprintf(output_file, "%s %s %s\n", "Location:", info->Location, "||");
                    info = info->next;
                }
                one_point = one_point->next_inradius_point;
            }
        }

        /* print out the count comparsion numnber */
        printf("%s %s %s --> %d\n",node->search_key[0], node->search_key[1], node->inputRadius, node ->count_comparison);
        node = node->next;
    }
}
