/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 13:59:58 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/08 17:50:59 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		calc_floor(t_vlst **list, t_mlx *mlx, int wallf, int bot)
{
	(**list).floorbot = (mlx->scr.center + ((mlx->p.h * mlx->scr.dist) /
				(**list).vector.dist) / 2);
	(**list).floortop = (**list).floorbot - (((mlx->p.h * mlx->scr.dist) /
				(**list).vector.dist) * (wallf / mlx->p.h) / 2);
	(**list).floorbot = bot;
	if ((**list).floorbot > mlx->hf)
	{
		(**list).floorsv = (**list).floorbot - mlx->hf;
		(**list).floorbot = mlx->hf;
	}
	if ((**list).floortop < mlx->hc)
	{
		(**list).floorev = mlx->hc - (**list).floortop;
		(**list).floortop = mlx->hc;
	}
	if ((**list).floortop < mlx->hf)
		return ((**list).floortop);
	return (mlx->hf);
}

int		calc_ceil(t_vlst **list, t_mlx *mlx, int wallc, int bot)
{
	(**list).ceilbot = (mlx->scr.center + ((mlx->p.h * mlx->scr.dist) /
				(**list).vector.dist) / 2);
	(**list).ceiltop = (**list).ceilbot - (((mlx->p.h * mlx->scr.dist) /
				(**list).vector.dist) * (wallc / mlx->p.h) / 2);
	(**list).ceilbot = bot;
	if ((**list).ceilbot < mlx->hc)
	{
		(**list).ceilsv = mlx->hc - (**list).ceilbot;
		(**list).ceilbot = mlx->hc;
	}
	if ((**list).ceiltop > mlx->hf)
	{
		(**list).ceilev = (**list).ceiltop - mlx->hf;
		(**list).ceiltop = mlx->hf;
	}
	if ((**list).ceiltop > mlx->hc)
		return ((**list).ceiltop);
	return (mlx->hc);
}

int		calc_wfloor(t_vlst **list, t_mlx *mlx, int *wallf, int *fbot)
{
	(**list).wfloorbot = (mlx->scr.center + ((mlx->p.h * mlx->scr.dist) /
				(**list).vector.dist) / 2);
	*wallf = mlx->map.floor[(int)floor(((**list).vector.y) / BLOCK)]
		[(int)floor(((**list).vector.x) / BLOCK)];
	(**list).wallf = *wallf;
	(**list).wfloortop = (**list).wfloorbot - (((mlx->p.h * mlx->scr.dist) /
				(**list).vector.dist) * (*wallf / mlx->p.h) / 2);
	if ((**list).wfloorbot > mlx->hf)
	{
		(**list).wfloorsv = (**list).wfloorbot - mlx->hf;
		(**list).wfloorbot = mlx->hf;
	}
	if ((**list).wfloortop < mlx->hc)
	{
		(**list).wfloorev = mlx->hc - (**list).wfloortop;
		(**list).wfloortop = mlx->hc;
	}
	*fbot = (**list).wfloortop;
	if ((**list).wfloortop < mlx->hf)
		return ((**list).wfloortop);
	return (mlx->hf);
}

int		calc_wceil(t_vlst **list, t_mlx *mlx, int *wallc, int *cbot)
{
	(**list).wceilbot = (mlx->scr.center + ((mlx->p.h * mlx->scr.dist) /
				(**list).vector.dist) / 2);
	*wallc = mlx->map.ceiling[(int)floor(((**list).vector.y) / BLOCK)]
		[(int)floor(((**list).vector.x) / BLOCK)];
	(**list).wallc = *wallc;
	(**list).wceiltop = (**list).wceilbot - (((mlx->p.h * mlx->scr.dist) /
				(**list).vector.dist) * (*wallc / mlx->p.h) / 2);
	(**list).wceilbot = (**list).wceiltop - (((mlx->p.h * mlx->scr.dist) /
				(**list).vector.dist) * ((512 - *wallc) / mlx->p.h) / 2);
	if ((**list).wceilbot < mlx->hc)
	{
		(**list).wceilsv = mlx->hc - (**list).wceilbot;
		(**list).wceilbot = mlx->hc;
	}
	if ((**list).wceiltop > mlx->hf)
	{
		(**list).wceilev = (**list).wceiltop - mlx->hf;
		(**list).wceiltop = mlx->hf;
	}
	*cbot = (**list).wceiltop;
	if ((**list).wceiltop > mlx->hc)
		return ((**list).wceiltop);
	return (mlx->hc);
}

void	line_cleaner(t_mlx *mlx, t_vlst *vlst, int num)
{
	t_vlst	*list;

	list = vlst;
	mlx->line[num].iter = 0;
	mlx->wall_f = mlx->map.floor[(int)floor(mlx->p.y / BLOCK)]
		[(int)floor(mlx->p.x / BLOCK)];
	mlx->wall_c = mlx->map.ceiling[(int)floor(mlx->p.y / BLOCK)]
		[(int)floor(mlx->p.x / BLOCK)];
	mlx->bot_f = mlx->scr.h;
	mlx->bot_c = 0;
	mlx->hf = mlx->scr.h;
	mlx->hc = 0;
	while (list && mlx->hf > mlx->hc)
	{
		list->hc = mlx->hc;
		list->hf = mlx->hf;
		mlx->hf = calc_floor(&list, mlx, mlx->wall_f, mlx->bot_f);
		mlx->hc = calc_ceil(&list, mlx, mlx->wall_c, mlx->bot_c);
		mlx->hf = calc_wfloor(&list, mlx, &mlx->wall_f, &mlx->bot_f);
		mlx->hc = calc_wceil(&list, mlx, &mlx->wall_c, &mlx->bot_c);
		mlx->line[num].iter++;
		list = list->next;
	}
	if (vlst)
		draw_line(mlx, vlst, num);
}
