## go build
- build -x -v选项来输出编译的详细过程

//testcrosscompile.go
package main

import (
"fmt"
"runtime"
)

func main() {
fmt.Println(runtime.GOOS)
} 
$go tool compile testcrosscompile.go
testcrosscompile.o
$go tool link testcrosscompile.o
a.out
$a.out
linux