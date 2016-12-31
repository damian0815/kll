//
// Created by Damian Stewart on 28/12/16.
//

#include "FileWatcher.h"
#include <fstream>
#include <strstream>
#include <fmt/format.h>
#include "../../3rdparty/picosha2.h"

void kll::FileWatcher::Setup(string fullPath)
{
    mFullPath = fullPath;
    mLastHash = GetHash(mFullPath);
    //fmt::print("hash {0}\n", mLastHash);
}


void kll::FileWatcher::Update()
{
    auto hash = GetHash(mFullPath);
    if (hash != mLastHash) {
        //fmt::print("hash changed from {0} to {1}\n", mLastHash, hash);
        mLastHash = hash;
        RaiseChanged();
    }
}

void kll::FileWatcher::RaiseChanged()
{
    mChangedEvent.notify(this, mFullPath);
}

string kll::FileWatcher::GetHash(const string &fullPath)
{
    picosha2::hash256_one_by_one hasher;

    std::ifstream stream(fullPath);
    std::string contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    hasher.process(contents.begin(), contents.end());
    hasher.finish();

    auto hash = get_hash_hex_string(hasher);
    return hash;
}

