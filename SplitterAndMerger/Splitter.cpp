#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

using namespace std;

int main(int argc,char* argv[]){

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

    

    return 0;
}