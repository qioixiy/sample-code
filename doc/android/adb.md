
# adb wifi
## android
$setprop service.adb.tcp.port 5555
$stop adbd
$start adbd
getprop | grep 'service.adb.tcp'
## pc connect
adb connect ip:port
## pc disconnect
adb disconnect ip:port
