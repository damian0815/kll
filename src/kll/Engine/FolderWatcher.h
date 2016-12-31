//
// Created by Damian Stewart on 31/12/16.
//

#ifndef OFAPP_FOLDERWATCHER_H
#define OFAPP_FOLDERWATCHER_H

#include <vector>
#include <string>
#include <events/ofEvent.h>
#include "FileWatcher.h"

using std::string;
using std::vector;


namespace kll
{

    class FolderWatcher
    {
    public:

        ~FolderWatcher();

        void Setup(string fullPath);
        void Update();

        ofEvent<string>& GetChangedEvent() { return mChangedEvent; }

    private:
        void CreateAndDestroyFileWatchersAsNecessary(const vector<string> &folderContents);
        vector<string> GetFolderContents();

        void OnFileChanged(const void *sender, string &fullPath);
        bool HasFileWatcher(const string &path);
        void CreateFileWatcher(const string &fullPath);

        void RaiseChanged() { mChangedEvent.notify(this, mFolderPath); }

        string mFolderPath;
        vector<string> mFolderContents;
        vector<FileWatcher*> mFileWatchers;

        ofEvent<string> mChangedEvent;

        bool mShouldNotifyChanged = false;


        void UpdateFileWatchers();
    };

}

#endif //OFAPP_FOLDERWATCHER_H
