
/*
 *	This file was automatically generated by dbusxx-xml2cpp; DO NOT EDIT!
 */

#ifndef __dbusxx__amarok_glue_h__PROXY_MARSHAL_H
#define __dbusxx__amarok_glue_h__PROXY_MARSHAL_H

#include <dbus-c++/dbus.h>

namespace org {
namespace freedesktop {

class MediaPlayer_proxy
 : public ::DBus::InterfaceProxy
{
public:

    MediaPlayer_proxy()
    : ::DBus::InterfaceProxy("org.freedesktop.MediaPlayer")
    {
        connect_signal(MediaPlayer_proxy, TrackChange, _TrackChange_stub);
        connect_signal(MediaPlayer_proxy, StatusChange, _StatusChange_stub);
        connect_signal(MediaPlayer_proxy, CapsChange, _CapsChange_stub);
    }

public:

    /* properties exported by this interface */
public:

    /* methods exported by this interface,
     * this functions will invoke the corresponding methods on the remote objects
     */
    void Pause()
    {
        ::DBus::CallMessage call;
        call.member("Pause");
        ::DBus::Message ret = invoke_method(call);
    }

    void Stop()
    {
        ::DBus::CallMessage call;
        call.member("Stop");
        ::DBus::Message ret = invoke_method(call);
    }

    void StopAfterCurrent()
    {
        ::DBus::CallMessage call;
        call.member("StopAfterCurrent");
        ::DBus::Message ret = invoke_method(call);
    }

    void Play()
    {
        ::DBus::CallMessage call;
        call.member("Play");
        ::DBus::Message ret = invoke_method(call);
    }

    void PlayPause()
    {
        ::DBus::CallMessage call;
        call.member("PlayPause");
        ::DBus::Message ret = invoke_method(call);
    }

    void Prev()
    {
        ::DBus::CallMessage call;
        call.member("Prev");
        ::DBus::Message ret = invoke_method(call);
    }

    void Next()
    {
        ::DBus::CallMessage call;
        call.member("Next");
        ::DBus::Message ret = invoke_method(call);
    }

    void Repeat(const bool& argin0)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << argin0;
        call.member("Repeat");
        ::DBus::Message ret = invoke_method(call);
    }

    ::DBus::Struct< int32_t, int32_t, int32_t, int32_t > GetStatus()
    {
        ::DBus::CallMessage call;
        call.member("GetStatus");
        ::DBus::Message ret = invoke_method(call);
        ::DBus::MessageIter ri = ret.reader();
	::DBus::Struct< int32_t, int32_t, int32_t, int32_t > argout;

        ri >> argout;
        return argout;
    }

    void VolumeSet(const int32_t& argin0)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << argin0;
        call.member("VolumeSet");
        ::DBus::Message ret = invoke_method(call);
    }

    int32_t VolumeGet()
    {
        ::DBus::CallMessage call;
        call.member("VolumeGet");
        ::DBus::Message ret = invoke_method(call);
        ::DBus::MessageIter ri = ret.reader();

        int32_t argout;
        ri >> argout;
        return argout;
    }

    void PositionSet(const int32_t& argin0)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << argin0;
        call.member("PositionSet");
        ::DBus::Message ret = invoke_method(call);
    }

    int32_t PositionGet()
    {
        ::DBus::CallMessage call;
        call.member("PositionGet");
        ::DBus::Message ret = invoke_method(call);
        ::DBus::MessageIter ri = ret.reader();

        int32_t argout;
        ri >> argout;
        return argout;
    }

    std::map< std::string, ::DBus::Variant > GetMetadata()
    {
        ::DBus::CallMessage call;
        call.member("GetMetadata");
        ::DBus::Message ret = invoke_method(call);
        ::DBus::MessageIter ri = ret.reader();

        std::map< std::string, ::DBus::Variant > argout;
        ri >> argout;
        return argout;
    }

    int32_t GetCaps()
    {
        ::DBus::CallMessage call;
        call.member("GetCaps");
        ::DBus::Message ret = invoke_method(call);
        ::DBus::MessageIter ri = ret.reader();

        int32_t argout;
        ri >> argout;
        return argout;
    }

    void VolumeUp(const int32_t& argin0)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << argin0;
        call.member("VolumeUp");
        ::DBus::Message ret = invoke_method(call);
    }

    void VolumeDown(const int32_t& argin0)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << argin0;
        call.member("VolumeDown");
        ::DBus::Message ret = invoke_method(call);
    }

    void Mute()
    {
        ::DBus::CallMessage call;
        call.member("Mute");
        ::DBus::Message ret = invoke_method(call);
    }

    void ShowOSD()
    {
        ::DBus::CallMessage call;
        call.member("ShowOSD");
        ::DBus::Message ret = invoke_method(call);
    }

    void LoadThemeFile(const std::string& argin0)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << argin0;
        call.member("LoadThemeFile");
        ::DBus::Message ret = invoke_method(call);
    }

    void Forward(const int32_t& argin0)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << argin0;
        call.member("Forward");
        ::DBus::Message ret = invoke_method(call);
    }

    void Backward(const int32_t& argin0)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << argin0;
        call.member("Backward");
        ::DBus::Message ret = invoke_method(call);
    }


public:

    /* signal handlers for this interface
     */
    virtual void TrackChange(const std::map< std::string, ::DBus::Variant >& argin0) = 0;
    virtual void StatusChange(const ::DBus::Struct< int32_t, int32_t, int32_t, int32_t >& argin0) = 0;
    virtual void CapsChange(const int32_t& argin0) = 0;

private:

    /* unmarshalers (to unpack the DBus message before calling the actual signal handler)
     */
    void _TrackChange_stub(const ::DBus::SignalMessage &sig)
    {
        ::DBus::MessageIter ri = sig.reader();

        std::map< std::string, ::DBus::Variant > arg0; ri >> arg0;
        TrackChange(arg0);
    }
    void _StatusChange_stub(const ::DBus::SignalMessage &sig)
    {
        ::DBus::MessageIter ri = sig.reader();

        ::DBus::Struct< int32_t, int32_t, int32_t, int32_t > arg0; ri >> arg0;
        StatusChange(arg0);
    }
    void _CapsChange_stub(const ::DBus::SignalMessage &sig)
    {
        ::DBus::MessageIter ri = sig.reader();

        int32_t arg0; ri >> arg0;
        CapsChange(arg0);
    }
};

} } 
#endif//__dbusxx__amarok_glue_h__PROXY_MARSHAL_H
