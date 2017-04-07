#include "wolf3d.h"

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

typedef struct s_pos_i
{
	int x;
	int y;
}				t_pos_i;



// void set_step(t_pos_f *ray_pos, t_pos_i *step, t_pos_f *side_dist, t_pos_i *map) {
	

// }
void get_wall_pos(t_pos_f *ray_pos, t_pos_f *side_dist, t_pos_i *map, t_pos_f *ray_dir)
{
		// t_pos_i step;
		// int hit = 0;
		// int side;

		// // set_step(ray_pos->x, ray_pos->y, &step, side_dist, map);

		// while (hit == 0)
		// {
		// 	if (side_dist->x < side_dist->y)
		// 	{
		// 	  side_dist->x += deltaDistX;
		// 	  map.x += step.x;
		// 	  side = 0;
		// 	}
		// 	else
		// 	{
		// 	  side_dist->y += deltaDistY;
		// 	  map.y += step.y;
		// 	  side = 1;
		// 	}
		// 	if (worldMap[map.x][map.y] > 0)
		// 		hit = 1;
		// } 
		// //Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
		// if (side == 0) perpWallDist = (map.x - ray_pos->x + (1 - step.x) / 2) / ray_dir->x;
		// else           perpWallDist = (map.y - ray_pos->y + (1 - step.y) / 2) / ray_dir->y;
}
void draw(t_env *e) {
	// e->startTime = time(NULL);
	// t_pos_f ray_dir;

	gettimeofday(&e->startTime, NULL);
	for(int x = 0; x < e->w_width; x++)
	{
		e->cameraX = 2 * x / (double)(e->w_width) - 1; //x-coordinate in camera space
		
		e->ray_pos.x = e->posX;
		e->ray_pos.y = e->posY;
		e->ray_dir.x = e->dirX + e->planeX * e->cameraX;
		e->ray_dir.y = e->dirY + e->planeY * e->cameraX;

		//which box of the map we're in
		t_pos_i map;
		map.x = (int)(e->ray_pos.x);
		map.y = (int)(e->ray_pos.y);

		//length of ray from current position to next x or y-side
		t_pos_f side_dist;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = sqrt(1 + (e->ray_dir.y * e->ray_dir.y) / (e->ray_dir.x * e->ray_dir.x));
		double deltaDistY = sqrt(1 + (e->ray_dir.x * e->ray_dir.x) / (e->ray_dir.y * e->ray_dir.y));
		double perpWallDist;
		t_pos_i step;

		step.x = (e->ray_dir.x < 0) ? -1 : 1;
		side_dist.x = (e->ray_dir.x < 0) ? (e->ray_pos.x - map.x) * deltaDistX : (map.x + 1.0 - e->ray_pos.x) * deltaDistX;
		step.y = (e->ray_dir.y < 0) ? -1 : 1;
		side_dist.y = (e->ray_dir.y < 0) ? (e->ray_pos.y - map.y) * deltaDistY : (map.y + 1.0 - e->ray_pos.y) * deltaDistY;

		// get_wall_pos(&e->ray_pos, &side_dist, &map);
		
		int hit = 0;
		int side;

		// set_step(e->ray_pos.x, e->ray_pos.y, &step, side_dist, map);

		while (hit == 0)
		{
			if (side_dist.x < side_dist.y)
			{
			  side_dist.x += deltaDistX;
			  map.x += step.x;
			  side = 0;
			}
			else
			{
			  side_dist.y += deltaDistY;
			  map.y += step.y;
			  side = 1;
			}
			if (worldMap[map.x][map.y] > 0)
				hit = 1;
		} 
		//Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
		if (side == 0) perpWallDist = (map.x - e->ray_pos.x + (1 - step.x) / 2) / e->ray_dir.x;
		else           perpWallDist = (map.y - e->ray_pos.y + (1 - step.y) / 2) / e->ray_dir.y;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(e->w_height/ perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + e->w_height/ 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + e->w_height/ 2;
		if(drawEnd >= e->w_height)
			drawEnd = e->w_height- 1;

		//choose wall color
		int color;
		switch(worldMap[map.x][map.y])
		{
			case 1:  color = 0xFF0000;  break; //red
			case 2:  color = 0x00FF00;  break; //green
			case 3:  color = 0x0000FF;   break; //blue
			case 4:  color = 0xFFFFFF;  break; //white
			default: color = 0xFFFF00; break; //yellow
		}

	  //give x and y sides different brightness
	  // if (side == 1) {color = color / 2;}

	  //draw the pixels of the stripe as a vertical line
	  t_point start;
	  start.x = x;
	  start.y = drawStart;

	  t_point end;
	  end.x = x;
	  end.y = drawEnd;

	  // draw_line(e, start, end, texX);
	  draw_line(e, start, end, color);
    	// ft_printf("%d, %d, %d\n", x, drawStart, color);
	}
	// draw_point_to_img(env, x, y, env->buffer[y][x]);
	// mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);

	// for(int x = 0; x < env->w_width; x++)
 //    	for(int y = 0; y < env->w_height; y++)
 //    		draw_point_to_img(env, x, y, 0);
	// draw_buffer(env);
    // for(int x = 0; x < env->w_width; x++)
    // 	for(int y = 0; y < env->w_height; y++)
    // 		env->buffer[y][x] = 0; //clear the buffer instead of cls()

	// env->endTime = time(NULL);
	gettimeofday(&e->endTime, NULL);
	long double frameTime = fabs((e->endTime.tv_usec - e->startTime.tv_usec) / 1000000.0);
	printf("Time: %Lf\n", 1.0 / frameTime);
	// printf("Time 2: %f\n", e->endTime - e->startTime);
	//speed modifiers
    e->moveSpeed = frameTime * 50.0; //the constant value is in squares/second
    e->rotSpeed = frameTime * 30.0; //the constant value is in radians/second
}

int	key_handler(int keycode, t_env *e)
{
	printf("%d\n", keycode);
    // W
	if (keycode == 13 || keycode == 126)
	{
		if(worldMap[(int)(e->posX + e->dirX * e->moveSpeed)][(int)(e->posY)] == 0) e->posX += e->dirX * e->moveSpeed;
		if(worldMap[(int)(e->posX)][(int)(e->posY + e->dirY * e->moveSpeed)] == 0) e->posY += e->dirY * e->moveSpeed;
	}
	// A
	if (keycode == 0 || keycode == 123)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = e->dirX;
		e->dirX = e->dirX * cos(e->rotSpeed) - e->dirY * sin(e->rotSpeed);
		e->dirY = oldDirX * sin(e->rotSpeed) + e->dirY * cos(e->rotSpeed);
		double oldPlaneX = e->planeX;
		e->planeX = e->planeX * cos(e->rotSpeed) - e->planeY * sin(e->rotSpeed);
		e->planeY = oldPlaneX * sin(e->rotSpeed) + e->planeY * cos(e->rotSpeed);
	}
	// S
	if (keycode == 1 || keycode == 125)
	{
		if(worldMap[(int)(e->posX - e->dirX * e->moveSpeed)][(int)(e->posY)] == 0) e->posX -= e->dirX * e->moveSpeed;
      	if(worldMap[(int)(e->posX)][(int)(e->posY - e->dirY * e->moveSpeed)] == 0) e->posY -= e->dirY * e->moveSpeed;
	}
	// D
	if (keycode == 2 || keycode == 124)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = e->dirX;
		e->dirX = e->dirX * cos(-e->rotSpeed) - e->dirY * sin(-e->rotSpeed);
		e->dirY = oldDirX * sin(-e->rotSpeed) + e->dirY * cos(-e->rotSpeed);
		double oldPlaneX = e->planeX;
		e->planeX = e->planeX * cos(-e->rotSpeed) - e->planeY * sin(-e->rotSpeed);
		e->planeY = oldPlaneX * sin(-e->rotSpeed) + e->planeY * cos(-e->rotSpeed);
	}

	mlx_destroy_image(e->mlx, e->img);
	e->img = mlx_new_image(e->mlx, e->w_width, e->w_height);

	draw(e);

	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return 0;
}

int main(int ac, char **av)
{
	double posX = 22;
	double posY = 12;
	double dirX = -1;
	double dirY = 0;
	double planeX = 0;
	double planeY = 0.66;


	// double time = 0;
	// double oldTime = 0;
	
	// struct timespec start, end;
	// clock_gettime(CLOCK_MONOTONIC_RAW, &start);

	t_env env;
	env.w_width = screenWidth;
	env.w_height = screenHeight;

	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, env.w_width, env.w_height, "Wolf3D");
	env.img = mlx_new_image(env.mlx, env.w_width, env.w_height);
	
	env.img_ptr = mlx_get_data_addr((void *)env.img, &(env.bpp),
		&(env.line_size), &(env.endian));

	env.posX = 22;
	env.posY = 12;
	env.dirX = -1;
	env.dirY = 0;
	env.planeX = 0;
	env.planeY = 0.66;
	env.tex_width = 64;
	env.tex_height = 64;


	// unsigned int buffer[env.w_height][env.w_width]; // y-coordinate first because it works per scanline
	// int texture[8][env.tex_width * env.tex_height];
	// for(int i = 0; i < 8; i++)
	// 	texture[i].resize(env.tex_width * env.tex_height);

	//generate some textures
	printf("textures\n");
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

	ft_printf("drawing");
	draw(&env);
	mlx_put_image_to_window(env.mlx, env.win, env.img, 0, 0);
	

	// mlx_hook(pe->env.win, 6, 1, drag, e);
	// time_t startTime = time(NULL);
	// time_t endTime = time(NULL);
	// gettimeofday(&stop, NULL);
	// uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
	// ft_printf("%d", delta_us);
	// int i = 0;
	// while (i < 1000000000)
	// {
	// 	i++;
	// }
	
	
	// t_point start;
	//   start.x = 0;
	//   start.y = 0;

	//   t_point end;
	//   end.x = 200;
	//   end.y = 200;
	// draw_line(&env, start, end, 0xFFFFFF);

	// draw(&env);
	mlx_hook(env.win, 2, 1, key_handler, &env);
	// mlx_key_hook(env.win, key_handler, &env);
	mlx_loop(env.mlx);

	
	ac = 0;
	av = 0;
	return (0);
}