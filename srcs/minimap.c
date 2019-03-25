/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjouber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:17:42 by adjouber          #+#    #+#             */
/*   Updated: 2019/03/25 15:43:57 by adjouber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	init_map(t_wolf *w, t_map *m)
{
	w->mm.xend = m->xend / 2;
	w->mm.yend = m->yend / 2;
	while ((m->next))
	{
		m = m->next;
		if (w->mm.xend < m->xend / 2)
			w->mm.xend = m->xend / 2;
		if (w->mm.yend < m->yend / 2)
			w->mm.yend = m->yend / 2;
	}
}

static void	player_map(t_wolf *w)
{
	int		x;
	int		y;

	y = 25;
	x = 25;
	while (y < 375)
	{
		while (x < 375)
		{
			if ((x > 350 / 2 + 20 && x < 350 / 2 + 30) && (y > 350 / 2 + 20
						&& y < 350 / 2 + 30))
				pixel_put_img(x, y, w, PERSO_MM);
			x++;
		}
		x = 25;
		y++;
	}
}

static void	color_map(t_wolf *w, int x, int y, t_map *m)
{
	int		x_map;
	int		y_map;

	x_map = x - 175 + w->p->x / 2;
	y_map = y - 175 + w->p->y / 2;
	if (x_map < 0 || y_map < 0 || x_map > w->mm.xend || y_map > w->mm.yend)
		return ;
	while ((m->next))
	{
		if ((x_map >= m->xbegin / 2 && x_map <= m->xend / 2) &&
				(y_map >= m->ybegin / 2 && y_map <= m->yend / 2))
			break ;
		m = m->next;
	}
	if (m->value == '2')
		pixel_put_img(x + 25, y + 25, w, WALL_MM);
	else
		pixel_put_img(x + 25, y + 25, w, ROOF_MM);
}

static void	crea_map(t_wolf *w, t_map *m, int x, int y)
{
	t_map	*save;

	save = m;
	while (y < 375)
	{
		while (x < 375)
		{
			pixel_put_img(x, y, w, VOID_MM);
			color_map(w, x - 25, y - 25, m);
			x++;
		}
		m = save;
		x = 25;
		y++;
	}
	player_map(w);
}

void		minimap(t_wolf *w)
{
	t_map	*tmp;
	t_map	*tmp_bis;

	tmp = w->m;
	tmp_bis = w->m;
	init_map(w, tmp_bis);
	crea_map(w, tmp, 25, 25);
	mlx_put_image_to_window(w->ptr, w->win, w->img, 0, 0);
}
