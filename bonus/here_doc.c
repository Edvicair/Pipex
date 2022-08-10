/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 02:27:10 by edvicair          #+#    #+#             */
/*   Updated: 2022/08/10 19:35:33 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	here_doc(t_pipe *pipe, char *limiter, int ac)
// {
// 	char	*line;
// 	int		len;

// 	if (ac < 6)
// 	{
// 		write(1, "<here_doc> <limiter> <cmd1> <cmd2> ... <file_out>\n", 50);
// 		exit(0);
// 	}
// 	pipe->child1 = fork();
// 	if (pipe->child1 == 0)
// 	{
// 		while (line = get_next_line(0))
// 		{
// 			if ((ft_strncmp(limiter, line, (ft_strlen(line) - 1)) == 0))
// 				exit(0);
// 			write(fd[1], line, ft_strlen(line));
// 		}
// 	}
// 	else
// 		wait(NULL);
// }

int		here_doc(t_pipe *pipe, char *limiter, int ac)
{
	char *line;

	// pipe->m_child = fork();
	// if (pipe->m_child == 0)
	// {
	while(1)	
	{
		write(1, "heredoc>",8);
		line = get_next_line(0);
		if (ft_strncmp(limiter, line, (ft_strlen(limiter))) == 0)
		{
			free(line);
			break;
		}
		write(pipe->fdd[1], line, ft_strlen(line));	
		free(line);
	}
	return (pipe->fdd[0]);
	// }
	// else
	// 	wait(NULL);
		// close(pipe->fd[0]);
		// dup2(pipe->fd[1], STDIN_FILENO);
		// dup2(pipe->out, STDOUT_FILENO);
}

int	create_pipe(t_pipe *pip, int ac)
{
	int i;
	
	i = 0;
	pip->count_cmd = ac - pip->here_doc;
	printf("cmd_count = %d | ac = %d | heredoc = %d\n", pip->count_cmd, ac, pip->here_doc);
	pip->fd = (int **)malloc(sizeof(int *) * (pip->count_cmd + 1));
	if (!pip->fd)
		return (-1);
	while(i < pip->count_cmd)
	{
		pip->fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!pip->fd[i])
			return (-1);
		if (pipe(pip->fd[i]) == -1)
		{
			perror("Can pipe");
			return(-1);
		}
		i++;
	}
	return (0);
}

int	middle_child(t_pipe *pipe, char **av, char **env)
{
	int	i;
	int j;
	char **cmd_split;

//	printf("MIDDLEEEEEEEEEEEEEEE\n");
	i = 1;
	j = pipe->here_doc;
	printf("i = %d | count = %d | heredoc = %d\n", i, pipe->count_cmd, pipe->here_doc);
	while (i <= pipe->count_cmd - 2)
	{
		cmd_split = ft_split(av[j], ' ');
	//	fprintf(stderr, "CMD3=%s\n", cmd_split[0]);
		exec_middle(pipe, pipe->fd[i], i, cmd_split, env);
		free_double(cmd_split);
		i++;
		j++;
	}
	return (i);
	// pipe->l_child = fork();
	// if (pipe->l_child == -1)
	// {
	// 	perror("Can't fork");
	// 	free_double(pipe->path);
	// 	exit(0);
	// }
	// if (pipe->l_child == 0)
	// {
	// 	cmd_split = ft_split(av[j], ' ');
	// 	dup2(pipe->fd[i][0], STDIN_FILENO);
	// 	dup2(pipe->out, STDOUT_FILENO);
	// 	close(pipe->fd[i][0]);
	// 	exec(pipe, cmd_split, env);
	// }
	// close(pipe->fd[i][1]);
}

void	exec_middle(t_pipe *pipe, int *fd, int i, char **cmd, char ** env)
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
		fprintf(stderr, "exec_middle\n");
		dup2(pipe->fd[i - 1][0], STDIN_FILENO);
		dup2(pipe->fd[i][1], STDOUT_FILENO);
		close(pipe->fd[i - 1][1]);
		close(pipe->fd[i][0]);
		fprintf(stderr, "CMD3=%s\n", cmd[0]);
		exec(pipe, cmd, env);
	}
	close(pipe->fd[i][1]);
}