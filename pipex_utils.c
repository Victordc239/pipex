/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdiez-cu <vdiez-cu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:22:12 by victor            #+#    #+#             */
/*   Updated: 2025/06/26 13:47:11 by vdiez-cu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		k;

	i = 0;
	k = 0;
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	while (s1[k] != '\0')
	{
		result[k] = s1[k];
		k++;
	}
	while (k < (ft_strlen(s1) + ft_strlen(s2)))
	{
		result[k] = s2[i];
		k++;
		i++;
	}
	result[k] = '\0';
	return (result);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	while (((s1[i] != '\0') || (s2[i] != '\0')) && (s1[i] == s2[i]) && (i < n))
	{
		i++;
	}
	if (s1[i] == s2[i])
	{
		return (0);
	}
	else if (i < n)
	{
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	else
	{
		return (0);
	}
}

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
