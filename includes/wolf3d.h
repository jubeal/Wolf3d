/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:00:10 by jubeal            #+#    #+#             */
/*   Updated: 2019/03/25 15:43:08 by adjouber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "get_next_line.h"
# include "mlx.h"

# define PI 3.14159265359
# define WIN_X 1650
# define WIN_Y 960
# define WALLS 0x1BA310
# define ROOF 0x666666
# define SKY 0x0099FF
# define WALL_MM 0x1BA310
# define ROOF_MM 0XBBBBBB
# define VOID_MM 0x0
# define PERSO_MM 0x2546FA

typedef struct		s_map
{
	int				x;
	int				y;
	int				xbegin;
	int				ybegin;
	int				xend;
	int				yend;
	char			value;
	struct s_map	*next;
}					t_map;

typedef struct		s_prc
{
	int				x1;
	int				x2;
	int				y1;
	int				y2;
	t_map			*m;
}					t_prc;

typedef struct		s_brese_para
{
	int				x1;
	int				x2;
	int				y1;
	int				y2;
	int				xinc;
	int				yinc;
	int				dx;
	int				dy;
}					t_brese_para;

typedef struct		s_player
{
	int				x;
	int				y;
	int				cam;
	double			fov;
	double			dov;
}					t_player;

typedef struct		s_mini
{
	int				xend;
	int				yend;
}					t_mini;

typedef struct		s_wolf
{
	void			*ptr;
	void			*win;
	void			*img;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
	t_mini			mm;
	t_player		*p;
	t_map			*m;
}					t_wolf;

t_map				*parser(int fd);
int					close_prog(t_wolf *w);
int					keyboard(int key, t_wolf *w);
void				init_wolf(t_wolf **w, t_map *m);
void				ft_open_windows(t_wolf *w);
int					*cast(t_prc *p);
void				wolf(t_wolf *w);
void				minimap(t_wolf *w);
int					move(int key, t_wolf *w);
void				pixel_put_img(int x, int y, t_wolf *current, int color);
void				interface(t_wolf *w);

#endif
