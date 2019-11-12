# Fractol  <img align="right" src="http://i.imgur.com/zuWTuWk.png" width="10%" height="100">
Discover 2D programming and the psychedelic universe of fractals, using minilibX (a basic Graphic library).

Implemented with OpenCL, parallel computing on GPU.

## Preview

<img align="left" src="https://media.giphy.com/media/mGV4koIhi1AchoXMOR/giphy.gif" width="45%" height="250px" >

<img align="right" src="https://media.giphy.com/media/QVyFdsO6DsPysFq39T/giphy.gif" width="45%" height="250px" >
 
<br> <br> <br> <br> <br>

## <br> <br> <br> <br> Installation

``` git clone --single-branch --branch fractol https://github.com/hlombard/42.git hlombard_fractol ```


## Compiling and running


Run `make`

Once executable is created : `./fractol -name`

Fractals available: 

- -julia 
- -mandelbrot
- -tricorn 
- -bs (burningship)


## Compatibility

Developed on macOS X.

macOS Sierra: Remove the ``-Werror`` flag in the Makefile and ignore the OpenCL's "deprecated" warnings.
