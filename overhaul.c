#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*line;
	char		*nlpos;
	char		tmp[BUFFER_SIZE + 1];
	char		*new;
	char		*other;
	ssize_t		reret;

	// Input error checker
	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 1)
		return (NULL);

	if (line == NULL)
	{
		line = calloc(BUFFER_SIZE + 1, sizeof(char));
		reret = read(fd, line, BUFFER_SIZE);
		if (reret <= -1)
			return (NULL);
		else if (reret == 0)
		{
			free(line);
			line = NULL;
			return (NULL);
		}
		//else
		//	return (get_next_line(fd));
	}

	nlpos = ft_strchr(line, '\n'); 
	if (nlpos != NULL)	// NOTE it's done on line not tmp
	{
		if ((size_t)(nlpos - line) == ft_strlen(line) - 1)	// if it's the last character
		{
			new = ft_strdup(line);	//	This can also be expressed as a ft_substr
			free(line);
			line = NULL;
			return (new);
		}
		other = line;
		new = ft_substr(line, 0, nlpos - line + 1 );
		line = ft_substr(other, nlpos - other + 1, BUFFER_SIZE); // len = BF is overkill but sufficient for now
		free(other);
		return (new);
	}


	// No '\n' in line

	nlpos = ft_strchr(tmp, '\n');
	while (nlpos == NULL)
	{
		reret = read(fd, tmp, BUFFER_SIZE);	
		if (reret <= -1)
			return (NULL);
		// read makes sure this happens by itself by adding weird stuff to last read!!!!!!!!!!
		if (reret == 0)
		{
			new = ft_strdup(line);	//	This can also be expressed as a ft_substr
			free(line);
			line = NULL;
			return (new);
		}
		tmp[reret] = '\0';	// The Golden Trick
		nlpos = ft_strchr(tmp, '\n');
		if (nlpos != NULL)
			break ;
		new = ft_strjoin(line, tmp);	// not sure what happens if line is empty
		free(line);
		line = new;
	}
	// return (line) up till '\n'
	// what if nlpos is the last char of line!!!
	if ((size_t)(nlpos - tmp) == ft_strlen(tmp) -1)	// if it's the last character
	{
		new = ft_strjoin(line, tmp);
		free(line);
		line = NULL;
		return (new);
	}
	other = ft_substr(tmp, 0, nlpos - tmp + 1 );	// string up to n' including '\n'	
	new = ft_strjoin(line, other);	// line + string up to n' including '\n'
	free(other);
	free(line);
	line = ft_substr(tmp, nlpos - tmp + 1, BUFFER_SIZE); // len = BF is overkill but sufficient for now. It's a max anyway

	return (new);
}
