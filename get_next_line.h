/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:29:27 by amaria-d          #+#    #+#             */
/*   Updated: 2021/11/22 18:14:26 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);

size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);

void   *ft_calloc(size_t count, size_t size);

size_t ft_strlen(const char *s);

char	*ft_strchr(const char *s, int c);

char	*ft_strdup(const char *s1);

void	ft_bzero(void *s, size_t n);

char	*ft_substr(char const *s, unsigned int start, size_t len);

void	*ft_memmove(void *dst, const void *src, size_t len);

#endif
