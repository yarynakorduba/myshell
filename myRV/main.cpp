#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <sstream>
#include <cstring>
#include <vector>
#include <boost/bind.hpp>
#include <list>
#include <algorithm>


using namespace std;

bool FileExistsDir( const std::string &Filename, char* dir )
{   chdir(dir);
    return access( Filename.c_str(), 0 ) == 0;
}
inline bool FileExistSameDir (const std::string& name) {
    return ( access( name.c_str(), F_OK ) != -1 );
}
bool findF(int numOfArgv, char** argvFindF){
    for(int i1 = 1; i1 < numOfArgv; i1++){
        if (string(argvFindF[i1]) == "-f"){
            return true;
        }
    }return false;

}
int findDir(int numOfArgv, char** argvFindDir){
    for(int i = 1; i < numOfArgv; i++) {
        DIR *dir = opendir((const char *) argvFindDir[i]);
        if(dir != NULL){
            return i;
        }
    }
    return -1;
}
int main(int num, char** argv){

    int globalIterOfArgv = 1;
    int stateOfDir = findDir(num, argv);
    char* curr = get_current_dir_name();
    cout<<(string(argv[1]));
    if((string(argv[1]) == "-h")&&(string(argv[1]) != "--help")) {
        cout<<"mrv will rename your file if two arguments are old and new name\n"
                "mrv will remove your program if first argument is the name of file and second is name of directory\n"
                "mrv -f will remove or rename files without asking for permission if files already exist"
            <<endl;

    }else if((num == 0)||(num == 2)){
        cout<<"Too few arguments"<<endl;
    }
    else if (findF(num, argv) && (stateOfDir != -1)){
        int iterOfArgvWithF = globalIterOfArgv;
        while(iterOfArgvWithF != num){
            if((string(argv[iterOfArgvWithF]) != "-f")||(iterOfArgvWithF != stateOfDir)){
                chdir(curr);
                const char* a = argv[iterOfArgvWithF];
                const char* b = argv[findDir(num, argv)];
                const char* d = "/";
                char* p=new char[strlen(b)+strlen(a)+strlen(d)+1];
                char* c=new char[strlen(b)+strlen(a)+strlen(d)+1];
                strcat(p,b);
                strcat(p,d);
                strcat(p,a);
                strcpy(c,p);
                rename(a, c);
                iterOfArgvWithF++;
            } else {
            iterOfArgvWithF++;
            }
        }
    }else if (!findF(num, argv) && (stateOfDir != -1)){
        int iterOfArgvWithOutF = globalIterOfArgv;
        while(iterOfArgvWithOutF != num){
            if(iterOfArgvWithOutF != stateOfDir){
                if(FileExistSameDir(argv[iterOfArgvWithOutF]) == 1){
                    if(FileExistsDir(argv[iterOfArgvWithOutF], argv[stateOfDir])){
                        chdir(curr);
                        //cout<<get_current_dir_name()<<endl;
                        string usrInput;
                        cout << "File " << argv[iterOfArgvWithOutF] << " already exist. Do you want to rewrite it [y/n]  ";
                        getline(cin, usrInput);
                        if (string(usrInput) == "y") {
                            const char* a = argv[iterOfArgvWithOutF];
                            const char* b = argv[num-1];
                            const char* d = "/";
                            char* p=new char[strlen(b)+strlen(a)+strlen(d)+1];
                            char* c=new char[strlen(b)+strlen(a)+strlen(d)+1];
                            strcat(p,b);
                            strcat(p,d);
                            strcat(p,a);
                            strcpy(c,p);
                            //cout<<c<<endl;
                            rename(a, c);
                            iterOfArgvWithOutF++;
                        }else{
                            iterOfArgvWithOutF++;
                        }
                    }else{
                        chdir(curr);
                        const char* a = argv[iterOfArgvWithOutF];
                        const char* b = argv[stateOfDir];
                        const char* d = "/";
                        char* p=new char[strlen(b)+strlen(a)+strlen(d)+1];
                        char* c=new char[strlen(b)+strlen(a)+strlen(d)+1];
                        strcat(p,b);
                        strcat(p,d);
                        strcat(p,a);
                        strcpy(c,p);
                        //cout<<c<<endl;
                        rename(a, c);
                        iterOfArgvWithOutF++;
                    }
                }else{
                    cout << "File " << argv[iterOfArgvWithOutF] << " does not exist"<<endl;
                    iterOfArgvWithOutF++;
                }
            }else{
                iterOfArgvWithOutF++;
            }
        }
    }else if (findF(num, argv) && (stateOfDir == -1) && (num == 4)){

        int iterOfArgvRenameWithF = globalIterOfArgv;
        vector<const char *> argsOfRename;
        while(iterOfArgvRenameWithF != num){
            if((string(argv[iterOfArgvRenameWithF]) != "-f")){
                argsOfRename.push_back((const char *&&) argv[iterOfArgvRenameWithF]);
                iterOfArgvRenameWithF++;
            }else{
                iterOfArgvRenameWithF++;
            }
        }
        if(FileExistSameDir(argsOfRename[0]) == 1){
            rename(argsOfRename[0],  argsOfRename[1]);
        }else{
            cout << "File " << argsOfRename[0] << " does not exist"<<endl;
        }

    }else if (!findF(num, argv) && (stateOfDir == -1) && (num == 3)){
        int iterOfArgvRenameWithOutF = globalIterOfArgv;
        vector<const char *> argsOfRename;
        while(iterOfArgvRenameWithOutF != num){
            if((string(argv[iterOfArgvRenameWithOutF]) != "-f")){
                argsOfRename.push_back((const char *&&) argv[iterOfArgvRenameWithOutF]);
                iterOfArgvRenameWithOutF++;
            }else{
                iterOfArgvRenameWithOutF++;
            }
        } if(FileExistSameDir(argsOfRename[0]) != 1){
            cout << "File " << argsOfRename[0] << " does not exist"<<endl;
        } else if(FileExistSameDir(argsOfRename[1]) == 1){
            string usrInput;
            cout << "File " << argsOfRename[1] << " already exist. Do you want to rewrite it [y/n]  ";
            getline(cin, usrInput);
            if (string(usrInput) == "y") {
                rename(argsOfRename[0], argsOfRename[1]);
            }
        } else{
            rename(argsOfRename[0], argsOfRename[1]);
        }
    }else{
        cout<<"No such directory"<<endl;
    }


    return 0;
}