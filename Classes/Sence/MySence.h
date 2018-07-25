//
// Created by fancylight on 2018/7/21.
//

#ifndef TEMPLATECPP_MYSENCE_H
#define TEMPLATECPP_MYSENCE_H


#include <cocos/2d/CCScene.h>

class MySence: public cocos2d::Scene {
public:
    bool init() override;
    virtual void update(float delta);
    CREATE_FUNC(MySence)
};


#endif //TEMPLATECPP_MYSENCE_H
