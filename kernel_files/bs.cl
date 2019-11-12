#define WIDTH		1920
#define HEIGHT		1080

kernel void bs_gpu(__global double *input, __global int *results)
{
	int			id;
	int			pixel;
	int			x;
	int			y;
	int			i;
	int			max_ite;

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
	color = input[6];

	real = 1.5 * (x - WIDTH / 2) / (double)(0.500 * WIDTH * zoom) + move_x;
	imag = (y - HEIGHT / 2) / (double)(0.500 * HEIGHT * zoom) + move_y;

	oldreal = oldimag = 0;
	newreal = real;
	newimag = imag;

	i = -1;
	while (++i < max_ite)
	{
		oldreal = newreal;
		oldimag = newimag;
		(oldreal < 0) ? oldreal = -oldreal : 0;
		(oldimag < 0) ? oldimag = -oldimag : 0;
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
