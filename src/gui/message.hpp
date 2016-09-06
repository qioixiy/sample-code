// 消息封装类

class Message
{
public:
    Message( UINT id_=0,WPARAM wparam_=0,LPARAM lparam_=0 )
        :id( id_ )
        ,wparam ( wparam_ )
        ,lparam ( lparam_ )
        ,result ( 0 )
        {}

    UINT      id;
    WPARAM    wparam;
    LPARAM    lparam;
    LRESULT   result;
};

//我是一个漂亮的观察者模式的消息监听者
class MessageListener
{
public:
    virtual LRESULT onMessage( Message* message ) = 0;
};

//监听者这样工作
MessageListener* listener;
window->addListener( listener );
