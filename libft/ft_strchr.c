/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 16:52:35 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/17 10:01:41 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	char	d;
	char	*ptr;

	d = (char)c;
	ptr = (char *)s;
	while (*ptr && *ptr != d)
		ptr++;
	if (*ptr == d)
		return (ptr);
	return (NULL);
}
