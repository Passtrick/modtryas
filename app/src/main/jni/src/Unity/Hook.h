#ifndef ANDROID_MOD_MENU_HOOK_H
#define ANDROID_MOD_MENU_HOOK_H

#include "Global.h"
#include <sys/syscall.h>
using namespace std;
#include <string>
#include <sstream>
#include <iostream>
#include<sstream>

long AfindLibrary(const char *library) {
    char filename[0xFF] = {0},
            buffer[1024] = {0};
    FILE *fp = NULL;
    long address = 0;

    sprintf( filename, "/proc/self/maps");

    fp = fopen( filename, "rt" );
    if( fp == NULL ){
        perror("fopen");
        goto done;
    }

    while( fgets( buffer, sizeof(buffer), fp ) ) {
        if(strstr( buffer, library ) ){
            address = (long)strtoul( buffer, NULL, 16 );
            goto done;
        }
    }

    done:

    if(fp){
        fclose(fp);
    }

    return address;
}

long ClibBase;

long AgetAbsoluteAddress(const char* libraryName, long relativeAddr) {
    if (ClibBase == 0) {
        ClibBase = AfindLibrary(libraryName);
        if (ClibBase == 0) {
            ClibBase = 0;
        }
    }
    return ClibBase + relativeAddr;
}

# define getRealOffset(offset) AgetAbsoluteAddress("libil2cpp.so",offset)

static void set_aim(void *player, Quaternion look) {
    void (*_set_aim)(void *players, Quaternion lock) = (void (*)(void *, Quaternion))getRealOffset(Global.set_aim);
    _set_aim(player, look);
}

static void *GetLocalPlayer(void* Match) {
    void *(*_GetLocalPlayer)(void *match) = (void *(*)(void *))getRealOffset(Global.GetLocalPlayer);
    return _GetLocalPlayer(Match);
}
class Vvector3 {
public:
    float X;
    float Y;
    float Z;
    Vvector3() : X(0), Y(0), Z(0) {}
    Vvector3(float x1, float y1, float z1) : X(x1), Y(y1), Z(z1) {}
    Vvector3(const Vvector3 &v);
    ~Vvector3();
};
Vvector3::Vvector3(const Vvector3 &v) : X(v.X), Y(v.Y), Z(v.Z) {}
Vvector3::~Vvector3() {}



static bool get_IsDieing(void *player) {
    bool (*_get_die)(void *players) = (bool (*)(void *))getRealOffset(Global.get_IsDieing);
    return _get_die(player);
}

static void *CurrentUIScene() {
    void *(*_CurrentUIScene)(void *nuls) = (void *(*)(void *))getRealOffset(Global.CurrentUIScene);
    return _CurrentUIScene(NULL);
}

static Vector3 WorldToScreenPoint(void *PlayerCam, Vector3 PlayerPos) {
    Vector3 (*_WorldToScreenPoint)(void* Camera, Vector3 position) = (Vector3 (*)(void*, Vector3)) getRealOffset(Global.WorldToScreenPoint);
    return _WorldToScreenPoint(PlayerCam,PlayerPos);
}

static bool get_IsCrouching(void *player) {
    bool (*_get_IsCrouching)(void *players) = (bool (*)(void *))getRealOffset(Global.get_IsCrouching);
    return _get_IsCrouching(player);
}

static void *Camera_main() {
    void *(*_Camera_main)(void *nuls) = (void *(*)(void *))getRealOffset(Global.Camera_main);
    return _Camera_main(NULL);
}

static Vector3 GetAttackableCenterWS(void *player) {
    Vector3 (*_GetAttackableCenterWS)(void *players) = (Vector3 (*)(void *))getRealOffset(Global.GetAttackableCenterWS);
    return _GetAttackableCenterWS(player);
}

static void *GetLocalPlayerOrObServer() {
    void *(*_GetLocalPlayerOrObServer)(void *players) = (void *(*)(void *))getRealOffset(Global.GetLocalPlayerOrObServer);
    return _GetLocalPlayerOrObServer(NULL);
}

static void *Current_Local_Player() {
    void *(*_Local_Player)(void *players) = (void *(*)(void *))getRealOffset(Global.Current_Local_Player);
    return _Local_Player(NULL);
}

static void *get_MyFollowCamera(void *players) {
    void *(*_get_MyFollowCamera) (void *player) = (void *(*)(void *))getRealOffset(Global.get_MyFollowCamera);
    return _get_MyFollowCamera(players);
}

static bool get_isAlive(void *player) {
    bool (*_get_isAlive)(void *players) = (bool (*)(void *))getRealOffset(Global.get_isAlive);
    return _get_isAlive(player);
}

static void *Curent_Match() {
    void *(*_Curent_Match) (void *nuls) = (void *(*)(void *))getRealOffset(Global.Curent_Match);
    return _Curent_Match(NULL);
}

static bool get_isLocalTeam(void *player) {
    bool (*_get_isLocalTeam)(void *players) = (bool (*)(void *))getRealOffset(Global.get_isLocalTeam);
    return _get_isLocalTeam(player);
}

static monoString *U3DStr(const char *str) {
    monoString *(*String_CreateString)(void *_this, const char *str) = (monoString * (*)(void *, const char *))getRealOffset(Global.U3DStr);
    return String_CreateString(NULL, str);
}

static bool get_IsFiring(void *player) {
    bool (*_get_IsFiring)(void *players) = (bool (*)(void *))getRealOffset(Global.get_IsFiring);
    return _get_IsFiring(player);
}

static monoString *U3DStrFormat(float distance) {
    char buffer[128] = {0};
    sprintf(buffer, "[ %.f M ]  [BOT]", distance);
    return U3DStr(buffer);
}
static monoString *U3DStrFormat2(float distance) {
    char buffer[128] = {0};
sprintf(buffer, "[ %.f M ] [ PLAYER ]", distance);
    return U3DStr(buffer);
}

static void AddTeammateHud(void *player, monoString *nick, monoString *grup) {
    void (*_AddTeammateHud)(void *players, monoString * nicks, monoString * nickss) = (void (*)(void *, monoString *, monoString *))getRealOffset(Global.AddTeammateHud);
    void *ui = CurrentUIScene();
    if (ui != NULL) {
        _AddTeammateHud(player, nick, grup);
    }
}


static monoString* get_NickName(void *player) {
    monoString* (*_get_NickName)(void *players) = (monoString * (*)(void *))getRealOffset(Global.get_NickName);
    return _get_NickName(player);
}



static void ShowAssistantText(void *player, monoString *nick, monoString *grup) {
    void (*_ShowAssistantText)(void *players, monoString * nicks, monoString * nickss) = (void (*)(void *, monoString *, monoString *))getRealOffset(Global.ShowPopupMessage);
    void *ui = CurrentUIScene();
    if (ui != NULL) {
        _ShowAssistantText(player, nick, grup);
    }
}
static Vector3 WorldLocToScreenPoint(void *PlayerCam, Vector3 PlayerPos) {
    Vector3 (*_WorldToScreenPoint)(void* Camera, Vector3 position) = (Vector3 (*)(void*, Vector3)) getRealOffset(Global.WorldToScreenPoint);
    return _WorldToScreenPoint(PlayerCam,PlayerPos);
}
static void *get_imo(void *player) {
    void *(*_get_imo)(void *players) = (void *(*)(void *))getRealOffset(Global.get_imo);
    return _get_imo(player);
}

static void set_esp(void *imo, Vector3 x, Vector3 y) {
    void (*_set_esp)(void *imo, Vector3 X, Vector3 Y) = (void (*)(void *, Vector3, Vector3))getRealOffset(Global.set_esp);
    _set_esp(imo, x, y);
}

static bool get_IsSighting(void *player) {
    bool (*_get_IsSighting)(void *players) = (bool (*)(void *))getRealOffset(Global.get_IsSighting);
    return _get_IsSighting(player);
}

static Vector3 Transform_INTERNAL_GetPosition(void *player) {
    Vector3 out = Vector3::Zero();
    void (*_Transform_INTERNAL_GetPosition)(void *transform, Vector3 * out) = (void (*)(void *, Vector3 *))getRealOffset(Global.Transform_INTERNAL_GetPosition);
    _Transform_INTERNAL_GetPosition(player, &out);
    return out;
}

static void *Component_GetTransform(void *player) {
    void *(*_Component_GetTransform)(void *component) = (void *(*)(void *))getRealOffset(Global.Component_GetTransform);
    return _Component_GetTransform(player);
}

static bool get_isVisible(void *player) {
    bool (*_get_isVisible)(void *players) = (bool (*)(void *))getRealOffset(Global.get_isVisible);
    return _get_isVisible(player);
}

static Vector3 GetForward(void *player) {
    Vector3 (*_GetForward)(void *players) = (Vector3 (*)(void *))getRealOffset(Global.GetForward);
    return _GetForward(player);
}





static int get_CurHP(void *player) {
	int (*_get_CurHP)(void *players) = (int(*)(void *))getRealOffset(Global.get_CurHP);
	return _get_CurHP(player);
}
static int get_MaxHP(void *player) {
	int (*_get_MaxHP)(void *players) = (int(*)(void *))getRealOffset(Global.get_MaxHP);
	return _get_MaxHP(player);
}


static void Transform_INTERNAL_SetPosition(void *player, Vvector3 inn) {
    void (*_Transform_INTERNAL_SetPosition)(void *transform, Vvector3 in) = (void (*)(void *, Vvector3))getRealOffset(Global.Transform_INTERNAL_SetPosition);
    _Transform_INTERNAL_SetPosition(player, inn);
}

static void *GetLocalCar(void *playerCar) {
    void *(*_Player_get_local)(void *Player) = (void *(*)(void *))getRealOffset(0x811588);
    return _Player_get_local(playerCar);
}


static bool IsDriver(void *player) {
    bool (*_IsDriver)(void *players) = (bool (*)(void *))getRealOffset(0x7F6654);
    return _IsDriver(player);
}

void *Grenade2 = NULL;

void *Render2 = NULL;

void (*_GrenadeLine_Update)(void *instance);
void GrenadeLine_Update(void *instance) {
    if (instance != NULL) {
        Grenade2 = instance;
        *(bool *)((uintptr_t)instance + Global.GrenadeLine_isVisible) = true;
        Render2 = *(void **)((long)instance + Global.GrenadeLine_m_GrenadeLine);
    }
    _GrenadeLine_Update(instance);
}

static void LineRenderer_SetPosition(void *Render, int value, Vector3 Location){
    void (*_LineRenderer_SetPosition)(void *Render, int value, Vector3 Location) = (void (*)(void*, int, Vector3))getRealOffset(Global.LineRenderer_SetPosition);
    return _LineRenderer_SetPosition(Render, value, Location);
}

static void LineRenderer_Set_PositionCount(void *Render, int value){
    void (*_LineRenderer_Set_PositionCount)(void *Render, int value) = (void (*)(void*, int))getRealOffset(Global.LineRenderer_Set_PositionCount);
    return _LineRenderer_Set_PositionCount(Render, value);
}

static void GrenadeLine_DrawLine(void *instance, Vector3 start, Vector3 end, Vector3 position) {
    void (*_GrenadeLine_DrawLine)(void *clz, Vector3 throwPos, Vector3 throwVel, Vector3 gravity) = (void (*)(void*, Vector3, Vector3,Vector3)) getRealOffset(Global.GrenadeLine_DrawLine);
    return _GrenadeLine_DrawLine(instance, start, end, position);
}

static void ShowDynamicPopupMessage(monoString *nick) {
    void (*_ShowDynamicPopupMessage)(void *players, monoString * nicks, float duration) = (void (*)(void *, monoString *, float))getRealOffset(Global.ShowDynamicPopupMessage);
    void *ui = CurrentUIScene();
    if (ui != nullptr) {
        _ShowDynamicPopupMessage(ui, nick, 0.1f);
    }
}

static monoString *FormatCount(int enemy) {
    char buf[128] = {};
    sprintf(buf, ("ENEMIES : %d"), enemy);
    return U3DStr(buf);
}



#endif




