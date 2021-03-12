#pragma once
#include "MapNode.h"
#include "SpriteAnim.h"
#include "ControlInput.h"
#include <math.h>
#include "Mesh2D.h"
#include "AIFSM.h"
#include "TMaths.h"

class MapSprite :
    public MapNode
{
public:
    MapSprite() {
        Anims.resize(0);
        Controller = new ControlInput();
    }

    void AddAnim(SpriteAnim* anim) {
        Anims.push_back(anim);
    }
    void PlayAnim(VString name) {
        
        if (CurrentAnim != NULL) {
            if (name.IsSame(CurrentAnim->GetName())) {
                return;
            }
        }

        for (int i = 0; i < Anims.size(); i++) {
            if (name.IsSame(Anims[i]->GetName()))
            {
                CurrentAnim = Anims[i];
                CurrentAnim->Play();
                return;
            }
        }
        printf("Could not find animation:");
        printf(name.GetConst());
        printf("|\n");
        return;
    }

    virtual void Update() {

    }

    virtual void Move(float lx, float ly, float rx, float ry)
    {

    }

    virtual void Triggers(float lt, float rt) {

    }

    float max(float a, float b) {
        if (a > b) return a;
        return b;
    }

    float min(float a, float b) {
        if (a < b) return a;
        return b;
    }
    
    float Lerp(float a, float b, float lerpFactor)
    {
        float result = ((1.f - lerpFactor) * a) + (lerpFactor * b);
        return result;
    }


    float LerpDegrees(float a, float b, float lerpFactor) // Lerps from angle a to b (both between 0.f and 360.f), taking the shortest path
    {
        float result;
        float diff = b - a;
        if (diff < -180.f)
        {
            // lerp upwards past 360
            b += 360.f;
            result = Lerp(a, b, lerpFactor);
            if (result >= 360.f)
            {
                result -= 360.f;
            }
        }
        else if (diff > 180.f)
        {
            // lerp downwards past 0
            b -= 360.f;
            result = Lerp(a, b, lerpFactor);
            if (result < 0.f)
            {
                result += 360.f;
            }
        }
        else
        {
            // straight lerp
            result = Lerp(a, b, lerpFactor);
        }

        return result;
    }

    void AimAt(float x, float y) {

        float ang = atan2(y, x);

        float pi = 3.1415926535897932384626433;

        float aa = (ang * 180.0f) / pi;

        aa = aa + 90;

        float a2 = GetRot();

        a2 = LerpDegrees(a2, aa, 0.11f);

        SetRot(a2);

    }

    void UpdateSprite() {

        if (CurrentAnim != NULL) {
            CurrentAnim->Update();
        }

        if (Controller != NULL) {

            Controller->Update();
            Move(Controller->leftStickX, -Controller->leftStickY, Controller->rightStickX, Controller->rightStickY);
            Triggers(Controller->leftTrigger, Controller->rightTrigger);

        }

        if (AI != NULL) {

            AI->Update();

        }

        Update();
    }

    VString GetCurrentAnim() {

        if (CurrentAnim == NULL) {
            return VString("None");
        }
        else {
            return CurrentAnim->GetName();
        }

    }

    Texture2D* GetFrame() {

        if (SingleImage != NULL) {
            return SingleImage;
        }
        if (CurrentAnim == NULL) {
            return NULL;
        }
        return CurrentAnim->GetFrame();

    }

    void SetSize(int w, int h) {
        SprWidth = w;
        SprHeight = h;
    }

    int GetWidth() {
        return SprWidth;
    }
    int GetHeight() {
        return SprHeight;
    }
    void Compile();
    void RenderCompiled();

    Mesh2D* GetMesh() {
        return CompiledMesh;
   }

    void SetAI(AIFSM* ai) {
        AI = ai;
    }
    void SetDebugStr(const char* s) {
        DebugString = s;
    }
    const char* GetDebugStr() {
        return DebugString;
    }
    void Hit(float force) {

        Life = Life - force;
        if (Life <= 0) {

            Alive = false;
            if (DieSoundPlayed == false) {
                DieSound->Play();
                DieSoundPlayed = true;
            }

        }
        if (Life > 0) {
            if (HitSound != NULL) {
                int ahs = TMaths::Rnd(0, 12);
                if (ahs > 8) {

                    HitSound->Play();

                }
            }
        }
        AfterHit();

    }
    float GetLife() {
        return Life;
    }
    virtual void AfterHit() {};
    bool IsAlive() {
        return Alive;
    }
    void DisableAI() {

        AI = NULL;

    }
    bool AIExists() {
        if (AI != NULL) return true;
        return false;
    }
    cpShape* GetShape() {
        return pShape;
    }
    void SetSingleImage(Texture2D* tex) {
        SingleImage = tex;
    }
    Texture2D* GetSingleImage() {
        return SingleImage;
    }
    int GetTeam() {
        return TeamID;
    }
    virtual void Attack() {

    }
protected:
    const char* DebugString = "";
    SpriteAnim* CurrentAnim = NULL;
    std::vector<SpriteAnim*> Anims;
    ControlInput* Controller;
    int SprWidth = 256;
    int SprHeight = 256;
    Mesh2D* CompiledMesh;
    AIFSM* AI = NULL;
    float Life = 100.0f;
    bool Alive = true;
    Texture2D* SingleImage = NULL;
    SoundSource* HitSound = NULL;
    bool DieSoundPlayed = false;
    SoundSource* DieSound = NULL;
    int TeamID = 0;
};



