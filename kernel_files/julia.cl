#define WIDTH		1920
#define HEIGHT		1080

__kernel void julia_gpu(__global double *input, __global int *results)
{
	int			id;
	int			x;
	int			y;
	int			i;
	int			max_ite;
	int			pixel;
	
	int			color;

	double		newreal;
	double		newimag;
	double		oldreal;
	double		oldimag;
	double		zoom;
	double		move_x;
	double		move_y;
	double		real;
	double		imag;

	id = get_global_id(0);
	pixel = get_global_id(1) * WIDTH + get_global_id(0);
	x = id % WIDTH;
	y = id / WIDTH;

	zoom = input[0];
	move_x = input[1];
	move_y = input[2];
	max_ite = input[3];
	real = input[4];
	imag = input[5];
	color = input[6];

	newreal = 1.5 * (x - WIDTH / 2) / (0.5 * zoom * WIDTH) + move_x;
	newimag = (y - HEIGHT / 2) / (0.5 * zoom * HEIGHT) + move_y;

	i = -1;
	while (++i < max_ite)
	{
		oldreal = newreal;
		oldimag = newimag;
		newreal = oldreal * oldreal - oldimag * oldimag + real;
		newimag = 2 * oldreal * oldimag + imag;
		if ((newreal * newreal + newimag * newimag) > 4)
			break ;
	}
	if (i == 0)
		results[pixel] = 0;
	else
		results[pixel] = i * color;
}
