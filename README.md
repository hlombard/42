# Fils de Fer (FdF)

This project is about creating a simplified 3D graphic representation of a relief landscape based on an isometric projection. Using minilibX (a basic Graphic library).

## Preview

<img  align="left"  src="https://media.giphy.com/media/jV5MLtO9Mutl5ZQq58/giphy.gif"  width="45%"  height="250px"  >
<img  align="right"  src="https://i.imgur.com/g4j8mQO.png"  width="45%"  height="250px">

<br><br><br><br><br>

## <br><br><br><br>Installation

``` git clone --single-branch --branch FdF https://github.com/hlombard/42.git hlombard_FdF ```


## Compiling and running


Run `make`

Once executable is created : `./fdf ./maps/42.fdf`

You can also enter a 2nd and a 3rd argument to set window resolution : `./fdf ./maps/42.fdf`  ``1280``  ``960``


(default is 1920 x 1080)


## Compatibility

Developed on macOS X.

macOS Sierra: Remove the ``Werror`` flag in the Makefile and ignore the "deprecated" warnings.
