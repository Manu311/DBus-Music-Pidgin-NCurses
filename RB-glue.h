
/*
 *	This file was automatically generated by dbusxx-xml2cpp; DO NOT EDIT!
 */

#ifndef __dbusxx__Translation_glue_h__PROXY_MARSHAL_H
#define __dbusxx__Translation_glue_h__PROXY_MARSHAL_H

#include <dbus-c++/dbus.h>

namespace org {
namespace gnome {
namespace Rhythmbox {

class Player_proxy
 : public ::DBus::InterfaceProxy
{
public:

    Player_proxy()
    : ::DBus::InterfaceProxy("org.gnome.Rhythmbox.Player")
    {
        connect_signal(Player_proxy, playingSongPropertyChanged, _playingSongPropertyChanged_stub);
        connect_signal(Player_proxy, elapsedChanged, _elapsedChanged_stub);
        connect_signal(Player_proxy, playingUriChanged, _playingUriChanged_stub);
        connect_signal(Player_proxy, playingChanged, _playingChanged_stub);
    }

public:

    /* properties exported by this interface */
public:

    /* methods exported by this interface,
     * this functions will invoke the corresponding methods on the remote objects
     */
    bool getMute()
    {
        ::DBus::CallMessage call;
        call.member("getMute");
        ::DBus::Message ret = invoke_method(call);
        ::DBus::MessageIter ri = ret.reader();

        bool argout;
        ri >> argout;
        return argout;
    }

    void setMute(const bool& mute)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << mute;
        call.member("setMute");
        ::DBus::Message ret = invoke_method(call);
    }

    void setVolumeRelative(const double& volume)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << volume;
        call.member("setVolumeRelative");
        ::DBus::Message ret = invoke_method(call);
    }

    void setVolume(const double& volume)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << volume;
        call.member("setVolume");
        ::DBus::Message ret = invoke_method(call);
    }

    double getVolume()
    {
        ::DBus::CallMessage call;
        call.member("getVolume");
        ::DBus::Message ret = invoke_method(call);
        ::DBus::MessageIter ri = ret.reader();

        double argout;
        ri >> argout;
        return argout;
    }

    void setElapsed(const uint32_t& elapsed)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << elapsed;
        call.member("setElapsed");
        ::DBus::Message ret = invoke_method(call);
    }

    uint32_t getElapsed()
    {
        ::DBus::CallMessage call;
        call.member("getElapsed");
        ::DBus::Message ret = invoke_method(call);
        ::DBus::MessageIter ri = ret.reader();

        uint32_t argout;
        ri >> argout;
        return argout;
    }

    std::string getPlayingUri()
    {
        ::DBus::CallMessage call;
        call.member("getPlayingUri");
        ::DBus::Message ret = invoke_method(call);
        ::DBus::MessageIter ri = ret.reader();

        std::string argout;
        ri >> argout;
        return argout;
    }

    bool getPlaying()
    {
        ::DBus::CallMessage call;
        call.member("getPlaying");
        ::DBus::Message ret = invoke_method(call);
        ::DBus::MessageIter ri = ret.reader();

        bool argout;
        ri >> argout;
        return argout;
    }

    void next()
    {
        ::DBus::CallMessage call;
        call.member("next");
        ::DBus::Message ret = invoke_method(call);
    }

    void previous()
    {
        ::DBus::CallMessage call;
        call.member("previous");
        ::DBus::Message ret = invoke_method(call);
    }

    void playPause(const bool& arg0)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << arg0;
        call.member("playPause");
        ::DBus::Message ret = invoke_method(call);
    }


public:

    /* signal handlers for this interface
     */
    virtual void playingSongPropertyChanged(const std::string& argin0, const std::string& argin1, const ::DBus::Variant& argin2, const ::DBus::Variant& argin3) = 0;
    virtual void elapsedChanged(const uint32_t& argin0) = 0;
    virtual void playingUriChanged(const std::string& argin0) = 0;
    virtual void playingChanged(const bool& argin0) = 0;

private:

    /* unmarshalers (to unpack the DBus message before calling the actual signal handler)
     */
    void _playingSongPropertyChanged_stub(const ::DBus::SignalMessage &sig)
    {
        ::DBus::MessageIter ri = sig.reader();

        std::string arg0; ri >> arg0;
        std::string arg1; ri >> arg1;
        ::DBus::Variant arg2; ri >> arg2;
        ::DBus::Variant arg3; ri >> arg3;
        playingSongPropertyChanged(arg0, arg1, arg2, arg3);
    }
    void _elapsedChanged_stub(const ::DBus::SignalMessage &sig)
    {
        ::DBus::MessageIter ri = sig.reader();

        uint32_t arg0; ri >> arg0;
        elapsedChanged(arg0);
    }
    void _playingUriChanged_stub(const ::DBus::SignalMessage &sig)
    {
        ::DBus::MessageIter ri = sig.reader();

        std::string arg0; ri >> arg0;
        playingUriChanged(arg0);
    }
    void _playingChanged_stub(const ::DBus::SignalMessage &sig)
    {
        ::DBus::MessageIter ri = sig.reader();

        bool arg0; ri >> arg0;
        playingChanged(arg0);
    }
};

} } } 
#endif//__dbusxx__Translation_glue_h__PROXY_MARSHAL_H