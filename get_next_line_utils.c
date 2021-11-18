/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 18:34:26 by amaria-d          #+#    #+#             */
/*   Updated: 2021/11/17 13:02:37 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	i = 0;
	while (i < len + 1)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*ptr;

	len = ft_strlen(s1);
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*	SUBSTR	*/
static int	ft_smin(long long a, long long b)
{
	if (a < b)
		return (a);
	return (b);
}
/*
len does not include the '\0'
    even though it is added to the end
        of the string
in other words:
    
    string[len] == '\0'

Things to add:
	long long	min;
	min = ft_smin((long long)start, (long long)len);
	ptr = ft_calloc(min + 1, sizeof(char));
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		slen;
	size_t		i;
	char		*ptr;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start < slen)
	{
		ptr = ft_calloc(ft_smin(slen, len) + 1, sizeof(char));
		if (!ptr)
			return (NULL);
		i = 0;
		while (start + i < slen && i < len)
		{
			ptr[i] = s[start + i];
			i++;
		}
		return (ptr);
	}
	ptr = ft_calloc(1, 1);
	if (!ptr)
		return (NULL);
	return (ptr);
}
/*	SUBSTR	*/
