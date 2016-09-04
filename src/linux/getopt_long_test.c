/*
 * ./test -f cdr -o cdr.txt -c cdr.desc -k 123456
 * ./test --file cdr --output cdr.txt --config cdr.desc --keyword 123456
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

void print_usage(const char *program_name) {
	printf("%s 1.0.0 (2010-06-13)\n", program_name);
	printf("This is a program decoding a BER encoded CDR file\n");
	printf("Usage: %s -f <file_name> -o <output_name> [-c <config_name>] [-k <keyword>]\n", program_name);
	printf("    -f --file       the CDR file to be decoded\n");
	printf("    -o --output     the output file in plain text format\n");
	printf("    -c --config     the description file of the CDR file, if not given, use default configuration\n");
	printf("    -k --keyword    the keyword to search, if not given, all records will be written into output file\n");
}

int main(int argc, char *argv[]) {
	char *file_name = NULL;
	char *output_name = NULL;
	char *config_name = NULL;
	char *keyword = NULL;

	const char *short_opts = "hf:o:c:k:";
	const struct option long_opts[] = {
		{"help", no_argument, NULL, 'h'},
		{"file", required_argument, NULL, 'f'},
		{"output", required_argument, NULL, 'o'},
		{"config", required_argument, NULL, 'c'},
		{"keyword", required_argument, NULL, 'k'},
		{0, 0, 0, 0}
	};
	int hflag = 0;

	int c;
	opterr = 0;

	while ( (c = getopt_long(argc, argv, short_opts, long_opts, NULL)) != -1 ) {
		switch ( c ) {
		case 'h' :
			hflag = 1;
			break;
		case 'f' :
			file_name = optarg;
			break;
		case 'o' :
			output_name = optarg;
			break;
		case 'c' :
			config_name = optarg;
			break;
		case 'k' :
			keyword = optarg;
			break;
		case '?' :
			if ( optopt == 'f' || optopt == 'o' || optopt == 'c' || optopt == 'k' )
				printf("Error: option -%c requires an argument\n", optopt);
			else if ( isprint(optopt) )
				printf("Error: unknown option '-%c'\n", optopt);
			else
				printf("Error: unknown option character '//x%x'\n", optopt);
			return 1;
		default :
			abort();
		}
	}

	if ( hflag || argc == 1 ) {
		print_usage(argv[0]);
		return 0;
	}
	if ( !file_name ) {
		printf("Error: file name must be specified\n");
		return 1;
	}
	if ( !output_name ) {
		printf("Error: output name must be specified\n");
		return 1;
	}

	// if not setting default, Linux OK, but SunOS core dump
	if ( !config_name ) config_name = "(null)";
	if ( !keyword ) keyword = "(null)";
	printf("Parameters got: file_name = %s, output_name = %s, config_name = %s, keyword = %s\n", file_name, output_name, config_name, keyword);
	return 0;
}
