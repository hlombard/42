package main

import (
	"encoding/csv"
	"flag"
	"fmt"
	"image/color"
	"io"
	"log"
	"math/rand"
	"os"
	"strconv"
	"time"

	"github.com/cheggaaa/pb"
	"gonum.org/v1/plot"
	"gonum.org/v1/plot/plotter"
	"gonum.org/v1/plot/vg/draw"
)

/*
		-graph=1
	You can use: feh --reload 0.1 graph.png to visualize on linux
*/

var MIN, MAX float64

func errCheck(err error, str string) {
	if err != nil {
		log.Fatalln(err, "on:", str)
		os.Exit(1)
	}
}

func getData(file string) map[float64]float64 {

	data := make(map[float64]float64)

	f, err := os.Open(file)
	if err != nil {
		log.Fatal("Unable to read input file "+file, err)
	}

	csvReader := csv.NewReader(f)
	i := 0
	for {
		line, err := csvReader.Read()
		if err == io.EOF {
			break
		} else if err != nil {
			log.Fatal(err)
		}

		if i != 0 {
			x, err := strconv.ParseFloat(line[0], 64)
			errCheck(err, line[0])
			y, err := strconv.ParseFloat(line[1], 64)
			errCheck(err, line[1])
			if x < 0 || y < 0 {
				log.Fatal("Invalid input -> X or Y cannot be less than 0")
			}
			data[x] = y
		}
		i++
	}
	return data
}

func linearRegression(data map[float64]float64) ([]float64, []float64) {

	learningRate := 0.5
	iterations := 1000
	var currT0 float64 = 0
	var currT1 float64 = 0

	var allT0, allT1 []float64

	for i := 0; i < iterations; i++ {
		currT0, currT1 = step(currT0, currT1, data, learningRate)
		tmpT0, tmpT1 := denormalizeData(currT0, currT1)
		allT0 = append(allT0, tmpT0)
		allT1 = append(allT1, tmpT1)
	}

	return allT0, allT1
}

func step(currT0 float64, currT1 float64, data map[float64]float64, learningRate float64) (float64, float64) {

	gradientT0 := 0.0
	gradientT1 := 0.0

	for x, y := range data {
		gradientT0 += (currT0 + (currT1 * x)) - y
		gradientT1 += ((currT0 + (currT1 * x)) - y) * x
	}

	currT0 -= learningRate / float64(len(data)) * gradientT0
	currT1 -= learningRate / float64(len(data)) * gradientT1

	return currT0, currT1
}

func getMinMax(data map[float64]float64) (float64, float64) {

	var minX, maxX float64

	i := 0
	for x := range data {
		if i == 0 {
			minX = x
			maxX = x
		} else if x < minX {
			minX = x
		} else if x > maxX {
			maxX = x
		}
		i++
	}

	return minX, maxX
}

func normalizeData(data map[float64]float64) map[float64]float64 {

	normalized := make(map[float64]float64)
	MIN, MAX = getMinMax(data)

	for x, y := range data {
		normalized[(x-MIN)/(MAX-MIN)] = y
	}

	return normalized
}

func denormalizeData(t0 float64, t1 float64) (float64, float64) {
	tmp0 := t0
	tmp1 := t1

	t0 = tmp1*-MIN/(MAX-MIN) + tmp0
	t1 = tmp1*(1-MIN)/(MAX-MIN) + tmp0 - t0

	return t0, t1
}

func writeThetas(t0 float64, t1 float64, output string) {
	f, err := os.Create(output)
	if err != nil {
		fmt.Println(err)
		return
	}

	str := fmt.Sprintf("%.15f %.15f\n", t0, t1)
	_, err = f.WriteString(str)
	if err != nil {
		fmt.Println(err)
		f.Close()
		return
	}

	fmt.Println("New thetas generated in", output)
	err = f.Close()
	if err != nil {
		fmt.Println(err)
		return
	}
}

func rearrangeData(data map[float64]float64) ([]float64, []float64) {

	var xs, ys []float64

	for x, y := range data {
		xs = append(xs, x)
		ys = append(ys, y)
	}
	return xs, ys
}

type xyer struct{ xs, ys []float64 }

func (x xyer) Len() int                    { return len(x.xs) }
func (x xyer) XY(i int) (float64, float64) { return x.xs[i], x.ys[i] }

func plotData(data map[float64]float64, t0, t1 []float64) {

	bar := pb.StartNew(len(t0))
	for i := 0; i < len(t0); i++ {
		p, err := plot.New()
		if err != nil {
			log.Fatal("Could not create plot:", err)
		}

		p.Title.Text = "Price for mileage"
		p.X.Label.Text = "Mileage"
		p.X.Label.Position = 0
		p.X.Label.Padding = 10
		p.X.Color = color.RGBA{255, 0, 0, 0}
		p.Y.Label.Text = "Price"
		p.Y.Label.Position = 0
		p.Y.Label.Padding = 10
		p.Y.Color = color.RGBA{255, 0, 0, 0}
		p.Add()

		xs, ys := rearrangeData(data)
		s, err := plotter.NewScatter(xyer{xs, ys})
		if err != nil {
			log.Fatal("Could not create scatter:", err)
		}

		s.GlyphStyle.Shape = draw.CrossGlyph{}
		s.Color = color.RGBA{R: 255, A: 255}
		p.Add(s)

		outFile, err := os.Create("graph.png")
		if err != nil {
			log.Fatal("Could not create:", "graph.png", err)
		}

		d := make(plotter.XYs, 2)
		d[0].X = MIN
		d[0].Y = t0[i] + t1[i]*MIN
		d[1].X = MAX
		d[1].Y = t0[i] + t1[i]*MAX

		l, err := plotter.NewLine(d)
		if err != nil {
			log.Fatal("could not create line:", err)
		}
		R := uint8(rand.Intn(255))
		G := uint8(rand.Intn(255))
		B := uint8(rand.Intn(255))
		l.Color = color.RGBA{R, G, B, 255}
		p.Add(l)

		writer, err := p.WriterTo(256, 256, "png")
		if err != nil {
			log.Fatal("Could not create writer:", err)
		}

		_, err = writer.WriteTo(outFile)
		if err != nil {
			log.Fatal("Could not write:", err)
		}

		bar.Increment()
		time.Sleep(200 * time.Millisecond)
	}
	bar.Finish()
}

func main() {

	viz := flag.Int("graph", 0, "Set to =1 for visualizer")
	dataFile := flag.String("data", "../data/data.csv", "the data file")
	output := flag.String("output", "../data/thetas.txt", "the output file")

	flag.Parse()

	defaultdata := getData(*dataFile)
	data := normalizeData(defaultdata)
	t0, t1 := linearRegression(data)

	if *viz == 1 {
		plotData(defaultdata, t0, t1)
	}

	writeThetas(t0[len(t0)-1], t1[len(t1)-1], *output)
}
