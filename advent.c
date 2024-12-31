#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

void usage(char *program) {
    fprintf(stderr, "Usage:\n    %s new `filename`\n    or\n    %s use `filename`\n", program, program);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    char *program = *argv;
    bool new = false;
    bool use = false;
    char *filename = NULL;

    if (argc == 3) {
	if (strlen(argv[1]) == 3) {
	    typedef union {
		uint8_t a[2];
		uint16_t b;
	    } check;

	    if (argv[1][0] == 'n') {
		if ((check){
			.a = {
			    argv[1][1],
			    argv[1][2]
			}
		    }.b ==
		    (check){
		        .a = {
			    'e',
			    'w'
			}
		    }.b
		) {
		    new = true;
		    use = false;
		    filename = argv[2];
		}
	    } else if (argv[1][0] == 'u') {
		if ((check){
		        .a = {
			    argv[1][1],
			    argv[1][2]
			}
		    }.b ==
		    (check){
		        .a = {
			    's',
			    'e'
			}
		    }.b
		) {
		    use = true;
		    new = false;
		    filename = argv[2];
		}
	    } else usage(program);
	} else usage(program);
    } else usage(program);

    FILE *fp = NULL;

    if (use) {
	fp = fopen(filename, "r");
    }

    if (new) {
	fp = fopen(filename, "w");
    }
    
    if (fp) fclose(fp);
}
