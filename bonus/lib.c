/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:52:32 by edvicair          #+#    #+#             */
/*   Updated: 2022/08/10 13:37:45 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || (s1[i] == '\0' && s2[i] == '\0'))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*buya;
	size_t	i;

	i = 0;
	buya = (char *)malloc(sizeof(char) * len + 1);
	if (!buya)
		return (NULL);
	if (len == 0 || start >= ft_strlen(s))
	{
		buya[0] = '\0';
		return (buya);
	}
	while (i < len)
	{
		buya[i] = s[start];
		i++;
		start++;
	}
	buya[i] = '\0';
	return (buya);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*dest;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1);
	len += ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	while (i < len)
	{
		while (s1[j])
			dest[i++] = s1[j++];
		j = 0;
		while (s2[j])
			dest[i++] = s2[j++];
	}
	dest[i] = '\0';
	return (dest);
}
