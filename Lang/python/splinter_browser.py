#-*- coding: UTF-8 -*-

from splinter.browser import Browser

b = Browser(driver_name="chrome")

# b.visit("http://www.baidu.com")

# b.fill("wd", "splinter")
# button = b.find_by_value(u"百度一下")
# button.click()

b.visit("https://kyfw.12306.cn/otn/login/init")
b.find_by_text(u"登录").click()
username="qioixiy"
passwd="12306_com_"
b.fill("loginUserDTO.user_name", username) # username部分输入自己的账号
b.fill("userDTO.password", passwd) # passwd部分输入账号密码

b.cookies.add({"_jc_save_fromDate":"2016-02-13"}) # 此处添加出发日期
b.cookies.add({"_jc_save_fromStation":"%u6210%u90FD%2CCDW"}) # 此处添加出发地
b.cookies.add({u'_jc_save_toStation':'%u676D%u5DDE%2CHZH'}) # 此处添加目的地
b.cookies.all()

b.find_by_text(u"查询").click()
b.find_by_text(u"预订")[1].click() # 下标1表示买的是可选班次的第二班车
