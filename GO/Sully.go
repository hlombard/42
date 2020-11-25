package main

import (
	"fmt"
	"io/ioutil"
	"os/exec"
)

var offset string

const fileFmt = "Sully_%d.go"

func main() {
	var i = 5
	if i <= 0 {
		return
	}
	if offset == "TRUE" {
		i++
	}
	i--
	file := fmt.Sprintf(fileFmt, i)
	str := "package main%[1]c%[1]cimport (%[1]c	%[2]cfmt%[2]c%[1]c	%[2]cio/ioutil%[2]c%[1]c	%[2]cos/exec%[2]c%[1]c)%[1]c%[1]cvar offset string%[1]c%[1]cconst fileFmt = %[2]cSully_%%d.go%[2]c%[1]c%[1]cfunc main() {%[1]c	var i = %[3]d%[1]c	if i <= 0 {%[1]c		return%[1]c	}%[1]c	if offset == %[2]cTRUE%[2]c {%[1]c		i++%[1]c	}%[1]c	i--%[1]c	file := fmt.Sprintf(fileFmt, i)%[1]c	str := %[2]c%[4]s%[2]c%[1]c	ioutil.WriteFile(file, []byte(fmt.Sprintf(str, 10, 34, i, str)), 0644)%[1]c	arg := fmt.Sprintf(%[2]cSully_%%d%[2]c, i)%[1]c	cmd := exec.Command(%[2]cgo%[2]c, %[2]cbuild%[2]c, %[2]c-ldflags%[2]c, %[2]c-X main.offset=FALSE%[2]c, arg+%[2]c.go%[2]c)%[1]c	cmd.Run()%[1]c	cmd = exec.Command(%[2]c./%[2]c + arg)%[1]c	cmd.Run()%[1]c}%[1]c"
	ioutil.WriteFile(file, []byte(fmt.Sprintf(str, 10, 34, i, str)), 0644)
	arg := fmt.Sprintf("Sully_%d", i)
	cmd := exec.Command("go", "build", "-ldflags", "-X main.offset=FALSE", arg+".go")
	cmd.Run()
	cmd = exec.Command("./" + arg)
	cmd.Run()
}
