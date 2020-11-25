package main

import (
	"fmt"
	"io/ioutil"
)

/*
	No macros in golang :[
*/

func main() {
	file := "Grace_kid.go"
	str := "package main%[1]c%[1]cimport (%[1]c	%[2]cfmt%[2]c%[1]c	%[2]cio/ioutil%[2]c%[1]c)%[1]c%[1]c/*%[1]c	No macros in golang :[%[1]c*/%[1]c%[1]cfunc main() {%[1]c	file := %[2]cGrace_kid.go%[2]c%[1]c	str := %[2]c%[3]s%[2]c%[1]c	ioutil.WriteFile(file, []byte(fmt.Sprintf(str, 10, 34, str)), 0644)%[1]c}%[1]c"
	ioutil.WriteFile(file, []byte(fmt.Sprintf(str, 10, 34, str)), 0644)
}
