package main

import (
	"fmt"
)

func main() {
	var a [2]int
	var b [2]int
	
	a = [...]int{1, 2}

	a = [...]int{1: 3}

	b = a

	fmt.Println(a)
	fmt.Println(b)
}
