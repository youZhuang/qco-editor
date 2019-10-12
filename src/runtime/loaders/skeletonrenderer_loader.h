#ifndef SKELETONRENDERER_LOADER_H
#define SKELETONRENDERER_LOADER_H

#include "node_loader.h"

class PIP_DLL SkeletonRendererLoader : public CCNodeLoader
{
public:
    DECLARE_LOADER(SkeletonRendererLoader)

    SkeletonRendererLoader();
};

#endif // SKELETONRENDERER_LOADER_H
