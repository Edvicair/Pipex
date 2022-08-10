/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:16:56 by edvicair          #+#    #+#             */
/*   Updated: 2022/06/10 12:21:31 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_countword(const char *s, char c)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	if (s[i] == '\0')
		return (n);
	if (s[0] != c)
		n++;
	while (s[i + 1] != '\0')
	{
		if (s[i] == c && s[i + 1] != c)
			n++;
		i++;
	}
	return (n);
}

static char	*ft_substrr(const char *s, int min, int max)
{
	int		i;
	char	*s2;

	s2 = malloc(sizeof(char *) * (max - min + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (min < max)
	{
		s2[i] = s[min];
		i++;
		min++;
	}
	s2[i] = '\0';
	return (s2);
}

static void	ft_free(int n, char **s)
{
	while (n >= 0)
	{
		free(s[n]);
		n--;
	}
}

static	void	boucle(const char *s, char **s2, char c)
{
	int	i;
	int	n;
	int	min;

	i = 0;
	n = 0;
	min = 0;
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		min = i;
		while (s[i] && s[i] != c)
			i++;
		if (n < ft_countword(s, c))
		{
			s2[n] = ft_substrr(s, min, i);
			if (s2[n] == NULL)
				ft_free(n, s2);
		}
		n++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**s2;

	if (!s)
		return (NULL);
	s2 = malloc(sizeof(char *) * (ft_countword(s, c) + 1));
	if (s2 == NULL)
		return (0);
	s2[ft_countword(s, c)] = 0;
	boucle(s, s2, c);
	return (s2);
}
