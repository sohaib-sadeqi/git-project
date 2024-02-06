//GIT project
#include "header.h"


char current_working_directory[256];
const char global_path[] = "/mnt/c/git-project";
const char global_config_user_path[] = "/mnt/c/git-project/global-config-user";

// #define INT_MAIN
#ifdef INT_MAIN
int main() {
    int argc = 2;
    char * argv[] = {"neogit", "config"};
#else
int main(int argc, char * argv[]) {

#endif

    // printf("\033[31m this is sample red text \033[0m \n");  red printing

    if( argc > 1 && strcmp(argv[0], "neogit") == 0 ) {
        
        getcwd(current_working_directory, 256 * sizeof(char)); /*determining current working directory*/

        //shortcut command
        if( argc == 2  &&  strcmp(argv[1], "init") != 0  
            &&  strcmp(argv[1], "log") != 0  &&  strcmp(argv[1], "status") != 0  
            &&  strcmp(argv[1], "branch") != 0 ) {

            char local_alias_path[512];
            const char local_alias[] = "alias.txt";
            const char global_alias[] = "global-alias.txt";

            sprintf(local_alias_path, "%s/%s", current_working_directory, "neogit/gitconfiglocal");
            
            //At first search the shortcut command in local alias
            if(chdir(local_alias_path) == 0  && isExistFile(local_alias_path, local_alias)){
                // open the alias.txt --> print it to a string --> strstr(string, argv[1])
                FILE * local_alias_ptr = fopen(local_alias, "r");
                char str[1024];
                if(fread(str, sizeof(char), 1023, local_alias_ptr) > 1) {

                    char * found_alias_ptr = malloc(1024);
                    //alias name might be similar to other commands after ':' So we have to search first characters
                    char *argv1_temp = argv[1];
                    strcat(argv1_temp, ":");

                    if((found_alias_ptr = strstr(str, argv1_temp)) != NULL) {
                        strtok(found_alias_ptr, ":");  /*The method of storing the alias and command: "alias:command"
                        until here the "found_alias_ptr" string starts from command -->e.g. add:neogit add . --> 
                        found_alias_ptr = "neogit add . 'and the following text file' "*/
                        char * tok = strtok(NULL, " ");
                        // strcpy(argv[0], tok);  --> Doesn't need that. because argv[0] = "neogit" and the first token is "neogit"
                        for(int i = 1; 0; i++) {
                            tok = strtok(NULL, " ");
                            if(strstr(tok, "\n") != NULL /*there is '\n' here*/) {
                                char * another_tok = strtok(tok, "\n");
                                strcpy(argv[i], another_tok);
                                break;
                            }
                            strcpy(argv[i], tok);
                        }
                    }
                }
            }
            //Then search in global alias
            else if(chdir(global_path) == 0  &&  isExistFile(global_path, global_alias)) {
                //open the alias file --> read the file and put it into a string --> strstr(string, argv[1])
                FILE * global_alias_ptr = fopen(global_alias, "r");
                if(global_alias_ptr != NULL) {
                    char str[1024];
                    if(fread(str, sizeof(char), 1023, global_alias_ptr) > 1) {

                        char * found_alias_ptr = malloc(1024);
                        if((found_alias_ptr = strstr(str, argv[1])) != NULL) {
                            if(strtok(found_alias_ptr, ":") != NULL) {
                                /*The method of storing the alias and command: "alias:command"
                                til here the "found_alias_ptr" string starts from command -->e.g. add:neogit add . --> 
                                found_alias_ptr = "neogit add . 'and the following text file' "*/
                                char * tok = strtok(NULL, " ");
                                
                                for(int i = 1; i < argc; i++) {
                                    tok = strtok(NULL, " ");
                                    argc++;
                                    argv[i] = (char *)malloc(64);
                                    if(strstr(tok, "\n") != NULL /*there is '\n' here*/) {
                                        char * another_tok = strtok(tok, "\n");
                                        strcpy(argv[i], another_tok);
                                        break;
                                    }
                                    strcpy(argv[i], tok);
                                }
                            }
                        }
                    }
                }
            }
            chdir(current_working_directory);
        }

        ///neogit config
        if( strcmp(argv[1], "config") == 0  &&  argc > 3) {
            
            if( strcmp(argv[2], "-global") == 0  &&  argc == 5 ) {
                if(strncmp(argv[3], "user", 4) == 0) {
                    global_config_user(argc, argv);
                    return EXIT_SUCCESS;
                }
                else if(strncmp(argv[3], "alias", 5) == 0) {
                    alias_global_config(argc, argv);
                    return EXIT_SUCCESS;
                }
                else {
                    printf("\033[31m Invalid command\n"
                           "usage: neogit config -global <mode> <configure-to> \033[0m \n");
                    return EXIT_FAILURE;
                }
            }
            if( argc == 4) {
                if(strncmp(argv[2], "user", 4) == 0) {
                    local_config_user(argc, argv);
                    return EXIT_SUCCESS;
                }
                else if(strncmp(argv[2], "alias", 4) == 0) {
                    alias_local_config(argc, argv);
                    return EXIT_SUCCESS;
                }
                else {
                    printf("\033[31m Invalid command\n"
                           "usage: neogit config <mode> <configure-to> \033[0m \n");
                    return EXIT_FAILURE;
                }
                
            }
        }
        ///neogit init
        if( strcmp(argv[1], "init") == 0 ){
            neogit_init();
            return EXIT_SUCCESS;
        }
        ///neogit add
        if( strcmp(argv[1], "add") == 0 ){

            return EXIT_SUCCESS;
        }
        ///neogit status
        if( strcmp(argv[1], "status") == 0 ){

            return EXIT_SUCCESS;
        }
        ///neogit reset
        if( strcmp(argv[1], "reset") == 0 ) {

            return EXIT_SUCCESS;
        }
        ///neogit commit
        if( strcmp(argv[1], "commit") == 0 ) {
            return EXIT_SUCCESS;
        }
        ///neogit log
        if( strcmp(argv[1], "log") == 0 ) {
            return EXIT_SUCCESS;
        }
        ///neogit branch
        if( strcmp(argv[1], "branch") == 0 ) {

            return EXIT_SUCCESS;
        }
        ///neogit checkout
        if( strcmp(argv[1], "checkout") == 0 ) {

            return EXIT_SUCCESS;
        }
        else {
            printf("\033[31m usage: neogit [command] <following-command>\n"
                   "command: add, checkout, commit, log, branch, reset, status, init, config \033[0m \n");
            return EXIT_FAILURE;
        }

    }
    else{
        printf("\033[31m Invalid input\n" "usage: neogit [command] \033[0m \n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

//search for a file in a particular directory not subdirectories and determines its existence
    int isExistFile(const char * dirPath, const char * fileName) {
        //open the directory and search for intended file. if exists return value is 1 and if not return value is 0.
        struct dirent * directory_files;
        DIR * dirName = opendir(dirPath);
        while((directory_files = readdir(dirName)) != NULL) {
            if(strcmp(directory_files->d_name, fileName) == 0) {
                return 1;
            }
        }
        return 0;
    }

//search directory function (recursive function)
    char * search_for_directory(char * current_path, char * target_directory_name) {
        DIR * dirPtr = opendir(current_path);
        if(dirPtr != NULL) {
            struct dirent * entry;
            while((entry = readdir(dirPtr)) != NULL) {
                if(entry->d_type == DT_DIR) { /* this condition used to check the entry if it is a directory or not */
                    
                    if(strcmp(entry->d_name, target_directory_name) == 0) {
                        
                        char * foundPath = malloc(256);  //don't forget to free the allocated memory
                        if(foundPath != NULL) {
                            sprintf(foundPath, "%s/%s", current_path, target_directory_name);
                            closedir(dirPtr);
                            return foundPath; 
                        }
                        else{
                            perror("malloc error in search for directory function\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                    else if(strcmp(entry->d_name, ".") != 0  &&  strcmp(entry->d_name, "..") != 0) {
                        
                        char nextPath[512];
                        snprintf(nextPath, sizeof(nextPath), "%s/%s", current_path, entry->d_name);
                        char * foundPath = search_for_directory(nextPath, target_directory_name);
                        if(foundPath != NULL) {
                            closedir(dirPtr);
                            return foundPath;
                        }
                    }
                }
            }
            closedir(dirPtr);
            return NULL;

        }
        else {
            printf("\033[31m search function error \033[0m \n");
            return NULL;
        }
    }

// neogit init
    void neogit_init(void) {
        // As soon as the "neogit" called, 
        //                                checking if there isn't neogit directory in parent directory 
        //                                else a directory is made
        char current_path[256];
        getcwd(current_path, 256);
        char current_path_temp[300];
        
        strcpy(current_path_temp, current_path);
        strcat(current_path, "/.neogit");
        
        
        while(strcmp(current_path_temp, "/") != 0) {
            if (search_for_directory(current_working_directory, ".neogit") != NULL) {
                printf("\033[31mYou have initialized a repository here or in the parent directories\n\033[0m");
                chdir(current_working_directory);
                exit(EXIT_FAILURE);
            }
            if(chdir("..") == 0)
                continue;
            else{
                perror("change directory failed in neogit_init function\n"); 
                exit(EXIT_FAILURE);
            }
            
        }
        chdir(current_working_directory);
        

        strcpy(current_path_temp, current_path);
        if(mkdir(current_path, 0755) == 0) {
            chdir(current_path);

            // In the "git" directory we need a directory to save local configurations
            strcat(current_path_temp, "/gitconfiglocal");
            mkdir(current_path_temp, 0755);
            chdir(current_path_temp);

            // In the "gitconfiglocal" directory we need a file to save shortcut commands here
            const char * aliasFile = "alias.txt";
            FILE * aliasFilePtr = fopen(aliasFile, "w"); /* We just want to make this file. So the mode of openning is "w". */
            fclose(aliasFilePtr);

            //In the "git" direcrory there is a master branch
            chdir(current_path);            
            strcat(current_path, "/master");
            mkdir(current_path, 0755);
            chdir(current_path);

            sprintf(current_path_temp, "%s/%s", current_path, "untracked");
            mkdir(current_path_temp, 0755);

            sprintf(current_path_temp, "%s/%s", current_path, "staged");
            mkdir(current_path_temp, 0755);

            sprintf(current_path_temp, "%s/%s", current_path, "commit");
            mkdir(current_path_temp, 0755);
        }
        else {
            perror("\033[31mmaking directory failed in neogit_init function\033[0m\n");
        }
    }


// neogit config user (local)
    void local_config_user(int argc, char *argv[]) {
        //check if repository created. check this for all commands
        char * newPath = malloc(256);
        newPath = search_for_directory(current_working_directory, ".neogit");
        
        if(newPath != NULL) {
            strcat(newPath, "/gitconfiglocal");
            if(chdir(newPath) == 0) {
                // change directory to "gitconfiglocal"
                if(strcmp(argv[2], "user.name") == 0) {
                    const char * userName = "userName.txt";
                    FILE * user_name_text_file = fopen(userName, "w");
                    if( fprintf(user_name_text_file, "%s\n", argv[3]) > 0 ) {
                        fclose(user_name_text_file);
                    }
                    else {
                        perror("writing (name) failed. in local config user function\n");
                        fclose(user_name_text_file);
                        exit(EXIT_FAILURE);
                    }
                }
                else if(strcmp(argv[2], "user.email") == 0) {
                    const char * userEmail = "userEmail.txt";
                    FILE * user_email_text_file = fopen(userEmail, "w");
                    if(fprintf(user_email_text_file, "%s\n", argv[3]) > 0) {
                        fclose(user_email_text_file);
                    }
                    else {
                        perror("writing (email) failed. in local config user function\n");
                        fclose(user_email_text_file);
                        exit(EXIT_FAILURE);
                    }
                } else {
                    printf("\033[31m Invalid command\n"
                           "usage: neogit config user.<name/email> <name/email> \033[0m\n");
                    exit(EXIT_FAILURE);
                }

            } else {
                perror("chdir in local config user failed\n");
                exit(EXIT_FAILURE);
            }

        } else {
            printf("\033[31m                --:: Warning ::-- \033[0m\n" 
                   "\033[31m        Please initialize a repository first\033[0m\n"
                   "\033[31mtype \"git init\" command to initialize a repository\033[0m\n");
            exit(EXIT_FAILURE);
        }
    }

// neogit config -global user
    void global_config_user(int argc,char * argv[]) {
        char global_config_user_path[] = "/mnt/c/git-project/global-config-user";
        if(chdir(global_config_user_path) == 0) {
            if(strcmp(argv[3], "user.name") == 0) {
                FILE * global_config_ptr = fopen("userName.txt", "w");
                fprintf(global_config_ptr, "%s\n", argv[4]);
                fclose(global_config_ptr);
            }
            else if(strcmp(argv[3], "user.email") == 0) {
                FILE * global_config_ptr = fopen("userEmail.txt", "w");
                fprintf(global_config_ptr, "%s\n", argv[4]);
                fclose(global_config_ptr);
            }
            else {
                printf("\033[31mInvalid command\n"
                       "usage: neogit config -global user.<name/email> <name/email>\033[0m\n");
            }
            
        }
        else {
            printf("\033[31mchange directory failed (in function global_config_user) \033[31m\n");
            exit(EXIT_FAILURE);
        }
    }

// neogit config -global alias
    void alias_global_config(int argc, char * argv[]){
        if( chdir(global_path) == 0 ) {
            //format of storing aliases is: alias:command
            FILE * global_alias_fptr = fopen("global-alias.txt", "a");
            // char * temp = strtok(argv[3], ".");
            fprintf(global_alias_fptr, "%s:%s\n", argv[3]+6, argv[4]);
            fclose(global_alias_fptr);
        }
        else {
            perror("change directory failed (alias_global_config)\n");
            exit(EXIT_FAILURE);
        }
    }



//neogit config alias (local)
    void alias_local_config(int argc, char * argv[]){

    }


