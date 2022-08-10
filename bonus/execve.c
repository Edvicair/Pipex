/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:23:05 by edvicair          #+#    #+#             */
/*   Updated: 2022/08/10 13:31:27 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*exec_path(t_pipe *pipe, char **cmd)
{
	int		i;
	char	*tmp;
	char	*paths;

	i = 0;
	while (pipe->path[i])
	{
		tmp = ft_strjoin(pipe->path[i], "/");
		paths = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(paths, X_OK) == 0)
			return (paths);
		free(paths);
		i++;
	}
	if (!pipe->path[i])
	{
		if (access(cmd[0], X_OK) == 0)
			return (cmd[0]);
	}
	return (NULL);
}

void	exec(t_pipe *pipe, char **cmd, char **env)
{	
	char	*paths;

	paths = exec_path(pipe, cmd);
	fprintf(stderr, "paths = %s\n", paths);
	if (paths == NULL)
	{
		write(2, "Can't find command\n", 19);
		free_double(cmd);
		free_double(pipe->path);
		exit(0);
	}
	else if (execve(paths, cmd, env) == -1)
	{
//		fprintf(stderr, "exec :\n%s\n%s\n", paths, cmd[1]);
		perror("Can't execve");
	}
}
