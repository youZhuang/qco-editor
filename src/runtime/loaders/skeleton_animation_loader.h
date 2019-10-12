#ifndef SKELETON_ANIMATION_LOADER_H
#define SKELETON_ANIMATION_LOADER_H

#include "skeletonrenderer_loader.h"

class PIP_DLL SkeletonAnimationLoader : public SkeletonRendererLoader
{
public:
    DECLARE_LOADER(SkeletonAnimationLoader)

    SkeletonAnimationLoader();
    virtual ObjectType* createObject(const JsonHandle &config) override;
    virtual void postLoaded(ObjectType *p, const JsonHandle &config) override;
};


#endif // SKELETON_ANIMATION_LOADER_H
