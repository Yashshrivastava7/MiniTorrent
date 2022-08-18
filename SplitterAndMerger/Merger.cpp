#include <dirent.h>

int main(){
    int file_count = 0;
    DIR * dirp;
    struct dirent * entry;

    dirp = opendir("path"); /* There should be error handling after this */
    while ((entry = readdir(dirp)) != NULL) {
        if (entry->d_type == DT_REG) { /* If the entry is a regular file */
            file_count++;
        }
    }
    closedir(dirp);
    return 0;
}