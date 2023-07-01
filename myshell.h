#ifndef MYSHELL_H
#define MYSHELL_H

#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h> 
#include <string.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h> 

#include "macros.h"

/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_program;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;

             /*To add, remove or show aliases*/
int output_alias(data_of_program *data, char *alias);

                  /*To get the alias*/
char *fetch_alias(data_of_program *data, char *name);

                  /*To add alias*/
int write_alias(char *string_alias, data_of_program *data);

       /*To allow to read a line from command prompt*/
int _getlines(data_of_program * data);

   /*To check for logical operators and split*/
int check_ops_logic(char *array_of_commands[], int x,
		char array_of_operators[]);

    /*exit program with status*/
int exit_builtin(data_of_program *data);

   /*change working dir*/
int cd_builtin(data_of_program *data);

      /*set working dir*/
int set_working_directory(data_of_program *data, char *new_dir);

      /*show environment of shell*/
int help_builtin(data_of_program *data);

       /*aliases*/
int alias_builtin(data_of_program *data);

    /*search and execute builtins match*/
int list_of_builtins(data_of_program *data);

    /*show shell environment*/
int builtin_environment(data_of_program *data);

        /*set env*/
int builtin_set_environment(data_of_program *data);

       /*unset env*/
int builtin_unset_environment(data_of_program *data);

      /*To free an array of pointers*/
void free_array_of_pointers(char **array);

     /*To free all fields of a program*/
void free_all_data(data_of_program *data);

     /*To free the fields needed for each loop of a program*/
void free_recurrent_data(data_of_program *data);

     /*To execute command*/
int execution(data_of_program *data);

    /*To expand variables*/
void variables_expansion(data_of_program *data);

    /*To expand alias*/
void alias_expansion(data_of_program *data);

    /*To append to buffer*/
int add_to_buffer(char *buffer, char *strings);

    /*To check if file exists*/
int check_files(char *file_path);

    /*To find program*/
int finding_program(data_of_program *data);

    /*To tokenize*/
char **tokenize_paths(data_of_program *data);

    /*To converts a number to a string type*/
void long_to_string(long number, char *string, int base);

    /*To convert a string of digits to an integer*/
int _atoi(char *s);

    /*To count the coincidences of character in string*/
int count_characters(char *string, char *character);

    /*To write an array of chars in the standard error*/
int _print_error(int errorcode, data_of_program *data);

    /*To write an array of chars in the standard error*/
int _printe(char *string);

     /*To write an array of chars in the standard output*/
int _print(char *string);

     /*To return the length of a null terminated string*/
int str_length(char *str);

     /*To duplicate a string*/
char *str_duplicate(char *str);

      /*To Compare two strings*/
int str_compare(char *str1, char *str2, int number);

      /*To concatenates two strings*/
char *str_concat(char *str1, char *str2);

     /*To reverse a string*/
void str_reverse(char *str);

      /*To initialize the variables of the program*/
int main(int argc, char *argv[], char *env[]);

     /*To print the prompt in a new line when the signal SIGINT*/
void handle_ctrl_c(int opr UNUSED);

       /*To inicialize the struct with the info of the program*/
void inicialize_data(data_of_program *data, int argc, char *argv[], char **env);

      /*An infinite loop that shows the prompt*/
void sisifo(char *prompt, data_of_program *data);

     /*To separate strings with delimiters*/
char *_strtok(char *line, char *delim);

char *environment_get_key(char *key, data_of_program *data);

int environment_set_key(char *key, char *value, data_of_program *data);

int environment_remove_key(char *key, data_of_program *data);

void print_environment(data_of_program *data);

void tokenize(data_of_program *data);

#endif /* MYSHELL_H */
