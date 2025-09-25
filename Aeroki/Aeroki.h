#ifndef __AEROKI__
#define __AEROKI__

// === Include STD Library ===
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

// === Data Type Enums ===
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_BOOLEAN,
    TYPE_ARRAY
} DataType;

// === Variable Structure ===
typedef struct {
    char name[32];
    DataType type;
    union {
        int int_val;
        double float_val;
        char string_val[256];
        bool bool_val;
        int array_val[100]; // Simple array implementation
    } value;
    int array_size; // For arrays
} Variable;

// === Function Structure ===
typedef struct {
    char name[32];
    char body[1024];
    char params[10][32]; // Up to 10 parameters
    int param_count;
} Function;

// === Core Functions ===
void __Ark_Shell();
void __Ark_Interpreted(FILE *__src_file);
void clear_memory();

// === Variable Management ===
Variable* get_variable_ptr(const char *name);
int get_int_variable(const char *name);
double get_float_variable(const char *name);
char* get_string_variable(const char *name);
bool get_bool_variable(const char *name);
void set_int_variable(const char *name, int value);
void set_float_variable(const char *name, double value);
void set_string_variable(const char *name, const char *value);
void set_bool_variable(const char *name, bool value);

// === Command Handlers ===
void handle_hai(char *line);        // Variable assignment
void handle_ha(char *line);         // Display/calculate
void handle_rubka(char *line);      // Input
void handle_tha(char *line);        // If statement
void handle_loop(char *line);       // Loop structures
void handle_function_def(char *line); // Function definition
void handle_function_call(char *line); // Function call
void handle_comment(char *line);    // Comments
void handle_print(char *line);      // Print statement
void handle_file_io(char *line);    // File operations
void handle_help(char *line);       // Help command

// === Utility Functions ===
bool evaluate_condition(const char *condition);
void execute_block(const char *block);
int compare_values(const char *left, const char *op, const char *right);
double math_function(const char *func, double val);
char* string_function(const char *func, const char *str);
void skip_to_matching_brace(FILE *file, char *current_line);
void ltrim(char *str);
void rtrim(char *str);
void trim(char *str);
bool is_number(const char *str);
bool is_float(const char *str);

#endif