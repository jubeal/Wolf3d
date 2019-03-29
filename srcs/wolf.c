/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:12:46 by jubeal            #+#    #+#             */
/*   Updated: 2019/03/18 15:12:49 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	draw_ray_cast(t_points *pts, t_wolf *w)
{
	int			x;
	int			y;
	int			color;
	int			chg;
	t_points	*tmp;

	x = 0;
	tmp = pts;
	while ((++x) && tmp->next)
		tmp= tmp->next;
	chg = (WIN_X - 400) / x;
	x = 400;
	tmp = pts;
	while (x < WIN_X)
	{
		color = SKY;
		y = 0;
		if (!((x - 400) % chg) && tmp->next)
			tmp = tmp->next;
		while (y < WIN_Y)
		{
			/*printf("%d\n", (WIN_Y / 2) - ((w->p->cam / tmp->dst * 255) / 2));
			printf("%d\n", (WIN_Y / 2) + ((w->p->cam / tmp->dst * 255) / 2));*/
			if (y > (WIN_Y / 2) + ((w->p->cam / tmp->dst * 255) / 2))
				color = GROUND;
			else if (y > (WIN_Y / 2) - ((w->p->cam / tmp->dst * 255) / 2))
			{
				if (tmp->dst == 400)
					color = 0;
				else
					color = WALLS;
			}
			pixel_put_img(x, y, w, color);
			y++;
		}
		x++;
	}
}

void		wolf(t_wolf *w)
{
	t_prc		*range;
	t_points	*pts;
	int			agl;

	if (!(range = (t_prc *)malloc(sizeof(t_prc))))
		return ;
	agl = w->p->dov - (w->p->fov / 2);
	agl = (agl < 0) ? (360 + agl) * (PI * 2) / 360 : agl * (PI * 2) / 360;
	range->x1 = 400 * cos(agl) + -sin(agl) + w->p->x;
	range->y1 = 400 * sin(agl) + cos(agl) + w->p->y;
	agl = w->p->dov + (w->p->fov / 2);
	agl = (agl > 360) ? (agl - 360) * (PI * 2) / 360 : agl * (PI * 2) / 360;
	range->x2 = 400 * cos(agl) + -sin(agl) + w->p->x;
	range->y2 = 400 * sin(agl) + cos(agl) + w->p->y;
	pts = bresenham(range);
	range->x1 = w->p->x;
	range->y1 = w->p->y;
	range->m = w->m;
	while (pts->next)
	{
		range->x2 = pts->x;
		range->y2 = pts->y;
		pts->dst = cast(range);
		pts = pts->next;
	}
	draw_ray_cast(pts, w);
	mlx_put_image_to_window(w->ptr, w->win, w->img, 0, 0);
}
