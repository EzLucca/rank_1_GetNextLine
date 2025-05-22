# Get Next Line

## Project from 42 school defendet at Hive Helsinki

Repeated calls (e.g., using a loop) to your get_next_line() function should let
you read the text file pointed to by the file descriptor, one line at a time.

Your function should return the line that was read.
If there is nothing left to read or if an error occurs, it should return NULL

Please note that the returned line should include the terminating \n character,
except when the end of the file is reached and the file does not end with a \n
character

### The Functions 

To accomplish the task I divided in 5 functions on the main file and another 5 helper functions
from previous project in the utils file.

Helper functions int file `get_next_line_utils.c`:
``` c
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *buffer, char *tmp_buf);
char	*ft_substr(char *s, unsigned int start, size_t len);
```

Functions on file `get_next_line.c`:
```c
char	*get_next_line(int fd);
static char	*read_from_file(int fd, char *buffer);
static char	*read_and_append(int fd, char *buffer, char *tmp_buf, ssize_t bytes);
static char	*extract_line(char *buffer);
static char	*update_buffer(char *buffer);
```

### The logic

Here I will explain the logic on the file `get_next_line.c`.

The buffer variable is declare as static and this is allow to the its value remain while
the program is running. 
The buffer_size is defined during the evaluations and should be tested with different values.
Once the buffer is initialized as an empty string the function read_from_file is called.
``` c
	if (!buffer)
	{
		buffer = malloc(1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
```
`read_from_file` will use a temporary variable called `tmp_buf` to correct concatenate 
with the possible remainer in the variable `buffer`.
