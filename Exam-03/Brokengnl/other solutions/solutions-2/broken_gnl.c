#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	static int	i = 0, r = 0;
	char	*line;
	int	j = 0;

	if (fd < 0 || BUFFER_SIZE <= 0 || !(line = malloc(10000)))
		return (NULL);
	while (1)
	{
		if (i >= r)
		{
			i = 0;
			r = read(fd, buf, BUFFER_SIZE);
			if (r <= 0)
				break ;
		}
		line[j++] = buf[i++];
		if (line[j - 1] == '\n')
			break ;
	}
	if (j)
	{
		line[j] = 0;
		return (line);
	}
	else
	{
		free(line);
		return (NULL);
	}
}