package main

import "unsafe"
import "fmt"

type T struct {
  a int
  b int
  c int
}

type SliceHeader struct {
 addr uintptr
 len  int
 cap  int
}

func main() {
 t := &T{a: 1, b: 2, c: 3}
 p := unsafe.Sizeof(*t)
 println(int(p))

 sl := &SliceHeader{
  addr: uintptr(unsafe.Pointer(t)),
  len:  int(p),
  cap:  int(p),
 }

 b := *(*[]byte)(unsafe.Pointer(sl))
 println(len(b))
 fmt.Println(b)

 b[0] = 7
 b[4] = 5
 b[8] = 8

 fmt.Println(t)

}
