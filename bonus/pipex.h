/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:39:59 by edvicair          #+#    #+#             */
/*   Updated: 2022/08/21 13:21:56 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "get_next_line.h"

typedef struct s_pipe
{
	char	**path;
	char	**cmd;
	int		in;
	int		out;
	int		here_doc;
	int		count_cmd;
	int		fdd[2];
	int		**fd;
	int		i;
	int		f_child;
	int		m_child;
	int		l_child;
}		t_pipe;

char	**get_env(char **env);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
void	exec(t_pipe *pipe, char **cmd, char **env);
void	exec_middle(t_pipe *pipe, char **cmd, char **env);
void	middle_child(t_pipe *pipe, char **av, char **env);
void	pipex(t_pipe *pipe, char **av, int ac, char **env);
int		create_pipe(t_pipe *pip, int ac);
void	free_all(t_pipe *pipe);
void	free_double(char **str);
void	free_pipe(int **str, t_pipe *pipe);
int		here_doc(t_pipe *pipe, char *limiter, int ac);

#endif
