/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:23:53 by jubeal            #+#    #+#             */
/*   Updated: 2019/03/25 15:42:46 by adjouber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	mlx(t_wolf *w)
{
	ft_open_windows(w);
	interface(w);
	minimap(w);
//	wolf(w);
	mlx_hook(w->win, 2, 1L << 1, move, w);
	mlx_key_hook(w->win, keyboard, w);
	mlx_hook(w->win, 17, 1L << 17, close_prog, w);
	mlx_loop(w->ptr);
}

int		main(int ac, char **av)
{
	int		fd;
	t_map	*m;
	t_wolf	*w;

	if (ac < 2)
		return (0);
	w = NULL;
	fd = open(av[1], O_RDONLY);
	if (!(m = parser(fd)))
		return (0);
	init_wolf(&w, m);
	if (!w)
		return (0);
	mlx(w);
	return (0);
}
