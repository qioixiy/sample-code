#!/usr/bin/env python
#-*- coding:utf-8 -*-

"""
说明: 简单远程控制客户端实现
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
"""

import ctypes;
import socket;
import SocketServer;
import threading;
import base64;
import json;
import os;
import ntpath;
import shutil;
import string;
import sys;

__metaclass__ = type;

# 定义进程结构
class PROCESSENTRY32(ctypes.Structure):
    _fields_ = [
        ("dwSize",ctypes.c_ulong),
        ("cntUsage",ctypes.c_ulong),
        ("th32ProcessID",ctypes.c_ulong),
        ("th32DefaultHeapID",ctypes.c_void_p),
        ("th32ModuleID",ctypes.c_ulong),
        ("cntThreads",ctypes.c_ulong),
        ("th32ParentProcessID",ctypes.c_ulong),
        ("pcPriClassBase",ctypes.c_long),
        ("dwFlags",ctypes.c_ulong),
        ("szExeFile",ctypes.c_char*260)
    ]

# 定义结构
class SECURITY_ATTRIBUTES(ctypes.Structure):
    _fields_ = [
        ("nLength",ctypes.c_ulong),
        ("lpSecurityDescriptor",ctypes.c_void_p),
        ("bInheritHandle",ctypes.c_bool)
    ]

# 通过Windows API调用进程列表
def GetProcessList():
    proclist = list();
    flag = False;
    try:
        kernel32 = ctypes.windll.LoadLibrary("kernel32.dll");
        if kernel32==None:
            return proclist,flag;
        pHandle = kernel32.CreateToolhelp32Snapshot(0x2,0x0);
        if pHandle==-1:
            return proclist,flag;
        proc = PROCESSENTRY32();
        proc.dwSize = ctypes.sizeof(proc);
        while kernel32.Process32Next(pHandle,ctypes.byref(proc)):
            proclist.append({"pid":proc.th32ProcessID,"name":ctypes.string_at(proc.szExeFile)});
            kernel32.CloseHandle(pHandle);
            flag = True;
    except Exception,e:
        flag = False;
    return proclist,flag;

# 通过Windows API弹出窗口
def ShowMessageBox(t,m):
    flag = False;
    try:
        user32 = ctypes.windll.LoadLibrary("user32.dll");
        if user32==None:
            return flag;
        rt = user32.MessageBoxA(None,m.encode("gbk"),t.encode("gbk"),0x1000|0x40);
        if rt==0:
            flag = False;
        else:
            flag = True;
    except Exception,e:
        flag = False;
    return flag;

# 通过Windows API锁定计算机
def LockComputer():
    flag = False;
    try:
        user32 = ctypes.windll.LoadLibrary("user32.dll");
        if user32==None:
            return flag;
        rt = user32.LockWorkStation();
        if rt==0:
            flag = False;
        else:
            flag = True;
    except Exception,e:
        flag = False;
    return flag;

# 调用Windows API结束进程
def TerminateProcess(pid):
    flag = False;
    try:
        kernel32 = ctypes.windll.LoadLibrary("kernel32.dll");
        if kernel32==None:
            return flag;
        pHandle = kernel32.OpenProcess(0x1,True,pid);
        if pHandle==None:
            return flag;
        rt = kernel32.TerminateProcess(pHandle,0x0);
        if rt==0:
            flag = False;
        else:
            flag = True;
    except Exception,e:
        flag = False;
    return flag;

# 调用Windows API执行进程
def ShellExecute(action,path,args,root):
    flag = False;
    try:
        shell32 = ctypes.windll.LoadLibrary("shell32.dll");
        if shell32==None:
            return flag;
        rt = shell32.ShellExecuteA(None,action,path,args,root,0x1);
        if rt==42:
            flag = True;
        else:
            flag = False;
    except Exception,e:
        flag = False;
    return flag;

# 列出本地目录
# -列出驱动器列表
# -对于不存在的返回false状态
def GetFileList(path):
    flag = False;
    plist = list();
    try:
        if not path:
            path = os.curdir;
            path = ntpath.abspath(path);
        if not ntpath.exists(path) or not ntpath.isdir(path):
            return plist,flag;
        for p in os.listdir(path):
            ppath = path+"\\"+p;
            ptype = 0;
            if ntpath.isdir(ppath):
                ptype = 1;
            elif ntpath.isfile(ppath):
                ptype = 2;
                stat = os.stat(ppath);
                psize = stat.st_size;
                pctime = stat.st_ctime;
                pmtime = stat.st_mtime;
                patime = stat.st_atime;
                plist.append({
                    "path" : ppath.replace("\\\\","\\"),
                    "type" : ptype,
                    "size" : psize,
                    "ctime" : pctime,
                    "mtime" : pmtime,
                    "atime" : patime
                });
                flag = True;
    except Exception,e:
        flag = False;
    return plist,flag;

# 获取计算机名称
def GetComputerInfo():
    flag = False;
    info = {"name":"","path":""};
    try:
        kernel32 = ctypes.windll.LoadLibrary("kernel32.dll");
        if kernel32==None:
            return info,flag;
        name = ctypes.create_string_buffer(16);
        rt = kernel32.GetComputerNameA(name,ctypes.byref(ctypes.c_int(16)));
        if rt==0:
            return info,flag;
        info["name"] = ctypes.string_at(name);
        info["path"] = ntpath.abspath(os.curdir);
        flag = True;
    except Exception,e:
        flag = False;
        print e;
    return info,flag;

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

# socket监听服务
def SocketService(port):
    class TCPServiceHandle(SocketServer.StreamRequestHandler):
        def handle(self):
            while True:
                try:
                    data = self.rfile.readline().strip();
                    data = DecodeMessage(data);
                    pstatus = False;
                    ptype = 0;
                    pinfo = None;
                    if data and data["s"]==True:
                        if data["t"]==1:
                            pinfo,pstatus = GetComputerInfo();
                        elif data["t"]==11:
                            pinfo,pstatus = GetProcessList();
                        elif data["t"]==12:
                            pstatus = TerminateProcess(data["p"]["pid"]);
                        elif data["t"]==21:
                            pstatus = ShowMessageBox(data["p"]["title"],data["p"]["message"]);
                        elif data["t"]==31:
                            pstatus = LockComputer();
                        elif data["t"]==41:
                            path = data["p"]["path"];
                            pinfo,pstatus = GetFileList(path);
                        elif data["t"]==51:
                            action = data["p"]["action"];
                            if action:
                                action = action.encode("gbk");
                                path = data["p"]["path"];
                            if path:
                                path = path.encode("gbk");
                                args = data["p"]["args"];
                            if args:
                                args = args.encode("gbk");
                                directory = data["p"]["dir"];
                            if directory:
                                directory = directory.encode("gbk");
                                pstatus = ShellExecute(action,path,args,directory);
                        elif data["t"]==61:
                            self.server.shutdown();
                        else:
                            ptype = data["t"];
                            encStr = EncodeMessage(pstatus,ptype,pinfo);
                            self.wfile.write(encStr);
                            self.wfile.write("\r\n");
                except Exception,e:
                    print e;
                    break;
    class ThreadTCPServer(SocketServer.ThreadingMixIn,SocketServer.TCPServer):
        def handle_error(self,request,client_address):
            pass;
        server = ThreadTCPServer((socket.gethostname(),port),TCPServiceHandle);
        server.serve_forever();


# 复制自身到Windows目录下
def CopyLocation():
    try:
        kernel32 = ctypes.windll.LoadLibrary("kernel32.dll");
        if kernel32==None:
            return False;
        path = ctypes.create_string_buffer(260);
        if kernel32.GetModuleFileNameA(None,path,260)==0:
            return False;
        path = ctypes.string_at(path);
        if not ntpath.exists(path):
            return False;
        root = "c:\\windows\\";
        if not ntpath.exists(root):
            root = "c:\\";
        if string.find(string.lower(path),string.lower(root))!=-1:
            return True;
        #dpath = root+"\\"+ntpath.basename(path);
        dpath = root+"\\kaserv.exe";
        if not ntpath.exists(dpath):
            shutil.copyfile(path,dpath);
            if not ntpath.exists(dpath):
                return False;
            ShellExecute("open",dpath,None,None);
        return False;
    except Exception,e:
        return False;

# 注册程序到注册表
def RegistryApp():
    pass;

# 删除程序注册表注册
def UnRegistryApp():
    pass;

# 删除程序自身
def DeleteApp():
    #bat
    #del /f /q e:\app.exe
    #del /f /q e:\del.bat
    pass;

# 确保程序只运行一次
def RunCenter():
    try:
        # 判断程序位置
        # 自身拷贝出现问题，需要修正
        #if not CopyLocation():
        #    return;
        # 注册程序到注册表
        RegistryApp();
        kernel32 = ctypes.windll.LoadLibrary("kernel32.dll");
        if kernel32==None:
            return;
        sec = SECURITY_ATTRIBUTES();
        sec.nLength = ctypes.sizeof(sec);
        sec.lpSecurityDescriptor = ctypes.c_void_p(None);
        sec.bInheritHandle = ctypes.c_bool(True);
        handle = kernel32.CreateMutexA(ctypes.byref(sec),ctypes.c_bool(False),ctypes.c_char_p("KernelARemotClientObject"));
        if kernel32.GetLastError()==183:
            kernel32.CloseHandle(handle);
            ShowMessageBox("提示".decode("utf-8"),"程序已经运行".decode("utf-8"));
            return False;
        ShowMessageBox("提示".decode("utf-8"),"程序开始运行".decode("utf-8"));
        SocketService(8888);
        kernel32.CloseHandle(handle);
    except Exception,e:
        return False;

if __name__ == "__main__":
    argv = sys.argv;
    act = None;
    if len(argv)>=2:
        act = argv[1];
    if act and string.lower(act)=="uninstall":
        UnRegistryApp();
        DeleteApp();
    else:
        RunCenter();
