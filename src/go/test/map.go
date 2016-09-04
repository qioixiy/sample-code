package main

import (
	"fmt"
)

func main() {
	var m map[int]string = make(map[int]string)
	fmt.Println(m)

	m[1] = "ok"
	fmt.Println(m)

	delete(m,1)
	fmt.Println(m)


	var n map[int]map[int]string = make(map[int]map[int]string)
	fmt.Println(n)

	n[1] = make(map[int]string)
	n[1][1] = "OK n"
	fmt.Println(n)
}
