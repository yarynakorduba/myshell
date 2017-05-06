#include <iostream>
#include <dirent.h>
#include <cstring>
#include <unistd.h>
#include <wait.h>


using namespace std;

bool findF(int numOfArgv, char** argvFindF){
    for(int i1 = 1; i1 < numOfArgv; i1++){
        if (string(argvFindF[i1]) == "-f"){
            return true;
        }
    }return false;

}

bool findR(int numOfArgv, char** argvFindF){
    for(int i1 = 1; i1 < numOfArgv; i1++){
        if (string(argvFindF[i1]) == "-R"){
            return true;
        }
    }return false;

}

bool findDir(const char* fileForCheckingDir){
        DIR *dir = opendir(fileForCheckingDir);
    return dir != NULL;

}
inline bool FileExistSameDir (const std::string& name) {
    return ( access( name.c_str(), F_OK ) != -1 );
}

void toRemove(const char* data) {
    if (remove(data) != 0) {
        perror("Error deleting file");
    } else {
        puts("File successfully deleted");
    }
};

int main(int num, char** argv){
    int globalIterOfArgv = 1;

    if (num == 1){
        cout << "missing operand" << endl;
        return 1;
    }

    if((string(argv[1]) == "--help")||(string(argv[1]) == "-h")){
        cout<<"Usage: rm [OPTION]... [FILE]...\n"
                "Remove (unlink) the FILE(s).\n"
                "\n"
                "  -f, --force           ignore nonexistent files and arguments, never prompt\n"
                "  -R, --recursive   remove directories and their contents recursively\n"
                "\n"
                "By default, rm does not remove directories.  Use the --recursive (-R)\n"
                "option to remove each listed directory, too, along with all of its contents.\n"
                "\n"
                "Note that if you use rm to remove a file, it might be possible to recover\n"
                "some of its contents, given sufficient expertise and/or time.  For greater\n"
                "assurance that the contents are truly unrecoverable, consider using shred.\n"
                "\n"
                "GNU coreutils online help: <http://w...content-available-to-author-only...g.ua/>\n"
                "Full documentation at: <http://w...content-available-to-author-only...t.org/software/coreutils/rm>\n";
    }
	
	//! УВАГА! Структура коду потворна -- просканувати опції слід на початку, зберегти у якихось 
	//! прапорцях, а вже потім  -- використовувати їх. Імена файлів, отримані при тому, скласти окремо. 
	//! Див, наприклад mls (там не ідеально, але таки краще).
	//! Плюс, копіпасти стільки...
    else if (findF(num, argv)&&findR(num, argv)) {
        int iterWithFR = globalIterOfArgv;
        while(iterWithFR != num){
            if ((string(argv[iterWithFR]) == "-f")||(string(argv[iterWithFR]) == "-R")){
                iterWithFR++;
            }else{
                if(FileExistSameDir(argv[iterWithFR]) || findDir(argv[iterWithFR])){
                        toRemove(argv[iterWithFR]);
                        iterWithFR++;
                }else{
                    cout<<"rm: cannot remove "<<argv[iterWithFR]<<" : No such file or directory"<<endl;
                    iterWithFR++;
                }
            }
        }

    }
    else if(findF(num, argv)&&!findR(num, argv)) {
        int iterWithF = globalIterOfArgv;
        while(iterWithF != num){
            if (string(argv[iterWithF]) == "-f"){
                iterWithF++;
            }else{
                if(FileExistSameDir(argv[iterWithF])&&!findDir(argv[iterWithF])){
                    toRemove(argv[iterWithF]);
                    iterWithF++;

                }else if (findDir(argv[iterWithF])){
                    cout<<"rm: cannot remove "<<argv[iterWithF]<<" : Is a directory"<<endl;
                    iterWithF++;
                }else{
                    cout<<"rm: cannot remove "<<argv[iterWithF]<<" : No such file"<<endl;
                    iterWithF++;
                }
            }
        }
    }else if(!findF(num, argv)&&!findR(num, argv)){
        int iterWithout = globalIterOfArgv;
        while(iterWithout != num){
            if(FileExistSameDir(argv[iterWithout])&&!findDir(argv[iterWithout])){
                string usrInput;
                cout << "Do you wish to delete " << argv[iterWithout] << "?" << "[y/n] ";
                getline(cin, usrInput);
                if (string(usrInput) == "y") {
                    toRemove(argv[iterWithout]);
                    iterWithout++;
                }else{
                    iterWithout++;
                }
            }else if(!FileExistSameDir(argv[iterWithout])&&!findDir(argv[iterWithout])){
                cout<<"rm: cannot remove "<<argv[iterWithout]<<" : No such file"<<endl;
                iterWithout++;
            }else if(findDir(argv[iterWithout])){
                cout<<"rm: cannot remove "<<argv[iterWithout]<<" : Is a directory"<<endl;
                iterWithout++;
            }

        }
    }else if(!findF(num, argv)&&findR(num, argv)){
        int iterWithR = globalIterOfArgv;
        while(iterWithR != num){
            if (string(argv[iterWithR]) == "-R"){
                iterWithR++;
            }else{
                if(FileExistSameDir(argv[iterWithR])){
                    string usrInput;
                    cout << "Do you wish to delete " << argv[iterWithR] << "?" << "[y/n] ";
                    getline(cin, usrInput);
                    if (string(usrInput) == "y") {
                        toRemove(argv[iterWithR]);
                        iterWithR++;
                    }else{
                        iterWithR++;
                    }
                }else{
                    cout<<"rm: cannot remove "<<argv[iterWithR]<<" : No such file or directory"<<endl;
                    iterWithR++;
                }
            }
        }
    }

    return 0;
}