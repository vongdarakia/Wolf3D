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

typedef struct	s_draw_env
{
	t_point cam_pos;
	t_point ray_pos;
	t_point ray_dir;
	// t_point map_pos;
	t_point side_dist;
	t_point dlt_dist_pos;
	int map_x;
	int map_y;
	int step_x;
	int step_y;
	int hit;
	int side;
	int line_height;
	int d_start;
	int d_end;
	int color;
	double perp_wall_dist;
}		t_draw_env;

void draw(t_env *env) {
	// env->startTime = time(NULL);
	t_draw_env denv;

	gettimeofday(&env->startTime, NULL);
	for(int x = 0; x < env->w_width; x++)
	{
		// printf("yo %d\n", x);
		denv.cam_pos.x = 2 * x / (double)(env->w_width) - 1; //x-coordinate in camera space
		denv.ray_pos.x = env->posX;
		denv.ray_pos.y = env->posY;
		denv.ray_dir.x = env->dirX + env->planeX * denv.cam_pos.x;
		denv.ray_dir.y = env->dirY + env->planeY * denv.cam_pos.x;

		//which box of the map we're in
		denv.map_x = (int)(denv.ray_pos.x);
		denv.map_y = (int)(denv.ray_pos.y);

		//length of ray from current position to next x or y-side
		// denv.side_dist.x denv.side_dist.x;
		// denv.side_dist.y denv.side_dist.y;

		//length of ray from one x or y-denv.side to next x or y-side
		denv.dlt_dist_pos.x = sqrt(1 + (denv.ray_dir.y * denv.ray_dir.y) / (denv.ray_dir.x * denv.ray_dir.x));
		denv.dlt_dist_pos.y = sqrt(1 + (denv.ray_dir.x * denv.ray_dir.x) / (denv.ray_dir.y * denv.ray_dir.y));
		// double denv.perp_wall_dist;

		//what direction to step in x or y-direction (either +1 or -1)
		// int denv.step_x;
		// int denv.step_y;


		// int denv.hit = 0; //was there a wall hit?
		// int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if (denv.ray_dir.x < 0)
		{
			denv.step_x = -1;
			denv.side_dist.x = (denv.ray_pos.x - denv.map_x) * denv.dlt_dist_pos.x;
		}
		else
		{
			denv.step_x = 1;
			denv.side_dist.x = (denv.map_x + 1.0 - denv.ray_pos.x) * denv.dlt_dist_pos.x;
		}
		if (denv.ray_dir.y < 0)
		{
			denv.step_y = -1;
			denv.side_dist.y = (denv.ray_pos.y - denv.map_y) * denv.dlt_dist_pos.y;
		}
		else
		{
			denv.step_y = 1;
			denv.side_dist.y = (denv.map_y + 1.0 - denv.ray_pos.y) * denv.dlt_dist_pos.y;
		}

		//perform DDA
		while (denv.hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (denv.side_dist.x < denv.side_dist.y)
			{
			  denv.side_dist.x += denv.dlt_dist_pos.x;
			  denv.map_x += denv.step_x;
			  denv.side = 0;
			}
			else
			{
			  denv.side_dist.y += denv.dlt_dist_pos.y;
			  denv.map_y += denv.step_y;
			  denv.side = 1;
			}
			//Check if ray has denv.hit a wall
			if (worldMap[denv.map_x][denv.map_y] > 0) denv.hit = 1;
		} 

		//Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
		if (denv.side == 0) denv.perp_wall_dist = (denv.map_x - denv.ray_pos.x + (1 - denv.step_x) / 2) / denv.ray_dir.x;
		else           denv.perp_wall_dist = (denv.map_y - denv.ray_pos.y + (1 - denv.step_y) / 2) / denv.ray_dir.y;

		//Calculate height of line to draw on screen
		denv.line_height = (int)(env->w_height/ denv.perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		denv.d_start = -denv.line_height / 2 + env->w_height/ 2;
		if(denv.d_start < 0)denv.d_start = 0;
		denv.d_end = denv.line_height / 2 + env->w_height/ 2;
		if(denv.d_end >= env->w_height)denv.d_end = env->w_height- 1;

		//choose wall color
		// int denv.color;
		switch(worldMap[denv.map_x][denv.map_y])
		{
			case 1:  denv.color = 0xFF0000; break; //red
			case 2:  denv.color = 0x00FF00; break; //green
			case 3:  denv.color = 0x0000FF; break; //blue
			case 4:  denv.color = 0xFFFFFF; break; //white
			default: denv.color = 0xFFFF00; break; //yellow
		}

	  //give x and y sides different brightness
	  if (denv.side == 1) {denv.color = denv.color / 2;}

		//texturing calculations
      // int texNum = worldMap[denv.map_x][denv.map_y] - 1; //1 subtracted from it so that texture 0 can be used!

      // //calculate value of wallX
      // double wallX; //where exactly the wall was hit
      // if (denv.side == 0) wallX = denv.ray_pos.y + denv.perp_wall_dist * denv.ray_dir.y;
      // else           wallX = denv.ray_pos.x + denv.perp_wall_dist * denv.ray_dir.x;
      // wallX -= floor((wallX));

      // //x coordinate on the texture
      // int texX = (int)(wallX * (double)(env->tex_width));
      // if(denv.side == 0 && denv.ray_dir.x > 0) texX = env->tex_width - texX - 1;
      // if(denv.side == 1 && denv.ray_dir.y < 0) texX = env->tex_width - texX - 1;

      // for(int y = denv.d_start; y<denv.d_end; y++)
      // {
      //   int d = y * 256 - env->tex_height * 128 + denv.line_height * 128;  //256 and 128 factors to avoid floats
      //   int texY = ((d * env->tex_height) / denv.line_height) / 256;
      //   unsigned int denv.color = env->texture[texNum][env->tex_height * texY + texX];
      //   //make denv.color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
      //   if(denv.side == 1) denv.color = (denv.color >> 1) & 8355711;
      //   // env->buffer[y][x] = denv.color;
      //   draw_point_to_img(env, x, y, denv.color);
      // }

	  //draw the pixels of the stripe as a vertical line
	  t_point start;
	  start.x = x;
	  start.y = denv.d_start;

	  t_point end;
	  end.x = x;
	  end.y = denv.d_end;

	  // draw_line(env, start, end, texX);
	  printf("drawing line %f, %f\n", start.x, start.y);
	  draw_line(env, start, end, denv.color);
    	// ft_printf("%d, %d, %d\n", x, denv.d_start, color);
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
	gettimeofday(&env->endTime, NULL);
	long double frameTime = fabs((env->endTime.tv_usec - env->startTime.tv_usec) / 1000000.0);
	printf("Time: %Lf\n", 1.0 / frameTime);
	// printf("Time 2: %f\n", env->endTime - env->startTime);
	//speed modifiers
    env->moveSpeed = frameTime * 50.0; //the constant value is in squares/second
    env->rotSpeed = frameTime * 30.0; //the constant value is in radians/second
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