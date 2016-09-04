char * str = "hello\n";
void print() {
  asm(
      "movl $8, %%edx\n\t"
      "movl %0, %%ecx\n\t"
      "movl $0, %%ebx\n\t"
      "movl $4, %%eax\n\t"
      "int $0x80\n\t"
      :
      :"r"(str)
      :"edx", "ecx", "ebx");
}
//*
void myexit() {
  asm(
      "movl $42, %%ebx\n\t"
      "movl $1, %%eax\n\t"
      "int $0x80\n\t"
      :::);
}
//*/
void nomain() {
  print();
  myexit();
}
