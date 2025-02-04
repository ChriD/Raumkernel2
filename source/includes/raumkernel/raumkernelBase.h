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
#ifndef RAUMKERNEL_RAUMKERNELBASE_H
#define RAUMKERNEL_RAUMKERNELBASE_H

#include <memory>
#include <cstring>

#include <raumkernel/os/os.h>
#include <raumkernel/tools/commonUtil.h>
#include <raumkernel/tools/xmlUtil.h>
#include <raumkernel/signals/signals.hpp>
#include <raumkernel/logger/logger.h>
#include <raumkernel/xml/pugixml/pugixml.hpp>


namespace Raumkernel
{

    class RaumkernelBase
    {
    public:
        EXPORT RaumkernelBase();
        EXPORT virtual ~RaumkernelBase();
        EXPORT void setLogObject(std::shared_ptr<Log::Log> _log);
        EXPORT std::shared_ptr<Log::Log> getLogObject();

    protected:
        // all modules and classes wich are attached to the raumkernel itself will have the ability to log into the same log file
        // therfore we define a shared pointer to a log which creating and distribution has to be handled by the main kernel class
        std::shared_ptr<Log::Log> logObject;

        // 
        EXPORT virtual void logDebug(const std::string &_log, const std::string &_location);
        EXPORT virtual void logWarning(const std::string &_log, const std::string &_location);
        EXPORT virtual void logInfo(const std::string &_log, const std::string &_location);
        EXPORT virtual void logError(const std::string &_log, const std::string &_location);
        EXPORT virtual void logCritical(const std::string &_log, const std::string &_location);

    };

}


#endif