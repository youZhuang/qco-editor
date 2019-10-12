#ifndef EDITOR_SPINE_H
#define EDITOR_SPINE_H

#include "editor-support/spine/spine-cocos2dx.h"
#include "editor-support/spine/spine.h"

class EditorSpine : public spine::SkeletonAnimation
{
public:
    static EditorSpine* create();
    static EditorSpine* create(const std::string &skelFile,const std::string &atlasFile);
    static EditorSpine* createWithBinaryFile (const std::string& skeletonBinaryFile, const std::string& atlasFile, float scale = 1);

    void setSkeletonFile(const std::string &skelFile);
    void setAtlasFile(const std::string &atlasFile);

    void playAnim(const std::string  &animName);
    bool setLoop(bool isLoop);

    std::vector<std::string> getAnimations();

CC_CONSTRUCTOR_ACCESS:
    EditorSpine();
    ~EditorSpine();

protected:
    std::string         _skelFile;
    std::string         _atlasFile;
    std::string         _curAnimName;
    bool                _isLoop;

    std::vector<std::string> _animations;
};


#endif // EDITOR_SPINE_H
