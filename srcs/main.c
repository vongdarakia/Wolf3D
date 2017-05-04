#include "wolf3d.h"

t_env init_env(int ac, char **av)
{
	t_env env;

	env.w_width = screenWidth;
	env.w_height = screenHeight;
	if (ac > 1)
		read_map(&env, av[1]);
	else
		read_map(&env, "map1.txt");
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, env.w_width, env.w_height, "Wolf3D");
	env.img = mlx_new_image(env.mlx, env.w_width, env.w_height);
	env.img_ptr = mlx_get_data_addr((void *)env.img, &(env.bpp),
		&(env.line_size), &(env.endian));
	env.ray_pos.x = 22;
	env.ray_pos.y = 12;
	env.dir.x = -1;
	env.dir.y = 0;
	env.plane.x = 0;
	env.plane.y = 0.66;
	env.tex_width = 64;
	env.tex_height = 64;
	// env.move_spd = 0;
	env.move_spd = 0.1;
	env.rot_spd = 0.05;
	env.prev_time = clock();
	ft_bzero(env.keys, NUM_KEYS);
	return (env);
}

int main(int ac, char **av)
{
	t_env env;

	env = init_env(ac, av);

	// generate some textures
	// printf("textures\n");
	env.buffer = (unsigned int**)malloc(sizeof(int*) * screenHeight);
	for (int i = 0; i < screenHeight; i++) {
		env.buffer[i] = (unsigned int*)malloc(sizeof(int) * screenWidth);
	}

	env.texture = (int**)malloc(sizeof(int*) * 8);
	for(int i = 0; i < 8; i++) {
		env.texture[i] = (int*)malloc(sizeof(int) * (env.tex_width * env.tex_height ));
	}
	for(int x = 0; x < env.tex_width; x++)
	for(int y = 0; y < env.tex_height; y++)
	{
		int xorcolor = (x * 256 / env.tex_width) ^ (y * 256 / env.tex_height);
		//int xcolor = x * 256 / env.tex_width;
		int ycolor = y * 256 / env.tex_height;
		int xycolor = y * 128 / env.tex_height + x * 128 / env.tex_width;
		env.texture[0][env.tex_width * y + x] = 65536 * 254 * (x != y && x != env.tex_width - y); //flat red texture with black cross
		env.texture[1][env.tex_width * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
		env.texture[2][env.tex_width * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
		env.texture[3][env.tex_width * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
		env.texture[4][env.tex_width * y + x] = 256 * xorcolor; //xor green
		env.texture[5][env.tex_width * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
		env.texture[6][env.tex_width * y + x] = 65536 * ycolor; //red gradient
		env.texture[7][env.tex_width * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
	}

	ft_printf("drawing\n");
	draw_rays(&env);
	mlx_put_image_to_window(env.mlx, env.win, env.img, 0, 0);

	// mlx_do_key_autorepeatoff(env.mlx);
	mlx_hook(env.win, 3, 1, key_released, &env);
	mlx_hook(env.win, 2, 1, key_pressed, &env);
	// mlx_key_hook(env.win, key_hook, &env);
	mlx_loop_hook(env.mlx, loop_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}