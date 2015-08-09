## smb share mount
sudo mount -o uid=1001,gid=1000,iocharset=utf8,username=user,password=password -l //192.168.1.50/public /smb/public/

## ssh share mount
sshfs user@domain:/ ~/sshfs

