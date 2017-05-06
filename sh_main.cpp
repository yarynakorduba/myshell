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
    chdir("/usr/bin");

    while(true)  {

        int i = 0;
        cout << my_get_current_dir_name() << "$ ";
        char command[128];
        cin.getline( command, 128 );


        vector<char*> args;
        char* prog = strtok( command, " " );
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

        char** argv = args.data();


        argv[args.size()] = NULL;

        if ((string(prog)=="mpwd")){
            mpwd(argv);
        }
        else if((string(prog)=="mcd")) {
            mcd(argv);
        }
        else if((string(prog)=="mexit")) {
            mexit(argv);
        }
        else if((string(prog)=="mls")||(string(prog)=="mrv")||(string(prog)=="mrm")||
                (string(prog)=="mmkdir")||(string(prog)=="mcpp")){
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
                    printf("Err: %i : %s\n", errno, strerror(errno));
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