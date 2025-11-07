#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// TODO: Include more header files (read the manpages to find out more!)

int main(int argc, const char* argv[]) {
    // TODO: Complete and document
    if (argc != 3) {
        const char *msg = "ERROR: No arguments\n";
        write(2, msg, strlen(msg));
        return 1;
    }

    const char *word = argv[1];
    const char *filename = argv[2];

    pid_t pid = fork();
    //Fork failed
    if (pid < 0) {
        const char *err = "fork failed\n";
        return 1;    
    }

    if (pid == 0) {
        //Child: exec grep
        char *grep_args[] = { "grep", "-s", "-q", (char*)word, (char*)filename, NULL};
        execv("/usr/bin/grep",grep_args); 
        const char *exec_err = "exec failed \n";
        write(2, exec_err, strlen(exec_err));
        return 1;
    } else {
        // Parent: wait for child
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);

            if (code == 0){ 
                write(1, "FOUND: ", 7);
                write(1, word, strlen(word));
                write(1, "\n", 1);
            } else if (code == 1) {
                write(1, "NOT FOUND: ", 11);
                write(1, word, strlen(word));
                write(1, "\n", 1);
            } else if (code == 2) {
                write(1, "ERROR: ", 7);
                write(1, filename, strlen(filename));
                write(1, " doesn't exist\n", 15);
                return 2;
            }   
        }
    }
    return 0;
}
