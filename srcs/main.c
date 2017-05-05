/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <vongdarakia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 22:01:31 by avongdar          #+#    #+#             */
/*   Updated: 2017/05/04 22:01:33 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_env	init_env(int ac, char **av)
{
	t_env env;

	env.w_width = WIN_WIDTH;
	env.w_height = WIN_HEIGHT;
	if (ac > 1)
		read_map(&env, av[1]);
	else
		read_map(&env, "map1.txt");
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, env.w_width, env.w_height, "Wolf3D");
	env.img = mlx_new_image(env.mlx, env.w_width, env.w_height);
	env.img_ptr = mlx_get_data_addr((void *)env.img, &(env.bpp),
		&(env.line_size), &(env.endian));
	env.ray_pos = pos_f(22, 12);
	env.dir = pos_f(-1, 0);
	env.plane = pos_f(0, 0.66);
	env.prev = pos_i(0, 0);
	env.tex_width = 64;
	env.tex_height = 64;
	env.move_spd = 0.1;
	env.rot_spd = M_PI * 2.0 / 180.0;
	ft_bzero(env.keys, NUM_KEYS);
	return (env);
}

void	set_texture(t_env *e, int x, int y, int bit_pos)
{
	int xorcolor;
	int ycolor;
	int xycolor;

	xorcolor = (x * 256 / e->tex_width) ^ (y * 256 / e->tex_height);
	ycolor = y * 256 / e->tex_height;
	xycolor = y * 128 / e->tex_height + x * 128 / e->tex_width;
	e->texture[0][bit_pos] = 65536 * 254 * (x != y && x != e->tex_width - y);
	e->texture[1][bit_pos] = xycolor + 256 * xycolor + 65536 * xycolor;
	e->texture[2][bit_pos] = 256 * xycolor + 65536 * xycolor;
	e->texture[3][bit_pos] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
	e->texture[4][bit_pos] = 256 * xorcolor;
	e->texture[5][bit_pos] = 65536 * 192 * (x % 16 && y % 16);
	e->texture[6][bit_pos] = 65536 * ycolor;
	e->texture[7][bit_pos] = 128 + 256 * 128 + 65536 * 128;
}

void	set_textures(t_env *e)
{
	int	i;
	int x;
	int y;

	i = -1;
	e->buffer = (unsigned int**)malloc(sizeof(int*) * WIN_HEIGHT);
	while (++i < WIN_HEIGHT)
		e->buffer[i] = (unsigned int*)malloc(sizeof(int) * WIN_WIDTH);
	i = -1;
	x = e->tex_width * e->tex_height;
	e->texture = (int**)malloc(sizeof(int*) * 8);
	while (++i < 8)
		e->texture[i] = (int*)malloc(sizeof(int) * x);
	x = -1;
	while (++(x) < e->tex_width)
	{
		y = -1;
		while (++(y) < e->tex_height)
			set_texture(e, x, y, e->tex_width * y + x);
	}
}

int		close_hook(t_env *e)
{
	exit(0);
}

int		main(int ac, char **av)
{
	t_env env;

	env = init_env(ac, av);
	set_textures(&env);
	draw_rays(&env);
	mlx_hook(env.win, 3, 1, key_released, &env);
	mlx_hook(env.win, 2, 1, key_pressed, &env);
	mlx_hook(env.win, 17, 1, close_hook, &env);
	mlx_loop_hook(env.mlx, loop_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}
