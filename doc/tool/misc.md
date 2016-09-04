## Uart文件传输工具
- [lrzsz](http://www.filewatcher.com/m/lrzsz-0.12.20.tar.gz.280938-0.html)

## sh color output
printf("\x1b[31mThis is red text\x1b[0m\n");
printf("\x1b[32mThis is green text\x1b[0m\n");
sed 's/200/\x1b[32m&\x1b[0m/g' access_log.log
sed 's/3[0-9][0-9]/\x1b[33m&\x1b[0m/g' access_log.log
sed 's/\(HTTP\/1\.[01]" \)\(3[0-9][0-9]\)/\1\x1b[33m\2\x1b[0m/g' access_log.log
sed 's/\(HTTP\/1\.[01]" [0-9][0-9][0-9] \)\([0-9]\+\)[0-9][0-9][0-9]/\1\x1b[31m[\2KB]\x1b[0m/g' access_log.log

## valgrind
`valgrind --tool=memcheck ./myList`

##
- xournal, 画板工具

## rss
http://www.linuxjournal.com/content/command-line-cloud-rss2email
