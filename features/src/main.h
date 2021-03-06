
/*
This file is part of OpenSceneGraph cross-platform guide:
  https://github.com/OGStudio/openscenegraph-cross-platform-guide

Copyright (C) 2017 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_GUIDE_MAIN_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_GUIDE_MAIN_H

#include "functions.h"

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

// FEATURE VBO/INCLUDE

// FEATURE RENDERING_DEFAULT/INCLUDE

// FEATURE PLUGINS_STATIC/IMPL

// This class prints OpenSceneGraph notifications to console.
class Logger : public osg::NotifyHandler
{
    public:
        Logger() { }
        virtual ~Logger() { }

        // Override NotifyHandler::notify() to receive OpenSceneGraph notifications.
        void notify(osg::NotifySeverity severity, const char *message)
        {
            std::string finalMessage =
                printfString(
                    "OSG/%s %s",
                    logLevelToString(severity).c_str(),
                    message);
            platformLog(finalMessage.c_str());
        }
};

// FEATURE VBO/DECL

class Application
{
    public:
        Application()
        {
            setupLogging();
            setupRendering();
        }
        ~Application()
        {
            tearDownLogging();
            tearDownRendering();
        }

        void loadScene(const std::string &fileName)
        {
            // Load scene.
            osg::Node *scene = osgDB::readNodeFile(fileName);
            if (!scene)
            {
                osg::notify(osg::FATAL) << "Could not load scene";
                return;
            }
            // FEATURE VBO/IMPL
            // Load shaders.
            osg::Program *prog = createShaderProgram(shaderVertex, shaderFragment);
            // Apply shaders.
            scene->getOrCreateStateSet()->setAttribute(prog);
            // Set scene.
            mViewer->setSceneData(scene);
        }
        // FEATURE INPUT_ANDROID/IMPL
        // FEATURE INPUT_EMSCRIPTEN/IMPL
        // FEATURE RENDERING_EMBEDDED/IMPL
        // FEATURE RENDERING_DEFAULT/IMPL
        // FEATURE RENDERING_DESKTOP/IMPL
        // FEATURE RENDERING_IOS/IMPL

    private:
        void setupLogging()
        {
            // Create custom logger.
            mLogger = new Logger;
            // Provide the logger to OpenSceneGraph.
            osg::setNotifyHandler(mLogger);
            // Only accept notifications of Info level or higher
            // like warnings and errors.
            osg::setNotifyLevel(osg::INFO);
        }
        void setupRendering()
        {
            // Create OpenSceneGraph viewer.
            mViewer = new osgViewer::Viewer;
            // FEATURE RENDERING_DEFAULT/CONSTRUCT
        }
        void tearDownLogging()
        {
            // Remove the logger from OpenSceneGraph.
            // This also destroys the logger: no need to deallocate it manually.
            osg::setNotifyHandler(0);
        }
        void tearDownRendering()
        {
            delete mViewer;
        }

    private:
        Logger *mLogger;
        osgViewer::Viewer *mViewer;
};

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_GUIDE_MAIN_H

