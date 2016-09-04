#!/usr/bin/env python

# http://www.pythontab.com/html/2014/pythonhexinbiancheng_0530/794.html
from subprocess import Popen, PIPE
import fcntl, os
import time

class subprocessServer(object):
  def __init__(self, args, server_env = None):
    if server_env:
      self.process = Popen(args, stdin=PIPE, stdout=PIPE, stderr=PIPE, env=server_env)
    else:
      self.process = Popen(args, stdin=PIPE, stdout=PIPE, stderr=PIPE)
    flags = fcntl.fcntl(self.process.stdout, fcntl.F_GETFL)
    fcntl.fcntl(self.process.stdout, fcntl.F_SETFL, flags | os.O_NONBLOCK)

  def kill(self):
    self.process.kill()
    
  def send(self, data, tail = '\n'):
    self.process.stdin.write(data + tail)
    self.process.stdin.flush()

  def recv(self, t=.1, e=1, tr=5, stderr=0):
    time.sleep(t)
    if tr < 1:
        tr = 1 
    x = time.time()+t
    r = ''
    pr = self.process.stdout
    if stderr:
      pr = self.process.stderr
    while time.time() < x or r:
      try:
        r = pr.read()
      except:
          raise Exception('read exception')
      if r is None:
        if e:
          raise Exception(message)
        else:
          break
      elif r:
        return r.rstrip()
      else:
        time.sleep(max((x-time.time())/tr, 0))

    return r.rstrip()

# test
if __name__ == "__main__":
  ServerArgs = ['/usr/bin/adb', 'shell']
  ServerArgs = ['/bin/sh']
  server = subprocessServer(ServerArgs) # 1
  my_env = os.environ
  my_env["LD_LIBRARY_PATH"] = "/lib"
  server = subprocessServer(ServerArgs, my_env) # 2

  test_data = 'ls -al', 'ls',
  for x in test_data:
    server.send(x)
    print x, server.recv()

