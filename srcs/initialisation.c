/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 17:58:30 by jubeal            #+#    #+#             */
/*   Updated: 2019/03/25 14:47:22 by adjouber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_player	*init_player(void)
{
	t_player	*p;

	if (!(p = (t_player*)malloc(sizeof(t_player))))
		return (0);
	p->cam = 50;
	p->x = 588;
	p->y = 415;
	p->fov = 70.;
	p->dov = 45.;
	return (p);
}

void		init_wolf(t_wolf **w, t_map *m)
{
	if (!((*w) = (t_wolf *)malloc(sizeof(t_wolf))))
		return ;
	(*w)->m = m;
	if (!((*w)->p = init_player()))
		return ;
}

void		ft_open_windows(t_wolf *w)
{
	if (!(w->ptr = mlx_init()))
	{
		ft_putstr("manque de place pour mlx_init\n");
		exit(0);
	}
	w->win = mlx_new_window(w->ptr, WIN_X, WIN_Y, "Wolf3d");
	if (!(w->img = mlx_new_image(w->ptr, WIN_X, WIN_Y)))
	{
		ft_putstr("manque de place pour new_image\n");
		exit(0);
	}
	if (!(w->data = mlx_get_data_addr(w->img, &w->bpp, &w->size_line,
					&w->endian)))
	{
		ft_putstr("manque de place pour data_addr\n");
		exit(0);
	}
}

void		pixel_put_img(int x, int y, t_wolf *curent, int color)
{
	int		pixel;

	pixel = x * 4 + y * curent->size_line;
	if (pixel < 0 || pixel > WIN_X * WIN_Y * 4)
		return ;
	curent->data[pixel] = color & 0xFF;
	curent->data[pixel + 1] = color >> 8 & 0xFF;
	curent->data[pixel + 2] = color >> 16 & 0xFF;
}
