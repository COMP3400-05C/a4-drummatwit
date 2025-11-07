#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

// TODO: Include more header files (read the manpages to find out more!)

int main(int argc, const char* argv[]) {
    //Check to see if no arguments
    if (argc == 1){
        const char *msg = "ERROR: No arguments\n";
        write(2, msg, strlen(msg));
        return 1;
    }
    int num_args = argc - 1;
    int mid_index = num_args / 2;

    //Build argument array for execv
    char *exec_args[4];
    exec_args[0] = "echo";

    if (num_args % 2 == 1) {
        exec_args[1] = (char*)argv[mid_index+1];
        exec_args[2] = NULL; 
    } else {
        exec_args[1] = (char*)argv[mid_index];
        exec_args[2] = (char*)argv[mid_index+1];
        exec_args[3] = NULL; 
    }

    if (execv("/bin/echo", exec_args) == -1){
        const char *err = "exec failed\n";
        write(2, err, strlen(err));
        return 1;
    }
    return 0;
}