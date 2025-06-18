/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:22:17 by alex              #+#    #+#             */
/*   Updated: 2024/10/23 17:05:57 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h"

static unsigned int	ft_count_words(const char *s, int c)
{
	unsigned int	count_words;
	int				i;

	i = 0;
	count_words = 0;
	while (s[i])
	{
		if ((i == 0 && s[i] != c) || (i >= 1 && (s[i] != c && s[i - 1] == c)))
			count_words++;
		i++;
	}
	return (count_words);
}

static void	*ft_counters(const char *s, unsigned int *aux_b, unsigned int *aux_e, char c)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	t;

	i = 0;
	j = 0;
	t = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 && s[i] != c) || (i >= 1 && (s[i] != c && s[i - 1] == c)))
			aux_b[j++] = i;
		if ((s[i] != c && s[i + 1] == s[ft_strlen(s)])
			|| ((s[i] != c && s[i + 1] == c)))
			aux_e[t++] = i;
		i++;
	}
	return (NULL);
}

static void	*ft_free(char **ptr, int i)
{
	while (i >= 0)
	{
		free(*(ptr + i));
		i--;
	}
	free(ptr);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**ptr;
	unsigned int	aux_b[ft_count_words(s, c)];
	unsigned int	aux_e[ft_count_words(s, c)];
	unsigned int	n;

	ft_counters(s, aux_b, aux_e, c);
	ptr = (char **)ft_calloc((ft_count_words(s, c) + 1), sizeof(char *));
	if (!ptr)
		return (NULL);
	n = -1;
	while (++n < ft_count_words(s, c))
	{
		*(ptr + n) = ft_substr(s, aux_b[n], (size_t)(aux_e[n] - aux_b[n] + 1));
		if (!*(ptr + n))
			return (ft_free(ptr, n));
	}
	return (ptr);
}


