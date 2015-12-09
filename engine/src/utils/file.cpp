/*
    File handling.
    Copyright (C) 2015 Denis BOURGE

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/

#include "hx3d/utils/file.hpp"

#include <SDL2/SDL_system.h>
#include <sstream>
#include <fstream>

#include "hx3d/core/platforms.hpp"
#include "hx3d/utils/log.hpp"

namespace hx3d {

File::File():
  data(nullptr), size(0)
{}

File::~File() {
  if (data) {
    delete[] data;
  }
}

///////////////////////////////////

Ptr<File> File::loadAsciiFile(std::string path) {
  #if defined(__ANDROID__)
    return loadAsciiFileAndroid(path);
  #elif defined(__IOS__)
    return loadAsciiFileiOS("assets/" + path);
  #else
    return loadAsciiFileDesktop("assets/" + path);
  #endif
}

Ptr<File> File::loadBinaryFile(std::string path) {
  #if defined(__ANDROID__)
    return loadBinaryFileAndroid(path);
  #elif defined(__IOS__)
    return loadBinaryFileiOS("assets/" + path);
  #else
    return loadBinaryFileDesktop("assets/" + path);
  #endif
}

std::string File::toString() {
  return std::string(data, size);
}

// Desktop ///////////////////////////////////

Ptr<File> File::loadAsciiFileDesktop(std::string path) {
  std::ifstream file(path);
  if (file) {
    std::ostringstream oss("");
    oss << file.rdbuf();

    std::string content = oss.str();

    Ptr<File> fileptr = Make<File>();
    fileptr->size = content.size() + 1;
    fileptr->data = new char[fileptr->size];
    std::copy(content.begin(), content.end(), fileptr->data);
    fileptr->data[content.size()] = '\0';

    return fileptr;
  }

  Log.Error("Bad path: %s", path.c_str());

  return nullptr;
}

Ptr<File> File::loadBinaryFileDesktop(std::string path) {
  std::ifstream file(path, std::ios::binary);
  if (file) {
    Ptr<File> fileptr = Make<File>();
    unsigned int size = 0;

    file.seekg(0, std::ios::end);
    size = file.tellg();
    file.seekg(0, std::ios::beg);

    fileptr->size = size;
    fileptr->data = new char[fileptr->size];
    file.read(fileptr->data, fileptr->size);
    file.close();

    return fileptr;
  }

  Log.Error("Bad path: %s", path.c_str());

  return nullptr;
}

}

// iOS ///////////////////////////////////////

#ifdef __APPLE__

#include "TargetConditionals.h"
#ifdef TARGET_OS_IPHONE

  #include <CoreFoundation/CoreFoundation.h>

namespace hx3d {

  Ptr<File> File::loadAsciiFileiOS(std::string path) {
    return loadAsciiFileDesktop(path);
  }

  Ptr<File> File::loadBinaryFileiOS(std::string path) {
    return loadBinaryFileDesktop(path);
  }
}

#endif
#endif

// Android ///////////////////////////////////

#ifdef __ANDROID__

  #include <jni.h>
  #include <android/log.h>
  #include <android/asset_manager.h>
  #include <android/asset_manager_jni.h>

namespace hx3d {

  std::string File::readAsString(std::string path) {
    // Environnement et classe de l'activité

    JNIEnv* env = (JNIEnv*)SDL_AndroidGetJNIEnv();

    jobject sdlActivity = (jobject)SDL_AndroidGetActivity();
    jclass sdlActivityClass = env->GetObjectClass(sdlActivity);
    env->DeleteLocalRef(sdlActivity);


    // Méthode getContext() depuis de l'activité SDLActivity

    jmethodID getContext = env->GetStaticMethodID(sdlActivityClass, "getContext", "()Landroid/content/Context;");
    jobject context = env->CallStaticObjectMethod(sdlActivityClass, getContext);


    // Objet AssetManager de l'activité SDLActivity

    jmethodID getAssets = env->GetMethodID(env->GetObjectClass(context), "getAssets", "()Landroid/content/res/AssetManager;");
    jobject assetManager = env->CallObjectMethod(context, getAssets);
    AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);

    if (mgr == NULL)
      return "";


    // Lecture de la ressource

    AAsset* asset = AAssetManager_open(mgr, path.c_str(), AASSET_MODE_STREAMING);
    std::string fileContent;
    char buffer;


    // Si elle n'existe pas

    if(asset == NULL) {
      __android_log_print(ANDROID_LOG_WARN, "SDL", "File \"%s\" does not exists", path.c_str());
      return "";
    }

    else {
      // Lecture

      while (AAsset_read(asset, &buffer, 1) > 0){
        fileContent += buffer;
      }

      AAsset_close(asset);
    }

    return fileContent;
  }

  Ptr<File> File::loadBinaryFileAndroid(std::string path) {

    std::string content = File::readAsString(path);

    Ptr<File> file = Make<File>();
    file->size = content.size();
    file->data = new char[file->size];
    std::copy(content.begin(), content.end(), file->data);

    return file;
  }

  Ptr<File> File::loadAsciiFileAndroid(std::string path) {
    std::string content = File::readAsString(path);

    Ptr<File> file = Make<File>();
    file->size = content.size();
    file->data = new char[file->size];
    std::copy(content.begin(), content.end(), file->data);
    // file->data[file->size] = '\0';

    return file;
  }
}

#endif
