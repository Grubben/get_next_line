#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*line;
	char		*nlpos;
	char		tmp[BUFFER_SIZE + 1];
	char		*new;
	char		*other;


	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 1)
		return (NULL);

	if (line != NULL)
	{
		nlpos = ft_strchr(line, '\n');	// NOTE it's done on line not tmp
		if (nlpos == NULL) 
		{
			// GOTO 24
		}
		else
			// GOTO 37
	}
	// Presuming no carry-on from past (== beginning)
	read(fd, tmp, BUFFER_SIZE);	
	nlpos = ft_strchr(tmp, '\n');
	while (nlpos == NULL)
	{
		new = ft_strjoin(line, tmp);	// not sure what happens if one is empty
		free(line);
		line = new;
		read(fd, tmp, BUFFER_SIZE);	
		nlpos = ft_strchr(line, '\n');
	}
	// return (line) up till '\n'
	other = ft_substr(tmp, 0, nlpos - tmp + 1 );
	new = ft_strjoin(line, other);	// string up to n' including '\n'
	free(line);
	line = ft_substr(tmp, nlpos - tmp + 1, BUFFER_SIZE); // len = BF is overkill but sufficient for now
	// what if nlpos is the last char of line!!!

	return (new);
}
