package main

import (
	"fmt"
)

const (
	a = "123"
	b = len(a)

	c = 2
	d

	e, f = 3, 4
	g, h
)

func main() {
	fmt.Println(4)
	
	fmt.Println(a)
	fmt.Println(b)
	
	fmt.Println(c, d, e, f, g, h)
}
