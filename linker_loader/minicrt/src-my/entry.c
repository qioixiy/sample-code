#include "minicrt.h"

#ifdef WIN32
#include <Windows.h>
#endif

int mini_crt_heap_init(void);/*heap init*/
int mini_crt_io_init(void);/*io init*/
int mini_crt_exit_rountine(void);/*exit*/

extern int main(int argc, char *argv[]);

void exit(int exitcode) {
	mini_crt_call_exit_routine();
#ifdef WIN32
	ExitProcess(exitcode);
#else
	asm("movl %0, %%ebx \n\t"
		"movl $1, %%eax \n\t"
		"int $0x80 \n\t"
		"hlt \n\t"
		:
		:"m"(exitcode)
		:);
#endif
}

static void crt_fatal_error(const char *msg) {
	printf("fatal error: %s", msg);
	exit(1);
}

void mini_crt_entry(void){
	int ret;
	
#ifdef WIN32
	int flag = 0;
	int argc = 0;
	char *argv[16];/*16 params*/
	char *cl = GetCommandLineA();

	char param[20];
	int i= 0, j = 0;
	for (; cl[i]; i++) {
		if (cl[i] == cl[i+1]) {
			if (cl[i] == ' ') {
				continue;
			}
		}
		param[j] = cl[i];
		j++;
	}
	param[j] = '\0';
	printf("%s\n", cl);
	printf("%s\n", param);
	
	argv[0] = param;
	//argv[0] = cl;
	cl = param;
	argc++;
	while(*cl) {
		if (*cl == '\"') {
			if (flag == 0) {
				flag = 1;
			} else {
				flag = 0;
			}
		} else if (*cl == ' ' && flag == 0) {
			if (*(cl+1)) {
				argv[argc] = cl + 1;
				argc++;
			}
			*cl = '\0';
		}
		cl++;
	}
#else
	int argc;
	char ** argv;
	char * ebp_reg = 0;
	//ebp_reg = %ebp;
	asm("
		movl %%ebp, %0\n"
		:"=r"(ebp_reg)
		::);
	argc = *(int *)(ebp_reg+4);
	argv = (char **)(ebp_reg+8);
#endif

	if (!mini_crt_heap_init()) {
		crt_fatal_error("heap initialize failed!\n");
	}else {
		printf("%s\n", "mem init ok");
	}
	if (!mini_crt_io_init()) {
		crt_fatal_error("io initialize failed!\n");
	}
	
	ret = main(argc, argv);
	
	exit(ret);
}

void mini_crt_call_exit_routine(void) {
	return;
}