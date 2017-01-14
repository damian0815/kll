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

void kll::FolderWatcher::Setup(string fullPath, bool recursive)
{
    mFolderPath = fullPath;
    mRecursive = recursive;

    auto folderContents = GetFolderContents(mFolderPath, mRecursive);
    mFolderContents = folderContents;
    CreateAndDestroyFileWatchersAsNecessary(folderContents);
}

void kll::FolderWatcher::Update(float dt)
{
    const float UPDATE_INTERVAL = 0.5f;
    mUpdateTimer -= dt;
    if (mUpdateTimer < 0) {
        UpdateFileWatchers();

        auto folderContents = GetFolderContents(mFolderPath, mRecursive);
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

vector<string> kll::FolderWatcher::GetFolderContents(const string &folderPath, bool recursive)
{
    DIR* dir;
    dir = opendir(folderPath.c_str());
    if (dir == nullptr) {
        fmt::print_colored(fmt::Color::RED, "Unable to open dir {0}: {1}\n", folderPath, strerror(errno));
        return {};
    }

    vector<string> result;
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        auto path = folderPath + "/" + entry->d_name;
        if (entry->d_type == DT_REG) {
            result.push_back(path);
        } else if (entry->d_type == DT_DIR && recursive) {
            if (string(entry->d_name) != "." && string(entry->d_name) != "..") {
                auto subdir = GetFolderContents(path, recursive);
                result.insert(result.end(), subdir.begin(), subdir.end());
            }
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




