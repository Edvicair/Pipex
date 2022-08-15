/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:52:09 by edvicair          #+#    #+#             */
/*   Updated: 2022/08/15 15:57:37 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pipe(int **str, t_pipe *pipe)
{
	int	i;

	i = 0;
	while (i < pipe->count_cmd)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_all(t_pipe *pipe)
{
	free_pipe(pipe->fd, pipe);
	free_double(pipe->path);
}
