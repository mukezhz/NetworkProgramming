#if !defined(__ASSIGNMENT__)
#define __ASSIGNMENT__

struct Message {
    char msg[1024];
    int status; // 0: for ok status; -1: for unable to find status; 1: for send again
};

void error_handle(char *message);
char* substr(char* str, int position, int length);

#endif