#include <dirent.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include <iostream>

using namespace std;
const int BUFF_SIZE = 4096;

int main(int argc,char* argv[]){

    char buff[BUFF_SIZE];

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
    string path_to_splitted_files = argv[1];

    string file_prefix = argv[2];

    string merged_file_path = argv[3];

    int read_size;

    int merged_file = open(argv[3],O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    for(int i=0;i<file_count;i++){
        string c = path_to_splitted_files+to_string(i)+".part";
        const char* ch = c.c_str();
        int temp_file = open(ch,O_RDONLY);
        while((read_size=read(temp_file,&buff,BUFF_SIZE))){
            write(merged_file,&buff,read_size);
        }
        close(temp_file);
    }
    close(merged_file);

    return 0;
}