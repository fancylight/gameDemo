//
// Created by fancylight on 2018/7/23.
//

#ifndef TEMPLATECPP_MARCO_H
#define TEMPLATECPP_MARCO_H
#define LOG(RECT) log(RECT.width);log(RECT.height);
#define RECT_PRINT(RECTNAME,RECT) std::cout<<"²âÊÔ:"<<RECTNAME<<std::endl; std::cout<<"rect.x: "<<RECT.origin.x<<std::endl; std::cout<<"rect.y: "<<RECT.origin.y<<std::endl; std::cout<<"rect.w: "<<RECT.size.width<<std::endl; std::cout<<"rect.h: "<<RECT.size.height<<std::endl;
#endif //TEMPLATECPP_MARCO_H
