# ft_ssl_des


**- Data Encryption Standard ecb/cbc/cfb**
<br>
**- Base64 Encoding**


## Clone

``` git clone --single-branch --branch ft_ssl_des https://github.com/hlombard/42.git ft_ssl_des ```

## Compiling and running

Run `make`

Once executable is created : **./ft_ssl [des_type/enc_type] [flags]**

<h5>

- **des_type:**

    - des-ecb
	- des-cbc
	- des-cfb

- **enc_type:**

    - base64


- **FLAGS:**

    - -e, encrypt mode (default)
	- -d, decrypt mode
	- -i, input file for message
	- -o, output file for message
	- -k, key in hex is the next arguement
	- -p, password in ascii is the next argument.
	- -P, print key/salt/vector
	- -s, the salt in hex is the next argument.
	- -v, initialization vector in hex is the next argument.
	- -a, decode/encode the input/output in base64, depending on the encrypt mode
	
### Usage example

$ cat auteur
> hlombard

$ ./ft_ssl des-ecb -i auteur -o auteur.enc -k "0123456789ABCDEF" -a ;cat auteur.enc
> nky7hRQdoPzga2spBpr1xA==

$ ./ft_ssl des-ecb -i auteur.enc -k "0123456789ABCDEF" -a -d
> hlombard

