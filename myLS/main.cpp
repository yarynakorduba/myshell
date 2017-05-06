#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
//#include <limits.h>
#include <dirent.h>
//#include <sstream>
#include <cstring>
#include <vector>
//#include <streambuf>
#include <sys/types.h>
//#include <sys/stat.h>
#include <sys/stat.h>
#include <algorithm>
#include <stdio.h>
//#include <time.h>
//#include <stdlib.h>

#include "sh_tools.h"

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
	//! УВАГА! От навіщо так складно?!
	return string(arr); // Тут і string зайвий, але хай буде.
	//Старий код залишаю -- щоб ви його бачили, стріть потім -- не варто такі залишки тримати
	// в коментах -- для того і є git чи інші системи контролю версій.	
/*
	int pointer = 0;

    while (arr[pointer] != NULL) {
        pointer++;
    }
    std::string str;

    str.append(arr, 0, pointer);
    return str;
*/	
}

//! УВАГА
// Хто і звідки цей жах передер?! Виясніть, що за речовини
// він чи вона вживає (нюхає? коле?) і більше їх йому не давайте!
// (Так, я знаю, де автор міг це побачити, але навіщо передер внутрішні назви класів?!)
//bool mySizeFunction (std::__cxx11::basic_string<char> f1, std::__cxx11::basic_string<char> f2) {
bool mySizeFunction (const std::string& f1, const std::string& f2) {
    struct stat attrib1;
    struct stat attrib2;
    stat(f1.data(), &attrib1);
    stat(f2.data(), &attrib2);
    return (attrib1.st_size > attrib2.st_size);
}

bool myMtimeFunction(const std::string& f1, const std::string& f2) {
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
    printf("Size: %lld bytes\n\n", attrib.st_size); //! Зверніть увагу на %lld -- long long int
}


int main(int num, char** argv){
    DIR *dp = NULL;
    struct dirent *dptr = NULL;
    unsigned int count = 0;
    dp = opendir( my_get_current_dir_name().data() ); //! УВАГА -- string, що повернула ф-ці
				// повинен прожити довше, ніж той, хто користується вказівником, 
				// повернутим data(), тому варіант: 
				// const char* curr_dir = my_get_current_dir_name().data();
				// dp = opendir( curr_dir );
				// буде невірним!


    string mask_trigger(" ");            //TRIGGER FOR EXTENTIONS
    int l_trigger = 0;                        //TRIGGER FOR PROPERTIES
    int S_size_trigger = 0;                   //TRIGGER FOR SORTING
    int r_trigger = 0;
    int error_trigger = 0;

	
    for (int i=0; i<num; i++) {//TRIGGERS TAKE VALUES

        string elm(argv[i]); //! Small optimization
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
			//! УВАГА Рішення із тригерами -- хороше, але ось тут краще enum використати
			//! замість магічних констант 1, 2, 3:
			//! enum S_size_trigger_list {SORT_BY_NAME = 1, SORT_BY_SIZE = 2,  SORT_BY_TIME = 3};
			//! Ну і де решта опцій?

			
            if ((elm.substr(6, 2) == "=N") || (elm.size() == 6)) { //! size()? WTF?!
                S_size_trigger = 1;
			}

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

        }else if (elm != "mls"){ //! Не бачу сенсу на власне ім'я перевіряти... Краще почати цикл з 1 і все.
            error_trigger = 1;
        }
    }

	//! Думаю, це варто робити перед циклом. Або opendir після нього -- якщо Ви про help
	//! турбуєтеся. Швидше таки -- opendir після циклу, щоб не смикати ОС, якщо опції некоректні.
    if(NULL == dp)
    {
        printf("\n ERROR : Could not open the working directory\n");
        return -1;
    }
    else{

        vector<string> dirlist;

		//! Це теж варто вище перенести, думаю.
        if (error_trigger == 1){
            cout<<"ls: invalid option -- \n"
            "Try 'ls --help' for more information."<<endl;
            return -1;
        }
        if (mask_trigger != " ") {

            for(count = 0; NULL != (dptr = readdir(dp)); count++) {

                if(dptr->d_name[0] != '.') {
					
					size_t pointer = strlen(dptr->d_name); //! УВАГА -- замість коду нижче
					/*
                    int pointer = 0;
                    while (dptr->d_name[pointer] != NULL) {
                        pointer++;
                    }
					*/
					//! УВАГА: щось Ви дивне тут робите... Розкажіть но мені, що саме?
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
            if (r_trigger == 1) {                   //SET UP REVERSE=TRUE
                for (int el= (int) (dirlist.size() - 1); el >= 0 ; el++) { //! el++?!
                    f_properties(dirlist[el].data());
                }
				//! Варіант вирішити проблему із інтом:
				/*
				for (size_t el= dirlist.size(); el > 0 ; el++) {
                    f_properties(dirlist[el-1].data());
                }
				*/
				//! Бо size_t -- беззнаковий і справді завжди >=0 за означенням.

            }
            else {                                  //SET UP REVERSE=FALSE
                for (size_t el=0; el <dirlist.size() ; el++) { 
                    f_properties(dirlist[el].data());
                }
            }
        }

        else if (l_trigger == 0) {
            if (r_trigger == 0) {                    //SET UP REVERSE=FALSE
                for (size_t el=0; el < dirlist.size(); el++) {
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
