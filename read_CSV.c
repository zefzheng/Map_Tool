#include "buildTree.h"
#include "read_CSV.h"

/* to separate every attribute/element from a one line */
void
separate_info(int nread, char *line, tree_t *tree, char *buffer) {
    int i = 0, j = 0, k = 0;
    int same_string = FLAG_TRUE;

    /* temporary array to store info from buffer */
    char **tmp = NULL;
    tmp = (char **)malloc(sizeof(char *) * (ELEMENTS));
    assert(tmp);

    for(i = 0; i < nread+1; i++) {
        /* checking whether it is in a string of attribute/element or not */
        if (same_string) {
            same_string = quotation_appear(&i, line);
        }

        /* store in to buffer if the comma appear and one attribute/element is finshed */
        if ((same_string) && ((line[i] == COMMA ) || (line[i] == NEW_LINE) || (line[i] == EMPTY_SPACE) || (line[i] == END_SPACE))) {
            buffer[k] = END_SPACE;
            k = 0;

            from_buffer_to_tmp(tmp, buffer, j);
            j++;

            /* prevent the last line is an empty line */
            if ((line[i] == NEW_LINE) ||(line[i] == EMPTY_SPACE) || (line[i] == END_SPACE)) {
                break;
            }

        }
        else {
            adding_to_buffer(line, buffer, &i, &k, &same_string);
        }
    }

    info_t *one_info = NULL;
    one_info = convert_struct(tmp);
    insert_into_tree(tree, one_info);
    free_array(tmp);
}

/* Check whether it's in a attribute/element, to prevent mistakes of comma/double quotation */
int
quotation_appear(int *i, char *line) {
    if(line[*i] == QUOTATION) {
        *i = *i + 1;
        return FLAG_FALSE;
    }
    else {
        return FLAG_TRUE;
    }
}

/* store each character of one info into buffer to sure the size */
void
adding_to_buffer(char *line, char *buffer, int *i, int *k, int *same_string) {
    int n = *k;
    int count_quote = 1;
    int output_quotation = 0;

    if (line[*i] != QUOTATION) {
        buffer[*k] = line[*i];
        *k += 1;
        return;
    }

    for (; line[*i+1] == QUOTATION; *i += 1) {
        count_quote++;
    }

    if (count_quote == 1) {
        *same_string = FLAG_TRUE;
        return;
    }
    else if ((count_quote % 2) == 0) {
        output_quotation = count_quote / 2;
    }
    else {
        output_quotation = (count_quote - 1) / 2;
        *same_string = FLAG_TRUE;
    }

    for (; *k < output_quotation + n; *k += 1) {
        buffer[*k] = QUOTATION;
    }
}

/* transfer info from buffer to tmp */
void
from_buffer_to_tmp(char **tmp, char *buffer, int j) {
    tmp[j] = (char *)malloc(sizeof(char) * strlen(buffer)+1);
    assert(tmp[j]);
    strcpy(tmp[j], buffer);
}

/* Dynamic allocate space for each attributes to store in temp array */
info_t
*initialise_struct(char **tmp) {
    info_t *one_info = NULL;

    one_info = (info_t *)malloc(sizeof(info_t));
    assert(one_info);
    one_info->Census_year = (char *)malloc(sizeof(char) * strlen(tmp[CENSUS_YEAR])+1);
    assert(one_info->Census_year);
    one_info->Block_ID = (char *)malloc(sizeof(char) * strlen(tmp[BLOCK_ID])+1);
    assert(one_info->Block_ID);
    one_info->Property_ID = (char *)malloc(sizeof(char) * strlen(tmp[PROPERTY_ID])+1);
    assert(one_info->Property_ID);
    one_info->Base_property_ID = (char *)malloc(sizeof(char) * strlen(tmp[BASE_PROPERTY_ID])+1);
    assert(one_info->Base_property_ID);
    one_info->CLUE_small_area = (char *)malloc(sizeof(char) * strlen(tmp[CLUE_SMALL_AREA])+1);
    assert(one_info->CLUE_small_area);
    one_info->Trading_name = (char *)malloc(sizeof(char) * strlen(tmp[TRADING_NAME])+1);
    assert(one_info->Trading_name);
    one_info->Industry_code = (char *)malloc(sizeof(char) * strlen(tmp[INDUSTRY_CODE])+1);
    assert(one_info->Industry_code);
    one_info->Industry_description = (char *)malloc(sizeof(char) * strlen(tmp[INDUSTRY_DESCRIPTION])+1);
    assert(one_info->Industry_description);
    one_info->x_coordinate = (char *)malloc(sizeof(char) * strlen(tmp[X_COOR])+1);
    assert(one_info->x_coordinate);
    one_info->y_coordinate = (char *)malloc(sizeof(char) * strlen(tmp[Y_COOR])+1);
    assert(one_info->y_coordinate);
    one_info->Location = (char *)malloc(sizeof(char) * strlen(tmp[LOCATION])+1);
    assert(one_info->Location);

    one_info->next = NULL;

    return one_info;
}

/* transfer info from tmp to struct */
info_t
*convert_struct(char **tmp) {
    info_t *one_info = initialise_struct(tmp);
    strcpy(one_info->Census_year, tmp[CENSUS_YEAR]);
    strcpy(one_info->Block_ID, tmp[BLOCK_ID]);
    strcpy(one_info->Property_ID, tmp[PROPERTY_ID]);
    strcpy(one_info->Base_property_ID, tmp[BASE_PROPERTY_ID]);
    strcpy(one_info->CLUE_small_area, tmp[CLUE_SMALL_AREA]);
    strcpy(one_info->Trading_name, tmp[TRADING_NAME]);
    strcpy(one_info->Industry_code, tmp[INDUSTRY_CODE]);
    strcpy(one_info->Industry_description, tmp[INDUSTRY_DESCRIPTION]);
    strcpy(one_info->x_coordinate, tmp[X_COOR]);
    strcpy(one_info->y_coordinate, tmp[Y_COOR]);
    strcpy(one_info->Location, tmp[LOCATION]);

    return one_info;
}

/* free memory of tmp array after copied */
void
free_array(char **tmp) {
    int i;
    for(i = 0; i < ELEMENTS; i++) {
        free(tmp[i]);
    }
    free(tmp);
}
