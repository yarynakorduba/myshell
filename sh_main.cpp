#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <dirent.h>
#include <sstream>
#include <cstring>
#include <vector>
#include <boost/bind.hpp>
#include <sys/stat.h>
#include <fstream>
#include <errno.h>

#include "sh_tools.h"

using namespace std;

#define PATH_MAX 4096


int mpwd(char** argv){
    if(argv[1] == NULL){
        cout << my_get_current_dir_name();
    }else if((string(argv[1])=="-h")||(string(argv[1])=="--help")){
        cout<<"Display current directory"<<endl;
    }else		
	{
		cerr << "Bad pwd option. Usage: [Тут лінь писати -- самі працюйте.]" << endl;
		return 1; // Error
	}

    return 0;
}

int mcd(char** argv){
    if ( argv[1] == NULL){
        chdir ("/home/yuriy");
    }else if((string(argv[1])=="-h")||(string(argv[1])=="--help")){
        cout<<"command mcd change directory \n"
                "just mcd - will move you to your home directory \n"
                "mcd and ../ - will move you to previous directory \n"
                "mcd and directory to which you want to go - will move you to the desired directory"<<endl;
    }
    else{
        DIR *dir = opendir((const char *) argv[1]);
        if (dir != NULL){
            chdir(argv[1]);}
        else{
            cout<<"No such file or directory";
        }
    }
    return 0;
}
void mexit(char** argv){
    if((string(argv[1])=="-h")||(string(argv[1])=="--help")){
        cout<<"mexit will finish your program"<<endl;

    } else{
        int castInputToInt;
        stringstream ss(argv[1]);
        ss >> castInputToInt;
        exit(castInputToInt);
    }
}



int main(int argc, char* argv[], char**env)
{
    //! chdir("/usr/bin");

    while(true)  {

        int i = 0;
        cout << my_get_current_dir_name() << "$ ";
		const size_t buf_size = 4096;
        char command[buf_size]; //! УВАГА -- суть змін зрозуміла? Ну і -- не жаднічайте.
        cin.getline( command, buf_size );

        vector<char*> args;
        char* prog = strtok( command, " " ); //! strtok краще уникати... Вона має глобальний стан.
        char* tmp = prog;

        if(tmp == NULL){
            continue;
        }

        while ( tmp != NULL )
        {
            if (tmp[0] == '#')
                break;
            args.push_back( tmp );
            i++;
            tmp = strtok( NULL, " " );
        }


		args.push_back( NULL ); //! В C++ краще використовувати nullptr.
        //argv[args.size()] = NULL; //! УВАГА Невизначена поведінка! Тамнемає такого елемента!
		
        char** argv = args.data(); //! Цей вказівник коректний лише поки args не змінювали. Тому після push_back 

		string progname(prog); //! Просто оптимізація
        if ( progname=="mpwd" ){ 
            mpwd(argv);
        }
        else if( progname=="mcd" ) {
            mcd(argv);
        }
        else if( progname=="mexit" ) {
            mexit(argv);
        }
		//! УВАГА! Краще переробити через std::set або щось аналогічне. Що це за простирадло...
        else if( (progname=="mls")||(progname=="mrv")||(progname=="mrm")||
                (progname=="mmkdir")||(progname=="mcp")){
            pid_t kidpid = fork();

            if (kidpid < 0)
            {
                perror( "Internal error: cannot fork." );
                return -1;
            }
            else if (kidpid == 0)
            {
                // I am the child.

                //const char* a = prog;
                //const char* b = "/home/yuriy/CLionProjects/myRV/";
                //const char* b = "";
                //char* p=new char[strlen(b)+strlen(a)+1];
                //char* c=new char[strlen(a)+1];
                //strcat(p,b);
                //strcat(p,a);
                //strcpy(c,p);
                //printf("Name %s\n", a);
                //printf("Path %s\n", getenv("PATH"));

                //puts(prog);
                int err = execvp (prog, argv);
                if(err == -1)
                {
					// Progname printed just for better diagnostic.
                    printf("Err: %i : %s\n\t Name: %s\n", errno, strerror(errno), prog); 
                }
                // The following lines should not happen (normally).
                //perror( command );
                return -1;
            }
            else
            {
                // I am the parent.  Wait for the child.
                if ( waitpid( kidpid, 0, 0 ) < 0 )
                {
                    perror( "Internal error: cannot wait for child." );
                    return -1;
                }
            }
        } else {
            cout<<argv[0]<<" :command not found"<<endl;
            //continue;
        }

        cout << "\n";
    }
}