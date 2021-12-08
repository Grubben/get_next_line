/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prafael- <prafael-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 15:23:29 by prafael-          #+#    #+#             */
/*   Updated: 2021/09/25 15:23:30 by prafael-         ###   ########.fr       */
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
	//char	*reret;

	fd = open("trash.txt", O_RDONLY);

	//printf("%d\n", BUFFER_SIZE);

	//reret = get_next_line(fd);
	//printf("%i", reret[0]);
	//printf("%i", reret[1]);
	
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));

	/*
	while (1)
	{
		reret = get_next_line(fd);
		if (reret == NULL)
			break;
		printf("%s", reret);
	}
	//printf("\n%d\n", !strcmp("0", "01"));
	*/
	close(fd);

	return (0);
}
