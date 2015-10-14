## build gdb server
- [BuildingCrossGDBandGDBserver](https://sourceware.org/gdb/wiki/BuildingCrossGDBandGDBserver)
- example `./configure --target=arm-linux-gnueabihf
cd gdb/gdbserver && ./configure --host=arm-linux-gnueabihf`

##net debug
- `./gdbserver 192.168.2.100:2345 hello
(gdb) target remote 192.168.2.223:2345
`

##UART debug
- 
`gdbserver /dev/ttyO0 ./simple-touch
(gdb) target remote /dev/ttyUSB0
`
