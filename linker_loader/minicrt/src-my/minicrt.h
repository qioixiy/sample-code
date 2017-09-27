#ifndef _MINICRT_H
#define _MINICRT_H

#define NULL ((void)0)

void mini_crt_entry(void);

/*memory*/
int mini_crt_heap_init(void);
void free(void *);
void * malloc(unsigned);

/*io*/
typedef int FILE;
#define EOF (-1)
#ifdef WIN32
#define stdin ((FILE*)GetStdHandle(STD_INPUT_HANDLE))
#define stdout ((FILE*)GetStdHandle(STD_OUTPUT_HANDLE))
#define stderr ((FILE*)GetStdHandle(STD_ERROE_HANDLE))
#else
#define stdin (FILE*(0))
#define stdout (FILE*(1))
#define stderr (FILE*(2))
#endif
FILE *fopen(const char *filename, const char *mode);
int fread(void *buffer, int size, int count, FILE *stream);
int fwrite(const void *buffer, int size, int count, FILE *stream);
int fclose(FILE *fp);
int fseek(FILE *fp, int offset, int set );
	
/*string*/
unsigned strlen(const char *str);
char *strcpy(char *dest, const char *src);
char *itoa(int n, char *str, int radix);
int strcmp(const char *src, const char * dst);

/*print*/
int fputc(int c, FILE *stream);
int fputs(const char *str, FILE *stream);
int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);

/*internal*/
void do_global_ctors();
void mini_crt_call_exit_routine();

/*atexit*/
typedef void (*atexit_func_t)(void);
int atexit(atexit_func_t func);

#endif
