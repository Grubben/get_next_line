/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:33:23 by amaria-d          #+#    #+#             */
/*   Updated: 2021/11/22 18:42:36 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	lasline[BUFFER_SIZE + 1];
	char		*nlpos;
	char		*new;
	size_t		nlidx;
	ssize_t		reret;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 1)
		return (NULL);
	nlpos = ft_strchr(lasline, '\n');
	if (lasline[0] == 0)
	{
		reret = read(fd, lasline, BUFFER_SIZE); 
		if (reret == -1)
				return (NULL);
		if (nlpos == NULL)
		{
			new = ft_strdup(lasline);
			ft_bzero(lasline, BUFFER_SIZE + 1);
			return (new);			
		}
	}
	nlidx = nlpos - lasline;
	new = ft_substr(lasline, 0, nlidx + 1);
	ft_memmove(lasline, lasline + nlidx + 1, BUFFER_SIZE - 1 - nlidx);
	ft_bzero(lasline + BUFFER_SIZE - 1 - nlidx, nlidx + 1);
	return (new);
}

/*
#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	int		fd;
	//char	lasline[42];
	
	fd = open("trash.txt", O_RDONLY);

	//printf("%d\n", BUFFER_SIZE);

	printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));

	//while (get_next_line(fd) != NULL)
	//	printf("\n||\n");


	close(fd);

	return (0);
}
*/
