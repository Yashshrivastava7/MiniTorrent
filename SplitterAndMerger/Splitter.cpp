#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

using namespace std;
const int BUFF_SIZE = 4096;


int main(int argc,char* argv[]){

    char buff[BUFF_SIZE];
    int first_file = open(argv[1],O_RDONLY);

    if(first_file == -1){
        cerr << "File Does not exist" << endl;
        return 1;
    }

    const char* file_name = argv[1];    

    struct stat st;
    stat(file_name,&st);
    off_t size = st.st_size;
    
    cout << "size : " << size << " " << endl;

    int size_of_chunks = stoi(argv[2]);
    int number_of_chunks = size / size_of_chunks;
    if(size%size_of_chunks!=0){
        number_of_chunks++;
    }
    cout << number_of_chunks << " " << endl;

    int read_size;
    
    int single_chunk_writes = size_of_chunks / BUFF_SIZE;

    string s = argv[1];
    
    for(int i=0;i<number_of_chunks;i++){
        string c = s+"image"+to_string(i)+".part";
        const char* ch = c.c_str();
        int temp_file = open(ch,O_WRONLY | O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        for(i=0;i<single_chunk_writes;i++){
            read_size = read(first_file,&buff,BUFF_SIZE);
            write(temp_file,&buff,read_size);
        }
        close(temp_file);
    }

    return 0;
}