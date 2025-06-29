/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:54:07 by victor            #+#    #+#             */
/*   Updated: 2025/06/29 11:38:15 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	char	*cmd1_str;
	char	*cmd2_str;
	char	**cmd1_split;
	char	**cmd2_split;
	char	**argv_split;
	char	*path_cmd1;
	char	*path_cmd2;
	int		count;
	int		infile_fd;
	int		outfile_fd;
	int		out_in_cmd_pipe[2];
	pid_t	pid1;
	pid_t	pid2;
}	t_pipex;

char	**ft_split(char const *s, char c);
char	**ft_free_result(char **result, size_t j);
char	*join_path(char *dir, char *cmd);
char	*find_executable(char *cmd, char **envp);
char	*ft_word(char const *s, char c, size_t *k);
char	*ft_strjoin(char const *s1, char const *s2);
char	*get_path_env(char **envp);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *str, int c);
void	ft_free_split(char **split);
void	arguments(int argc, char **argv, t_pipex *p);
void	ft_close(t_pipex *p, int num_close);
void	ft_perror_exit(char *str, int num_close, t_pipex *p);
int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, int n);
size_t	ft_count_words(char const *s, char c);
size_t	ft_count_char_word(char const *s, char c, size_t k);

#endif