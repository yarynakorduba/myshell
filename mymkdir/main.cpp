#include <iostream>
#include <sys/stat.h>
#include <zconf.h>


using namespace std;

inline bool exists_test2 (const std::string& name) {
    return ( access( name.c_str(), F_OK ) != -1 );
}

int main(int num, char **argv) {

        if(num == 1){
            cout<<"mmkdir: missing operand"<<"\n"<<
                "Try 'mmkdir --help or mmkdir -h' for more information."<<endl;
        }else{
            int i = 1;
            while (i != num){
                if(exists_test2(argv[i]) == 1){
                    cout<<"mmkdir: cannot create directory "<<argv[i]<<" : File exists"<<endl;
                    i++;
                }else if((string(argv[1]) == "-h")||(string(argv[1]) == "--help")){
                    cout<<"mmkdir will create new directory"<<endl;
                    i++;
                }else{
                    mkdir(argv[i], 0777);
                    i++;
                }
            }
        }
    
        return 0;
}
