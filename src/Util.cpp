#pragma once
#include <time.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>



class Point{
public:
    int x;
    int y;
    Point(){x=0;y=0;}
    Point(int _x,int _y){x=_x;y=_y;}
    void set(int _x, int _y){x=_x;y=_y;}
    
    Point operator+(Point arg) 
    {
        Point returned;
        returned.set(x+arg.x,y+arg.y);
        return returned;
    }
    
    Point operator-(Point arg) 
    {
        Point returned;
        returned.set(x-arg.x,y-arg.y);
        return returned;
    }
    
    Point operator+=(Point arg) 
    {
        x += arg.x;
        y += arg.y;
        return *this;
    }
    
    Point operator=(int args[2]) 
    {
        x = args[0];
        y = args[1];
        return *this;
    }
    
    Point operator*(Point p1)
    {
        Point result = {0,0};
        result.x = x * p1.x;
        result.y = y * p1.y;
        return result;
    }
    
    Point normalized()
    {
    
        
        float magnitude = sqrt(x*x + y*y);
        if(magnitude==0) return {0,0};
        float _x=x;
        _x = std::round(_x / magnitude);
        float _y=y;
        _y = std::round(_y / magnitude);
    
        return {(int)_x,(int)_y};
    }
    
    // Dot product
    float dot(Point p1)
    {
        float result = (x * p1.x) +(y * p1.y);
        return result;
        
    }
    
    // Get string of values
    char* str(){
        char tmp[50];
        sprintf(tmp,"(%i,%i)",x,y);
        return tmp;
    }
};


class PointF{
public:
    float x;
    float y;
    PointF(){x=0;y=0;}
    PointF(float _x,float _y){x=_x;y=_y;}
    set(float _x, float _y){x=_x;y=_y;}
    
    PointF operator+(PointF arg) 
    {
        PointF returned;
        returned.set(x+arg.x,y+arg.y);
        return returned;
    }
    
    PointF operator-(PointF arg) 
    {
        PointF returned;
        returned.set(x-arg.x,y-arg.y);
        return returned;
    }
    
    PointF operator+=(PointF arg) 
    {
        x += arg.x;
        y += arg.y;
        return *this;
    }
    
    PointF operator=(int args[2]) 
    {
        x = args[0];
        y = args[1];
        return *this;
    }
    
    PointF operator*(PointF p1)
    {
        PointF result = {0,0};
        result.x = x * p1.x;
        result.y = y * p1.y;
        return result;
    }
    
    PointF normalized()
    {
    
        
        float magnitude = sqrt(x*x + y*y);
        if(magnitude==0) return {0,0};
        float _x=x;
        _x = std::round(_x / magnitude);
        float _y=y;
        _y = std::round(_y / magnitude);
    
        return {_x,_y};
    }
    
    // Dot product
    float dot(PointF p1)
    {
        float result = (x * p1.x) +(y * p1.y);
        return result;
        
    }
    
    // Get string of values
    char* str(){
        char tmp[50];
        sprintf(tmp,"(%i,%i)",x,y);
        return tmp;
    }
};


class Random{
public:
    static int randInt(int min, int max){
        //srand(time(NULL));
        return rand() % max + min;
    }
};

class Timer{
    
    
private:
	Uint32 timer = 0;
    bool timerRunning = false;
    Uint32 interval; // Time to wait 
public:    
    
    void start(Uint32 timeToWait)
    {
        timerRunning = true;
        interval = timeToWait;
        timer = SDL_GetTicks();
    }

    bool isDone()
    {
        if(!timerRunning) return true;
        Uint32 currTime = SDL_GetTicks();
        if((currTime - timer) >= interval){
            timerRunning = false;
            return true;
        }else return false;
    }
    
    void reset()
    {
        timerRunning = true;
        interval = SDL_GetTicks();
    }
    
    
};



