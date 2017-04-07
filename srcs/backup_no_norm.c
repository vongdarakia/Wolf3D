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

void draw(t_env *env) {
	// env->startTime = time(NULL);
	gettimeofday(&env->startTime, NULL);
	for(int x = 0; x < env->w_width; x++)
	{
		double cameraX = 2 * x / (double)(env->w_width) - 1; //x-coordinate in camera space
		double rayPosX = env->posX;
		double rayPosY = env->posY;
		double rayDirX = env->dirX + env->planeX * cameraX;
		double rayDirY = env->dirY + env->planeY * cameraX;

		//which box of the map we're in
		int mapX = (int)(rayPosX);
		int mapY = (int)(rayPosY);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
		stepX = -1;
		sideDistX = (rayPosX - mapX) * deltaDistX;
		}
		else
		{
		stepX = 1;
		sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
		stepY = -1;
		sideDistY = (rayPosY - mapY) * deltaDistY;
		}
		else
		{
		stepY = 1;
		sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
		}

		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
			  sideDistX += deltaDistX;
			  mapX += stepX;
			  side = 0;
			}
			else
			{
			  sideDistY += deltaDistY;
			  mapY += stepY;
			  side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0) hit = 1;
		} 

		//Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
		if (side == 0) perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
		else           perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(env->w_height/ perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + env->w_height/ 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + env->w_height/ 2;
		if(drawEnd >= env->w_height)drawEnd = env->w_height- 1;

		//choose wall color
		int color;
		switch(worldMap[mapX][mapY])
		{
			case 1:  color = 0xFF0000;  break; //red
			case 2:  color = 0x00FF00;  break; //green
			case 3:  color = 0x0000FF;   break; //blue
			case 4:  color = 0xFFFFFF;  break; //white
			default: color = 0xFFFF00; break; //yellow
		}

	  //give x and y sides different brightness
	  if (side == 1) {color = color / 2;}

		//texturing calculations
      // int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

      // //calculate value of wallX
      // double wallX; //where exactly the wall was hit
      // if (side == 0) wallX = rayPosY + perpWallDist * rayDirY;
      // else           wallX = rayPosX + perpWallDist * rayDirX;
      // wallX -= floor((wallX));

      // //x coordinate on the texture
      // int texX = (int)(wallX * (double)(env->tex_width));
      // if(side == 0 && rayDirX > 0) texX = env->tex_width - texX - 1;
      // if(side == 1 && rayDirY < 0) texX = env->tex_width - texX - 1;

      // for(int y = drawStart; y<drawEnd; y++)
      // {
      //   int d = y * 256 - env->tex_height * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
      //   int texY = ((d * env->tex_height) / lineHeight) / 256;
      //   unsigned int color = env->texture[texNum][env->tex_height * texY + texX];
      //   //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
      //   if(side == 1) color = (color >> 1) & 8355711;
      //   // env->buffer[y][x] = color;
      //   draw_point_to_img(env, x, y, color);
      // }

	  //draw the pixels of the stripe as a vertical line
	  t_point start;
	  start.x = x;
	  start.y = drawStart;

	  t_point end;
	  end.x = x;
	  end.y = drawEnd;

	  // draw_line(env, start, end, texX);
	  draw_line(env, start, end, color);
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