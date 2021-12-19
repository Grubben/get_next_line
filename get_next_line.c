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

char	*no_n(int fd, char **line)
{
	ssize_t	reret;
	char	*nlpos;
	char	*new;
	char	*tmp;


	tmp = malloc(BUFFER_SIZE + 1);
	tmp[BUFFER_SIZE] = 0;


	reret = read(fd, tmp, BUFFER_SIZE);	
	if (reret <= -1)
		return (free_ret(&tmp, NULL));
	if (reret == 0)
	{
		free(tmp);
		tmp = ft_substr(line[fd], 0, ft_strlen(line[fd]));	// == ft_strdup(line[fd])
		//if (line[fd] != NULL)
		free_chg(&line[fd], NULL);
		return (tmp);
	}
	
	tmp[reret] = '\0';	// The Golden Trick

	nlpos = ft_strchr(tmp, '\n');
	if (nlpos != NULL)
	{
		if ((size_t)(nlpos - tmp) == ft_strlen(tmp) -1)	// if '\n' is the last character
		{
			new = ft_strjoin(line[fd], tmp);
			free(tmp);
			return (free_ret(&line[fd], new));
		}
		new = ft_substr(tmp, 0, nlpos - tmp + 1 );	// string up to n' including '\n'
		free_chg(&new, ft_strjoin(line[fd], new));	// all the string up to n' including '\n'


		free_chg(&line[fd], ft_substr(tmp, nlpos - tmp + 1, BUFFER_SIZE)); // len = BF is overkill but sufficient for now. It's a max anyway

		return (new);
	}

	free_chg(&line[fd], ft_strjoin(line[fd], tmp));
	free(tmp);
	tmp = NULL;
	
	return (no_n(fd, line));
}

char	*get_next_line(int fd)
{
	static char	*line[MAX_FD];
	char		*nlpos;
	char		*tmp;
	char		*new;
	ssize_t		reret;

	// Input error checker
	if (fd < 0 || (fd > 256 || BUFFER_SIZE < 1))
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

	// Yes a '\n' in line[fd]
	if (nlpos != NULL)
	{
		if ((size_t)(nlpos - line[fd]) == ft_strlen(line[fd]) - 1)	// if it's the last character
		{
			new = ft_substr(line[fd], 0, ft_strlen(line[fd]));	// == ft_strdup(line[fd])
			return (free_ret(&line[fd], new));
		}
		tmp = line[fd];
		new = ft_substr(line[fd], 0, nlpos - line[fd] + 1 );
		line[fd] = ft_substr(tmp, nlpos - tmp + 1, BUFFER_SIZE); // len = BF is overkill but sufficient for now
		return (free_ret(&tmp, new));
	}

	return (no_n(fd, line));
}
