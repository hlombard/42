# Ft_ssl_md5

**Implementation of hash functions: MD5, SHA256, SHA512, SHA224, SHA384**

## Preview

<img  align="center"  src="https://i.gyazo.com/ad94680ba9663dc4c9f4f93bdde28a5e.gif"  width="90%"  height="130px">

## Installation

``` git clone --single-branch --branch ft_ssl_md5 https://github.com/hlombard/42.git ft_ssl_md5 ```

## Compiling and running

Run `make`

Once executable is created : ./ft_ssl [hash] [flags] [arguments]

<h5>

- **hash:**
	- md5
	- sha256
	- sha512
	- sha224
	- sha384

- **flags:**
	- -q (quiet mode)
	- -r (reverse the format of the output)
	- -s (print the sum of the given string. ex: ./ft_ssl_md5 sha256 -s "Hello world !")
	- -p (echo STDIN to STDOUT and append the checksum to STDOUT)

- **arguments:** any files or executables (big files/exec will take a while.. I wasn't allowed to use fstat for a one time read)

</h5>

## Compatibility

Developed on Linux Xubuntu. </br>
Tested on macOS High Sierra
