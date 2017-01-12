//
// Created by Damian Stewart on 31/12/16.
//

#include <dirent.h>
#include <fmt/format.h>
#include "FolderWatcher.h"

kll::FolderWatcher::~FolderWatcher()
{
    for (auto fw: mFileWatchers) {
        delete fw;
    }

    mFileWatchers.clear();
}

void kll::FolderWatcher::Setup(string fullPath)
{
    mFolderPath = fullPath;

    auto folderContents = GetFolderContents();
    mFolderContents = folderContents;
    CreateAndDestroyFileWatchersAsNecessary(folderContents);
}

void kll::FolderWatcher::Update(float dt)
{
    const float UPDATE_INTERVAL = 0.5f;
    mUpdateTimer -= dt;
    if (mUpdateTimer < 0) {
        UpdateFileWatchers();

        auto folderContents = GetFolderContents();
        CreateAndDestroyFileWatchersAsNecessary(folderContents);

        if (folderContents != mFolderContents) {
            mShouldNotifyChanged = true;
            mFolderContents = folderContents;
        }

        if (mShouldNotifyChanged) {
            RaiseChanged();
            mShouldNotifyChanged = false;
        }

        mUpdateTimer = UPDATE_INTERVAL;
    }
}

void kll::FolderWatcher::CreateAndDestroyFileWatchersAsNecessary(const vector<string> &folderContents)
{
    auto newFileWatchersEnd = std::remove_if(mFileWatchers.begin(), mFileWatchers.end(), [&folderContents](auto* fw) {
        return std::find(folderContents.begin(), folderContents.end(), fw->GetFullPath()) == folderContents.end();
    });
    for (auto it = newFileWatchersEnd; it != mFileWatchers.end(); ++it) {
        auto fw = *it;
        fmt::print("deleting FileWatcher for {0}\n", fw->GetFullPath());
        fw->GetChangedEvent().remove(this, &FolderWatcher::OnFileChanged, 0);
        delete *it;
    }
    mFileWatchers.erase(newFileWatchersEnd, mFileWatchers.end());

    for (const auto& path: folderContents) {
        if (!HasFileWatcher(path)) {
            CreateFileWatcher(path);
        }
    }
}

void kll::FolderWatcher::CreateFileWatcher(const string &fullPath)
{
    fmt::print("adding FileWatcher for {0}\n", fullPath);
    auto fw = new FileWatcher();
    fw->Setup(fullPath);
    fw->GetChangedEvent().add(this, &FolderWatcher::OnFileChanged, 0);
    mFileWatchers.push_back(fw);
}

vector<string> kll::FolderWatcher::GetFolderContents()
{
    DIR* dir;
    dir = opendir(mFolderPath.c_str());
    if (dir == nullptr) {
        fmt::print_colored(fmt::Color::RED, "Unable to open dir {0}: {1}\n", mFolderPath, strerror(errno));
        return {};
    }

    vector<string> result;
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_REG) {
            auto path = mFolderPath + "/" + entry->d_name;
            result.push_back(path);
        }
    }
    closedir(dir);

    return result;
}

void kll::FolderWatcher::OnFileChanged(const void *sender, string &fullPath)
{
    mShouldNotifyChanged = true;
}

bool kll::FolderWatcher::HasFileWatcher(const string &path)
{
    return std::any_of(mFileWatchers.begin(), mFileWatchers.end(), [&path](auto* fw) { return fw->GetFullPath() == path;});
}

void kll::FolderWatcher::UpdateFileWatchers()
{
    for (auto fw: mFileWatchers) {
        fw->Update();
    }
}


