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
#ifndef RAUMKERNEL_UPNPMANAGER_H
#define RAUMKERNEL_UPNPMANAGER_H

#include <thread>
#include <raumkernel/manager/managerBase.h>

#include <OpenHome/Net/Cpp/OhNet.h>
#include <OpenHome/Net/Cpp/CpDevice.h>
#include <OpenHome/Net/Cpp/CpDeviceDv.h>
#include <OpenHome/Net/Cpp/CpDeviceUpnp.h>


namespace Raumkernel
{
    namespace Manager
    {

        /**
        * The Network adapter identifier
        *
        * This struct holds the network adapter name we want to use and if the system should untill itts online to start 
        * the upnp stack      
        */
        struct NetworkAdapterIdentifier
        {
            NetworkAdapterIdentifier(std::string _adapterIdentifier, std::int32_t _timeToWaitForAdapterMS = 0)
            {
                adapterIdentifier = _adapterIdentifier;
                timeToWaitForAdapterMS = _timeToWaitForAdapterMS;
            }

            std::string adapterIdentifier = "";
            std::int32_t timeToWaitForAdapterMS = 0;
        };

        /**
        * The UPNPManager
        *
        * This class handles the appearance and disappearance of UPNPDevices with the OpenHome OhNet UPNP Stack
        * It will relay this information to the 'DeviceManager' which will take care of screening and 
        * creating proper device classes for the upnpDevices
        */
        class UPNPManager : public ManagerBase
        {
            public:
                EXPORT UPNPManager();
                EXPORT virtual ~UPNPManager();
                /**
                * Not intended for external use
                * Initialization of the UPNPManager
                *
                * Will be called by the kernel init which will provide a network adapter name.
                * If the adapter name is empty the UPNPManager will get the appointed one in the settings
                */
                void init(std::string _networkAdapterName = "");
                /**
                * Not intended for external use
                * Starts discovering for upnp devices
                *
                * will be called by the kernel init
                */
                void discover();
                /**
                * Refresh the device list.
                *
                * This may be a useful way to quickly update the device list after a device has been removed
                * abruptly from the network (without announcing its removal).
                *
                * The 'deviceFound' callback may run any time after this is called to notify new devices.
                * Any removed devices will be notified by a burst of calls to the 'deviceLost' callback          
                */
                void refresh();

            protected:  
                OpenHome::Net::CpDeviceListCppUpnpAll* upupDeviceListAll;

                bool refreshDeviceListThreadStarted;
                std::thread refreshDeviceListThreadObject;
                std::atomic_bool stopThreads;                

                /**
                * Not intended for external use
                * Will be called when the discover finds a valid existing UPNP device  or when it announces itself in the network
                */
                void onDeviceFound(OpenHome::Net::CpDeviceCpp& _device);
                /**
                * Not intended for external use
                * Will be called when a valid existing UPNP device says byebye
                */
                void onDeviceLost(OpenHome::Net::CpDeviceCpp& _device);
                /**
                * Not intended for external use
                * ist a thread which will do the refresh of the device list in a periodical manner
                */
                void refreshDeviceListThread(std::atomic_bool &_stopThread, std::uint32_t _refreshTimeMS);
                /**
                * Not intended for external use
                * will catch logs from the upnp stack
                */
                void upnpStackLog(const char* _log);
                void addLogLevels();

        };
    }
}


#endif