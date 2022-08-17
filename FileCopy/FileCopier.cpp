#include<iostream>
#include<unsitd.h>
#include<fcntl.h>

using namespace std;

int main(int argc,char* argv[]){
    char buffer[4096];

    int First_file,Second_file = 0;

    First_file = open(argv[1],O_RDONLY);

    Second_file = open(argv[2],O_WRONLY | O_CREAT);

    while(read(First_file,&buffer,4096)){
        write(Second_file,&buffer,4096);
    }

    cout << "Copy Successful" << endl;

    close(First_file);
    close(Second_file);

    return 0;
}

