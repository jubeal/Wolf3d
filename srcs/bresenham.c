/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:37:19 by jubeal            #+#    #+#             */
/*   Updated: 2019/03/28 14:37:23 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	new_link(t_points *pts, int x, int y)
{
	t_points	*tmp;

	tmp = pts;
	while (tmp->next)
		tmp = tmp->next;
	if (!(tmp->next = (t_points *)malloc(sizeof(t_points))))
		exit(0);
	tmp = tmp->next;
	tmp->x = x;
	tmp->y = y;
	tmp->next = NULL;
}

static void	draw_line2(t_brese_para *param, t_points *pts)
{
	int		cumul;
	int		x;
	int		y;

	x = param->x1;
	y = param->y1;
	cumul = param->dy;
	while (y != param->y2)
	{
		y += param->yinc;
		cumul -= param->dx * 2;
		if (cumul <= 0 && ((x += param->xinc) || !(x)))
			cumul += param->dy * 2;
		new_link(pts, x, y);
	}
}

static void	draw_line(t_brese_para *param, t_points *pts)
{
	int		cumul;
	int		x;
	int		y;

	x = param->x1;
	y = param->y1;
	if (param->dx > param->dy)
	{
		cumul = param->dx;
		while (x != param->x2)
		{
			x += param->xinc;
			cumul -= param->dy * 2;
			if (cumul <= 0 && ((y += param->yinc) || !(y)))
				cumul += param->dx * 2;
			new_link(pts, x, y);
		}
	}
	else
		draw_line2(param, pts);
}

t_points	*bresenham(t_prc *p)
{
	t_brese_para	*param;
	t_points		*pts;

	if (!(pts = (t_points *)malloc(sizeof(t_points))))
		exit(0);
	if (!(param = (t_brese_para *)malloc(sizeof(t_brese_para))))
		exit(0);
	param->dx = p->x2 - p->x1;
	param->dy = p->y2 - p->y1;
	param->xinc = (param->dx > 0) ? 1 : -1;
	param->yinc = (param->dy > 0) ? 1 : -1;
	param->dx = abs(param->dx);
	param->dy = abs(param->dy);
	param->x1 = p->x1;
	param->x2 = p->x2;
	param->y1 = p->y1;
	param->y2 = p->y2;
	pts->x = p->x1;
	pts->y = p->y1;
	pts->next = NULL;
	draw_line(param, pts);
	return (pts);
}
