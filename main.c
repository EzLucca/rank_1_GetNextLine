#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include "get_next_line.h"

int main(int argc, char **argv)
{
	// Open all files passed on the command line.
	int file_count = argc - 1;
	int files[file_count + 1];
	if (argc > 1) {
		for (int i = 0; i < file_count; i++)
			files[i] = open(argv[i + 1], O_RDONLY);

	// Use standard input if no files were given.
	} else {
		files[0] = 0;
		file_count = 1;
	}

	// Keep track of how many files are active.
	int active_count = file_count;
	char file_is_active[file_count];
	memset(file_is_active, 1, sizeof(file_is_active));

	// Cycle between active files, printing one line from each.
	for (int i = 0; active_count > 0; i = (i + 1) % file_count) {
		if (file_is_active[i]) {
			char *line = get_next_line(files[i]);
			if (line == NULL) {
				file_is_active[i] = 0;
				active_count--;
			} else {
				printf("%s", line);
				free(line);
			}
		}
	}
}
