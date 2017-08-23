/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 16:01:45 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/10 16:04:16 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnclear(t_list **begin_list, int nb)
{
	t_list	*list;
	t_list	*tmp;
	int		i;

	list = *begin_list;
	tmp = NULL;
	i = 0;
	while (list && i < nb)
	{
		if (list->next)
			tmp = list->next;
		else
			tmp = NULL;
		free(list);
		list = tmp;
		i++;
	}
	*begin_list = NULL;
	return (list);
}
