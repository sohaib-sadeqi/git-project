#ifndef _HEADER_H_
#define _HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

///prototypes  :

//search for a file in a particular directory not subdirectories and determines its existence
int isExistFile(const char * dirPath, const char * fileName);

//search directory function (recursive function)
char * search_for_directory(char * current_path, char * target_directory_name);

// neogit init : initialize a repository
void neogit_init(void);

// neogit config user (local)
void local_config_user(int argc , char * argv[]);

// neogit config -global user
void global_config_user(int argc , char * argv[]);

// neogit config -global alias
void alias_global_config(int argc, char * argv[]);

//neogit config alias (local)
void alias_local_config(int argc, char * argv[]);

#endif