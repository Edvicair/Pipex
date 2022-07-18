/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:49:41 by edvicair          #+#    #+#             */
/*   Updated: 2022/06/30 14:06:17 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_env(char **env)
{
	int		i;
	int		len;
	char	*sub;
	char	**path;

	i = 0;
	len = 0;
	path = NULL;
	sub = NULL;
	if (!env)
		return (NULL);
	while (env[i] != NULL && (ft_strncmp("PATH", env[i], 4) != 0))
		i++;
	if (ft_strncmp("PATH", env[i], 4) == 0)
	{
		len = ft_strlen(env[i]);
		sub = ft_substr(env[i], 5, len);
		path = ft_split(sub, ':');
		free(sub);
		return (path);
	}
	return (NULL);
}
