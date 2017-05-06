#include <iostream>
#include <sys/stat.h>
#include <zconf.h>


using namespace std;

inline bool exists_test2 (const std::string& name) {
    return ( access( name.c_str(), F_OK ) != -1 );
}

int main(int num, char **argv) {
    //                                                     cout<<argv[1]<<endl;
        if(num == 1){
            cout<<"mkdir: missing operand"<<"\n"<<
                "Try 'mkdir --help' for more information."<<endl;
        }else{
            //const char* curr = get_current_dir_name();
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