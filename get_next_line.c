/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:31:08 by amaria-d          #+#    #+#             */
/*   Updated: 2022/02/08 13:31:09 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
 *	free_chg(x, b);
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
		new = ft_substr(tmp, 0, nlpos - tmp + 1);
		free_chg(&new, ft_strjoin(line[fd], new));
		if ((size_t)(nlpos - tmp) == ft_strlen(tmp) - 1)
			free_chg(&line[fd], NULL);
		else
			free_chg(&line[fd],
				ft_substr(tmp, nlpos - tmp + 1, ft_strlen(line[fd])));
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

	tmp = ft_substr(line[fd], 0, ft_strlen(line[fd])); //copy



		if (reret <= -1)
		{
			free(tmp);
			return (NULL);
		}
		if (reret == 0)
		{
			free(&tmp);
			tmp = ft_substr(line[fd], 0, ft_strlen(line[fd]));
			free(line[fd]);
			line[fd] = NULL;
			return (tmp);
		}
		tmp[reret] = '\0';
		new = make_new(fd, line, &tmp);
	}
	return (new);
}

void	emptyRead(int fd, char **line)
{
	ssize_t	reret;

	line[fd] = malloc(BUFFER_SIZE + 1);
	reret = read(fd, line[fd], BUFFER_SIZE);
	if (reret <= 0)
	{
		free(line[fd]);
		return ;
	}
	line[fd][reret] = '\0';
}

char	*debrisRead(int fd, char **line)
{
	char	*nlpos;
	char	*new;

	nlpos = ft_strchr(line[fd], '\n');
	if (nlpos == NULL)
	{
		no_n(fd, line);
		return (debrisRead(fd, line));
	}
	new = ft_substr(line[fd], 0, nlpos - line[fd] + 1);
	if ((size_t)(nlpos - line[fd]) == ft_strlen(line[fd]) - 1)
	{
		free(&line[fd]);
		line[fd] = NULL;
	}
	else
	{
		free(&line[fd]);
		line[fd] = ft_substr(line[fd], nlpos - line[fd] + 1, ft_strlen(line[fd]));
		// !!! WRONG !!!
	}
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*line[MAX_FD];
	char		*new;
	ssize_t		check;

	if (read(fd, 0, 0) || BUFFER_SIZE < 1)
		return (NULL);
	if (line[fd] == NULL)
	{
		check = emptyRead(fd, line);
		if (check <= 0)
			return (NULL);
	}
	new = debrisRead(fd, line);
	return (new);
}
