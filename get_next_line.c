/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:31:08 by amaria-d          #+#    #+#             */
/*   Updated: 2022/02/27 17:40:09 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*newLine(int fd, char **line)
{
	ssize_t	reret;

	line[fd] = malloc(BUFFER_SIZE + 1);
	reret = read(fd, line[fd], BUFFER_SIZE);
	if (reret <= 0)
	{
		free(line[fd]);
		line[fd] = NULL;
		return (NULL);
	}
	line[fd][reret] = '\0';
	return (line[fd]);
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
		rest = ft_substr(line[fd], pos - line[fd] + 1, ft_strlen(pos));
		free(line[fd]);
		line[fd] = rest;
	}
	return (new);

}

int	get_more(int fd, char **line)
{
	char	*tmp;
	char	*new;
	ssize_t	reret;

	tmp = malloc(BUFFER_SIZE + 1);
	reret = read(fd, tmp, BUFFER_SIZE);
	if (reret <= -1)
	{
		free(&tmp);
		return (0);
	}
	tmp[reret] = '\0';
	new = ft_strjoin(line[fd], tmp);
	free(line[fd]);
	free(tmp);
	line[fd] = new;
	if (reret == 0)
	{
		return (1);
	}
	return (2);
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
			new = final_prep(fd, line, NULL); 
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

	if (read(fd, 0, 0) || BUFFER_SIZE < 1)
		return (NULL);
	if (line[fd] == NULL)
	{
		if (newLine(fd, line) == NULL)
			return (NULL);
	}
	new = debrisLine(fd, line);
	return (new);
}
