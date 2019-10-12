#include "skeleton_animation_loader.h"
#include "../json_helper.h"
#include "editor-support/spine/spine-cocos2dx.h"
#include "editor-support/spine/spine.h"
#include <QtCore/QVariant>

#ifdef BUILD_EDITOR
#include "editor/extend/editor_spine.h"
#include "editor/framework.h"
typedef EditorSpine _Spine;
#else
typedef spine::SkeletonAnimation _Spine;
#endif

#ifdef BUILD_EDITOR
DECLARE_PROPERTY_SETTER(_Spine, skelFile, setSkeletonFile, ResourceHolder)
DECLARE_PROPERTY_SETTER(_Spine, atlasFile, setAtlasFile, ResourceHolder)
DECLARE_PROPERTY_SETTER(_Spine,animClip,playAnim,std::string);
DECLARE_PROPERTY_SETTER(_Spine,isLoop,setLoop,bool);

DEFINE_PROPERTY_SETTER(_Spine, animations)
{
    mjson::Array *arr = value->asArray();
    std::vector<std::string> anims;

    for(const mjson::Node &node : *arr)
    {
        std::string anim = json2string(node);
        anims.push_back(anim);
    }
}

DEFINE_PROPERTY_GETTER(_Spine, animations)
{
    JsonValue ret;
    mjson::Array *arr = ret.setArray();

    std::vector<std::string> anims;
    anims = node->getAnimations();
    for (int i = 0; i < anims.size();i++) {
       arr->append(anims[i]);
    }
    return ret;
}
#endif

SkeletonAnimationLoader::SkeletonAnimationLoader()
{
#ifdef BUILD_EDITOR
    REGISTER_PROPERTY_SETTER(skelFile);
    REGISTER_PROPERTY_SETTER(atlasFile);
    REGISTER_PROPERTY_SETTER(animClip);
    REGISTER_PROPERTY_SETTER(isLoop);
    REGISTER_PROPERTY_SETTER(animations);

    REGISTER_PROPERTY_GETTER(animations);
#endif
}

ObjectType* SkeletonAnimationLoader::createObject(const JsonHandle &config)
{
    std::string skelFile;
    std::string spAtlas_;
    config["skelFile"] >> skelFile;
    config["spAtlas"] >> spAtlas_;
    if(!skelFile.empty() && !spAtlas_.empty())
    {
        RESOLVE_FILE_RESOURCE(skelFile);
        RESOLVE_FILE_RESOURCE(spAtlas_);
        _Spine* spine = _Spine::createWithBinaryFile(skelFile,spAtlas_,1.0f);

        return spine;
    }
    else
    {
        return nullptr;
    }
}

void SkeletonAnimationLoader::postLoaded(ObjectType* node, const JsonHandle& config)
{
//#ifdef BUILD_EDITOR
//        JsonValue ret;
//        mjson::Array *arr = ret.setArray();

//        std::vector<std::string> anims;
//        anims = ((_Spine*)node)->getAnimations();
//        for (int i = 0; i < anims.size();i++) {
//           arr->append(anims[i]);
//        }
//        Editor::Framework::instance()->emitNodePropertyChange((_Spine*)node, "animations", ret);
//#endif
}
