/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:29:27 by amaria-d          #+#    #+#             */
/*   Updated: 2021/11/17 13:18:28 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif


size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

void	*ft_calloc(size_t count, size_t size);

size_t	ft_strlen(const char *s);

char	*ft_strchr(const char *s, int c);

char	*ft_strdup(const char *s1);

char	*ft_substr(char const *s, unsigned int start, size_t len);
