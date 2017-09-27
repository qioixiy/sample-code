package main

import (
  "unsafe"
  "C"
)

func Test(args[] string){
  arg := make([](*_Ctype_char), 0)  //C语言char*指针创建切片
  l := len(args)
  for i,_ := range args{
      char := C.CString(args[i])
      defer C.free(unsafe.Pointer(char)) //释放内存
      strptr := (*_Ctype_char)(unsafe.Pointer(char))
      arg = append(arg, strptr)  //将char*指针加入到arg切片
  }
                                                                                 
  C.test(C.int(l), (**_Ctype_char)(unsafe.Pointer(&arg[0])))  //即c语言的main(int argc,char**argv)
}

func main() {
     Test("hello")
}