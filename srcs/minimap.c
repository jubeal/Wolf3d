/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjouber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:17:42 by adjouber          #+#    #+#             */
/*   Updated: 2019/03/26 15:37:32 by adjouber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	player_map(t_wolf *w)
{
	int		x;
	int		y;

	y = 75;
	x = 75;
	while (y < 325)
	{
		while (x < 325)
		{
			if ((x > 250 / 2 + 70 && x < 250 / 2 + 80) && (y > 250 / 2 + 70
						&& y < 250 / 2 + 80))
				pixel_put_img(x, y, w, PERSO_MM);
			x++;
		}
		x = 75;
		y++;
	}
}

static void	color_map(t_wolf *w, int x, int y, t_map *m)
{
	int		x_map;
	int		y_map;

	x_map = x - 125 + w->p->x / 2;
	y_map = y - 125 + w->p->y / 2;
	if (x_map < 0 || y_map < 0 || x_map > w->mm.xend || y_map > w->mm.yend)
		return ;
	while ((m->next) && m->next_line)
	{
		if ((x_map >= m->xbegin / 2 && x_map <= m->xend / 2) &&
				(y_map >= m->ybegin / 2 && y_map <= m->yend / 2))
			break ;
		m = m->next;
	}
	if (m->value == '2')
		pixel_put_img(x + 75, y + 75, w, WALL_MM);
	else
		pixel_put_img(x + 75, y + 75, w, ROOF_MM);
}

static void	range_map(t_wolf *w, t_map **m)
{
	t_map	*save;

	save = (*m);
	w->mm.xmax = w->p->x / 2 + 125;
	w->mm.ymax = w->p->y / 2 + 125;
	w->mm.xmin = w->p->x / 2 - 125;
	w->mm.ymin = w->p->y / 2 - 125;
	while (((*m)->next) && ((*m)->next_line))
	{
		//printf("%d, %d\n", (*m)->x, (*m)->y);
		if (w->mm.xmin <= (*m)->xend / 2 && w->mm.ymin <= (*m)->yend)
			break ;
	//	if ((*m)->xbegin > w->mm.xmax)
	//	{
	//		(*m) = save;
	//		(*m) = (*m)->next_line;
	//		save = (*m);
	//	}
	//	else
			(*m) = (*m)->next;
	}
}

void		minimap(t_wolf *w, int x, int y)
{
	t_map	*tmp;
	t_map	*save;

	save = w->m;
	range_map(w, &save);
	while (y < 325)
	{
		tmp = save;
		while (x < 325)
		{
			pixel_put_img(x, y, w, VOID_MM);
			color_map(w, x - 75, y - 75, tmp);
			x++;
		}
		x = 75;
		y++;
	}
	player_map(w);
	mlx_put_image_to_window(w->ptr, w->win, w->img, 0, 0);
}
