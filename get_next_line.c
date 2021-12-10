#include "get_next_line.h"

char	*free_ret(char **toleave, char *toret)
{
	free(*toleave);
	*toleave = NULL;
	return (toret);
}


char	*get_next_line(int fd)
{
	static char	*line[MAX_FD];
	char		*nlpos;
	char		*tmp;
	char		*new;
	char		*other;
	ssize_t		reret;

	// Input error checker
	if (fd < 0 || (fd > 256 || BUFFER_SIZE < 1))
		return (NULL);

	if (line[fd] == NULL)
	{
		//line[fd] = calloc(BUFFER_SIZE + 1, sizeof(char));
		line[fd] = malloc(BUFFER_SIZE + 1);
		line[fd][BUFFER_SIZE] = 0;

		reret = read(fd, line[fd], BUFFER_SIZE);
		if (reret <= -1)
			return (NULL);
		else if (reret == 0)
		{
			free(line[fd]);
			line[fd] = NULL;
			return (NULL);
		}
	}

	nlpos = ft_strchr(line[fd], '\n');	// NOTE it's done on line[fd] not tmp

	// Yes a '\n' in line[fd]
	if (nlpos != NULL)
	{
		if ((size_t)(nlpos - line[fd]) == ft_strlen(line[fd]) - 1)	// if it's the last character
		{
			new = ft_substr(line[fd], 0, ft_strlen(line[fd]));	// This used to be a ft_strdup
			free(line[fd]);
			line[fd] = NULL;
			return (new);
		}
		tmp = line[fd];
		new = ft_substr(line[fd], 0, nlpos - line[fd] + 1 );
		line[fd] = ft_substr(tmp, nlpos - tmp + 1, BUFFER_SIZE); // len = BF is overkill but sufficient for now
		free(tmp);
		return (new);
	}
	// No '\n' in line[fd]
	tmp = malloc(BUFFER_SIZE + 1);
	tmp[BUFFER_SIZE] = 0;
	//nlpos = ft_strchr(tmp, '\n');
	while (nlpos == NULL)
	{
		reret = read(fd, tmp, BUFFER_SIZE);	
		if (reret <= -1)
			return (NULL);
		// read makes sure this happens by itself by adding weird stuff to last read!!!!!!!!!!
		if (reret == 0)
		{
			free(tmp);
			// new = ft_strdup(line[fd]);	//	This can also be expressed as a ft_substr
			new = ft_substr(line[fd], 0, ft_strlen(line[fd]));
			free(line[fd]);
			line[fd] = NULL;
			return (new);
		}
		tmp[reret] = '\0';	// The Golden Trick
		nlpos = ft_strchr(tmp, '\n');
		if (nlpos != NULL)
			break ;
		new = ft_strjoin(line[fd], tmp);	// not sure what happens if line[fd] is empty
		free(line[fd]);
		line[fd] = new;
	}
	// return (line[fd]) up till '\n'
	// what if nlpos is the last char of line[fd]!!!
	if ((size_t)(nlpos - tmp) == ft_strlen(tmp) -1)	// if it's the last character
	{
		new = ft_strjoin(line[fd], tmp);
		free(tmp);
		free(line[fd]);
		line[fd] = NULL;
		return (new);
	}
	other = ft_substr(tmp, 0, nlpos - tmp + 1 );	// string up to n' including '\n'	
	new = ft_strjoin(line[fd], other);	// line[fd] + string up to n' including '\n'
	free(other);
	free(line[fd]);
	line[fd] = ft_substr(tmp, nlpos - tmp + 1, BUFFER_SIZE); // len = BF is overkill but sufficient for now. It's a max anyway
	free(tmp);

	return (new);
}
