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

To accomplish the task I divided in 5 functions on the main file and another 5 
helper functions from previous project in the utils file.

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

The buffer variable is declare as static and this is allow to the its value 
remain while the program is running. 
The buffer_size is defined during the evaluations and should be tested with 
different values.
Once the buffer is initialized as an empty string the function read_from_file 
is called.
``` c
	if (!buffer)
	{
		buffer = malloc(1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
```
`read_from_file` will use a temporary variable called `tmp_buf` to correct 
concatenate with the possible remainer in the variable `buffer`.
The variable `tmp_buf` use malloc to allocate memory of the size `BUFFER_SIZE + 1`
for `'\0'`.
The correct way to handle the failed allocation is to also free the buffer 
before returning NULL, this piece of code will be repeated in the code.
```c
	if (!tmp_buf)
	{
		free(buffer);
		return (NULL);
	}
```
Freeing the buffer if malloc fail or the result is null is standard practice 
and ensure that no memory remains allocated.

The next called function is `read_and_append` and the purpous is to read from 
file descriptor and store the content in `tmp_buf`.
To ensure the read function worked or if evething was readed from the file
the variable `bytes` is created.
```c
	while (!ft_strchr(buffer, '\n') && bytes > 0)
	{
		bytes = read(fd, tmp_buf, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		tmp_buf[bytes] = '\0';
		new_buffer = ft_strjoin(buffer, tmp_buf);
		if (!new_buffer)
		{
			free (buffer);
			return (NULL);
		}
		free (buffer);
		buffer = new_buffer;
	}
```
The while loop will continue until the `\n` is added in the buffer and it has
read something. The call of `ft_strjoin` is used to join the new read(`tmp_buf`)
in the leftover(`buffer`) from previous read.

Once it return the `buffer` will contain the line to be returned and possibly
leftover, so the function `extract_line` is called to create a new string that
will have only the line to be outputed.

To achieve this I uses the function `ft_substr`.

```c
static char	*extract_line(char *buffer)
{
	char	*line;
	size_t	i;

	if (!buffer || buffer[0] == '\0')
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
	{
		line = ft_substr(buffer, 0, i + 1);
		if (!line)
			return (free(buffer), NULL);
}
	else
	{
		line = ft_substr(buffer, 0, i);
		if (!line)
			return (free(buffer), NULL);
	}
	return (line);
}
```

Now my variable `line` has the whole line to be outputed.
My static variable `buffer` at this point still have the line and the leftover.
So the function `update_buffer` is used to update the content of my static
variable for the next call.

```c
static char	*update_buffer(char *buffer)
{
	char	*rest_of_line;
	char	*newline_ptr;
	size_t	rest_len;

	newline_ptr = ft_strchr(buffer, '\n');
	if (!newline_ptr)
	{
		free(buffer);
		return (NULL);
	}
	rest_len = ft_strlen(newline_ptr + 1);
	rest_of_line = ft_substr(newline_ptr + 1, 0, rest_len);
	if (!rest_of_line)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (rest_of_line);
}
```
The key to achieve this, is the use of the `ft_strchr` that will point to the 
`\n` inside te buffer.
Is necessary to increase this pointer by one to point to the next element (because
I don't want the `\n`) and create a substring that will have only the leftovers.

After the call of `update_buffer` the variable `line` has the line to be returned
and the variable `buffer` has the leftover from the read to be appended.

### The Bonus

For the bonus part the function should be able to deal with multiple file descriptor.
To achieve this the static variable is defined as an array of strings `*buffer[MAX_FD]`
and when its called tin the `get_next_line` the file descriptor must be declared.
With the file descriptor declared the string will be saved in `[fd]` position.

```c
char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = malloc(1);
		if (!buffer[fd])
		{
			free(buffer[fd]);
			buffer[fd] = NULL;
			return (NULL);
		}
		buffer[fd][0] = '\0';
	}
	buffer[fd] = read_from_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = extract_line(buffer[fd]);
	buffer[fd] = update_buffer(buffer[fd]);
	return (line);
}
```
