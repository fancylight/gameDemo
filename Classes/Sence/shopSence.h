//
// Created by fancylight on 2018/7/23.
//

#ifndef TEMPLATECPP_SHOPSENCE_H
#define TEMPLATECPP_SHOPSENCE_H
#include <cocos/2d/CCScene.h>
class MySprite;
class ShopSence: public cocos2d::Scene {
public:
    /**
     * 初始化函数  初始sence元素
     * @return
     */
    bool init() override;
    CREATE_FUNC(ShopSence)
	
    //抽卡菜单的回调
    bool randomCharacter(Ref *pSender);
private:
    MySprite* mySprite;//表示当前的出现在屏幕上的精灵
    bool animation=false;//true表示动画进行
    std::string randonName();//随机产生一个精灵的名字
	void setNextBuy();
	void backMenu(Ref* ref);
};


#endif //TEMPLATECPP_SHOPSENCE_H
