# lamp
## install 1
``` sh
sudo apt-get update
sudo apt-get install apache2
sudo apt-get install php
sudo apt-get install mysql-server mysql-client
sudo apt-get install phpmyadmin
sudo chmod 777 /var/www
sudo ln -s /usr/share/phpmyadmin /var/www/html
firefox localhost/phpadmin
```
## install 2
``` sh
sudo tasksel install lamp-server
```
