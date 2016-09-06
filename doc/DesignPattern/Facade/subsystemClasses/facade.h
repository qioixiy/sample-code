#include "util.h"

/*----------------------------------------------------------------*/
/* class MsgFacade                                                */
/*----------------------------------------------------------------*/
enum MsgType
{
    SMS,
    MMS,
    PUSH,
    MSG_ALL
};

class MsgFacade: public Base
{
protected:
    MsgFacade()
    {
        m_sms = new SmsUtil();
        m_mms = new MmsUtil();
        m_push = new PushUtil();
    }
public:
    static MsgFacade* getInstance()
    {
        if (s_instance == NULL)
        {
            s_instance = new MsgFacade();
        }

        return s_instance;
    }
    static void closeInstance()
    {
        delete s_instance;
    }
public:
    bool checkReady(int type)
    {
        bool resutl = false;

        resutl = m_sms->checkReady();
        resutl &= m_mms->checkReady();
        resutl &= m_push->checkReady();

        return resutl;
    }
    bool getMsgContent(int type,int msg_id,char* pContent)
    {
        switch(type)
        {
        case SMS:
        {
            m_sms->getSmsContent(msg_id,pContent);
            break;
        }
        case MMS:
        {
            m_mms->getMmsContent(msg_id,pContent);
            break;
        }
        case PUSH:
        {
            m_push->getPushContent(msg_id,pContent);
            break;
        }
        default:
            break;
        }

        return true;
    }
private:
    SmsUtil* m_sms;
    MmsUtil* m_mms;
    PushUtil* m_push;

    static MsgFacade* s_instance;
};
MsgFacade* MsgFacade::s_instance = NULL;
