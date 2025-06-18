/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:19:38 by alcarril          #+#    #+#             */
/*   Updated: 2024/10/23 17:06:29 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	total_leng;
	size_t	i;
	size_t	j;

	j = 0;
	total_leng = ft_strlen(s1) + ft_strlen(s2) + 1;
	i = 0;
	ptr = (char *)malloc(total_leng);
	if (!(ptr))
		return (0);
	while ((i <= (total_leng - 1)) && s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	while ((i < (total_leng - 1)) && s2[j] != '\0')
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}