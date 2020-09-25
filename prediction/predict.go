package main

import (
	"bufio"
	"flag"
	"fmt"
	"io/ioutil"
	"log"
	"os"
	"strconv"
	"strings"
)

func getThetas(file string) (float64, float64) {

	var t0, t1 float64

	data, err := ioutil.ReadFile(file)
	if err != nil {
		fmt.Printf("Warning: no %s file found, default set to 0\n", file)
		return 0, 0
	}

	_, err = fmt.Sscanf(string(data), "%f %f", &t0, &t1)
	if err != nil {
		log.Fatal("Couldn't get thetas from file", file, err)
	}

	return t0, t1

}

func getInput() float64 {

	fmt.Printf("Enter a mileage: ")
	reader := bufio.NewReader(os.Stdin)
	input, err := reader.ReadString('\n')
	input = strings.TrimRight(input, "\r\n")
	if err != nil {
		log.Fatal("Couldn't get a valid input", err)
	}

	mileage, err := strconv.ParseFloat(input, 64)
	if err != nil {
		log.Fatal(err)
	}

	return mileage
}

func outputResult(mileage float64, t0, t1 float64) {

	f := func(input float64, t0, t1 float64) float64 {
		return t0 + (t1 * mileage)
	}

	fmt.Println(f(mileage, t0, t1))
}

func main() {

	thetasFile := flag.String("thetas", "../data/thetas.txt", "the thetas file path")
	flag.Parse()

	t0, t1 := getThetas(*thetasFile)
	mileage := getInput()
	outputResult(mileage, t0, t1)
}
