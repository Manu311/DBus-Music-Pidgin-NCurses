
/*
 *	This file was automatically generated by dbusxx-xml2cpp; DO NOT EDIT!
 */

#ifndef __dbusxx__RBS_glue_h__PROXY_MARSHAL_H
#define __dbusxx__RBS_glue_h__PROXY_MARSHAL_H

#include <dbus-c++/dbus.h>

namespace org {
namespace gnome {
namespace Rhythmbox {

class Shell_proxy
 : public ::DBus::InterfaceProxy
{
public:

    Shell_proxy()
    : ::DBus::InterfaceProxy("org.gnome.Rhythmbox.Shell")
    {
        connect_signal(Shell_proxy, visibilityChanged, _visibilityChanged_stub);
    }

public:

    /* properties exported by this interface */
public:

    /* methods exported by this interface,
     * this functions will invoke the corresponding methods on the remote objects
     */
    void notify(const bool& userRequested)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << userRequested;
        call.member("notify");
        ::DBus::Message ret = invoke_method(call);
    }

    void clearQueue()
    {
        ::DBus::CallMessage call;
        call.member("clearQueue");
        ::DBus::Message ret = invoke_method(call);
    }

    void removeFromQueue(const std::string& uri)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << uri;
        call.member("removeFromQueue");
        ::DBus::Message ret = invoke_method(call);
    }

    void quit()
    {
        ::DBus::CallMessage call;
        call.member("quit");
        ::DBus::Message ret = invoke_method(call);
    }

    void addToQueue(const std::string& uri)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << uri;
        call.member("addToQueue");
        ::DBus::Message ret = invoke_method(call);
    }

    void setSongProperty(const std::string& uri, const std::string& propname, const ::DBus::Variant& value)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << uri;
        wi << propname;
        wi << value;
        call.member("setSongProperty");
        ::DBus::Message ret = invoke_method(call);
    }

    std::map< std::string, ::DBus::Variant > getSongProperties(const std::string& uri)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << uri;
        call.member("getSongProperties");
        ::DBus::Message ret = invoke_method(call);
        ::DBus::MessageIter ri = ret.reader();

        std::map< std::string, ::DBus::Variant > argout;
        ri >> argout;
        return argout;
    }

    void present(const uint32_t& arg0)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << arg0;
        call.member("present");
        ::DBus::Message ret = invoke_method(call);
    }

    ::DBus::Path getPlaylistManager()
    {
        ::DBus::CallMessage call;
        call.member("getPlaylistManager");
        ::DBus::Message ret = invoke_method(call);
        ::DBus::MessageIter ri = ret.reader();

        ::DBus::Path argout;
        ri >> argout;
        return argout;
    }

    ::DBus::Path getPlayer()
    {
        ::DBus::CallMessage call;
        call.member("getPlayer");
        ::DBus::Message ret = invoke_method(call);
        ::DBus::MessageIter ri = ret.reader();

        ::DBus::Path argout;
        ri >> argout;
        return argout;
    }

    void loadURI(const std::string& arg0, const bool& arg1)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << arg0;
        wi << arg1;
        call.member("loadURI");
        ::DBus::Message ret = invoke_method(call);
    }


public:

    /* signal handlers for this interface
     */
    virtual void visibilityChanged(const bool& argin0) = 0;

private:

    /* unmarshalers (to unpack the DBus message before calling the actual signal handler)
     */
    void _visibilityChanged_stub(const ::DBus::SignalMessage &sig)
    {
        ::DBus::MessageIter ri = sig.reader();

        bool arg0; ri >> arg0;
        visibilityChanged(arg0);
    }
};

} } } 
#endif//__dbusxx__RBS_glue_h__PROXY_MARSHAL_H