#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <dirent.h>
#include <sstream>
#include <cstring>
#include <vector>
#include <streambuf>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <algorithm>
#include <stdio.h>
//#include <time.h>
//#include <stdlib.h>

using namespace std;

#define PATH_MAX 4096

bool findSign(int numOfArgv, char** argvFindSign){
    for(int i1 = 1; i1 < numOfArgv; i1++){
        if (string(argvFindSign[i1]) == "^"){
            return true;
        }
    }return false;

}


int ls_help() {
    cout << "Usage: ls [OPTION]... [FILE]...\n"
            "List information about the FILEs (the current directory by default)\n"
            "Arguments (works at eny position after mls): \n"
            "-l output with file properties\n"
            "--sort=N | t | S sort by names | time of last modification | size \n"
            "Default sort by names. \n"
            "-r sort in reverse order\n"
            ".[ext] sorting by extention"
            "\n[path] all files in path"<<endl;
    return 0;
}


string toStr(char arr[]) {
    int pointer = 0;

    while (arr[pointer]) {
        pointer++;
    }
    std::string str;

    str.append(arr, 0, pointer);
    return str;
}

bool mySizeFunction (std::__cxx11::basic_string<char> f1, std::__cxx11::basic_string<char> f2) {
    struct stat attrib1;
    struct stat attrib2;
    stat(f1.data(), &attrib1);
    stat(f2.data(), &attrib2);
    return (attrib1.st_size > attrib2.st_size);
}

bool myMtimeFunction(std::__cxx11::basic_string<char> f1, std::__cxx11::basic_string<char> f2) {
    struct stat attrib1;
    struct stat attrib2;
    stat(f1.data(), &attrib1);
    stat(f2.data(), &attrib2);
    return (attrib1.st_mtime > attrib2.st_mtime);
}


void f_properties(const char* filename) {
    struct tm *foo;
    struct stat attrib;
    cout << filename;
    stat(filename, &attrib);
    foo = gmtime(&(attrib.st_mtime));
    printf("\ndate of modification: %d/", foo->tm_year+1900); //tm_year gives year from 1900
    printf("%d/", foo->tm_mon+1); //tm_mon has range (0, 11)
    printf("%d ", foo->tm_mday);
    printf("%d:", foo->tm_hour);
    printf("%d\n", foo->tm_min);
    printf("Size: %d bytes\n\n", (int)attrib.st_size);
}


int main(int num, char** argv){
    char* curr_dir = get_current_dir_name();
    DIR *dp = NULL;
    struct dirent *dptr = NULL;
    unsigned int count = 0;
    dp = opendir((const char*)curr_dir);

    string mask_trigger(" ");            //TRIGGER FOR EXTENTIONS
    int l_trigger = 0;                        //TRIGGER FOR PROPERTIES
    int S_size_trigger = 0;                   //TRIGGER FOR SORTING
    int r_trigger = 0;
    int error_trigger = 0;


        for (int i=0; i<num; i++) {//TRIGGERS TAKE VALUES

            string elm(" ");
            elm = argv[i];
            cout<<elm<<endl;

            if (elm == "-l") {
                l_trigger = 1;
            }
            else if (elm[0] == '/') {
                dp=opendir((const char*)argv[i]);}


            else if (elm[0] == '.') {
                mask_trigger = elm;
            }

            else if (elm.substr(0, 6) == "--sort") {

                if ((elm.substr(6, 2) == "=N") || (elm.size() == 6)) {
                    S_size_trigger = 1;}

                else if (elm.substr(6, 2) == "=S") {
                    S_size_trigger = 2;
                }

                else if (elm.substr(6, 2) == "=t") {
                    S_size_trigger = 3;
                }

            }

            else if (elm == "-r") {
                r_trigger = 1;
            }
            else if ((elm == "-h") || (elm == "--help")) {
                return ls_help();

            }else if (elm != "mls"){
                error_trigger = 1;


            }
        }


    if(NULL == dp)
    {
        printf("\n ERROR : Could not open the working directory\n");
        return -1;
    }
    else{

        vector<string> dirlist;

        if (error_trigger == 1){
            cout<<"ls: invalid option -- \n"
            "Try 'ls --help' for more information."<<endl;
            return -1;
        }
        if (mask_trigger != " ") {

            for(count = 0; NULL != (dptr = readdir(dp)); count++) {

                if(dptr->d_name[0] != '.') {

                    int pointer = 0;
                    while (dptr->d_name[pointer]) {
                        pointer++;
                    }

                    if (pointer > mask_trigger.size()) {
                        string str;
                        str.append(dptr->d_name, pointer-mask_trigger.size(), pointer);

                        if (str.compare(mask_trigger) == 0) { //
                            dirlist.push_back(dptr->d_name);
                        }
                    }
                }
            }
        }

        else {
            for(count = 0; NULL != (dptr = readdir(dp)); count++) {
                if(dptr->d_name[0] != '.') {
                    dirlist.push_back(dptr->d_name);
                }
            }
        }
        if (S_size_trigger != 0) {

            if (S_size_trigger == 1){
                sort(dirlist.begin(), dirlist.end());
            }
            else if (S_size_trigger == 2) {
                cout << "SORTED BY SIZE" << endl;
                sort(dirlist.begin(), dirlist.end(), mySizeFunction);}

            else if (S_size_trigger == 3) {
                cout << "SORTED BY MODIFICATION TIME" << endl;
                sort(dirlist.begin(), dirlist.end(), myMtimeFunction);
            }
        }


        if (l_trigger == 1)  {
            if (r_trigger ==1) {                   //SET UP REVERSE=TRUE
                for (int el= (int) (dirlist.size() - 1); el >= 0 ; el++) {
                    f_properties(dirlist[el].data());
                }
            }
            else {                                  //SET UP REVERSE=FALSE
                for (int el=0; el <dirlist.size() ; el++) {
                    f_properties(dirlist[el].data());
                }
            }
        }

        else if (l_trigger == 0) {

            if (r_trigger==0) {                    //SET UP REVERSE=FALSE
                for (int el=0; el < dirlist.size(); el++) {
                    cout << dirlist[el] << endl;
                }
            }
            else {                                  //SET UP REVERSE=TRUE
                for (int el=dirlist.size()-1; el >= 0; el--) {
                    cout << dirlist[el] << endl;
                }
            }
        }


        return 0;
    }
}
