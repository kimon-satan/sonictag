#ifndef _GEOM_FUNCTIONS_H
#define _GEOM_FUNCTIONS_H
#include <stdio.h>
#include "ofMain.h"


namespace geom {
    
    inline bool pointInRect(int x, int y, ofRectangle r) {
        //	cout << x << "," << y << "," << r.x << "," << r.y << "," << r.width << "," << r.height << "," << endl;
        return ((x >= r.x) && (y >= r.y) && (x <= r.x + r.width) && (y <= r.y + r.height));
    }
    
    inline bool pointInRect(int x, int y, int rx, int ry, int rw, int rh) {
        //	cout << x << "," << y << "," << r.x << "," << r.y << "," << r.width << "," << r.height << "," << endl;
        return ((x >= rx) && (y >= ry) && (x <= rx + rw) && (y <= ry + rh));
    }
    
    inline float distBetween(ofPoint a, ofPoint b) {
        int dx = a.x - b.x;
        int dy = a.y - b.y;
        return sqrt((dx * dx) + (dy * dy));
    }
    
    inline float distBetween(int x1, int y1, int x2, int y2) {
        int dx = x2 - x1;
        int dy = y2 - y1;
        return sqrt((dx * dx) + (dy * dy));
    }
    
    inline float angleBetween(ofPoint a, ofPoint b) {
        int dx = a.x - b.x;
        int dy = a.y - b.y;
        return atan2((float)dy , (float)dx);
    }
    
    inline float angleBetween(int x1, int y1, int x2, int y2) {
        int dx = x1 - x2;
        int dy = y1 - y2;
        return atan2((float)dy , (float)dx);
    }
    
    inline float angleBetween2(int x1, int y1, int x2, int y2) {
        float dx = x2 - x1;
        float dy = y2 - y1;
        return atan(dy / dx);
    }
    
    
    inline float* distAndAngleBetween(ofPoint a, ofPoint b) {
        int dx = a.x - b.x;
        int dy = a.y - b.y;
        float* result = new float[2];
        result[0] = sqrt((dx * dx) + (dy * dy));
        result[1] = atan2((float)dy , (float)dx);
        return result;
    }
    
    inline float* distAndAngleBetween(int x1, int y1, int x2, int y2) {
        int dx = x1 - x2;
        int dy = y1 - y2;
        float* result = new float[2];
        result[0] = sqrt((dx * dx) + (dy * dy));
        result[1] = atan2((float)dy , (float)dx);
        return result;
    }
    
};


#endif