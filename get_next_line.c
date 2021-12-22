#include "get_next_line.h"

char	*free_ret(char **toleave, char *toret)
{
	free(*toleave);
	*toleave = NULL;
	return (toret);
}

/* x = b;
 * free(a);
 * ->
 *  free_chg(x, b);
*/
void	free_chg(char **tofree, char *newval)
{
	free(*tofree);
	*tofree = newval;
}

char	*make_new(int fd, char **line, char **adtmp)
{
	char	*nlpos;
	char	*new;
	char	*tmp;

	tmp = *adtmp;
	

	nlpos = ft_strchr(tmp, '\n');
	if (nlpos != NULL)
	{
		new = ft_substr(tmp, 0, nlpos - tmp + 1 );	// tmp up to n' including '\n'
		free_chg(&new, ft_strjoin(line[fd], new));	// all the string up to n' including '\n'
		if ((size_t)(nlpos - tmp) == ft_strlen(tmp) -1)	// if '\n' is the last character
			free_chg(&line[fd], NULL);
		else
			free_chg(&line[fd], ft_substr(tmp, nlpos - tmp + 1, ft_strlen(line[fd]))); // len = strlen is overkill but sufficient for now. It's a max anyway
		free(tmp);
		return (new);
	}
	free_chg(&line[fd], ft_strjoin(line[fd], tmp));
	free(tmp);

	return (NULL);
}

char	*no_n(int fd, char **line)
{
	ssize_t	reret;
	char	*new;
	char	*tmp;


	tmp = malloc(BUFFER_SIZE + 1);
	//tmp[BUFFER_SIZE] = 0;
	reret = read(fd, tmp, BUFFER_SIZE);	
	if (reret <= -1)
		return (free_ret(&tmp, NULL));
	if (reret == 0)
	{
		free_chg(&tmp, ft_substr(line[fd], 0, ft_strlen(line[fd])));	// => tmp = ft_strdup(line[fd])
		free_chg(&line[fd], NULL);
		return (tmp);
	}
	tmp[reret] = '\0';	// The Golden Trick

	new = make_new(fd, line, &tmp);
	if (new == NULL)
		return (no_n(fd, line));
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*line[MAX_FD];
	char		*nlpos;
	char		*new;
	ssize_t		reret;

	if (fd < 0 || (fd > 256 || BUFFER_SIZE < 1))	// Input error checker
		return (NULL);
	if (line[fd] == NULL)
	{
		line[fd] = malloc(BUFFER_SIZE + 1);
		line[fd][BUFFER_SIZE] = 0;

		reret = read(fd, line[fd], BUFFER_SIZE);
		if (reret <= 0)
			return (free_ret(&line[fd], NULL));
		line[fd][reret] = '\0';	// Magic trick
	}
	nlpos = ft_strchr(line[fd], '\n');	// NOTE it's done on line[fd] not tmp
	if (nlpos != NULL)	// Yes a '\n' in line[fd]
	{
		new = ft_substr(line[fd], 0, nlpos - line[fd] + 1 );	// tmp up to n' including '\n'
		if ((size_t)(nlpos - line[fd]) == ft_strlen(line[fd]) -1)	// if '\n' is the last character
			free_chg(&line[fd], NULL);
		else
			free_chg(&line[fd], ft_substr(line[fd], nlpos - line[fd] + 1, ft_strlen(line[fd]))); // len = strlen is overkill but sufficient for now. It's a max anyway
		return (new);
	}
	return (no_n(fd, line));
}
