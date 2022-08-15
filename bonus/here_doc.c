/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 02:27:10 by edvicair          #+#    #+#             */
/*   Updated: 2022/08/15 17:06:18 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	free_pipe(int **str, t_pipe *pipe)
// {
// 	int	i;

// 	i = 0;
// 	while (i < pipe->count_cmd)
// 	{
// 		free(str[i]);
// 		i++;
// 	}
// 	free(str);
// }

int	create_pipe(t_pipe *pip, int ac)
{
	int	i;

	i = 0;
	pip->count_cmd = ac - pip->here_doc;
	pip->fd = (int **)malloc(sizeof(int *) * (pip->count_cmd + 1));
	if (!pip->fd)
		return (-1);
	while (i < pip->count_cmd)
	{
		pip->fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!pip->fd[i])
			return (-1);
		if (pipe(pip->fd[i]) == -1)
		{
			perror("Can pipe");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	here_doc(t_pipe *pipe, char *limiter, int ac)
{
	char	*line;

	while (1)
	{
		write(1, "heredoc>", 8);
		line = get_next_line(0);
		if (!ft_strncmp(limiter, line, (ft_strlen(limiter))))
		{
			free(line);
			break ;
		}
		write(pipe->fdd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe->fdd[1]);
	return (pipe->fdd[0]);
}

void	middle_child(t_pipe *pipe, char **av, char **env)
{
	int	j;

	pipe->i = 1;
	j = pipe->here_doc;
	while (pipe->i <= pipe->count_cmd - 2)
	{
		pipe->cmd = ft_split(av[j], ' ');
		exec_middle(pipe, pipe->fd[pipe->i], pipe->cmd, env);
		free_double(pipe->cmd);
		pipe->i++;
		j++;
	}
}

void	exec_middle(t_pipe *pipe, int *fd, char **cmd, char **env)
{
	pipe->m_child = fork();
	if (pipe->m_child == -1)
	{
		perror("Can't fork");
		free_double(pipe->path);
		exit(0);
	}
	if (pipe->m_child == 0)
	{
		dup2(pipe->fd[pipe->i - 1][0], STDIN_FILENO);
		dup2(pipe->fd[pipe->i][1], STDOUT_FILENO);
		close(pipe->fd[pipe->i][0]);
		exec(pipe, cmd, env);
		free_double(pipe->cmd);
	}
	close(pipe->fd[pipe->i][1]);
}
