#! /usr/bin/env python
#-*- encoding: utf-8 -*-

try:
    import subprocessServer
    import os
    import sys
    import wx
except:
    print 'except'
    os.system('sudo apt-get install python-wxgtk2.8 python-wxtools')

import wx
class MyFrame(wx.Frame):
    
    def __init__(self, parent, ID, title):
        wx.Frame.__init__(self,parent,ID,title,(-1,-1),wx.Size(200,700))

        self.Bind(wx.EVT_CLOSE, self.OnCloseWindow)

        panel=wx.Panel(self,-1)
        box=wx.BoxSizer(wx.VERTICAL)

        # power status
        btn_power_status_0 = wx.Button( panel, -1, 'power_status_0')
        box.Add(btn_power_status_0, 0, wx.EXPAND)
        self.Bind(wx.EVT_BUTTON, self.onClicked_power_status_0, btn_power_status_0)
        btn_power_status_1 = wx.Button( panel, -1, 'power_status_1')
        box.Add(btn_power_status_1, 0, wx.EXPAND)
        self.Bind(wx.EVT_BUTTON, self.onClicked_power_status_1, btn_power_status_1)
        btn_power_status_2 = wx.Button( panel, -1, 'power_status_2')
        box.Add(btn_power_status_2, 0, wx.EXPAND)
        self.Bind(wx.EVT_BUTTON, self.onClicked_power_status_2, btn_power_status_2)

        # speed
        btn_speed = wx.Button( panel, -1, 'speed')
        box.Add(btn_speed, 0, wx.EXPAND)
        self.Bind(wx.EVT_BUTTON, self.onClicked_speed, btn_speed)

        # turn signal
        btn_left_turn_signal_0= wx.Button( panel, -1, 'left_turn_signal_0')
        box.Add(btn_left_turn_signal_0, 0, wx.EXPAND)
        self.Bind(wx.EVT_BUTTON, self.onClicked_left_turn_signal_0, btn_left_turn_signal_0)
        btn_left_turn_signal_1= wx.Button( panel, -1, 'left_turn_signal_1')
        box.Add(btn_left_turn_signal_1, 0, wx.EXPAND)
        self.Bind(wx.EVT_BUTTON, self.onClicked_left_turn_signal_1, btn_left_turn_signal_1)
        btn_right_turn_signal_0 = wx.Button( panel, -1, 'right_turn_signal_0')
        box.Add(btn_right_turn_signal_0, 0, wx.EXPAND)
        self.Bind(wx.EVT_BUTTON, self.onClicked_right_turn_signal_0, btn_right_turn_signal_0)
        btn_right_turn_signal_1 = wx.Button( panel, -1, 'right_turn_signal_1')
        box.Add(btn_right_turn_signal_1, 0, wx.EXPAND)
        self.Bind(wx.EVT_BUTTON, self.onClicked_right_turn_signal_1, btn_right_turn_signal_1)

        # gear
        btn_gear_p = wx.Button( panel, -1, 'gear_p' )
        btn_gear_r = wx.Button( panel, -1, 'gear_r' )
        btn_gear_n = wx.Button( panel, -1, 'gear_n' )
        btn_gear_d = wx.Button( panel, -1, 'gear_d' )
        box.Add(btn_gear_p, 0, wx.EXPAND)
        box.Add(btn_gear_r, 0, wx.EXPAND)
        box.Add(btn_gear_n, 0, wx.EXPAND)
        box.Add(btn_gear_d, 0, wx.EXPAND)
        self.Bind(wx.EVT_BUTTON, self.onClicked_gear_p, btn_gear_p)
        self.Bind(wx.EVT_BUTTON, self.onClicked_gear_r, btn_gear_r)
        self.Bind(wx.EVT_BUTTON, self.onClicked_gear_n, btn_gear_n)
        self.Bind(wx.EVT_BUTTON, self.onClicked_gear_d, btn_gear_d)

        # wheel angle
        btn_wheel_angle = wx.Button( panel, -1, 'wheel_angle' )
        box.Add(btn_wheel_angle, 0, wx.EXPAND)
        self.Bind(wx.EVT_BUTTON, self.onClicked_wheel_angle, btn_wheel_angle)

        # manual
        btn_manual_start = wx.Button( panel, -1, 'manual_start' )
        btn_manual_stop = wx.Button( panel, -1, 'manual_stop' )
        box.Add(btn_manual_start, 0, wx.EXPAND)
        box.Add(btn_manual_stop, 0, wx.EXPAND)
        self.Bind(wx.EVT_BUTTON, self.onClicked_manual_start, btn_manual_start)
        self.Bind(wx.EVT_BUTTON, self.onClicked_manual_stop, btn_manual_stop)

        # setting
        btn_auto_start_on = wx.Button( panel, -1, 'auto_start_on' )
        btn_auto_start_off = wx.Button( panel, -1, 'auto_start_off' )
        box.Add(btn_auto_start_on, 0, wx.EXPAND)
        box.Add(btn_auto_start_off, 0, wx.EXPAND)
        self.Bind(wx.EVT_BUTTON, self.onClicked_auto_start_on, btn_auto_start_on)
        self.Bind(wx.EVT_BUTTON, self.onClicked_auto_start_off, btn_auto_start_off)

        btn_sync_lamp_on = wx.Button( panel, -1, 'sync_lamp_on' )
        btn_sync_lamp_off = wx.Button( panel, -1, 'sync_lamp_off' )
        box.Add(btn_sync_lamp_on, 0, wx.EXPAND)
        box.Add(btn_sync_lamp_off, 0, wx.EXPAND)
        self.Bind(wx.EVT_BUTTON, self.onClicked_sync_lamp_on, btn_sync_lamp_on)
        self.Bind(wx.EVT_BUTTON, self.onClicked_sync_lamp_off, btn_sync_lamp_off)
        
        #
        panel.SetSizer(box)
        self.Centre()

    def system(self, cmd):
        os.system(cmd)
    #
    def onClicked_power_status_0(self, event):
        self.system('''adb shell "echo 'a\nIPCL_CAN_POWER_STATUS\n0'>> /tmp/xxx" ''')
    def onClicked_power_status_1(self, event):
        self.system('''adb shell "echo 'a\nIPCL_CAN_POWER_STATUS\n1'>> /tmp/xxx" ''')
    def onClicked_power_status_2(self, event):
        self.system('''adb shell "echo 'a\nIPCL_CAN_POWER_STATUS\n2'>> /tmp/xxx" ''')
    #
    def onClicked_speed(self, event):
        dlg = wx.SingleChoiceDialog(None,
                                    'What speed are you using?', 'Single Choice',
                                    ['5', '12', '16'])
        response ='0'
        if dlg.ShowModal() == wx.ID_OK:
            response = dlg.GetStringSelection()
        dlg.Destroy()
        #cmd = '''adb shell "echo 'a\nIPCL_CAN_VEHICLE_SPEED\n5'>> /tmp/xxx" '''
        cmd = '''adb shell "echo 'a\nIPCL_CAN_VEHICLE_SPEED\n''' + response + ''' '>> /tmp/xxx" '''
        print cmd
        self.system(cmd)
    #
    def onClicked_left_turn_signal_0(self, event):
        self.system('''adb shell "echo 'a\nIPCL_CAN_LEFT_TURN_SIGNAL_STATUS\n0'>> /tmp/xxx" ''')
    def onClicked_right_turn_signal_0(self, event):
        self.system('''adb shell "echo 'a\nIPCL_CAN_RIGHT_TURN_SIGNAL_STATUS\n0'>> /tmp/xxx" ''')
    def onClicked_left_turn_signal_1(self, event):
        self.system('''adb shell "echo 'a\nIPCL_CAN_LEFT_TURN_SIGNAL_STATUS\n1'>> /tmp/xxx" ''')
    def onClicked_right_turn_signal_1(self, event):
        self.system('''adb shell "echo 'a\nIPCL_CAN_RIGHT_TURN_SIGNAL_STATUS\n1'>> /tmp/xxx" ''')
    #
    def onClicked_gear_p(self, event):
        self.system('''adb shell "echo 'a\nIPCL_CAN_GEAR_STATUS\np'>> /tmp/xxx" ''')
    def onClicked_gear_r(self, event):
        self.system('''adb shell "echo 'a\nIPCL_CAN_GEAR_STATUS\nr'>> /tmp/xxx" ''')
    def onClicked_gear_n(self, event):
        self.system('''adb shell "echo 'a\nIPCL_CAN_GEAR_STATUS\nn'>> /tmp/xxx" ''')
    def onClicked_gear_d(self, event):
        self.system('''adb shell "echo 'a\nIPCL_CAN_GEAR_STATUS\nd'>> /tmp/xxx" ''')

    #
    def onClicked_wheel_angle(self, event):
        dlg = wx.SingleChoiceDialog(None,
                                    'What speed are you using?', 'Single Choice',
                                    ['5', '12', '16', '30', '60'])
        response ='0'
        if dlg.ShowModal() == wx.ID_OK:
            response = dlg.GetStringSelection()
        dlg.Destroy()
        self.system('''adb shell "echo 'a\nIPCL_CAN_STEERING_WHEEL_ANGLE `bc <<< "(''' + response + '''+2048)/0.0625"`\nd'>> /tmp/xxx" ''')

    #
    def onClicked_manual_start(self, event):
        cmd='''adb shell "dbus-send --system --print-reply --dest=com.saic.ivi.ADAS.Srv /com/saic/ivi/ADAS/Srv/Service com.saic.ivi.ADAS.Srv.Service.SetValue string:'{\\"type\\":\\"ManualStart\\",\\"value\\":\\"1\\"}'"'''
        os.system(cmd)
    def onClicked_manual_stop(self, event):
        cmd='''adb shell "dbus-send --system --print-reply --dest=com.saic.ivi.ADAS.Srv /com/saic/ivi/ADAS/Srv/Service com.saic.ivi.ADAS.Srv.Service.SetValue string:'{\\"type\\":\\"ManualStart\\",\\"value\\":\\"0\\"}'"'''
        os.system(cmd)

    def onClicked_auto_start_on(self, event):
        cmd='''adb shell "dbus-send --system --print-reply --dest=com.saic.ivi.ADAS.Srv /com/saic/ivi/ADAS/Srv/Service com.saic.ivi.ADAS.Srv.Service.SetValue string:'{\\"type\\":\\"AutoStart\\",\\"value\\":\\"1\\"}'"'''
        os.system(cmd)

    def onClicked_auto_start_off(self, event):
        cmd='''adb shell "dbus-send --system --print-reply --dest=com.saic.ivi.ADAS.Srv /com/saic/ivi/ADAS/Srv/Service com.saic.ivi.ADAS.Srv.Service.SetValue string:'{\\"type\\":\\"AutoStart\\",\\"value\\":\\"0\\"}'"'''
        os.system(cmd)
    def onClicked_sync_lamp_on(self, event):
        cmd='''adb shell "dbus-send --system --print-reply --dest=com.saic.ivi.ADAS.Srv /com/saic/ivi/ADAS/Srv/Service com.saic.ivi.ADAS.Srv.Service.SetValue string:'{\\"type\\":\\"SyncLamp\\",\\"value\\":\\"1\\"}'"'''
        os.system(cmd)

    def onClicked_sync_lamp_off(self, event):
        cmd='''adb shell "dbus-send --system --print-reply --dest=com.saic.ivi.ADAS.Srv /com/saic/ivi/ADAS/Srv/Service com.saic.ivi.ADAS.Srv.Service.SetValue string:'{\\"type\\":\\"SyncLamp\\",\\"value\\":\\"0\\"}'"'''
        os.system(cmd)

    def OnCloseWindow(self, evt):
        ret = wx.MessageBox('Do you really want to leave?',  'Confirm', wx.OK|wx.CANCEL)
        if ret == wx.OK:
            # do something here...
            server.kill()
            self.Destroy()
            evt.Skip()
        
class MyApp(wx.App):
    def OnInit(self):
        frame = MyFrame( None, -1, '360-debug.py' )
        frame.Show(True)
        return True

import threading
class myThread(threading.Thread):
    def __init__(self, threadname=''):
        threading.Thread.__init__(self, name=threadname)

    def run(self):
        while (True):
            try:
                print server.recv()
            except:
                pass

os.system('adb shell "echo > /tmp/xxx"')
server = subprocessServer.subprocessServer(['adb', 'shell', 'tail -f /tmp/xxx | carservice'])

recvThread = myThread('recv')
recvThread.setDaemon(True)
recvThread.start()

app = MyApp(0)
app.MainLoop()  
