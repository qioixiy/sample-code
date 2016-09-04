/*!
@file
@author		Albert Semenov
@date		11/2007
@module
*/
/*
This file is part of MyGUI.

MyGUI is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MyGUI is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with MyGUI.  If not, see <http://www.gnu.org/licenses/>.
*/

namespace delegates
{

#define MYGUI_COMBINE(a, b)						MYGUI_COMBINE1(a, b)
#define MYGUI_COMBINE1(a, b)					a##b

#define MYGUI_I_DELEGATE						MYGUI_COMBINE(IDelegate, DELEGATE_SUFFIX)

#define MYGUI_C_STATIC_DELEGATE					MYGUI_COMBINE(CStaticDelegate, DELEGATE_SUFFIX)
#define MYGUI_C_METHOD_DELEGATE					MYGUI_COMBINE(CMethodDelegate, DELEGATE_SUFFIX)

#define MYGUI_C_DELEGATE						MYGUI_COMBINE(CDelegate, DELEGATE_SUFFIX)
#define MYGUI_C_MULTI_DELEGATE					MYGUI_COMBINE(CMultiDelegate, DELEGATE_SUFFIX)


    // base class of all delegates
    DELEGATE_TEMPLATE   DELEGATE_TEMPLATE_PARAMS
    class MYGUI_I_DELEGATE
    {
    public:
        virtual ~MYGUI_I_DELEGATE() { }
        virtual bool isType( const std::type_info& _type) = 0;
        virtual void invoke( DELEGATE_PARAMS ) = 0;
        virtual bool compare(  MYGUI_I_DELEGATE DELEGATE_TEMPLATE_ARGS  * _delegate) const = 0;
        virtual bool compare(IDelegateUnlink * _unlink) const { return false; }
    };


    // delegate to a static function
    DELEGATE_TEMPLATE   DELEGATE_TEMPLATE_PARAMS
    class MYGUI_C_STATIC_DELEGATE : public  MYGUI_I_DELEGATE DELEGATE_TEMPLATE_ARGS
    {
    public:
        typedef void (*Func)( DELEGATE_PARAMS );

        MYGUI_C_STATIC_DELEGATE (Func _func) : mFunc(_func) { }

        virtual bool isType( const std::type_info& _type) { return typeid( MYGUI_C_STATIC_DELEGATE DELEGATE_TEMPLATE_ARGS ) == _type; }

        virtual void invoke( DELEGATE_PARAMS )
        {
            mFunc( DELEGATE_ARGS );
        }

        virtual bool compare(  MYGUI_I_DELEGATE DELEGATE_TEMPLATE_ARGS  * _delegate) const
        {
            if (0 == _delegate || !_delegate->isType(typeid(MYGUI_C_STATIC_DELEGATE DELEGATE_TEMPLATE_ARGS)) ) return false;
            MYGUI_C_STATIC_DELEGATE DELEGATE_TEMPLATE_ARGS * cast = static_cast<MYGUI_C_STATIC_DELEGATE DELEGATE_TEMPLATE_ARGS *>(_delegate);
            return cast->mFunc == mFunc;
        }
        virtual bool compare(IDelegateUnlink * _unlink) const { return false; }

    private:
        Func mFunc;
    };


    // delegate for the method of the class
    template DELEGATE_T_TEMPLATE_PARAMS
    class MYGUI_C_METHOD_DELEGATE : public  MYGUI_I_DELEGATE DELEGATE_TEMPLATE_ARGS
    {
    public:
        typedef void (T::*Method)( DELEGATE_PARAMS );

        MYGUI_C_METHOD_DELEGATE(IDelegateUnlink * _unlink, T * _object, Method _method) : mUnlink(_unlink), mObject(_object), mMethod(_method) { }

        virtual bool isType( const std::type_info& _type) { return typeid( MYGUI_C_METHOD_DELEGATE DELEGATE_T_TEMPLATE_ARGS ) == _type; }

        virtual void invoke( DELEGATE_PARAMS )
        {
            (mObject->*mMethod)( DELEGATE_ARGS );
        }

        virtual bool compare(  MYGUI_I_DELEGATE DELEGATE_TEMPLATE_ARGS  * _delegate) const
        {
            if (0 == _delegate || !_delegate->isType(typeid(MYGUI_C_METHOD_DELEGATE DELEGATE_T_TEMPLATE_ARGS)) ) return false;
            MYGUI_C_METHOD_DELEGATE DELEGATE_T_TEMPLATE_ARGS  * cast = static_cast<  MYGUI_C_METHOD_DELEGATE DELEGATE_T_TEMPLATE_ARGS  * >(_delegate);
            return cast->mObject == mObject && cast->mMethod == mMethod;
        }

        virtual bool compare(IDelegateUnlink * _unlink) const
        {
            return mUnlink == _unlink;
        }

    private:
        IDelegateUnlink *mUnlink;
        T * mObject;
        Method mMethod;
    };

} // namespace delegates

// template to create a delegate static function
// parameters: a pointer to a function
// example : newDelegate(funk_name);
// example : newDelegate(class_name::static_method_name);
DELEGATE_TEMPLATE   DELEGATE_TEMPLATE_PARAMS
inline  delegates::MYGUI_I_DELEGATE DELEGATE_TEMPLATE_ARGS  * newDelegate( void (*_func)( DELEGATE_PARAMS ) )
{
    return new delegates::MYGUI_C_STATIC_DELEGATE DELEGATE_TEMPLATE_ARGS  (_func);
}


// template to create a delegate class method
// options : pointer to the class object and a pointer to a class method
// example : newDelegate(&object_name, &class_name::method_name);
template DELEGATE_T_TEMPLATE_PARAMS
inline  delegates::MYGUI_I_DELEGATE DELEGATE_TEMPLATE_ARGS  * newDelegate( T * _object, void (T::*_method)( DELEGATE_PARAMS ) )
{
    return new delegates::MYGUI_C_METHOD_DELEGATE  DELEGATE_T_TEMPLATE_ARGS  (delegates::GetDelegateUnlink(_object), _object, _method);
}

namespace delegates
{
    // pattern of the delegate class
    DELEGATE_TEMPLATE   DELEGATE_TEMPLATE_PARAMS
    class MYGUI_C_DELEGATE
    {
    public:
        typedef  MYGUI_I_DELEGATE DELEGATE_TEMPLATE_ARGS  IDelegate;

        MYGUI_C_DELEGATE () : mDelegate(0) { }
        MYGUI_C_DELEGATE (const MYGUI_C_DELEGATE  DELEGATE_TEMPLATE_ARGS& _event)
        {
            // pick up his own
            mDelegate = _event.mDelegate;
            const_cast< MYGUI_C_DELEGATE  DELEGATE_TEMPLATE_ARGS& >(_event).mDelegate = 0;
        }
        ~MYGUI_C_DELEGATE () { clear(); }

        bool empty() const { return mDelegate == 0; }

        void clear()
        {
            if (mDelegate)
            {
                delete mDelegate;
                mDelegate = 0;
            }
        }

        MYGUI_C_DELEGATE  DELEGATE_TEMPLATE_ARGS & operator=(IDelegate* _delegate)
        {
            delete mDelegate;
            mDelegate = _delegate;
            return *this;
        }

        MYGUI_C_DELEGATE  DELEGATE_TEMPLATE_ARGS & operator=(const MYGUI_C_DELEGATE  DELEGATE_TEMPLATE_ARGS& _event)
        {
            // pick up his own
            delete mDelegate;
            mDelegate = _event.mDelegate;
            const_cast< MYGUI_C_DELEGATE  DELEGATE_TEMPLATE_ARGS& >(_event).mDelegate = 0;

            return *this;
        }

        void operator()( DELEGATE_PARAMS )
        {
            if (mDelegate == 0) return;
            mDelegate->invoke( DELEGATE_ARGS );
        }

    private:
        IDelegate * mDelegate;
    };


    // template class multi delegate
    DELEGATE_TEMPLATE   DELEGATE_TEMPLATE_PARAMS
    class MYGUI_C_MULTI_DELEGATE
    {
    public:
        typedef  MYGUI_I_DELEGATE DELEGATE_TEMPLATE_ARGS  IDelegate;
        typedef DELEGATE_TYPENAME std::list<IDelegate* /*, Allocator<IDelegate*>*/ > ListDelegate;
        typedef DELEGATE_TYPENAME ListDelegate::iterator ListDelegateIterator;
        typedef DELEGATE_TYPENAME ListDelegate::const_iterator ConstListDelegateIterator;

        MYGUI_C_MULTI_DELEGATE () { }
        ~MYGUI_C_MULTI_DELEGATE () { clear(); }

        bool empty() const
        {
            for (ConstListDelegateIterator iter = mListDelegates.begin(); iter!=mListDelegates.end(); ++iter)
            {
                if (*iter) return false;
            }
            return true;
        }

        void clear()
        {
            for (ListDelegateIterator iter=mListDelegates.begin(); iter!=mListDelegates.end(); ++iter)
            {
                if (*iter)
                {
                    delete (*iter);
                    (*iter) = 0;
                }
            }
        }

        void clear(IDelegateUnlink * _unlink)
        {
            for (ListDelegateIterator iter=mListDelegates.begin(); iter!=mListDelegates.end(); ++iter)
            {
                if ((*iter) && (*iter)->compare(_unlink))
                {
                    delete (*iter);
                    (*iter) = 0;
                }
            }
        }

        MYGUI_C_MULTI_DELEGATE  DELEGATE_TEMPLATE_ARGS & operator+=(IDelegate* _delegate)
        {
            for (ListDelegateIterator iter=mListDelegates.begin(); iter!=mListDelegates.end(); ++iter)
            {
                if ((*iter) && (*iter)->compare(_delegate))
                {
                    delete _delegate;
                    return *this;
                    //MYGUI_ASSERT(false, "dublicate delegate");
                }
            }
            mListDelegates.push_back(_delegate);
            return *this;
        }

        MYGUI_C_MULTI_DELEGATE  DELEGATE_TEMPLATE_ARGS & operator-=(IDelegate* _delegate)
        {
            for (ListDelegateIterator iter=mListDelegates.begin(); iter!=mListDelegates.end(); ++iter)
            {
                if ((*iter) && (*iter)->compare(_delegate))
                {
                    // verify the identity of the delegates
                    if ((*iter) != _delegate) delete (*iter);
                    (*iter) = 0;
                    break;
                }
            }
            delete _delegate;
            return *this;
        }

        void operator()( DELEGATE_PARAMS )
        {
            ListDelegateIterator iter = mListDelegates.begin();
            while (iter != mListDelegates.end())
            {
                if (0 == (*iter))
                {
                    iter = mListDelegates.erase(iter);
                }
                else
                {
                    (*iter)->invoke( DELEGATE_ARGS );
                    ++iter;
                }
            }
        }

    private:
        // constructor and operator =, without implementation, just for private
        MYGUI_C_MULTI_DELEGATE (const MYGUI_C_MULTI_DELEGATE  DELEGATE_TEMPLATE_ARGS & _event);
        MYGUI_C_MULTI_DELEGATE  DELEGATE_TEMPLATE_ARGS & operator=(const MYGUI_C_MULTI_DELEGATE  DELEGATE_TEMPLATE_ARGS & _event);


    private:
        ListDelegate mListDelegates;

    };


#undef MYGUI_COMBINE
#undef MYGUI_COMBINE1

#undef MYGUI_I_DELEGATE

#undef MYGUI_C_STATIC_DELEGATE
#undef MYGUI_C_METHOD_DELEGATE

#undef MYGUI_C_DELEGATE
#undef MYGUI_C_MULTI_DELEGATE

#undef DELEGATE_SUFFIX
#undef DELEGATE_TEMPLATE
#undef DELEGATE_TEMPLATE_PARAMS
#undef DELEGATE_TEMPLATE_ARGS
#undef DELEGATE_T_TEMPLATE_PARAMS
#undef DELEGATE_T_TEMPLATE_ARGS
#undef DELEGATE_PARAMS
#undef DELEGATE_ARGS
#undef DELEGATE_TYPENAME

} // namespace delegates
