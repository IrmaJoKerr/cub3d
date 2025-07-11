/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:38:15 by wjun-kea          #+#    #+#             */
/*   Updated: 2024/11/15 16:39:15 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp_list;
	t_list	*tmp_element;

	tmp_list = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		tmp_element = ft_lstnew(f(lst->content));
		if (!tmp_element)
		{
			ft_lstclear(&tmp_list, del);
			return (NULL);
		}
		ft_lstadd_back(&tmp_list, tmp_element);
		lst = lst->next;
	}
	return (tmp_list);
}
