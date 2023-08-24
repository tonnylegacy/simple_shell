#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define HIST_MAX 4096
#define HIST_FILE ".simple_shell_history"

/* Structs */
typedef struct list_s
{
    char *str;
    int num;
    struct list_s *next;
} list_t;

typedef struct info_s
{
    char *arg;
    char **argv;
    char *path;
    int argc;
    char *fname;
    list_t *env;
    list_t *history;
    list_t *alias;
    char **environ;
    int env_changed;
    int histcount;
    int linecount_flag;
    char *cmd_buf;
    int cmd_buf_type;
    int readfd;
} info_t;

/* Functions from main.c */
void populate_env_list(info_t *info);
void hsh(info_t *info, char **av);

/* Functions from builtins.c */
int hsh_cd(info_t *info);
int hsh_help(info_t *info);
int hsh_exit(info_t *info);

/* Other functions from various files */
char *convert_number(int num, int base, int is_caps);
char *_strdup(const char *str);
size_t _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strchr(const char *s, int c);
void _puts(const char *str);
void _putchar(char c);
void _eputs(const char *str);
void _eputchar(char c);
int starts_with(const char *str, const char *prefix);
void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);
ssize_t get_input(info_t *info);
void sigintHandler(int sig_num);
char **list_to_strings(list_t *head);
void free_list(list_t **head_ptr);
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
size_t list_len(const list_t *h);
size_t print_list(const list_t *h);
int bfree(void **ptr);
int is_cmd(info_t *info, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(info_t *info, char *pathstr, char *cmd);

#endif /* SHELL_H */
