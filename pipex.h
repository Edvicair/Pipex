/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:39:59 by edvicair          #+#    #+#             */
/*   Updated: 2022/07/14 11:41:43 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipe
{
	char	**path;
	char	**cmd1;
	char	**cmd2;
	int		in;
	int		out;
	int		fd[2];
	int		child1;
	int		child2;
}		t_pipe;

char	**get_env(char **env);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
void	exec(t_pipe *pipe, char **cmd, char **env);
void	free_double(char **str);

#endif
