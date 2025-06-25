/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdiez-cu <vdiez-cu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:05:21 by vdiez-cu          #+#    #+#             */
/*   Updated: 2025/03/31 11:05:21 by vdiez-cu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
		{
			words++;
		}
		i++;
	}
	return (words);
}

size_t	ft_count_char_word(char const *s, char c, size_t k)
{
	size_t	char_word;

	char_word = 0;
	while (s[char_word + k] != '\0' && s[char_word + k] != c)
	{
		char_word++;
	}
	return (char_word);
}

char	*ft_word(char const *s, char c, size_t *k)
{
	size_t	i;
	char	*word;

	word = (char *)malloc(sizeof(char) * (ft_count_char_word(s, c, *k) + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < ft_count_char_word(s, c, *k))
	{
		word[i] = s[*k + i];
		i++;
	}
	word[i] = '\0';
	*k = *k + ft_count_char_word(s, c, *k);
	return (word);
}

char	**ft_free_result(char **result, size_t j)
{
	while (j > 0)
	{
		free(result[j - 1]);
		j--;
	}
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	result = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!result)
		return (NULL);
	while (s[k] != '\0')
	{
		while (s[k] == c)
			k++;
		if (s[k] != c && s[k] != '\0')
		{
			result[j] = ft_word(s, c, &k);
			if (!result[j])
				return (ft_free_result(result, j));
			j++;
		}
	}
	result[j] = NULL;
	return (result);
}
/*
int	main(void)
{
	char	s[] = "HOLA_ADIOS";
	char	c = '_';
	char	**result = ft_split(s, c);
	printf("Resultado: %s\n", result[0]);
	printf("Resultado: %s\n", result[1]);
	return(0);
}*/