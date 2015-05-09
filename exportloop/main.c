#include <stdio.h>

#include "../src/vgmstream.h"
#include "../src/util.h"

char* remove_extension_and_path(const char* input) {
	// Loop through characters backwards to find extension
	const char* end = input + strlen(input);
	for (const char* ptr = end; ptr >= input; ptr--) {
		if (*ptr == '/' || *ptr == '\\') {
			// No extension
			break;
		} else if (*ptr == '.') {
			// Extension found - remove
			end = ptr;
			break;
		}
	}

	// Loop through characters backwards to find slash/backslash
	const char* start = input;
	for (const char* ptr = end; ptr >= input; ptr--) {
		if (*ptr == '/' || *ptr == '\\') {
			// Found directory separator
			start = ptr + 1;
			break;
		}
	}

	int len = end - start;
	char* buffer = (char*)malloc(len + 1);
	strncpy(buffer, start, len);
	buffer[len] = '\0';

	return buffer;
}

int usage(int retval, char* name) {
	fprintf(stderr, "exportloop\n"
		"\n"
		"Usage: %s [-0L] [-LE] [-0E] {files ...}\n", name);
	return retval;
}

typedef enum {
	START_TO_LOOP = 1,
	LOOP_TO_END = 2,
	START_TO_END = 4
} export_types;

int main(int argc, char** argv) {
	if (argc == 1) {
		return usage(1, argv[0]);
	}

	export_types export_type = 0;

	int i;
	for (i = 1; i < argc; i++) {
		char* arg = argv[i];
		if (arg == NULL) {
			// End of parameters
			break;
		} else if (strcasecmp("-0L", arg) == 0) {
			export_type |= START_TO_LOOP;
		} else if (strcasecmp("-LE", arg) == 0) {
			export_type |= LOOP_TO_END;
		} else if (strcasecmp("-0E", arg) == 0) {
			export_type |= START_TO_END;
		} else if (strcasecmp("--help", arg) == 0) {
			return usage(0, argv[0]);
		} else {
			// End of loop parameters
			break;
		}
	}

	if (export_type == 0) {
		export_type = START_TO_END;
	}

	int filename_count = argc - i;
	char** filenames = argv + i;

	for (int j = 0; j < filename_count; j++) {
		char* infile = filenames[j];

		char* infile_noext = remove_extension_and_path(infile);
		printf("%s\n", infile_noext);

		char* outfile = (char*)malloc(strlen(infile_noext) + 20);

		if (export_type & START_TO_LOOP) {
			sprintf(outfile, "%s (beginning).wav", infile_noext);
			printf("out: %s\n", outfile);
		}
		if (export_type & LOOP_TO_END) {
			sprintf(outfile, "%s (loop).wav", infile_noext);
			printf("out: %s\n", outfile);
		}
		if (export_type & START_TO_END) {
			sprintf(outfile, "%s.wav", infile_noext);
			printf("out: %s\n", outfile);
		}

		free(outfile);
		free(infile_noext);
	}
}
