/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 16:19:27 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/18 14:47:05 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int ft_strcmp(const char *s1, const char *s2)
{
	int i;
	int ret;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	i = 0;
	while (*((unsigned char *)s1 + i) == *((unsigned char *)s2 + i))
	{
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	ret = (int)(*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
	return (ret);
}
