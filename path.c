/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdiez-cu <vdiez-cu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:59:09 by victor            #+#    #+#             */
/*   Updated: 2025/06/27 12:33:09 by vdiez-cu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*join_path(char *dir, char *cmd)
{
	char	*path;
	char	*temp;

	temp = ft_strjoin(dir, "/");
	path = ft_strjoin(temp, cmd);
	free(temp);
	return (path);
}

char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_executable(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*full_path;
	char	*path_env;

	i = 0;
	path_env = get_path_env(envp);
	if (path_env == NULL)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (paths == NULL)
		return (NULL);
	while (paths[i] != NULL)
	{
		full_path = join_path(paths[i], cmd);
		if (access(full_path, X_OK) == 0)
			return (ft_free_split(paths), full_path);
		free(full_path);
		i++;
	}
	return (ft_free_split(paths), NULL);
}
