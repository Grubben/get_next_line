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

	if (line != NULL && ft_strchr(line, '\n') != NULL)	// NOTE it's done on line not tmp
	{
		nlpos = ft_strchr(line, '\n'); 
		new = ft_substr(tmp, 0, nlpos - tmp + 1 );
		free(line);
		line = ft_substr(tmp, nlpos - tmp + 1, BUFFER_SIZE); // len = BF is overkill but sufficient for now
		return (new);
	}

	// line can be == NULL or no '\n' in line

	if (line == NULL)
		line = malloc(BUFFER_SIZE + 1);	// if there's stuff inside it'll get deleted

	nlpos = NULL;
	while (nlpos == NULL)
	{
		reret = read(fd, tmp, BUFFER_SIZE);	
		if (reret == -1)
			return (NULL);
		nlpos = ft_strchr(tmp, '\n');
		if (reret == 0)
		{
			if (nlpos == NULL)
			{
				free(line);
				return (ft_strjoin(line, tmp));
			}
			else
				break ;
		}
		tmp[reret] = '\0';
		new = ft_strjoin(line, tmp);	// not sure what happens if line is empty
		free(line);
		line = new;
	}
	// return (line) up till '\n'
	// what if nlpos is the last char of line!!!
	other = ft_substr(tmp, 0, nlpos - tmp + 1 );
	new = ft_strjoin(line, other);	// string up to n' including '\n'
	free(line);
	line = ft_substr(tmp, nlpos - tmp + 1, BUFFER_SIZE); // len = BF is overkill but sufficient for now. It's a max anyway

	return (new);
}
