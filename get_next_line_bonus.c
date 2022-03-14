/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:29:13 by amaria-d          #+#    #+#             */
/*   Updated: 2022/02/08 13:29:14 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*free_ret_bns(char **toleave, char *toret)
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
void	free_chg_bns(char **tofree, char *newval)
{
	free(*tofree);
	*tofree = newval;
}

char	*make_new_bns(int fd, char **line, char **adtmp)
{
	char	*nlpos;
	char	*new;
	char	*tmp;

	tmp = *adtmp;
	nlpos = ft_strchr_bns(tmp, '\n');
	if (nlpos != NULL)
	{
		new = ft_substr_bns(tmp, 0, nlpos - tmp + 1);
		free_chg_bns(&new, ft_strjoin_bns(line[fd], new));
		if ((size_t)(nlpos - tmp) == ft_strlen_bns(tmp) - 1)
			free_chg_bns(&line[fd], NULL);
		else
			free_chg_bns(&line[fd],
				ft_substr_bns(tmp, nlpos - tmp + 1, ft_strlen_bns(line[fd])));
		free(tmp);
		return (new);
	}
	free_chg_bns(&line[fd], ft_strjoin_bns(line[fd], tmp));
	free(tmp);
	return (NULL);
}

char	*no_n_bns(int fd, char **line)
{
	ssize_t	reret;
	char	*new;
	char	*tmp;

	new = NULL;
	while (new == NULL)
	{
		tmp = malloc(BUFFER_SIZE + 1);
		reret = read(fd, tmp, BUFFER_SIZE);
		if (reret <= -1)
			return (free_ret_bns(&tmp, NULL));
		if (reret == 0)
		{
			free_chg_bns(&tmp, ft_substr_bns(line[fd], 0, ft_strlen_bns(line[fd])));
			free_chg_bns(&line[fd], NULL);
			return (tmp);
		}
		tmp[reret] = '\0';
		new = make_new_bns(fd, line, &tmp);
	}
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*line[MAX_FD];
	char		*nlpos;
	char		*new;
	ssize_t		reret;

	if (read(fd, 0, 0) || BUFFER_SIZE < 1)
		return (NULL);
	if (line[fd] == NULL)
	{
		line[fd] = malloc(BUFFER_SIZE + 1);
		reret = read(fd, line[fd], BUFFER_SIZE);
		if (reret <= 0)
			return (free_ret_bns(&line[fd], NULL));
		line[fd][reret] = '\0';
	}
	nlpos = ft_strchr_bns(line[fd], '\n');
	if (nlpos == NULL)
		return (no_n_bns(fd, line));
	new = ft_substr_bns(line[fd], 0, nlpos - line[fd] + 1);
	if ((size_t)(nlpos - line[fd]) == ft_strlen_bns(line[fd]) - 1)
		free_chg_bns(&line[fd], NULL);
	else
		free_chg_bns(&line[fd], ft_substr_bns(line[fd],
				nlpos - line[fd] + 1, ft_strlen_bns(line[fd])));
	return (new);
}
