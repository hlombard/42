# API

#### PING

/api/ping </br>
	✅ ``GET: check connection`` </br>

#### ACCOUNT

/api/account/create </br>
	✅ ``POST: create account`` </br>

/api/account/verify?token=xxx </br>
	✅ ``POST: verify the account of token's owner (token= aes enc of email)`` </br>

/api/account/forgot_password </br>
	✅ ``POST: send reset_password mail`` </br>

/api/account/reset_password?token=xxx </br>
	✅ ``POST: reset the password of token's owner (token= random hex string)`` </br>

#### USER

/api/user/:username </br>
	✅ ``GET get username data`` </br>
	✅ ``PATCH change username data (if access token == username)`` </br>

/api/user/:username/find </br>
	✅ ``POST get suggested profiles for :username or research`` </br>

/api/user/:username/visit </br>
	✅ ``POST add username a visit (from access token owner)`` </br>

/api/user/:username/like </br>
	✅ ``POST add username a like (from access token owner)`` </br>
	✅ ``DELETE remove the like to username (from access token owner)`` </br>

/api/user/:username/rating </br>
	✅ ``POST add/update username rating (from access token owner)`` </br>

/api/user/:username/report </br>
	✅ ``POST add username a report (from access token owner)`` </br>

/api/user/:username/block </br>
	✅ ``POST add username a block (from access token owner)`` </br>
	✅ ``DELETE remove a block from username (from access token owner)`` </br>

/api/user/:username/tag </br>
	✅ ``POST add a tag to username`` </br>
	✅ ``DELETE remove a tag from username`` </br>



#### LOGIN && REFRESH && LOGOUT

/api/login </br>
	✅ ``POST: login`` </br>

/api/refresh </br>
	✅ ``GET: refresh JWT`` </br>

/api/logout </br>
	✅ ``POST: Remove Access and Refresh tokens and set is_online to false`` </br>

#### IMAGES

/api/images/:username/{1..5}.png </br>
	✅ ``GET get username pictures`` </br>

/api/images?number={1..5} </br>
	✅ ``POST upload an image png/jpg and save it locally (server)`` </br>
