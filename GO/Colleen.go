package main

import "fmt"

/*
	42
*/
func colleen() {
	return
}

func main() {
	/*
		Hi
	*/
	str := "package main%[1]c%[1]cimport %[2]cfmt%[2]c%[1]c%[1]c/*%[1]c	42%[1]c*/%[1]cfunc colleen() {%[1]c	return%[1]c}%[1]c%[1]cfunc main() {%[1]c	/*%[1]c		Hi%[1]c	*/%[1]c	str := %[2]c%[3]s%[2]c%[1]c	fmt.Printf(str, 10, 34, str)%[1]c	colleen()%[1]c	return%[1]c}%[1]c"
	fmt.Printf(str, 10, 34, str)
	colleen()
	return
}
