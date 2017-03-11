#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <dirent.h>
#include <sstream>

using namespace std;

#define PATH_MAX 4096

char *curr_dir = (char *) "/usr/bin";
/*
string comm;
string argum;

int splitting(string l) {
    string arr[3];

    int i = 0;
    stringstream ssin(l);

    while (ssin.good() && i < 3) {
        ssin >> arr[i];

        ++i;
        if(i == 3){
            printf("ERROR : TU DAUN! TAK NE MOZNA PYSATY.");
            return -1;
        }

    }
    comm = arr[0];

    argum = arr[1];
    cout << comm << endl;
    cout << argum;
    return 0;


}*/
string command;
string args;
void split( string line){
    int i = 0;
    while(line[i] != ' '){
        i++;
    }command = line.substr(0,i);
    args = line.substr(i+1, sizeof(line));

}

int ls(){
/*
    char cwd[1024];
    chdir("/path/to/change/directory/to");
    getcwd(cwd, sizeof(cwd));
    printf( "%s\n", cwd); }
    */
    DIR *dp = NULL;
    struct dirent *dptr = NULL;
    unsigned int count = 0;

    dp = opendir((const char*)curr_dir);
    if(NULL == dp)
    {
        printf("\n ERROR : Could not open the working directory\n");
        return -1;
    }

    for(count = 0; NULL != (dptr = readdir(dp)); count++)
    {
        // Check if the name of the file/folder begins with '.'
        // If yes, then do not display it.
        if(dptr->d_name[0] != '.')
            printf("%s  ",dptr->d_name);
    }

    return 0;
}

int main(int argc, char* argv[], char**env)
{
/*
    pid_t pid = fork();

    if (pid == -1)
    {
        cout << "ERROR" << &endl;
    }
    else if (pid > 0)
    {
        int status;
        waitpid(pid, &status, 0);
    }
    else {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        //printf( "%s\n", cwd);
        execve("/bin/ls", argv, env);
        _exit(EXIT_FAILURE);
    }*/
    string input = "";
    char *ptr;
    int a = 10;

    while( a < 20 )  {
        a++;
        //string command;
        // char commandChar[1024];    // Will store the command entered by user in character array
        // char *argVector[10];    // Will store the arguments after they are tokenized
        //int argCount;        // Will store the number of arguments

        //char cwd[1024];
        //getcwd(cwd, sizeof(cwd));
        //printf( "%s$\n", cwd);

        cout << curr_dir << "$ ";
        getline(cin, input);
        //cout << input;
        split(input);
        cout<<command<<endl;
        cout<<args;
        //cout << *arg;
        if (input == "pwd"){
            cout << curr_dir;
        }
        else if ( input == "ls"){
            ls();

        }
        else if(input == "cd"){

        }

        cout << "\n";


        //cout << input << endl;



        /*
        ptr = strtok(commandChar, " ");
        argVector[argCount] = ptr;
        argCount++;
        while (ptr != NULL)
        {
            ptr = strtok(commandChar, " ");
            cout << ptr << " " << argCount << "\n";
            argVector[argCount] = ptr;
            argCount++;
            //execvp(argvec[0], argvec);
            //fatal("exec failed");
        }
*/
    }

    return 0;

}