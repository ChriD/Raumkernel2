//
// The MIT License (MIT)
//
// Copyright (c) 2015 by ChriD
//
// Permission is hereby granted, free of charge,  to any person obtaining a copy of
// this software and  associated documentation  files  (the "Software"), to deal in
// the  Software  without  restriction,  including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software,  and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this  permission notice  shall be included in all
// copies or substantial portions of the Software.
//
// THE  SOFTWARE  IS  PROVIDED  "AS IS",  WITHOUT  WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE  AND NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE  LIABLE FOR ANY CLAIM,  DAMAGES OR OTHER LIABILITY, WHETHER
// IN  AN  ACTION  OF  CONTRACT,  TORT  OR  OTHERWISE,  ARISING  FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#pragma once
#ifndef RAUMKERNEL_DEVICESMANAGER_H
#define RAUMKERNEL_DEVICESMANAGER_H

#include <map>
#include <unordered_map>
#include <raumkernel/manager/managerBase.h>
#include <raumkernel/device/deviceMediaRenderer.h>
#include <raumkernel/device/deviceCreator.h>

#include <OpenHome/Net/Cpp/OhNet.h>
#include <OpenHome/Net/Cpp/CpDevice.h>
#include <OpenHome/Private/Debug.h>


namespace Raumkernel
{
    namespace Manager
    {
        /**
        * The DeviceManager
        *
        * This class handles all the devices found on the network stack and creats/holds the appropriate wrapper classes like Renderer / MediaServer
        */
        class DeviceManager : public ManagerBase
        {
            public:
                EXPORT DeviceManager();
                EXPORT virtual ~DeviceManager();   

                /**
                * Not intended for external use
                * Adds a ohNet UPNP Device and the appropriate wrapper class
                */
                void addDevice(OpenHome::Net::CpDeviceCpp& _device);
                /**
                * Not intended for external use
                * Removes a ohNet UPNP Device and the appropriate wrapper class
                */
                void removeDevice(OpenHome::Net::CpDeviceCpp& _device);

                /**               
                * locks the manager so he is not able to add or delete devices
                * device lists should always be locked when updateing the list or when performing an action on any of those devices
                * so the pointer does go out of scope
                * do not forget to unlock those lists again
                */
                EXPORT void lock();
                /**             
                * unlocks the internal device lists
                * device lists should always be locked when updateing the list or when performing an action on any of those devices
                * do not forget to unlock those lists again
                */
                EXPORT void unlock();
                /**
                * Returns a pointer to a media renderer device
                * Returns nullptr if no device was found!
                * do not forget to lock / unock the internal list when using the media renderer object
                */
                EXPORT Devices::MediaRenderer* getMediaRenderer(std::string _udn);
                /**
                * Returns a pointer to a media server device
                * Returns nullptr if no devive was found!
                * do not forget to lock / unock the internal list when using the media server object
                */
                EXPORT  Devices::MediaServer* getMediaServer(std::string _udn);
                /**
                * Returns a pointer to  theraumfeld media server device
                * Returns nullptr if media server was not found!
                * do not forget to lock / unock the internal list when using the media server object
                */
                EXPORT Devices::MediaServer_Raumfeld* getRaumfeldMediaServer();
                /**
                * Returns a string with the ip to the raumfeld host
                * will be empty if host was not found
                */
                EXPORT std::string getRaumfeldHostIP();
                /**
                * Returns a copy of the media renderer map
                */
                EXPORT std::unordered_map<std::string, Devices::MediaRenderer*> getMediaRenderers();
                /**
                * Returns a copy of the media renderer map
                */
                EXPORT std::unordered_map<std::string, Devices::MediaServer*> getMediaServers();

                /**
                * this signal will be fired if a media renderer was added to the internal list.        
                */
                sigs::signal<void(Devices::MediaRenderer*)> sigMediaRendererAdded;
                /**
                * this signal will be fired if a media renderer was removed from the internal list.        
                */
                sigs::signal<void(Devices::MediaRenderer*)> sigMediaRendererRemoved;
                /**
                * this signal will be fired if a media server was added to the internal list.              
                */
                sigs::signal<void(Devices::MediaServer*)> sigMediaServerAdded;
                /**
                * this signal will be fired if a media server was removed from the internal list.             
                */
                sigs::signal<void(Devices::MediaServer*)> sigMediaServerRemoved;              
                /**
                * this signal will be fired if a usable device (MediaServer, MediaRenderer, ...) was added to the internal list.            
                */
                sigs::signal<void()> sigDeviceListChanged;

            protected:
              
                // this map holds references to all the UPNP devices found by the UPNP control point, no matter if they ar usable by the kenrel or not
                std::unordered_map<std::string, OpenHome::Net::CpDeviceCpp*> upnpDeviceMap;

                // this map holds all the media renderer devices found, no matter if they are virtual ones or not
                std::unordered_map<std::string, Devices::MediaRenderer*> mediaRendererMap;

                // this map holds all the media server devices found, no matter if they are raumfeld media servers or not
                // but in fact only the raumfeld media server will be used
                std::unordered_map<std::string, Devices::MediaServer*> mediaServerMap;                

                // a mutex that will secure our device lists
                std::mutex mutexDeviceLists;

                // UDN of the raumfeld media server 
                // will be empty if no media server is offline
                std::string raumfeldMediaServerUDN;

                // IP of the raumfeld host
                // will be empty if system is offline
                std::string raumfeldHostIP;

               


        };
    }
}


#endif