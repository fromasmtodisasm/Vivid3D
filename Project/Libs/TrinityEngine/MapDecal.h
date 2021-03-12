#pragma once
#include "MapNode.h"
class MapDecal :
    public MapNode
{
public:
    MapDecal(Texture2D* tex) {
        DecalTex = tex;
        W = 64;
        H = 64;
    }
    Texture2D* GetDecalTex() {
        return DecalTex;
    }
    int GetWidth() {
        return W;
    }
    int GetHeight() {
        return H;
    }
    void SetSize(int w, int h) {
        W = w;
        H = h;
    }
private:
    Texture2D* DecalTex;
    float W, H;
};

