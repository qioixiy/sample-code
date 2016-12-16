#!/bin/env python
#coding: utf-8

# https://www.oschina.net/code/snippet_177666_17218

import requests
from requests.auth import AuthBase

import hashlib
from urllib import urlencode

class oschinaAuth(AuthBase):
    """Attaches HTTP Pizza Authentication to the given Request object."""
    def __init__(self, email, pwd, save_login = 1):
        # setup any auth-related data here
        self.email = email

        #sha1 pwd
        self.pwd = hashlib.sha1( pwd ).hexdigest()
        self.save_login = save_login

    def build_myself( self, r ):
        #chg method

        r.method = "POST"
        data = {'email': self.email,
                'pwd': self.pwd,
                'save_login':self.save_login }

        #fix path
        r.url += "?" + urlencode(data)

    def handle_200(self, r):
        pass

    def __call__(self, r):
        # modify and return the request
        self.build_myself( r )
        return r


agent="Mozilla/5.0 (X11; U; Linux i686 (x86_64); zh-CN; rv:1.9.1.2) Gecko/20090729 Firefox/3.5.2"

s = requests.Session()
s.headers.update({'User-Agent': agent})
s.headers.update({'Referer': "https://www.oschina.net/home/login?goto_page=http%3A%2F%2Fwww.oschina.net%2F"})

r = s.get('https://www.oschina.net/action/user/hash_login',
          auth=oschinaAuth('user@gmail.com','passwd'))
print r.cookies.get('oscid', False)
