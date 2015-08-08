## Ubuntu 安装Chrome步骤
1. 添加PPA
    - 从Google Linux Repository（http://www.google.com/linuxrepositories/）下载安装Key，或把下面的代码复制进终端，回车，需要管理员密码
    - wget -q -O - https://dl-ssl.google.com/linux/linux_signing_key.pub | sudo apt-key add -
    - Key安装好后，在终端输入：sudo sh -c 'echo "deb http://dl.google.com/linux/chrome/deb/ stable main" >> /etc/apt/sources.list.d/google-chrome.list'

2. 更新
    - 在终端输入：sudo apt-get update

3. 安装
    - sudo apt-get install google-chrome-stable
    - sudo apt-get install google-chrome-beta
    - sudo apt-get install google-chrome-unstable