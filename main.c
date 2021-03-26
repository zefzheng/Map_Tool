/* Program written by Daniel Zefeng Zheng, Sep 2020
* Student ID: 1111121
*
* This program is to search the nearest coordinate and which the coordinates inside the input radius, from a specific input data file (A file only from the City of Melbourne Census of Land Use and Employment (CLUE) ).
*
* For searching the nearest coordinate (MAP 1): User needs to input two no more than 10 digits coordinates as a KEY file to search for the nearest store. And the program will output that store's information of businesses in Melbourne. (e.g.: 144.967058 -37.817313)
* For searching coordinates in a radius (MAP 2): User also needs to input the same format coordinates. And the radius (e.g.: 144.967058 -37.817313 0.0005).
*
* To run this program, type:
*  make all
*       ./map1 CLUEdata2018_random.csv outputfile.txt < key.txt
*  OR:  ./map2 CLUEdata2018_random.csv outputfile.txt < key.txt
*
* This program including 10 files, which are: main.c, buildTree.h, buildTree.c, searchData.h, searchData.c, printout.h, printout.c, read_CSV.h, read_CSV.c and Makefile.
*
* Attrubution of some funtion from all files:
* "make_empty_tree", "insert_into_tree", "recursive_insert",
* "checkSameCoor", "append_to_link_list", "recursive_free_tree"
*  are modified from  "Programming, Problem Solving, and Abstraction with C", written by Alistair Moffat.
*

* Hope you have a nice reading/marking time!
* Cheers!
*/

#include "buildTree.h"
#include "read_CSV.h"
#include "searchData.h"
#include "printout.h"

/* This main function is a general main function for both Map1 adn Map2 */

int
main(int argc, char **argv) {
    /* open the input file and check whether it is vaild */
    FILE *file;
    if ((file = fopen(INPUT_FILE_NAME, "r")) == NULL || argc < ARGV_NUM){
        printf("Cannot open %s\n", INPUT_FILE_NAME);
        fprintf(stderr, "Incorrect arguments\n");
        fprintf(stderr, "Run in the form\n");
        fprintf(stderr, "\tdict datafile outputfile < inputfile\n");
        exit(EXIT_FAILURE);
    }

    tree_t *tree = NULL;
    tree = make_empty_tree();
    size_t len = 0;
    int nread = 0;
    char *line = NULL;
    char buffer[ELEMENTS_CHARS];

    /* get the waste title line */
    getline(&line, &len, file);

    /* reading data */
    while (getline(&line, &len, file) != EOF) {
        nread = (int)strlen(line);
        separate_info(nread, line, tree, buffer);
    }

    free(line);
    fclose(file);

    /* search for the keys and output outcomes */
    FILE *output_file;
    if ((output_file = fopen(OUTPUT_FILE_NAME, "w")) == NULL) {
       printf("Cannot open %s\n", OUTPUT_FILE_NAME);
       exit(EXIT_FAILURE);
    }

    list_t *outcome_list;
    /* searching and printing for stage one */
    if (!strcmp(argv[STAGE_POSI_NUM], "./map1")) {
        outcome_list = map1_searchRecord(tree);
        map1_printout_to_file(output_file, outcome_list);
    }
    /* searching and printing for stage two */
    else {
        outcome_list = map2_searchRecord(tree);
        map2_printout_to_file(output_file, outcome_list);
    }

    fclose(output_file);
    free_tree (tree);

    free_list(outcome_list, argv[STAGE_POSI_NUM]);
}
