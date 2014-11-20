/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 17:18:20 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/20 17:38:01 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*ptr_maillon;

	if (content == NULL)
		content_size = 0;
	ptr_maillon = (t_list *)malloc(sizeof(*ptr_maillon));
	if (ptr_maillon == NULL)
		return (NULL);
	ft_memmove(ptr_maillon->content, content, content_size);
	ptr_maillon->next = NULL;
	return (ptr_maillon);
}