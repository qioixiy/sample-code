#!/usr/bin/env python
#-*- coding:utf-8 -*-

"""
说明: 简单远程控制服务端实现
作者: wangaibo168@163.com
编码: UTF-8
更新:

消息类型
1获取计算机名
11获取进程列表
12结束进程
21弹出对话框
31锁定计算机
41列出目录
51执行程序
61退出程序

待升级:
获取窗口标题列表
获取桌面图片
下载对方电脑文件
上传对方电脑文件
升级列出驱动器列表
升级关闭、重启、注销对方电脑
升级读取当前用户名称
wxPython可视化界面
"""

import socket;
import json;
import base64;

# 编码数据
def EncodeMessage(s,t,p):
    return base64.b64encode(json.dumps({"s":s,"t":t,"p":p}));

# 解码数据
def DecodeMessage(data):
    sdata = None;
    try:
        sdata = base64.b64decode(data);
        if not sdata:
            return sdata;
        sdata = json.loads(sdata);
    except:
        sdata = None;
    return sdata;

def SendSocketMessage(s,m):
    if not s:
        return;
    try:
        s.send(m);
        s.send("\r\n");
    except Exception,e:
        pass;

def GetSocketMessage(s):
    if not s:
        return None;
    data = list();
    try:
        while True:
            data.append(s.recv(4096));
            if "".join(data)[-1:]=="\n":
                break;
    except Exception,e:
        pass;
    data = "".join(data);
    data = data.strip();
    return DecodeMessage(data);

def T01(s):
    SendSocketMessage(s,EncodeMessage(True,1,None));
    data = GetSocketMessage(s);
    if data:
        print data;

def T12(s,pid):
    SendSocketMessage(s,EncodeMessage(True,12,{"pid":pid}));
    data = GetSocketMessage(s);
    if data:
        print data;

def T11(s):
    SendSocketMessage(s,EncodeMessage(True,11,None));
    data = GetSocketMessage(s);
    if data:
        for p in data["p"]:
            print p

def T21(s,t,m):
    SendSocketMessage(s,EncodeMessage(True,21,{"title":t,"message":m}));
    print("ok!");

def T31(s):
    SendSocketMessage(s,EncodeMessage(True,31,None));
    data = GetSocketMessage(s);
    if data:
        print data;

def T41(s,path):
    SendSocketMessage(s,EncodeMessage(True,41,{"path":path}));
    data = GetSocketMessage(s);
    if data:
        for p in data["p"]:
            print p

def T51(s,action,path,args,directory):
    SendSocketMessage(s,EncodeMessage(True,51,{"action":action,"path":path,"args":args,"dir":directory}));
    data = GetSocketMessage(s);
    if data:
        print data;

def T61(s):
    SendSocketMessage(s,EncodeMessage(True,61,None));

def SocketService(host,port):
    try:
        s = socket.socket(socket.AF_INET,socket.SOCK_STREAM,0);
        s.connect((host,port));
        s.settimeout(5);
        #T01(s);
        #T11(s);
        #T12(s,1760);
        #T21(s,"消息","哈哈好玩吧");
        #T31(s);
        #T41(s,"D:\\");
        T51(s,"open",r"D:\\20088139278380_2.jpg",None,None);
        #T61(s);
    except Exception,e:
        pass;
    finally:
        if s:
            s.close();

if __name__ == "__main__":
    SocketService("192.168.0.123",8888);
