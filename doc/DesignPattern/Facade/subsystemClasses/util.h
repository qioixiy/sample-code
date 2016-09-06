#include "base.h"

/*----------------------------------------------------------------*/
/* class SmsUtil                                                  */
/*----------------------------------------------------------------*/
class SmsUtil: public Base
{
#define SMS_CONTENT "I am sms content"
public:
    SmsUtil(){}
    bool checkReady()
    {
        cout<<"SmsUtil checkReady"<<endl;
        return true;
    }
    bool getSmsContent(int msg_id,char* pContent)
    {
        cout<<"SmsUtil getSmsContent"<<endl;
        strcpy(pContent,SMS_CONTENT);
        return true;
    }
};

/*----------------------------------------------------------------*/
/* class MmsUtil                                                  */
/*----------------------------------------------------------------*/
class MmsUtil: public Base
{
#define MMS_CONTENT "I am mms content"
public:
    MmsUtil(){}
    bool checkReady()
    {
        cout<<"MmsUtil checkReady"<<endl;
        return true;
    }
    bool getMmsContent(int msg_id,char* pContent)
    {
        cout<<"MmsUtil getMmsContent"<<endl;
        strcpy(pContent,MMS_CONTENT);
        return true;
    }
};

/*----------------------------------------------------------------*/
/* class PushUtil                                                 */
/*----------------------------------------------------------------*/
class PushUtil: public Base
{
#define PUSH_CONTENT "I am push content"
public:
    PushUtil(){}
    bool checkReady()
    {
        cout<<"PushUtil checkReady"<<endl;
        return true;
    }
    bool getPushContent(int msg_id,char* pContent)
    {
        cout<<"PushUtil getPushContent"<<endl;
        strcpy(pContent,PUSH_CONTENT);
        return true;
    }
};
