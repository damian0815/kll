//
// Created by Damian Stewart on 28/12/16.
//

#ifndef OFAPP_DIRECTORYWATCHER_H
#define OFAPP_DIRECTORYWATCHER_H

#include <string>
#include <events/ofEvent.h>

using std::string;

namespace kll
{
    class FileWatcher
    {
    public:
        void Setup(string fullPath);
        void Update();

        ofEvent<string>& GetChangedEvent() { return mChangedEvent; }

        const string &GetFullPath() { return mFullPath; };

    private:
        string mFullPath;
        string mLastHash;

        ofEvent<string> mChangedEvent;

        static string GetHash(const string &fullPath);

        void RaiseChanged();
    };
}


#endif //OFAPP_DIRECTORYWATCHER_H
