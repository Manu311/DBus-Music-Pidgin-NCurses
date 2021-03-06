
/*
 *	This file was automatically generated by dbusxx-xml2cpp; DO NOT EDIT!
 */

#ifndef __dbusxx__exaile_glue_h__PROXY_MARSHAL_H
#define __dbusxx__exaile_glue_h__PROXY_MARSHAL_H

#include <dbus-c++/dbus.h>

namespace org {
namespace exaile {

class Exaile_proxy
 : public ::DBus::InterfaceProxy
{
public:

    Exaile_proxy()
    : ::DBus::InterfaceProxy("org.exaile.Exaile")
    {
        connect_signal(Exaile_proxy, TrackChanged, _TrackChanged_stub);
        connect_signal(Exaile_proxy, StateChanged, _StateChanged_stub);
    }

public:

    /* properties exported by this interface */
public:

    /* methods exported by this interface,
     * this functions will invoke the corresponding methods on the remote objects
     */
    void StopAfterCurrent()
    {
        ::DBus::CallMessage call;
        call.member("StopAfterCurrent");
        ::DBus::Message ret = invoke_method(call);
    }

    void SetTrackAttr(const std::string& attr, const ::DBus::Variant& value)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << attr;
        wi << value;
        call.member("SetTrackAttr");
        ::DBus::Message ret = invoke_method(call);
    }

    void SetRating(const int32_t& value)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << value;
        call.member("SetRating");
        ::DBus::Message ret = invoke_method(call);
    }

    void Next()
    {
        ::DBus::CallMessage call;
        call.member("Next");
        ::DBus::Message ret = invoke_method(call);
    }

    void GuiToggleVisible()
    {
        ::DBus::CallMessage call;
        call.member("GuiToggleVisible");
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

    void Play()
    {
        ::DBus::CallMessage call;
        call.member("Play");
        ::DBus::Message ret = invoke_method(call);
    }

    std::string GetVolume()
    {
        ::DBus::CallMessage call;
        call.member("GetVolume");
        ::DBus::Message ret = invoke_method(call);
        ::DBus::MessageIter ri = ret.reader();

        std::string argout;
        ri >> argout;
        return argout;
    }

    void GetCoverData()
    {
        ::DBus::CallMessage call;
        call.member("GetCoverData");
        ::DBus::Message ret = invoke_method(call);
    }

    void Stop()
    {
        ::DBus::CallMessage call;
        call.member("Stop");
        ::DBus::Message ret = invoke_method(call);
    }

    void Enqueue(const std::vector< std::string >& filenames)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << filenames;
        call.member("Enqueue");
        ::DBus::Message ret = invoke_method(call);
    }

    void TestService(const std::string& arg)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << arg;
        call.member("TestService");
        ::DBus::Message ret = invoke_method(call);
    }

    int32_t GetRating()
    {
        ::DBus::CallMessage call;
        call.member("GetRating");
        ::DBus::Message ret = invoke_method(call);
        ::DBus::MessageIter ri = ret.reader();

        int32_t argout;
        ri >> argout;
        return argout;
    }

    std::string GetState()
    {
        ::DBus::CallMessage call;
        call.member("GetState");
        ::DBus::Message ret = invoke_method(call);
        ::DBus::MessageIter ri = ret.reader();

        std::string argout;
        ri >> argout;
        return argout;
    }

    std::string CurrentPosition()
    {
        ::DBus::CallMessage call;
        call.member("CurrentPosition");
        ::DBus::Message ret = invoke_method(call);
        ::DBus::MessageIter ri = ret.reader();

        std::string argout;
        ri >> argout;
        return argout;
    }

    void ChangeVolume(const int32_t& value)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << value;
        call.member("ChangeVolume");
        ::DBus::Message ret = invoke_method(call);
    }

    void PlayFile(const std::string& filename)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << filename;
        call.member("PlayFile");
        ::DBus::Message ret = invoke_method(call);
    }

    std::string GetTrackAttr(const std::string& attr)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << attr;
        call.member("GetTrackAttr");
        ::DBus::Message ret = invoke_method(call);
        ::DBus::MessageIter ri = ret.reader();

        std::string argout;
        ri >> argout;
        return argout;
    }

    std::string Query()
    {
        ::DBus::CallMessage call;
        call.member("Query");
        ::DBus::Message ret = invoke_method(call);
        ::DBus::MessageIter ri = ret.reader();

        std::string argout;
        ri >> argout;
        return argout;
    }

    std::string GetVersion()
    {
        ::DBus::CallMessage call;
        call.member("GetVersion");
        ::DBus::Message ret = invoke_method(call);
        ::DBus::MessageIter ri = ret.reader();

        std::string argout;
        ri >> argout;
        return argout;
    }

    bool IsPlaying()
    {
        ::DBus::CallMessage call;
        call.member("IsPlaying");
        ::DBus::Message ret = invoke_method(call);
        ::DBus::MessageIter ri = ret.reader();

        bool argout;
        ri >> argout;
        return argout;
    }

    void Seek(const double& value)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << value;
        call.member("Seek");
        ::DBus::Message ret = invoke_method(call);
    }

    std::string CurrentProgress()
    {
        ::DBus::CallMessage call;
        call.member("CurrentProgress");
        ::DBus::Message ret = invoke_method(call);
        ::DBus::MessageIter ri = ret.reader();

        std::string argout;
        ri >> argout;
        return argout;
    }


public:

    /* signal handlers for this interface
     */
    virtual void TrackChanged() = 0;
    virtual void StateChanged() = 0;

private:

    /* unmarshalers (to unpack the DBus message before calling the actual signal handler)
     */
    void _TrackChanged_stub(const ::DBus::SignalMessage &sig)
    {
        TrackChanged();
    }
    void _StateChanged_stub(const ::DBus::SignalMessage &sig)
    {
        StateChanged();
    }
};

} } 
#endif//__dbusxx__exaile_glue_h__PROXY_MARSHAL_H
