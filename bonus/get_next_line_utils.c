/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:28:22 by edvicair          #+#    #+#             */
/*   Updated: 2021/09/14 20:45:14 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	char	*cpy;
	int		i;

	i = -1;
	if (!s)
		return (NULL);
	cpy = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!cpy)
		return (NULL);
	while (s[++i])
		cpy[i] = s[i];
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_strjoin_gnl(char *s1, const char *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strdup(s2));
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	while (s1[j])
		s3[i++] = s1[j++];
	free(s1);
	s1 = NULL;
	j = 0;
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*s_cpy;

	i = 0;
	s_cpy = (char *)s;
	if (!s)
		return (NULL);
	while (s_cpy[i])
	{
		if (s_cpy[i] == c)
		{
			return (s_cpy + i);
		}
		i++;
	}
	if (c == '\0')
	{
		return (s_cpy + i);
	}
	return (NULL);
}
