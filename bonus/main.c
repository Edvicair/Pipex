/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:51:50 by edvicair          #+#    #+#             */
/*   Updated: 2022/08/12 05:02:39 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

static void	first_child(t_pipe *pipe, char **av, char **env)
{
	pipe->f_child = fork();
	if (pipe->f_child == -1)
	{
		perror("Can't fork");
		free_double(pipe->path);
		exit(0);
	}
	if (pipe->f_child == 0)
	{
		dup2(pipe->in, STDIN_FILENO);
		dup2(pipe->fd[0][1], STDOUT_FILENO);
		close(pipe->fd[0][0]);
		close(pipe->fd[0][1]);
		pipe->cmd = ft_split(av[pipe->here_doc - 1], ' ');
		exec(pipe, pipe->cmd, env);
		free_double(pipe->cmd);
	}
	close(pipe->fd[0][1]);
}

static void	last_child(t_pipe *pipe, char **av, char **env, int ac, int i)
{
	pipe->l_child = fork();
	if (pipe->l_child == -1)
	{
		perror("Can't fork");
		free_double(pipe->path);
		free_pipe(pipe->fd, pipe);
		exit(0);
	}
	if (pipe->l_child == 0 && pipe->in != -1)
	{
		pipe->out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (pipe->out == -1)
		{
			perror("Can't create <file2>");
			free_double(pipe->path);
			exit(0);
		}
		dup2(pipe->out, STDOUT_FILENO);
		dup2(pipe->fd[i - 1][0], STDIN_FILENO);
		close(pipe->fd[i][1]);
		close(pipe->fd[i][0]);
		close(pipe->fd[i - 1][0]);
		pipe->cmd = ft_split(av[ac - 2], ' ');
		exec(pipe, pipe->cmd, env);
		free_double(pipe->cmd);
	}
	close(pipe->fd[i][1]);
}

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
	if ((ft_strncmp(av[1], "here_doc", 8)) == 0)
	{
		if (pipe.out == -1)
			perror("Can't open <file1>");
		pipe.in = here_doc(&pipe, av[2], ac);
	}
	else
	{	
		pipe.in = open(av[1], O_RDONLY);
		if (pipe.in == -1)
			perror("Can't open <file1>");
	}
	first_child(&pipe, av, env);
	i = middle_child(&pipe, av, env);
	last_child(&pipe, av, env, ac, i);
	free_double(pipe.path);
	free_pipe(pipe.fd, &pipe);
	waitpid(pipe.f_child, NULL, 0);
	waitpid(pipe.m_child, NULL, 0);
	waitpid(pipe.l_child, NULL, 0);
}
