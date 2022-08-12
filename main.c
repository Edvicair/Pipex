/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:51:50 by edvicair          #+#    #+#             */
/*   Updated: 2022/08/11 21:26:08 by edvicair         ###   ########.fr       */
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
	pipe->child1 = fork();
	if (pipe->child1 == -1)
	{
		perror("Can't fork");
		free_double(pipe->path);
		exit(0);
	}
	if (pipe->child1 == 0)
	{
		close(pipe->fd[0]);
		dup2(pipe->in, STDIN_FILENO);
		dup2(pipe->fd[1], STDOUT_FILENO);
		close(pipe->fd[1]);
		pipe->cmd1 = ft_split(av[2], ' ');
		exec(pipe, pipe->cmd1, env);
	}
}

static void	second_child(t_pipe *pipe, char **av, char **env)
{
	pipe->child2 = fork();
	if (pipe->child2 == -1)
	{
		perror("Can't fork");
		free_double(pipe->path);
		exit(0);
	}
	if (pipe->child2 == 0 && pipe->in != -1)
	{
		pipe->out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (pipe->out == -1)
		{
			perror("Can't create <file2>");
			free_double(pipe->path);
			exit(0);
		}
		close(pipe->fd[1]);
		dup2(pipe->out, STDOUT_FILENO);
		dup2(pipe->fd[0], STDIN_FILENO);
		close(pipe->fd[0]);
		pipe->cmd2 = ft_split(av[3], ' ');
		exec(pipe, pipe->cmd2, env);
	}
}

static int	check(int ac, t_pipe *pip, char **env)
{
	if (ac != 5)
	{
		write(1, "Error arg : <file1> <cmd1> <cmd2> <file2>\n", 42);
		return (-1);
	}
	if (pipe(pip->fd) == -1)
	{
		perror("Can't pipe");
		return (-1);
	}
	pip->path = get_env(env);
	if (pip->path == NULL)
	{
		perror("Can't get environment variable");
		return (-1);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_pipe	pipe;

	if (!*env)
	{
		write(1, "Can't get environment varible\n", 30);
		return (0);
	}
	if (check(ac, &pipe, env) == -1)
		return (0);
	pipe.in = open(av[1], O_RDONLY);
	if (pipe.in == -1)
		perror("Can't open <file1>");
	else
	{
		first_child(&pipe, av, env);
		second_child(&pipe, av, env);
	}
	free_double(pipe.path);
}
