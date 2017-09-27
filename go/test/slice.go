package main

import (
	"fmt"
)

func main() {

	var s1 []int
	fmt.Println(s1)

	a := [10]int{1,2,3,4,5,6,7,8,9,10}
	fmt.Println(a)

	s2 := a[5:10]
	fmt.Println(s2)

	s3 := a[6:]
	fmt.Println(s3)

	s4 := make([]int, 3, 10)
	fmt.Println(s4)
}
