#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <sstream>
#include <cstring>
#include <vector>
#include <boost/bind.hpp>
#include <list>
#include <algorithm>

#include "sh_tools.h"


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
	string cur_dir = my_get_current_dir_name(); // Див. комент щодо цієї ф-ції в myLS
    const char* curr = cur_dir.data();

    if((num == 0)||(num == 1)) {
        cout << "Too few arguments" << endl;
    }else if((string(argv[1]) == "-h")&&(string(argv[1]) != "--help")) {
        cout<<"The order of the arguments is not significant \n"
                "\n"
                "Examples and explaining: \n"
                "\n"
                "mrv current_name_of_file desired_name_of_file -- will rename your file with asking the permission if "
                "file that has the same name as desired_name_of_file already exist\n"
                "mrv -f current_name_of_file desired_name_of_file -- will rename your file without asking the permission if "
                "file that has the same name as desired_name_of_file already exist\n"
                "mrv current_name_of_file name_of_directory -- will remove your file to the desired directory "
                "with asking the permission if file already exist in this directory\n"
                "mrv -f current_name_of_file name_of_directory -- will remove your file to the desired directory "
                "without asking the permission if file already exist in this directory\n"
            <<endl;
		//! Вивели хелп і виходимо:
		return 0;
    }
	//! УВАГА! Структура коду потворна -- просканувати опції слід на початку, зберегти у якихось 
	//! прапорцях, а вже потім  -- використовувати їх. Імена файлів, отримані при тому, скласти окремо. 
	//! От як Ваш же stateOfDir.
	//! Див, також  mls (там не ідеально, але таки краще). 
	//! Плюс, копіпасти стільки...
	
    else if (findF(num, argv) && (stateOfDir != -1)){
        int iterOfArgvWithF = globalIterOfArgv;
        while(iterOfArgvWithF != num){
            if((string(argv[iterOfArgvWithF]) != "-f")||(iterOfArgvWithF != stateOfDir)){
                chdir(curr); 
				//! От що за імена?!
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
