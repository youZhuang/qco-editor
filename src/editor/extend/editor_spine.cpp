#include "editor_spine.h"


USING_NS_CC;

EditorSpine::EditorSpine()
{

}

EditorSpine::~EditorSpine()
{

}

/*static*/ EditorSpine* EditorSpine::create()
{
    EditorSpine *p = new (std::nothrow) EditorSpine();
    if(p->init())
    {
        p->autorelease();
        return p;
    }
    delete p;
    return nullptr;
}

/*static*/ EditorSpine* EditorSpine::create(const std::string &skelFile,const std::string &atlasFile)
{
    spAtlas* atlas = spAtlas_createFromFile(atlasFile.c_str(), nullptr);

    EditorSpine* spine = new (std::nothrow)EditorSpine();
    spine->initWithBinaryFile(skelFile,atlas,1.0f);
    if (spine)
    {
        spine->autorelease();
        return spine;
    }
    CC_SAFE_DELETE(spine);
    return nullptr;
}

EditorSpine* EditorSpine::createWithBinaryFile (const std::string& skeletonBinaryFile, const std::string& atlasFile, float scale) {
    EditorSpine* node = new EditorSpine();
    spAtlas* atlas = spAtlas_createFromFile(atlasFile.c_str(), nullptr);
    node->initWithBinaryFile(skeletonBinaryFile, atlas, scale);
    node->autorelease();
    return node;
}

void EditorSpine::setSkeletonFile(const std::string &skelFile)
{
    if (_ownsSkeletonData) spSkeletonData_dispose(_skeleton->data);
    spSkeleton_dispose(_skeleton);
    if (_atlas) spAtlas_dispose(_atlas);
    if (_attachmentLoader) spAttachmentLoader_dispose(_attachmentLoader);
    delete [] _worldVertices;

    this->clearTracks();
    std::string atlasFile = skelFile.substr(0,skelFile.rfind(".",skelFile.length()-1))  + ".atlas";
    spAtlas* atlas = spAtlas_createFromFile(atlasFile.c_str(), nullptr);

    _skelFile = skelFile;
    _atlasFile = atlasFile;
    initWithBinaryFile(skelFile,atlas,1.0f);
}

void EditorSpine::setAtlasFile(const std::string &atlasFile)
{
    if (_ownsSkeletonData) spSkeletonData_dispose(_skeleton->data);
    spSkeleton_dispose(_skeleton);
    if (_atlas) spAtlas_dispose(_atlas);
    if (_attachmentLoader) spAttachmentLoader_dispose(_attachmentLoader);
    delete [] _worldVertices;

    this->clearTracks();
    std::string skelFile = atlasFile.substr(0,atlasFile.rfind(".",atlasFile.length()-1)) + ".skel";
    spAtlas* atlas = spAtlas_createFromFile(atlasFile.c_str(), nullptr);

    _skelFile = skelFile;
    _atlasFile = atlasFile;
    initWithBinaryFile(skelFile,atlas,1.0f);
}

std::vector<std::string> EditorSpine::getAnimations()
{
    if (_animations.empty()) {
        spSkeleton* skel = getSkeleton();
        spSkeletonData* data = skel->data;
        for(int i= 0; i < data->animationsCount;i++) {
            spAnimation* anim = data->animations[i];
            std::string animName = anim->name;
            _animations.push_back(animName);
        }
    }
    return _animations;
}

void EditorSpine::playAnim(const std::string  &animName)
{
    _curAnimName = animName;
    clearTracks();
    spAnimation* anim = this->findAnimation(_curAnimName);
    if (anim) {
        this->setAnimation(0,_curAnimName,_isLoop);
    }else {//查找第一个动画
        spSkeleton* skel = getSkeleton();
        spSkeletonData* data = skel->data;
        spAnimation* anim = data->animations[0];
        std::string animName = anim->name;
        _curAnimName = animName;
    }
    this->setAnimation(0,_curAnimName,_isLoop);
}

bool EditorSpine::setLoop(bool isLoop)
{
    _isLoop = isLoop;
    clearTracks();
    this->setAnimation(0,_curAnimName,_isLoop);
}
