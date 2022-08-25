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
    int last_slash = 0;
    //efficient approach: start from the back
    for(int i=0;i<s.size();i++){
        if(s[i]=='/'){
            last_slash = i;
        }
    }
    string processed = s.substr(0,last_slash+1);

    cout << processed << endl;
    
    for(int i=0; i<number_of_chunks; i++) {
        cerr << "I = " << i << endl;
        string c = processed+"image"+to_string(i)+".part";
        const char* ch = c.c_str();
        int temp_file = open(ch, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        for(int j=0;j<single_chunk_writes;j++){
            read_size = read(first_file,&buff,BUFF_SIZE);
            write(temp_file,&buff,read_size);
        }
        close(temp_file);
    }

    close(first_file);

    return 0;
}