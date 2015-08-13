## dbus with systemd
- `dbus-daemon --system --nopidfile --systemd-activation --print-address start standlone dbus session`
- `systemd address DBUS_SESSION_BUS_ADDRESS=unix:path=/var/run/dbus/system_bus_socket`

## gcc error:__stack_chk_fail,[url](http://bbs.csdn.net/topics/350133222)
- gcc error:__stack_chk_fail
- undefined reference to `__stack_chk_fail', CFLAGS中添加-fno-stack-protector
