#-*-coding:utf-8-*-
#python3.3.5
import urllib.parse,urllib.request,http.cookiejar,io,webbrowser
import tkinter as tk
from tkinter import *
from tkinter.ttk import *
from urllib.request import urlopen
from PIL import Image, ImageTk
global root
#设置cookie
cookie = http.cookiejar.CookieJar()
cookieProc = urllib.request.HTTPCookieProcessor(cookie)
opener = urllib.request.build_opener(cookieProc)
urllib.request.install_opener(opener)
#根据路径和POST内容来提交表单
def getUrlRequest(iUrl,iStrPostData):
    postdata = urllib.parse.urlencode(iStrPostData)
    postdata = postdata.encode(encoding='UTF8')
    header = {'User-Agent':'Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)'}
    req= urllib.request.Request(
        url = iUrl,
        data = postdata,
        headers = header)
    data = urllib.request.urlopen(req).read()
    try:
        data = data.decode('utf-8')
    except:
        data = data.decode('gbk', 'ignore')
    return data

#获取验证码图片
def getCodeImg():
    urlCode='http://csdn.juming.com/code.htm'
    image_bytes = urlopen(urlCode).read()
    # internal data file
    data_stream = io.BytesIO(image_bytes)
    # open as a PIL image object
    pil_image = Image.open(data_stream)
    tk_image = ImageTk.PhotoImage(pil_image)
    return tk_image

#构建界面
def createGui(msg=''):
    global root
    root = tk.Tk()
    root.title("CSDN免积分下载器 v0.1")
    root.resizable(False, False)   #禁止修改窗口大小
    root.geometry('+400+250')  #屏幕位置
    #-------------------------------------------
    tk_image = getCodeImg()
    # put the image on a typical widget
    frm_top_label = tk.Label(root,compound = 'top',image=tk_image,text="验证码图片",fg="blue",bg="brown",font=('Tempus Sans ITC',20))
    frm_top_label.grid(row = 0, column = 0, padx = 15, pady = 2)
    #-------------------------------------------
    frm_bottom = tk.LabelFrame(root)
    frm_bottom.grid(row = 1, column = 0, padx = 15, pady = 2)

    frm_bottom_label_0 = tk.Label(frm_bottom,text="下载地址:", font=('Tempus Sans ITC',15))
    frm_bottom_label_0.grid(row = 0, column = 0, padx = 5, pady = 2,sticky = "e") #控件右对齐

    frm_bottom_label_1 = tk.Label(frm_bottom,text="  验证码:", font=('Tempus Sans ITC',15))
    frm_bottom_label_1.grid(row = 1, column = 0, padx = 5, pady = 2,sticky = "e")

    frm_bottom_entry_var_0 = StringVar()
    frm_bottom_entry_0 = tk.Entry(frm_bottom,textvariable=frm_bottom_entry_var_0)
    frm_bottom_entry_0.grid(row = 0, column = 1, padx = 15, pady = 2)

    frm_bottom_entry_var_1 = StringVar()
    frm_bottom_entry_1 = tk.Entry(frm_bottom,textvariable=frm_bottom_entry_var_1) #设置密码输入框，熟悉show
    frm_bottom_entry_1.grid(row = 1, column = 1, padx = 15, pady = 2)

    frm_bottom_btn_0 = tk.Button(frm_bottom,text="下   载",relief=RIDGE,bd=4,width=10, font=('Tempus Sans ITC',12),command=lambda:downloadSource(frm_bottom_entry_var_0,frm_bottom_entry_var_1,frm_top_label,frm_foot_label))
    frm_bottom_btn_0.grid(row = 3, column = 1, padx = 15, pady = 2,sticky = "w")

    frm_foot_label = tk.Label(root,text=msg ,font=('Tempus Sans ITC',10))
    frm_foot_label.grid(row = 3, column = 0, padx = 15, pady = 2)

    root.mainloop()

#获取下载资源地址
def getSourceUrl(code,ziyuandz):
    #资源信息
    strLoginInfo = {'csdn_zh': '用户名',
                    'csdn_mm': '密码',
                    're_yzm':code,
                    'ziyuandz':ziyuandz #'http://download.csdn.net/detail/shinian1987/8430743' #
    }
    #下载资源地址
    urlLogin='http://csdn.juming.com/index.htm'
    returnHtml = str(getUrlRequest(urlLogin,strLoginInfo))
    a = returnHtml.find('电信下载地址：<strong>') + 15
    b = returnHtml.find('</strong><br>网通下载地址：')
    durl = returnHtml[a:b]
    return durl

#下载资源
def downloadSource(frm_bottom_entry_var_0,frm_bottom_entry_var_1,frm_top_label,frm_foot_label):
    try:
        ziyuandz = frm_bottom_entry_var_0.get()
        code = frm_bottom_entry_var_1.get()
        durl = getSourceUrl(code,ziyuandz)
        print('资源地址：'+ durl)
        reMsg = "已经打开浏览器，请下载..."
        yzm = durl.find("验证码")
        #yzm += durl.find("验证码验证错误")
        #yzm += durl.find("验证码输入不正确")
        fs = durl.find("封杀本工具特意加")
        gs = durl.find("正确的格式如")
        jf = durl.find("成功获取到0点积分")
        xzzy = durl.find("http:")
        if fs > 0:
            reMsg = "该资源被封杀，请稍后再下载..."
        elif code=='':
            reMsg = "验证码不能为空..."
        elif ziyuandz=='':
            reMsg = "下载地址不能为空..."
        elif gs > 0:
            reMsg = "资源地址错误，请重新输入..."
        elif yzm > 0:
            reMsg = "验证码输入错误..."
        elif jf > 0:
            reMsg = "积分不足，资源无法下载..."
        elif xzzy >= 0:
            webbrowser.open(durl, new=0, autoraise=True)
        else:
            reMsg = "资源错误或没有找到下载资源..."
            #print(xzzy)
        frm_foot_label['text'] = reMsg
        tk_image = getCodeImg()
        frm_top_label.configure(image = tk_image)
        frm_top_label.image= tk_image
    except:
        root.destroy()
        createGui('程序错误，请重新下载...')
        #MAIN
createGui()
