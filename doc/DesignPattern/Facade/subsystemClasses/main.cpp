#include <string.h>
#include <iostream>
using namespace std;

#include "facade.h"

int main()
{
  MsgFacade* msg = MsgFacade::getInstance();
  msg->checkReady(MSG_ALL);

  cout<<endl;
  char content[100] = {0};

  msg->getMsgContent(SMS,0,content);
  cout<<content<<endl;

  msg->getMsgContent(MMS,0,content);
  cout<<content<<endl;

  msg->getMsgContent(PUSH,0,content);
  cout<<content<<endl;

  return 0;
}
