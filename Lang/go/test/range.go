package main

import (
	"fmt"
)

func main() {
	sli := []int{1,2,3}
	for i, v := range sli {
		fmt.Println(i, ":", v)
	}

}
