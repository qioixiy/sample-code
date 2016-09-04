#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <regex.h>
#include <memory.h>

int reg_match()
{
 
    char *bematch = "hhhericchd@gmail.com";
    char *pattern = "h{3,10}(.*)@.{5}.(.*)";
    char errbuf[1024];
    char match[100];
    
    regex_t reg;
    int err,nm = 10;
    regmatch_t pmatch[nm];
 
    if(regcomp(&reg, pattern, REG_EXTENDED) < 0){
        regerror(err, &reg, errbuf, sizeof(errbuf));
        printf("err:%s\n", errbuf);
    }
 
    err = regexec(&reg, bematch, nm, pmatch, 0);
    if(err == REG_NOMATCH){
        printf("no match\n");
        return -1;
    }else if(err){
        regerror(err, &reg, errbuf, sizeof(errbuf));
        printf("err:%s\n", errbuf);
        return -1;
    }

    int i;
    for(i=0; i<10 && pmatch[i].rm_so!=-1; i++){
        int len = pmatch[i].rm_eo - pmatch[i].rm_so;
        if(len){
            memset(match, '\0', sizeof(match));
            memcpy(match, bematch+pmatch[i].rm_so, len);
            printf("%s\n", match);
        }
    }
    regfree(&reg);  
    return 0;
}

int main(int argc, char **argv)
{
    struct stat buf;
    char *fileName = argv[1];
    stat(fileName, &buf);
    if (S_ISDIR(buf.st_mode)) {
        struct dirent *pDirEntry = NULL;
        DIR *pDir = NULL;
        if( (pDir = opendir(fileName)) == NULL ) {
            printf("opendir failed!\n");
            return 1;
        } else {
            while( pDirEntry = readdir(pDir) ) {
                if (DT_REG == pDirEntry->d_type) {
                    printf("%s\n", pDirEntry->d_name);
                }
            }
            closedir(pDir);
        }
    }

    reg_match();
}
