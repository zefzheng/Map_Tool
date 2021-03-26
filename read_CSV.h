/* These two functions files are developed by Daniel Zefeng Zheng, Aug 2020
* 
* read_CSV files are use to first read the input file, then seperate those attribute keys.
*/

#define INPUT_FILE_NAME argv[1]
#define OUTPUT_FILE_NAME argv[2]
#define ELEMENTS 11
#define FLAG_TRUE 1
#define FLAG_FALSE 0
#define EMPTY_SPACE '\r'
#define NEW_LINE '\n'
#define END_SPACE '\0'
#define COMMA ','
#define QUOTATION '"'


int quotation_appear(int *i, char *line);
void adding_to_buffer(char *line, char *buffer, int *i, int *k, int *same_string);
void from_buffer_to_tmp(char **tmp, char *buffer, int j);
void free_array(char **tmp);
