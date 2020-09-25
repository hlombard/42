# Ft_linear_regression

**A linear regression implemented with Gradient Descent**

## Preview

<img  align="center"  src="https://i.gyazo.com/b4a63d4b7d43693a105a33a85cdab497.gif"  width="50%"  height="50%">

## Installation

``` git clone --single-branch --branch ft_linear_regression $GOPATH/src/ft_linear_regression ```

## Compiling and running

<h4>- First we train the algorithm:</h4>


- ``` cd training; go run train.go ```
This will generate a file thetas.txt by default

<h4>- Now we can predict:</h4>

-  ``` cd prediction; go run predict.go ```
Enter an X value, and it will predict his Y value using t0 and t1 generated in the thetas.txt

Flags available: ./train.go | ./predict.go **-help**

## Compatibility
Developed on Linux Xubuntu. </br>
