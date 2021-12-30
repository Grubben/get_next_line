/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 14:49:10 by amaria-d          #+#    #+#             */
/*   Updated: 2021/12/28 14:49:11 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

///*
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
int	main(void)
{
	int		fd;
	char		*info;
	//char	*reret;

	fd = open("trash.txt", O_RDONLY);

	//printf("%d\n", BUFFER_SIZE);

	//reret = get_next_line(fd);
	//printf("%i", reret[0]);
	//printf("%i", reret[1]);
	
	//printf("%s", get_next_line(1000));
	//printf("%s", get_next_line(-1));
	//printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));

	while (1)
	{
		info = get_next_line(fd);
		if (info == NULL)
			break;
		printf("%s", info);
		free(info);
	}
	//printf("\n%d\n", !strcmp("0", "01"));
	close(fd);

	return (0);
}
