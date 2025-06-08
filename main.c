/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:54:15 by victor            #+#    #+#             */
/*   Updated: 2025/06/08 19:56:58 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	char	*infile;
	char	*cmd1_str;
	char	*cmd2_str;
	char	*outfile;
	char	**argv_split;
	int		count;
	int		infile_fd;
	int		outfile_fd;

	if (argc == 2)
	{
		argv_split = ft_split(argv[1], ' ');
		if (!argv_split)
			exit(EXIT_FAILURE);
		count = 0;
		while (argv_split[count])
			count++;
		if (count != 4)
		{
			write(2, "Error: formato inválido\n", 24);
			exit(EXIT_FAILURE);
		}
		infile = argv_split[0];
		cmd1_str = argv_split[1];
		cmd2_str = argv_split[2];
		outfile = argv_split[3];
	}
	else if (argc == 5)
	{
		infile = argv[1];
		cmd1_str = argv[2];
		cmd2_str = argv[3];
		outfile = argv[4];
	}
	else
	{
		write(1, "Error\nArguments\n", 17);
		exit(EXIT_FAILURE);
	}
	if (access(infile, R_OK) == -1)
	{
		perror(infile);
		exit(EXIT_FAILURE);
	}
	infile_fd = open(infile, O_RDONLY);
	if (infile_fd < 0)
	{
		perror("open infile");
		exit(EXIT_FAILURE);
	}
	outfile_fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		perror("open outfile");
		close(infile_fd);
		exit(EXIT_FAILURE);
	}
	close(infile_fd);
	close(outfile_fd);
	return (0);
}
