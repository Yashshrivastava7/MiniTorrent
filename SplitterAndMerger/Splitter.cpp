#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utility>

using namespace std;
const int BUFF_SIZE = 4096;

//string split_path(string s);

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

    if (mkdir("SplittedFiles", 0777) == -1){
        cerr << "Error :  " << strerror(errno) << endl;
        return 1;
    }
    else{
        cout << "Directory created" << endl;
    }

    bool slash = true;

    string new_path = argv[3];

    if(new_path[new_path.size()]!='/'){
        slash = false;
    }

    
    for(int i=0; i<number_of_chunks; i++) {
        string c = "";
        if(slash){
            c = new_path+"SplittedFiles/"+to_string(i)+".part";
        }
        else{
            c = new_path+"/SplittedFiles/"+to_string(i)+".part";
        }
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

// string split_path(string s){
//     int last_slash_index = -1;
//     int n = s.size();
//     for(int i=n-1;i>=0;--i){
//         if(s[i]=='/'){
//             last_slash_index = i;
//             break;
//         }
//     }
//     return s.substr(0,last_slash_index);
// }