/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:33:23 by amaria-d          #+#    #+#             */
/*   Updated: 2021/11/17 13:17:15 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	lasline[BUFFER_SIZE * 2];	// needs to be double because we're going to join the new with the potentially
	char		*nlpos;						// very large old


	if (read(fd, lasline, BUFFER_SIZE) != -1)
	{
		nlpos = ft_strchr(lasline, '\n');
		if (nlpos == NULL)
			return (ft_strdup(lasline));
		else
			return (ft_substr(lasline, 0, 3)); // 3 does not include '\0' -> would make it 4 but substr might already do that for us
	}
	return (NULL);
}

int	main(void)
{
	int		fd;
	
	fd = open("trash.txt", O_RDONLY);

	printf("%s\n", get_next_line(fd));
	//printf("%s\n", str + 26 );

	close(fd);

	return (0);
}

