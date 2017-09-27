package main

import (
	"fmt"
)

type TZ int

func main() {
	var a TZ
	a.Print()
	(*TZ).Print(&a)

	var i int
	i.Increase()
}

func (a *TZ) Print() {
	fmt.Println("TZ")
}

func (i *int) Increase() {
	*i = *i + 100;
}
