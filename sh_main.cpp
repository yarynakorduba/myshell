#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <dirent.h>
#include <sstream>
#include <cstring>
#include <vector>
#include <boost/bind.hpp>

#include "sh_tools.h"

using namespace std;

int mpwd(char** argv){
    if(argv[1] == NULL){
        cout << get_current_dir_name();
    }else if((string(argv[1])=="-h")||(string(argv[1])=="--help")){
        cout<<"Display current directory"<<endl;
    }
    else
    {
        cerr << "Bad pwd option." << endl;
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
void mexit(char** argv, int num){
    if(num != 1){
        if((string(argv[1])=="-h")||(string(argv[1])=="--help")){
            cout<<"mexit will finish your program"<<endl;

        }else{
            int castInputToInt;
            stringstream ss(argv[1]);
            ss >> castInputToInt;
            exit(castInputToInt);
        }
    }else{
        exit(0);
    }
}
void globalHelp(){
    cout<<"You can use the following commands: \n"
            "\n"
            "mrm\n"
            "\n"
            "The order of the arguments is not significant \n"
            "\n"
            "Examples and explaining: \n"
            "\n"
            "mrm -f -R name_Of_Folder_or_File -- will remove your folder(even if it isn't empty) or file "
            "without asking the permission. \n"
            "mrm -f name_Of_File -- will remove only your file without asking the permission. Can't remove folder. \n"
            "mrm name_Of_File -- will remove only your file with asking the permission. Can't remove folder. \n"
            "mrm -R name_Of_Folder_or_File -- will remove your folder (even if it isn't empty) "
            "file with asking the permission.\n"
            "\n"
            "mrv\n"
            "\n"
            "The order of the arguments is not significant \n"
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
            "\n"
            "mmkdir\n"
            "\n"
            "mmkdir will create new directory\n"
            "\n"
            "mcp\n"
            "\n"

        <<endl;

}
int execution(char* prog, char** argv){
    pid_t kidpid = fork();

    if (kidpid < 0)
    {
        perror( "Internal error: cannot fork." );
        return -1;
    }
    else if (kidpid == 0)
    {
        // I am the child.

        //const char* b = "/home/yuriy/CLionProjects/myRV/";

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


}
inline bool FileExistSameDir (const std::string& name) {
    return ( access( name.c_str(), F_OK ) != -1 );
}



int main(int argc, char* argv[], char**env)
{
    chdir("/usr/bin");

    while(true)  {

        int i = 0;
        cout << get_current_dir_name() << "$ ";
        const size_t buf_size = 4096;
        char command[buf_size];
        cin.getline( command, buf_size );


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

        args.push_back( NULL );
        char** argv = args.data();
        string progname(prog);

        if((progname=="mshell")){
            if(FileExistSameDir(argv[1])){
                string str1 = argv[1];
                ifstream file(str1);
                string str;
                string delimiter = " ";
                while (getline(file, str))
                {
                    vector<char*> args1;
                    size_t pos = 0;
                    string token;
                    int n = 0;
                    while ((pos = str.find(" ")) != std::string::npos) {
                        token = str.substr(0, pos);
                        char *cstr = new char[token.length() + 1];
                        strcpy(cstr, token.c_str());
                        n +=1;
                        args1.push_back(cstr);
                        str.erase(0, pos + delimiter.length());
                    }

                    char *cstr = new char[str.length() + 1];
                    strcpy(cstr, str.c_str());
                    n +=1;
                    args1.push_back(cstr);

                    args1.push_back(NULL);
                    char** argv1 = args1.data();

                    if ((string(argv1[0])=="mpwd")){

                        mpwd(argv1);

                    }if((string(argv1[0])=="mcd")) {

                        mcd(argv1);
                    }
                    else if((string(argv1[0])=="mexit")) {

                        mexit(argv1, n);

                    }
                    else if((string(argv1[0])=="mhelp")) {

                        globalHelp();
                    }
                    else {

                        execution(argv1[0], argv1);
                    }

                }
                cout << "\n";
            }else{
                cout<<"No such file"<<endl;
            }
        }
        else if ((progname=="mpwd")){
            mpwd(argv);
        }
        else if((progname=="mcd")) {
            mcd(argv);
        }
        else if((progname=="mexit")) {
            mexit(argv, i);
            return -1;
        }
        else if((progname=="help")) {
            globalHelp();
        }
        else{
            execution(prog, argv);
        }

        cout << "\n";

    }
}
