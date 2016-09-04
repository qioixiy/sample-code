package main

import (
	"fmt"
)

func main() {
LABEL1:
	for i := 0 ; i < 10; i++ {
		for {
			fmt.Println(i)
			//goto LABEL1
			continue LABEL1
		}
	}
}
