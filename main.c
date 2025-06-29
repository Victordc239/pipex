/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:54:15 by victor            #+#    #+#             */
/*   Updated: 2025/06/28 16:29:47 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	arguments(int argc, char **argv, t_pipex *p)
{
	if (argc == 2)
	{
		p->argv_split = ft_split(argv[1], ' ');
		if (p->argv_split == NULL)
			exit(EXIT_FAILURE);
		p->count = 0;
		while (p->argv_split[p->count] != NULL)
			p->count++;
		if (p->count != 4)
		{
			ft_free_split(p->argv_split);
			(write(2, "Error format\n", 14), exit(EXIT_FAILURE));
		}
		p->infile = p->argv_split[0];
		p->cmd1_str = p->argv_split[1];
		p->cmd2_str = p->argv_split[2];
		p->outfile = p->argv_split[3];
	}
	else if (argc == 5)
	{
		p->infile = argv[1];
		p->cmd1_str = argv[2];
		p->cmd2_str = argv[3];
		p->outfile = argv[4];
	}
}

void	first_child(t_pipex *p, char **envp)
{
	p->pid1 = fork();
	if (p->pid1 < 0)
		ft_perror_exit("fork cmd1", 0, p);
	if (p->pid1 == 0)
	{
		if (dup2(p->infile_fd, STDIN_FILENO) < 0)
			ft_perror_exit("dup2 infile cmd1", 0, p);
		if (dup2(p->out_in_cmd_pipe[1], STDOUT_FILENO) < 0)
			ft_perror_exit("dup2 pipe write cmd1", 0, p);
		ft_close(p, 4);
		p->cmd1_split = ft_split(p->cmd1_str, ' ');
		if (p->cmd1_split[0] == NULL)
			(ft_free_split(p->cmd1_split), exit(EXIT_FAILURE));
		p->path_cmd1 = find_executable(p->cmd1_split[0], envp);
		if (p->path_cmd1 == NULL)
		{
			write(2, "command not found: ", 19);
			write(2, p->cmd1_split[0], ft_strlen(p->cmd1_split[0]));
			write(2, "\n", 1);
			ft_free_split(p->cmd1_split);
			exit(EXIT_FAILURE);
		}
		execve(p->path_cmd1, p->cmd1_split, envp);
		ft_perror_exit("execve cmd1", 0, p);
	}
}

void	second_child(t_pipex *p, char **envp)
{
	p->pid2 = fork();
	if (p->pid2 < 0)
		ft_perror_exit("fork cmd1", 0, p);
	if (p->pid2 == 0)
	{
		if (dup2(p->out_in_cmd_pipe[0], STDIN_FILENO) < 0)
			ft_perror_exit("dup2 pipe read cmd2", 0, p);
		if (dup2(p->outfile_fd, STDOUT_FILENO) < 0)
			ft_perror_exit("dup2 outfile cmd2", 0, p);
		ft_close(p, 4);
		p->cmd2_split = ft_split(p->cmd2_str, ' ');
		if (p->cmd2_split[0] == NULL)
			(write(2, "command not found: \n", 20),
				ft_free_split(p->cmd2_split), exit(127));
		p->path_cmd2 = find_executable(p->cmd2_split[0], envp);
		if (p->path_cmd2 == NULL)
		{
			write(2, "command not found: ", 19);
			write(2, p->cmd2_split[0], ft_strlen(p->cmd2_split[0]));
			write(2, "\n", 1);
			(ft_free_split(p->cmd2_split), exit(127));
		}
		execve(p->path_cmd2, p->cmd2_split, envp);
		ft_perror_exit("execve cmd2", 0, p);
	}
}

void	open_files(t_pipex *p, int *outfile_error)
{
	p->infile_fd = open(p->infile, O_RDONLY);
	if (p->infile_fd < 0)
	{
		perror("open infile");
		p->infile_fd = open("/dev/null", O_RDONLY);
		if (p->infile_fd < 0)
			ft_perror_exit("open /dev/null", 0, p);
	}
	p->outfile_fd = open(p->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (p->outfile_fd < 0)
	{
		perror("open outfile");
		*outfile_error = 1;
		p->outfile_fd = open("/dev/null", O_WRONLY);
		if (p->outfile_fd < 0)
			ft_perror_exit("open /dev/null", 1, p);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	p;
	int		status1;
	int		status2;
	int		outfile_error;

	outfile_error = 0;
	if (argc == 2 || argc == 5)
		arguments(argc, argv, &p);
	else
		(write(1, "Error\nArguments\n", 17), exit(EXIT_FAILURE));
	open_files(&p, &outfile_error);
	if (pipe(p.out_in_cmd_pipe) < 0)
		ft_perror_exit("pipe", 2, &p);
	(first_child(&p, envp), second_child(&p, envp), ft_close(&p, 4));
	(waitpid(p.pid1, &status1, 0), waitpid(p.pid2, &status2, 0));
	if (argc == 2)
		ft_free_split(p.argv_split);
	if (outfile_error)
		return (1);
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	else
		return (1);
}
