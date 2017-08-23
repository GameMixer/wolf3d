/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 13:16:30 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/01 11:40:44 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	vect_init(t_vlst **list)
{
	(**list).floorev = 0;
	(**list).floorsv = 0;
	(**list).floorbot = 0;
	(**list).floortop = 0;
	(**list).wfloorsv = 0;
	(**list).wfloorev = 0;
	(**list).wfloorbot = 0;
	(**list).wfloortop = 0;
	(**list).ceilsv = 0;
	(**list).ceilev = 0;
	(**list).ceilbot = 0;
	(**list).ceiltop = 0;
	(**list).wceilsv = 0;
	(**list).wceilev = 0;
	(**list).wceilbot = 0;
	(**list).wceiltop = 0;
	(**list).wallc = 0;
	(**list).wallf = 0;
	(**list).hc = 0;
	(**list).hf = 0;
}

t_vlst	*vect_new(t_vector *content, char side)
{
	t_vlst		*list;
	t_vector	data;

	data.x = content->x;
	data.y = content->y;
	data.dist = content->dist;
	data.uvx = content->uvx;
	data.uvy = content->uvy;
	list = (t_vlst *)malloc(sizeof(t_vlst));
	list->side = side;
	list->next = NULL;
	list->vector = data;
	vect_init(&list);
	return (list);
}

void	vect_addsort(t_vlst **vlst, t_vector *content, char side)
{
	t_vlst	*tmp;
	t_vlst	*tmp2;
	t_vlst	**tmp3;

	tmp2 = *vlst;
	if (tmp2)
	{
		tmp = vect_new(content, side);
		tmp3 = &*vlst;
		while (tmp2 && tmp2->vector.dist < tmp->vector.dist)
		{
			tmp3 = &tmp2->next;
			tmp2 = tmp2->next;
		}
		*tmp3 = tmp;
		tmp->next = tmp2;
	}
	else
		*vlst = vect_new(content, side);
}

void	vect_clear(t_vlst **vlst)
{
	t_vlst	*list;
	t_vlst	*tmp;

	list = *vlst;
	tmp = NULL;
	while (list)
	{
		if (list->next)
			tmp = list->next;
		else
			tmp = NULL;
		free(list);
		list = tmp;
	}
	*vlst = NULL;
}
