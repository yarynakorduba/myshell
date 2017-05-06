#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <dirent.h>
#include <sstream>
#include <cstring>
#include <vector>
#include <boost/bind.hpp>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

#define PATH_MAX 4096


//char *curr_dir = (char *) "/usr/bin";

//! УВАГА! Глобалньі змінні!
vector<char*> vectorOfPath;
string command;
string args;
void splitString( string line){
    int i = 0;
    while(i != sizeof(line)){
        if(line[i] == ' '){
            command = line.substr(0,i);
            args = line.substr(i+1, sizeof(line));
            break;
        }else{
            command = line;
        }
        i++;
    }}

bool is_file(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISREG(buf.st_mode);
}

bool is_dir(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

int rewrite_check() {
    cout << "Do you want to rewrite? [y/n]";
    char answ[16];
    cin.getline(answ, 16);
    char *ans = strtok(answ, " ");
    char first = ans[0];
    cout << ans << endl;
    if (first == 'y') {
        return 0;
    }
    return -1;
}

int inside_copy(char** argv, int source, int dest) {
    ifstream f1 (argv[source], fstream::binary);
    ofstream f2 (argv[dest], fstream::trunc|fstream::binary);
    f2 << f1.rdbuf();
    return 0;
}

int inside_copy_dir(char** argv, int numb) {
    int i=1;
    std::string additive(argv[1]);
    if (additive == "-f") {i=2;}
    while (i != numb) {
        std::string name(argv[numb]);
        char str[4096]; //! УВАГА 128 -- мало!

		//! Уникайте strtok!
		//! Взагалі, який сенс маніпуляцій нижче?
		//! Ви розрізали по "/", щоб потім по ньому склеїти?! 
		//! Лише щоб вивести filename?
		//! УВАГА! Як я наголошував, для такого аналізу є спеціальні функції:
		//! https://linux.die.net/man/3/dirname
		//! http://www.boost.org/doc/libs/1_48_0/libs/filesystem/v3/doc/tutorial.html -- tut3.cpp i tut4.cpp
		//!		is_directory(p), exists(p), .filename() і т.д.
        strcpy (str, argv[i]);                                                //start of splitting
        char * token = std::strtok(str, "/");
        char* temp = token;
        while (token != NULL) {
            temp=token;
            token = strtok(NULL, "/");
        }
        cout << " filename "<< temp << endl;
        // const char* spl = "/";
        name += '/';
        name+= temp;
        const char* nName = name.c_str();
        int ch = 0;
        if (is_file(nName) && (additive != "-f")) {
            int check = rewrite_check();
            if (check == -1) {ch = -1;}
        }
        if ((ch==0) || (additive == "-f") ||!(is_file(temp))) {
			//! У вас же вище якраз функція для того є!
            ifstream f1 (argv[i], fstream::binary);                               //start copying file
            ofstream f2 (nName, fstream::trunc|fstream::binary);
            f2 << f1.rdbuf();
        }
        i++;

    }
	return 0;
}

int cp_help(){
    cout << "Usage: cp [-f] SOURCE DEST \n or:  cp [-f] SOURCE... DIRECTORY \n Copy SOURCE to DEST, or multiple SOURCE(s) to DIRECTORY. \n -f - rewrite existing files without asking" << endl;
    return 0;
}

int main(int a, char** argv) {
    struct stat st;
    int i=1;
    std::string name(argv[1]);
    if (name=="-h"|| name=="--help") {return cp_help();}
    if (name == "-f") {i=2;}
    while (i!=sizeof(argv))   {
		//! УВАГА! Ви вилазите за масив! у нього немає елемента з номером argv!
        if (argv[i+1] == NULL) {                                    // pointer is on the last argument
            if ((i!=1) && (is_dir(argv[i]))) {                     //spec. option for copying few f into dir
                return inside_copy_dir(argv, i);
            }
            else if (((i==1)&&((name!="-h")||(name != "--help"))) ||
                     ((i>2)&&(name != "-f"))||((i>3)&&(name == "-f"))) {
                cout << "WRONG ARGUMENT" << endl;
                return -1;
            }
            else if (((((i==2)&&(stat(argv[i],&st) == -1))||
                       ((i==3)&&(stat(argv[i],&st) == 0)&&(name == "-f"))))) {
                return inside_copy(argv, i-1, i);
            }
            else if((i=2) && (stat(argv[i],&st) == 0)){
                if (rewrite_check()==0) {
                    return inside_copy(argv, i-1, i);
                }
                else{return -1;}
            }
		}

        else {                                             //for all files except the last one
            if (stat(argv[i],&st) != 0) {                 //checking for existance of each file we want to rewrite
                cout << "NO SUCH FILE"<<endl;
                return -1; }}
			i++; 
		}
}