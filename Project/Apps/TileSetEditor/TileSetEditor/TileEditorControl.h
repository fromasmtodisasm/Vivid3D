#pragma once
#include "MapTile.h"
#include <UIControl.h>
#include "Vec2.h"
#include "ImageDropControl.h"
#include "ButtonControl.h"
#include "BoolControl.h"
#include "MapLight.h"

enum EditMode {
    Tile,Light,Node,Logic,Script
};

class TileEditorControl :
    public UIControl
{
public:

    TileEditorControl();

    static MapTile* CurTile;
    static MapLight* CurLight;
    static MapNode* CurNode;
    static TileEditorControl* Main;
    static void SetTile(MapTile* tile);
    static void SetLight(MapLight* light);
    static void SetNode(MapNode* node);
    void Rebuild();

    UIControl* AddTexture(const char* name, Texture2D* tex);
    void AddVec3(const char* name, Vec3* v);
    void AddVec2(const char* name, Vec2* v);
    void AddString(const char* name, const char* init);
    void AddFile(const char* name, const char* path);
    void AddFloat(const char* name, float* v);
    BoolControl *AddBool(const char* name, bool* b);
    void Render();
private:
    EditMode Mode;
    int EditY = 5;
    Texture2D* white;
    //std::vector<std::function<void(const char(*))

};

