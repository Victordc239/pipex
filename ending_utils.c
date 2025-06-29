/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 11:34:47 by victor            #+#    #+#             */
/*   Updated: 2025/06/29 11:35:22 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_perror_exit(char *str, int num_close, t_pipex *p)
{
	if (num_close == 1)
		close(p->infile_fd);
	if (num_close == 2)
	{
		close(p->infile_fd);
		close(p->outfile_fd);
	}
	perror(str);
	exit(EXIT_FAILURE);
}

void	ft_close(t_pipex *p, int num_close)
{
	if (num_close == 4)
	{
		close(p->out_in_cmd_pipe[0]);
		close(p->out_in_cmd_pipe[1]);
		close(p->infile_fd);
		close(p->outfile_fd);
	}
	else if (num_close == 2)
	{
		close(p->infile_fd);
		close(p->outfile_fd);
	}
}
