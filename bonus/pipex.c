/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:40:55 by edvicair          #+#    #+#             */
/*   Updated: 2022/08/21 13:21:28 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_last(t_pipe *pipe, char **av, int ac)
{
	pipe->out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (pipe->out == -1)
	{
		perror("Can't create <file2>");
		free_all(pipe);
		exit(0);
	}
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

static void	last_child(t_pipe *pipe, char **av, char **env, int ac)
{
	pipe->l_child = fork();
	if (pipe->l_child == -1)
	{
		perror("Can't fork");
		free_all(pipe);
		exit(0);
	}
	if (pipe->l_child == 0 && pipe->in != -1)
	{
		open_last(pipe, av, ac);
		dup2(pipe->out, STDOUT_FILENO);
		dup2(pipe->fd[pipe->i - 1][0], STDIN_FILENO);
		close(pipe->fd[pipe->i][1]);
		close(pipe->fd[pipe->i][0]);
		close(pipe->fd[pipe->i - 1][0]);
		pipe->cmd = ft_split(av[ac - 2], ' ');
		exec(pipe, pipe->cmd, env);
		free_double(pipe->cmd);
	}
	close(pipe->fd[pipe->i][1]);
}

void	pipex(t_pipe *pipe, char **av, int ac, char **env)
{
	if ((ft_strncmp(av[1], "here_doc", 8)) == 0)
	{
		pipe->in = here_doc(pipe, av[2], ac);
		if (pipe->in == -1)
		{
			free_all(pipe);
			exit(0);
		}
	}
	else
	{
		pipe->in = open(av[1], O_RDONLY);
		if (pipe->in == -1)
		{
			perror("Can't open <file1>");
			free_all(pipe);
			exit(0);
		}
	}
	first_child(pipe, av, env);
	middle_child(pipe, av, env);
	last_child(pipe, av, env, ac);
}
