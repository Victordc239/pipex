/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:22:12 by victor            #+#    #+#             */
/*   Updated: 2025/06/29 11:35:17 by victor           ###   ########.fr       */
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

char	*ft_strchr(const char *str, int c)
{
	size_t			i;
	unsigned char	new_c;

	if (c < 0 || c > 255)
		new_c = (unsigned char)(c % 256);
	else
		new_c = (unsigned char)c;
	i = 0;
	while ((unsigned char)str[i] != '\0')
	{
		if ((unsigned char)str[i] == new_c)
			return ((char *)&str[i]);
		i++;
	}
	if (c == '\0' || new_c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*result;
	size_t	i;
	size_t	size_s;
	char	*aux;

	aux = (char *)s;
	i = 0;
	size_s = ft_strlen(aux);
	result = (char *)malloc(sizeof(char) * size_s + 1);
	if (!result)
		return (NULL);
	while (aux[i] != '\0')
	{
		result[i] = aux[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
