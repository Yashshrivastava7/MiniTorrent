#include<iostream>
#include<unistd.h>
#include<fcntl.h>

using namespace std;

const int BUFF_SIZE = 4096;

int main(int argc,char* argv[]){
    char buffer[BUFF_SIZE];

    int First_file,Second_file;

    First_file = open(argv[1],O_RDONLY);

    Second_file = open(argv[2],O_WRONLY | O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    int size;

    while((size=read(First_file,&buffer,BUFF_SIZE))){
        write(Second_file,&buffer,size);
    }

    cout << "Copy Successful" << endl;

    close(First_file);
    close(Second_file);

    return 0;
}