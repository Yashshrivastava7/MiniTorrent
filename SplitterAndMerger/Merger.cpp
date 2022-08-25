#include <dirent.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include <iostream>

using namespace std;

int main(int argc,char* argv[]){

    int file_count = 0;
    DIR * dirp;
    struct dirent * entry;

    dirp = opendir(argv[1]); 
    while ((entry = readdir(dirp)) != NULL) {
        if (entry->d_type == DT_REG) { 
            file_count++;
        }
    }
    closedir(dirp);
    cout << file_count << endl;
    return 0;
}