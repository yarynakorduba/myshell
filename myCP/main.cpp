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
#include <libgen.h>

using namespace std;

#define PATH_MAX 4096


//! УВАГА! Глобалньі змінні!

void splitString( string line){
    string args;
    string command;
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
        return 1;
    }
    if (first == 'n') {
        return 0;}

    cout << "ERROR IN THE INPUT. THIS FILE WON`T BE COPIED" << endl;

    return -1;
}


int inside_copy(char** argv, int source, int dest, int f_trigger) {
    struct stat st;
    if (stat(argv[source],&st) != 0) {

        //checking for existance of each file we want to rewrite
                      cout << "NO SUCH FILE"<<endl;
                      return -1; }
    int rewrit = 0;
    if ((f_trigger == 0) && ((stat(argv[dest],&st) == 0))) {
        rewrit = rewrite_check();
    }

    if ((rewrit == 1) || (f_trigger == 1) || (stat(argv[dest],&st) == -1)) {
        cout << argv[dest] << endl;
        ifstream f1 (argv[source], fstream::binary);
        ofstream f2 (argv[dest], fstream::trunc|fstream::binary);
        f2 << f1.rdbuf();

}
    return 0;
}

int inside_copy_dir(char** argv, int numb, int f_trigger) {
    int i=1;
    struct stat st;

    while (i != numb) {
        if (string(argv[i]) != "-f") {
        char *basec, *bname;
        basec = strdup(argv[i]);
        bname = basename(basec);

        std::string name1(argv[numb]);
        name1 += "/" + (string)bname;

        cout << " filename "<< bname << endl;

        const char* nName = name1.c_str();

        if (stat(argv[i],&st) != 0) {
                    //checking for existance of each file we want to rewrite
             cout << "NO SUCH FILE bname"<<endl;
        }
        else {
        int rewrit = 0;
        if ((f_trigger == 0) && ((stat(nName,&st) == 0))) {
            rewrit = rewrite_check();
        }

        if ((rewrit==1) || (f_trigger==1) ||(!(is_file(nName)))) {
            ifstream f1 (argv[i], fstream::binary);                               //start copying file
            ofstream f2 (nName, fstream::trunc|fstream::binary);
            f2 << f1.rdbuf();
        }}}

        i++;
    }
        return 0;
}


int cp_help(){
    cout << "Usage: cp [-f] SOURCE DEST \n or:  cp [-f] SOURCE... DIRECTORY \n Copy SOURCE to DEST, or multiple SOURCE(s) to DIRECTORY. \n -f - rewrite existing files without asking" << endl;
    return 0;
}


int main(int num, char** argv) {
    int help_trigger = 0;
    int f_trigger = 0;
    int dir_trigger = 0;


    if (is_dir(argv[num-1])) {
            dir_trigger = 1;
        }

    int i = 1;
    while (i<num) {//TRIGGERS TAKE VALUES

        string elm(argv[i]); //! Small optimization

        if (elm == "-f") {
            f_trigger = 1;
        }

        else if ((elm == "-h") || (elm == "--help")) {
            help_trigger = 1;
            return cp_help();
        }
        ++i;
    }

    if ((num <=2) && (help_trigger != 1)) {
        cout << "WRONG QUANTITY OF ARGUMENTS";
        return -1;
    }

//    if (!is_dir(argv[i-1])
//        && (f_trigger == 0)) {
//        cout << "WRONG ARGUMENTS. NO SUCH FILE OR DIRECTORY" << endl;
//        return -1;
//    }

    if (dir_trigger == 1) {
        return inside_copy_dir(argv, i-1, f_trigger);
    }

    else {
        return inside_copy(argv, num-2, num-1, f_trigger);
    }

}
