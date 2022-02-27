/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:31:08 by amaria-d          #+#    #+#             */
/*   Updated: 2022/02/27 16:55:44 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_more(int fd, char **line)
{
	char	*tmp;
	char	*reret;

	tmp = malloc(BUFFER_SIZE + 1);
	reret = read(fd, tmp, BUFFER_SIZE);
	if (reret <= -1)
	{
		free(&tmp);
		return (0);
	}
	if (reret = 0)
	{
		final_prep(fd, line, NULL);
		return (1);
	}
	return (2);
}

char	*final_prep(int fd, char **line, char *pos)
{
	char	*new;
	char	*rest;

	if (pos == NULL)
	{
		new = ft_substr(line[fd], 0, ft_strlen(line[fd])); //copy
		free(line[fd]);
		line[fd] = NULL;
	}
	else
	{
		new = ft_substr(line[fd], 0, pos - line[fd]);
		rest = ft_substr(line[fd], pos - line[fd] + 1, ft_strlen(line[fd] + pos));
		free(line[fd]);
		line[fd] = rest;
	}
	return (new);

}

char	*debrisLine(int fd, char **line)
{
	char	*nlpos;
	char	*new;
	int	tmp;

	nlpos = ft_strchr(line[fd], '\n');
	if (nlpos == NULL)
	{
		tmp = get_more(fd, line); 
		if (tmp == 0)
			return (NULL);
		if (tmp == 1)
		{
			new = final_prep(fd, line, ft_strlen(line[fd]));
			return (new);
		}
		if (tmp == 2)
			return (debrisLine(fd, line));
	}
	new = final_prep(fd, line, nlpos);
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
