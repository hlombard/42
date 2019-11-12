/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 12:47:53 by hlombard          #+#    #+#             */
/*   Updated: 2019/07/23 12:48:36 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	read_kernel(t_kernel *kernel, int type)
{
	int			fd;

	if (type == 1)
	{
		if ((fd = open("./kernel_files/mandelbrot.cl", O_RDONLY)) < 0)
			fractol_exit("Couldn't open mandelbrot.cl");
	}
	else if (type == 2)
	{
		if ((fd = open("./kernel_files/julia.cl", O_RDONLY)) < 0)
			fractol_exit("Couldn't open julia.cl");
	}
	else if (type == 3)
	{
		if ((fd = open("./kernel_files/bs.cl", O_RDONLY)) < 0)
			fractol_exit("Couldn't open bs.cl");
	}
	else
	{
		if ((fd = open("./kernel_files/tricorn.cl", O_RDONLY)) < 0)
			fractol_exit("Couldn't open tricorn.cl");
	}
	get_file_info(kernel, fd, type);
}

void	get_file_info(t_kernel *kernel, int fd, int type)
{
	int ret;

	if (type == 1)
		ret = stat("./kernel_files/mandelbrot.cl", &kernel->stat_ret);
	else if (type == 2)
		ret = stat("./kernel_files/julia.cl", &kernel->stat_ret);
	else if (type == 3)
		ret = stat("./kernel_files/bs.cl", &kernel->stat_ret);
	else
		ret = stat("./kernel_files/tricorn.cl", &kernel->stat_ret);
	if (ret != 0)
		fractol_exit("Couldn't get .cl infos");
	if (!(kernel->file_content = (char*)malloc(sizeof(char)
			* kernel->stat_ret.st_size)))
		fractol_exit("Couldn't allocate .cl file");
	if (read(fd, kernel->file_content, kernel->stat_ret.st_size) < 0)
		fractol_exit("Couldn't read .cl file");
	kernel->st_size = (size_t)kernel->stat_ret.st_size;
}

void	init_opencl(t_fract *fract, t_kernel *kernel)
{
	cl_int	ret;

	ret = clGetPlatformIDs(1, &kernel->platform_id,
			&kernel->ret_num_platforms);
	ret = clGetDeviceIDs(kernel->platform_id, CL_DEVICE_TYPE_DEFAULT,
			1, &kernel->device_id, &kernel->ret_num_devices);
	kernel->context = clCreateContext(NULL, 1, &kernel->device_id,
			NULL, NULL, &ret);
	kernel->command_queue = clCreateCommandQueue(kernel->context,
			kernel->device_id, 0, &ret);
	kernel->results = clCreateBuffer(kernel->context, CL_MEM_READ_WRITE,
			fract->width * fract->height * sizeof(int), NULL, &ret);
	kernel->input = clCreateBuffer(kernel->context, CL_MEM_READ_WRITE,
		sizeof(double) * 7, NULL, &ret);
	create_kernel(fract, kernel);
}

void	create_kernel(t_fract *fract, t_kernel *kernel)
{
	cl_int ret;

	kernel->program = clCreateProgramWithSource(kernel->context, 1,
		(const char **)&kernel->file_content,
			(const size_t *)&kernel->st_size, &ret);
	ret = clBuildProgram(kernel->program, 0, NULL,
		NULL, NULL, NULL);
	if (fract->type == 1)
		kernel->kernel = clCreateKernel(kernel->program,
			"mandelbrot_gpu", &ret);
	if (fract->type == 2)
		kernel->kernel = clCreateKernel(kernel->program, "julia_gpu", &ret);
	if (fract->type == 3)
		kernel->kernel = clCreateKernel(kernel->program, "bs_gpu", &ret);
	if (fract->type == 4)
		kernel->kernel = clCreateKernel(kernel->program, "tricorn_gpu", &ret);
	ret = clSetKernelArg(kernel->kernel, 0, sizeof(cl_mem), &kernel->input);
	ret = clSetKernelArg(kernel->kernel, 1, sizeof(cl_mem), &kernel->results);
	kernel->global_item_size = fract->width * fract->height;
}

void	exec_kernel(t_kernel *kernel, t_fract *fract)
{
	double	input[7];

	set_input(input, fract);
	kernel->ret = clEnqueueWriteBuffer(kernel->command_queue,
		kernel->input, CL_TRUE, 0, sizeof(double) * 7, input, 0, NULL, NULL);
	kernel->ret = clGetKernelWorkGroupInfo(kernel->kernel, kernel->device_id,
		CL_KERNEL_WORK_GROUP_SIZE, sizeof(kernel->local), &kernel->local, NULL);
	kernel->ret = clEnqueueNDRangeKernel(kernel->command_queue, kernel->kernel,
		1, NULL, &kernel->global_item_size, &kernel->local, 0, NULL, NULL);
	if (kernel->ret)
		ft_printf("OpenCL Error code =  [%d]\n", kernel->ret);
	kernel->ret = clEnqueueReadBuffer(kernel->command_queue,
		kernel->results, CL_TRUE, 0, fract->width * fract->height * sizeof(int),
			fract->data_buffer, 0, NULL, NULL);
	kernel->ret = clFlush(kernel->command_queue);
	kernel->ret = clFinish(kernel->command_queue);
}
