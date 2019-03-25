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

void	wolf(t_wolf *w)
{
	t_prc	*range;
	int		t;
	int		i;
	int		x;
	int		y;
	int		*wall;

	if (!(range = (t_prc *)malloc(sizeof(t_prc))))
		return ;
	if (!(wall = (int *)malloc(sizeof(int) * 2)))
		return ;
	x = w->p->x;
	y = w->p->y;
	range->x1 = 100 * cos((w->p->dov - (w->p->fov / 2)) * (PI * 2) / 360) +
		-sin((w->p->dov - (w->p->fov / 2)) * (PI * 2) / 360) + w->p->x;
	range->y1 = 100 * sin((w->p->dov - (w->p->fov / 2)) * (PI * 2) / 360) +
		cos((w->p->dov - (w->p->fov / 2)) * (PI * 2) / 360) + w->p->y;
	pixel_put_img(x, y, w, 0xFFFFFF);
	pixel_put_img(range->x1, range->y1, w, 0xFFFFFF);
	range->x2 = 100 * cos((w->p->dov + (w->p->fov / 2)) * (PI * 2) / 360) +
		-sin((w->p->dov + (w->p->fov / 2)) * (PI * 2) / 360) + w->p->x;
	range->y2 = 100 * sin((w->p->dov + (w->p->fov / 2)) * (PI * 2) / 360) +
		cos((w->p->dov + (w->p->fov / 2)) * (PI * 2) / 360) + w->p->y;
	pixel_put_img(range->x2, range->y2, w, 0xFFFFFF);
	x = range->x1;
	y = range->y1;
	i = 0;
	while (i != 1256)
	{
		t = x;
		x = round(((x - w->p->x) * cos(0.05)) + ((y - w->p->y) * -sin(0.05)) +
			w->p->x);
		y = round(((t - w->p->x) * sin(0.05)) + ((y - w->p->y) * cos(0.05)) +
			w->p->y);
		pixel_put_img(x, y, w, 0xFFFFFF);
		i++;
	}
	mlx_put_image_to_window(w->ptr, w->win, w->img, 0, 0);
}
