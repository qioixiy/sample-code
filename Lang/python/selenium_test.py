import os
from selenium import webdriver
from selenium.webdriver.common.keys import Keys

# IE
# iedriver = "C:\Program Files\Internet Explorer\IEDriverServer.exe"
# os.environ["webdriver.ie.driver"] = iedriver
# driver = webdriver.Ie(iedriver)

# chrome
# chromedriver = "C:\Program Files (x86)\Google\Chrome\Application\chromedriver.exe"
# chromedriver = "/usr/bin/chromedriver"
# os.environ["webdriver.chrome.driver"] = chromedriver
# driver = webdriver.Chrome(chromedriver)

#firefox
driver = webdriver.Firefox()

driver.get("http://www.python.org")
assert "Python" in driver.title
elem = driver.find_element_by_name("q")
elem.send_keys("selenium")
elem.send_keys(Keys.RETURN)
assert "Google" in driver.title
driver.close()
driver.quit()
