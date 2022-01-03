/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 18:34:26 by amaria-d          #+#    #+#             */
/*   Updated: 2021/12/28 16:33:32 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
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
	size_t		min;
	size_t		i;
	char		*ptr;

	if (!s)
		return (NULL);
	min = len;
	if (ft_strlen(s + start) < len)
		min = ft_strlen(s + start);
	if (start >= ft_strlen(s))
		ptr = malloc(1);
	else
		ptr = malloc((min + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ptr);
	i = 0;
	while (i < min)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;
	size_t	sl1;
	size_t	sl2;

	if (!s1)
		return (NULL);
	sl1 = ft_strlen(s1);
	sl2 = ft_strlen(s2);
	ptr = malloc(sl1 + sl2 + 1);
	if (!ptr)
		return (NULL);
	j = 0;
	i = 0;
	while (i < sl1)
		ptr[j++] = s1[i++];
	i = 0;
	while (i < sl2)
		ptr[j++] = s2[i++];
	ptr[j] = '\0';
	return (ptr);
}
