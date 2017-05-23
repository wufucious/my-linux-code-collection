#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>

static void recur_mkdir(const char *dir) {
    char tmp[256];
    char *p = NULL;
    size_t len;

    snprintf(tmp, sizeof(tmp),"%s",dir);
    len = strlen(tmp);
    
    if(tmp[0] == '/')
        p = tmp + 1;
    else
        p = tmp;

    if(tmp[len - 1] == '/')
        tmp[len - 1] = 0;
    
    for(; *p; p++){
        if(*p == '/') {
            *p = 0;
            mkdir(tmp, S_IRWXU);
            *p = '/';
        }
    }
    mkdir(tmp, S_IRWXU);
}

int main(int argc, char const *argv[])
{
    char path[80];
    getcwd(path, sizeof(path));
    printf("current working directory : %s\n", path);

    char *buf = "/usr/local/var/run";
    strcat(path,buf);

    DIR* dir = opendir(path);
    if (dir)
    {
        printf("path:%s exists\n", path);
        closedir(dir);
    }
    else if (ENOENT == errno)
    {
        printf("path:%s does not exists, going to create it recursively\n", path);
        recur_mkdir(path);
    }
    else
    {
        //TODO:opendir() failed for some other reason.
    }

    recur_mkdir("new/home/abc");

    return 0;
}