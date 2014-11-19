/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 16:33:10 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/08 20:12:55 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (*((unsigned char *)s1 + i) == *((unsigned char *)s2 + i))
	{
		if (s1[i] == '\0' || i + 1 == n)
			return (0);
		i++;
	}
	return (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
}
