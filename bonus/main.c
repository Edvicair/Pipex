/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:51:50 by edvicair          #+#    #+#             */
/*   Updated: 2022/08/15 16:02:48 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	check(int ac, t_pipe *pip, char **env)
{
	int	i;

	i = 0;
	if (ac < 5)
	{
		write(1, "Error arg :\n", 12);
		write(1, "<file_in> <cmd1> <cmd2> ... <file_out>\n", 39);
		write(1, "<here_doc> <limiter> <cmd1> <cmd2> ... <file_out>\n", 50);
		return (-1);
	}
	pip->path = get_env(env);
	if (pipe(pip->fdd) == -1)
		return (perror("Can't pipe"), -1);
	else if (!pip->path)
		return (perror("Can't get environment variable"), -1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_pipe	pipe;
	char	*buff;
	int		i;

	pipe.here_doc = 3;
	if (!*env)
	{
		write(1, "Can't get environment varible\n", 30);
		return (0);
	}
	if (check(ac, &pipe, env) == -1)
		return (0);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		pipe.here_doc = 4;
	if (create_pipe(&pipe, ac) < 0)
		return (0);
	pipex(&pipe, av, ac, env);
	free_double(pipe.path);
	free_pipe(pipe.fd, &pipe);
	waitpid(pipe.f_child, NULL, 0);
	waitpid(pipe.m_child, NULL, 0);
	waitpid(pipe.l_child, NULL, 0);
}
