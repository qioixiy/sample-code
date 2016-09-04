#include "minicrt.h"

int main(int argc, char *argv[]) {
	int i;
	FILE *fp;
	char **v;

	printf("start...\n");
	printf("argc:%d\n", argc);
	
	for ( i = argc; i--;) {
		printf("arg[%d]=%s\n",i, argv[i]);
	}
	v = malloc(argc * sizeof(char *));
	
	while(1);
	for (i = 0; i < argc; i++) {
		v[i] = malloc(strlen(argv[i] + 1));
		strcpy(v[i], argv[i]);
		printf("s:%s\n", argv[i]);
	}
	
	printf("start open test.txt...\n");
	if (fp = fopen("test.txt", "w")) {
		printf("open test.txt failes...\n");
	}
	printf("open test.txt ok...\n");
	
	for (i = 0; i < argc; i++) {
		int len = strlen(v[i]);
		fwrite(&len, 1, sizeof(int), fp);
		fwrite(v[i], 1, len, fp);
	}
	fclose(fp);

	fp = fopen("test.txt", "r");
	for (i = 0; i < argc; i++) {
		int len;
		char *buf;
		fread(&len, 1, sizeof(int), fp);
		buf = malloc(len+1);
		fread(buf, 1, len, fp);
		buf[len] = '\0';
		printf("%d %s\n", len, buf);
		free(buf);
		free(v[i]);
	}
	fclose(fp);
}
