#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct  s_env
{
	void *mlx;
	void *win;
	int z;
	int y;
	int x;
	int x2;
	int y2;
	int r;
	int g;
	int b;
	t_coord	 **coord;

}				t_;

typedef struct s_coord
{
	int z;
	int y;
	int x;
	int x2;
	int y2;
}				t_coord;

void draw(t_mlx *p)
{
	p->y = 250;
	while (p->y < 300)
	{
		p->x = 250;
		while (p->x < 300)
		{
			mlx_pixel_put(p->mlx, p->win, p->x, p->y, p->rgb);
			p->x++;
		}
		p->y++;
	}
}

int key_funct(int keycode, t_mlx *p)
{
	printf("keycode = %d\n",keycode);
	if(keycode == 53)
		exit(0);
	if (keycode == 126)
	{

		draw(p);
	}
	return (0);
}

int exp_funct(t_mlx *p)
{
	draw(p);
	return (0);
}
int main()
{
	t_mlx p;

	p.mlx = mlx_init();
	p.win = mlx_new_window(p.mlx, 500, 500, "mlx 42");
	mlx_key_hook(p.win, key_funct, &p);
	mlx_expose_hook(p.win, exp_funct, &p);
	mlx_loop(p.mlx);
}
