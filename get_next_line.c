/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:31:08 by amaria-d          #+#    #+#             */
/*   Updated: 2022/02/27 18:03:41 by amaria-d         ###   ########.fr       */
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


char	*final_prep(int fd, char **line, char *nlpos)
{
	char	*new;
	char	*rest;

	if (nlpos == NULL)
	{
		new = ft_substr(line[fd], 0, ft_strlen(line[fd])); //copy
		free(line[fd]);
		line[fd] = NULL;
	}
	else
	{
		if ((size_t)(nlpos - line[fd]) == ft_strlen(line[fd]) - 1) // if nl is last char of string
		{
			new = ft_substr(line[fd], 0, ft_strlen(line[fd])); //copy
			free(line[fd]);
			line[fd] = NULL;
			return (new);
		}
		// else
		new = ft_substr(line[fd], 0, nlpos - line[fd] + 1);
		rest = ft_substr(line[fd], nlpos - line[fd] + 1, ft_strlen(nlpos));
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
		free(tmp);
		return (-1);
	}
	if (reret == 0)
	{
		free(tmp);
		return (0);
	}
	tmp[reret] = '\0';
	new = ft_strjoin(line[fd], tmp);
	free(line[fd]);
	free(tmp);
	line[fd] = new;
	return (1);
}

char	*debrisLine(int fd, char **line)
{
	char	*nlpos;
	char	*new;
	ssize_t	tmp;

	nlpos = ft_strchr(line[fd], '\n');
	if (nlpos == NULL)
	{
		tmp = get_more(fd, line);
		if (tmp == -1)
			return (NULL);
		if (tmp == 0)
		{
			new = final_prep(fd, line, NULL); 
			return (new);
		}
		if (tmp == 1)
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
