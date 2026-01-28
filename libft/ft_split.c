/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:04:02 by gita              #+#    #+#             */
/*   Updated: 2026/01/15 17:05:33 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_this(char c, char *charset)
{
	if (ft_strchr(charset, c))
		return (1);
	return (0);
}

static size_t	one_word_len(char const *s, char *charset)
{
	int	foot;

	foot = 0;
	while (*s && !ft_strchr(charset, *s))
	{
		s++;
		foot++;
	}
	return (foot);
}

static size_t	number_of_words(char const *s, char *charset)
{
	size_t	number;
	int		start_word;

	number = 0;
	start_word = 0;
	while (s != NULL && *s != '\0')
	{
		if (!skip_this(*s, charset) && start_word == 0)
		{
			start_word = 1;
			number++;
		}
		if (skip_this(*s, charset))
			start_word = 0;
		s++;
	}
	return (number);
}

static void	*release(char **arr_of_pointers, int m)
{
	int	i;

	i = 0;
	while (i <= m)
	{
		free (arr_of_pointers[i]);
		arr_of_pointers[i] = NULL;
		i++;
	}
	free (arr_of_pointers);
	arr_of_pointers = NULL;
	return (NULL);
}

char	**ft_split(char const *s, char *charset)
{
	char	**feather;
	int		i;
	int		count;

	i = 0;
	count = number_of_words(s, charset);
	feather = malloc((count + 1) * sizeof(char *));
	if (feather == NULL)
		return (NULL);
	while (*s)
	{
		if (!skip_this(*s, charset))
		{
			feather[i] = ft_substr(s, 0, one_word_len(s, charset));
			if (!feather[i])
				return (release(feather, i));
			s += one_word_len(s, charset);
			i++;
		}
		else
			s++;
	}
	feather[i] = NULL;
	return (feather);
}
