#include <pthread.h>
#include <jni.h>
#include <stdio.h>
#include <wchar.h>
#include "Substrate/SubstrateHook.h"
#include <src/Socket/SocketServer.h>
#include "src/Unity/Quaternion.hpp"
#include "src/Unity/Vector3.hpp"
#include "src/Unity/Vector3.hpp"
#include "src/Unity/Unity.h"
#include "src/Unity/Hook.h"
#include "src/Unity/Global.h"
#include "src/Unity/Color.hpp"
#include "src/Unity/Rect.hpp"
#include "src/Unity/ESP.h"
#include "KittyMemory/MemoryPatch.h"
#include "Includes/Logger.h"

# define getRealOffset(offset) AgetAbsoluteAddress("libil2cpp.so", offset)

# define HOOK(offset, ptr, orig) MSHookFunction((void *)getRealOffset(offset), (void *)ptr, (void **)&orig)

using namespace std;


SocketServer server;
int SWidth = 1920;
int SHeight = 1080;

#define maxplayerCount 30

enum Mode {
    InitMode = 1,
    HackMode = 2,
    StopMode = 3,
	ESPMode = 4,
	
};

enum m_Features {
	g_aimAuto = 4,
	g_aimAtirar = 5,
	g_aimMirar = 6,
	g_aimAgachar = 7,
	g_espNames = 8,
	g_espAlerta = 9,
	g_espGranada = 10,
	g_telekill = 11,
	g_EspFire = 12,
	g_TelecarPro = 13,
	g_nightmode = 14,
	g_fly = 15,
	g_under = 16,
	g_medkitrun = 17,
    g_speedhack = 18,
	g_speedhack100x = 19,
	g_speedhack1000x = 20,
	
	g_func1 = 21,
    g_func2 = 22,
	g_xxx = 23,
};


struct Request {
    int Mode;
    bool m_IsOn;
    int ScreenWidth;
    int ScreenHeight;
};

struct PlayerData {
    float Distance;
    Vector3 Location;
    Vector3 HeadLocation;
	Vector3 PositionHip;
	Vector3 PositionDedoS;
	Vector3 PositionPeD;
	Vector3 PositionPeS;
	Vector3 PositionRShoulder;
	Vector3 PositionLShoulder;
	Vector3 PositionRightHand;
	Vector3 PositionLeftHand;
	Vector3 PositionToe;
	Vector3 PositionRJ;
	Vector3 PositionLJ;
	Vector3 CenterWS;
	float Health;
	Vector3 HeadRaw;
	
};

struct Response {
    bool Success;
    int PlayerCount;
    PlayerData Players[50];
};




struct My_Patches {
    MemoryPatch GodMode,
	MagicB,
	SpeedC,
	SpeedB,
	NoAnim,
	FlyC,
	UnderC;
	
    MemoryPatch modcorHd;
    MemoryPatch TeletransportarCarro;
    MemoryPatch fakeName;
    MemoryPatch teleKill;
    MemoryPatch FlyArma;
    MemoryPatch FlyHeight;
    MemoryPatch NoRecoil;
    MemoryPatch Corridinha50x;
    MemoryPatch Speed100x;
	MemoryPatch Speed1000x;
    MemoryPatch Speed2x;
    MemoryPatch Speed3x;
    MemoryPatch Speed4x;
    MemoryPatch Speed5x;
	MemoryPatch SpeedCar;
	MemoryPatch Wallhack;
	MemoryPatch Speedfire;
	MemoryPatch antiSpeed,
	WallStone , Aim1 , MagicBullet, revive ,WallStone1 ,WallStone2,WallStone3
	;
	
	MemoryPatch ghost ,MedKitRunning,MedKitRunning2,NightMod,WallPedra;

   
} hexPatches;

bool aimAuto = false;
bool aimAtirar = false;
bool aimMirar = false;
bool aimAgachar = false;
bool espNames = false;
bool espAlerta = false;
bool espGranada = false;

bool enableFov = true;

int enemyCountAround = 0;
int botCountAround = 0;

int counterFPS;
bool nightmode = false;
bool verify = false;
bool active = true;
bool launched = false;
bool TelecarPro = false;
bool EspFire = false;
bool telekill = false;
float aimFov = 360.0f;
bool fly = false;
bool under = false;
bool medkitrun = false;
bool Speed = false;

bool xxx =false;
bool iSpeed100x = false;



Vector3 GetHeadPosition(void* player) {
    return Transform_INTERNAL_GetPosition(*(void**) ((uint64_t) player + Global.HeadTF));
}

Vector3 GetHipPosition(void* player) {
    return Transform_INTERNAL_GetPosition(*(void**) ((uint64_t) player + Global.HipTF));
}

Vector3 GetToePosition(void* player) {
    return Transform_INTERNAL_GetPosition(*(void**) ((uint64_t) player + Global.ToeTF));
}

Vector3 CameraMain(void* player){
    return Transform_INTERNAL_GetPosition(*(void**) ((uint64_t) player + Global.MainCameraTransform));
}

void *GetClosestEnemy(void *match) {
    if(!match) {
        return NULL;
    }
	
    float shortestDistance = 99999;
    float maxAngle = aimFov;
	
    void* closestEnemy = NULL;
    void* LocalPlayer = GetLocalPlayer(match);
	
    if(LocalPlayer != NULL && !get_IsDieing(LocalPlayer)) {
       
		monoDictionary<uint8_t *, void **> *players = *(monoDictionary<uint8_t*, void **> **)((long)match + Global.Dictionary);
		for(int u = 0; u < players->getNumValues(); u++) {
            void* Player = players->getValues()[u];
           
			if(Player != NULL && !get_isLocalTeam(Player) && !get_IsDieing(Player) && get_isVisible(Player) && get_MaxHP(Player)) {
			  
                Vector3 PlayerPos = GetHipPosition(Player);
                Vector3 LocalPlayerPos = GetHeadPosition(LocalPlayer);
				
                if(enableFov) {
                    Vector3 targetDir = Vector3::Normalized(PlayerPos - LocalPlayerPos);
                    float angle = Vector3::Angle(targetDir, GetForward(Component_GetTransform(Camera_main()))) * 100.0;
                   
					if(angle <= maxAngle) {
                        if(angle < shortestDistance) {
                            shortestDistance = angle;
                            closestEnemy = Player;
                        }
                    }
                } else {
                    if(maxAngle < shortestDistance) {
                        shortestDistance = maxAngle;
                        closestEnemy = Player;
                    }
                }
            }
        }
    }
	return closestEnemy;
}
void (*LateUpdate)(void *componentPlayer);

void* UpdateCanvas = nullptr;
void get_CanvasUpdate(void* player) {
	UpdateCanvas = player;
}

void *fakeEnemy;
void _LateUpdate(void *player) {
	if(player != nullptr) {
		void *local_player = Current_Local_Player();
       
        if (local_player == NULL){
            local_player = GetLocalPlayerOrObServer();
        }
      
        if (local_player != NULL){
            void *current_match = Curent_Match();
         
            if (current_match != NULL) {
                
                
                    
                
                
                void *fakeCamPlayer = get_MyFollowCamera(local_player);
                void *fakeCamEnemy = get_MyFollowCamera(player);
             
                if (fakeCamPlayer != NULL && fakeCamEnemy != NULL){
                    void *fakeCamPlayerTF = Component_GetTransform(fakeCamPlayer);
                    void *fakeCamEnemyTF = Component_GetTransform(player);
                
                    if (fakeCamPlayerTF != NULL && fakeCamEnemyTF != NULL) {
                        Vector3 fakeCamPlayerPos = Transform_INTERNAL_GetPosition(fakeCamPlayerTF);
                        Vector3 fakeCamEnemyPos = Transform_INTERNAL_GetPosition(fakeCamEnemyTF);
                        float distance = Vector3::Distance(fakeCamPlayerPos, fakeCamEnemyPos);
                     
                        if (player != local_player) {
                          
                            if (distance < 1.6f) {
                                fakeEnemy = player;
                            }
                        }
                    }
                }
	        }
        }
		
		if(xxx){
		void* Match = Curent_Match(); {
            void* LocalPlayer = GetLocalPlayer(Match);
            
            if(LocalPlayer) {
				void* closestEnemy = GetClosestEnemy(Match);
				
			if(closestEnemy) {
                    
					Vector3 EnemyLocation = GetHeadPosition(closestEnemy);
					Vector3 PlayerLocation = CameraMain(LocalPlayer);
					Vector3 CenterWS = GetAttackableCenterWS(LocalPlayer);
					
					Quaternion PlayerLook = GetRotationToLocation(GetHeadPosition(closestEnemy), 0.1f, PlayerLocation);
					Quaternion PlayerLook2 = GetRotationToLocation(GetHipPosition(closestEnemy), 0.1f, PlayerLocation);
					Quaternion PlayerLook3 = GetRotationToLocation(GetToePosition(closestEnemy), 0.1f, PlayerLocation);
					
					float distance = Vector3::Distance(CenterWS, EnemyLocation);
					
					Vector3 LocalPlayerPos = GetHeadPosition(LocalPlayer);
					Vector3  PlayerPos    = GetHeadPosition(closestEnemy);
					
					bool scope = get_IsSighting(LocalPlayer);
					bool agachado = get_IsCrouching(LocalPlayer);
					bool firing = get_IsFiring(LocalPlayer);
					bool caido = get_IsDieing(closestEnemy);
					
					
					
					bool dirigindo = IsDriver(LocalPlayer);
  if (TelecarPro && distance < 105.0f && dirigindo) {

    // INICIO DO TELEPORTE
    void *_TeleCarTP = Component_GetTransform(closestEnemy);
    if (_TeleCarTP != NULL) {
        Vector3 TeleCarTP =
                Transform_INTERNAL_GetPosition(_TeleCarTP) - (GetForward(_TeleCarTP) * 0.0f);

        void* LocalCar = GetLocalCar(LocalPlayer);
        if (LocalCar != NULL) {

            Transform_INTERNAL_SetPosition(Component_GetTransform(LocalCar), Vvector3(TeleCarTP.X, TeleCarTP.Y + 3.0f, TeleCarTP.Z ));

        }

    }
    // FIM DO TELEPORTE


}
// TELEPORTE CAR

        if (telekill) {
            void *_MountTF = Component_GetTransform(closestEnemy);
            if (_MountTF != NULL) {
                Vector3 MountTF =
                        Transform_INTERNAL_GetPosition(_MountTF) -
                        (GetForward(_MountTF) * 0.0f);
                Transform_INTERNAL_SetPosition(Component_GetTransform(LocalPlayer),
                                               Vvector3(MountTF.X, MountTF.Y + 1.0f,
                                                        MountTF.Z));
            }
        }

                        if (EspFire ) {
							        void *imo = get_imo(LocalPlayer);
                            if (imo != NULL ) {
                                set_esp(imo, CenterWS, PlayerPos);
                                 }
                        }


                                 if (espNames) {
                
					monoString* count = FormatCount((enemyCountAround + botCountAround)-1);
				
					ShowDynamicPopupMessage(count);
					
					           }

                    int tmpEnemyCountAround = 0;
                    int tmpBotCountAround = 0;

                    monoDictionary<uint8_t *, void **> *players = *(monoDictionary<uint8_t *, void **> **) ((long) Match + 0x44);
                    for (int u = 0; u < players->getNumValues(); u++) {
                    void *closestEnemy = players->getValues()[u];

                    enemyCountAround = tmpEnemyCountAround;
                    botCountAround = tmpBotCountAround;

                    if (closestEnemy != NULL && closestEnemy != LocalPlayer && !get_isLocalTeam(closestEnemy) && get_isVisible(closestEnemy) && get_isAlive(closestEnemy)) {

                    if (closestEnemy != NULL) {
                    bool isBot = *(bool*)((uintptr_t)closestEnemy + Global.IsClientBot);
                    if (isBot) {
                    ++tmpBotCountAround;
                    } else {
                    ++tmpEnemyCountAround;
                    }
                 }
              }
            
         }
		     
						
					
					
					if (espNames) {
						          bool ind = *(bool *) (
                                    (uintptr_t) closestEnemy +
                                    Global.IsClientBot);
                            void *ui = CurrentUIScene();

                            if (ui != NULL) {
                                if (ind) {
                                    monoString *nick = get_NickName(closestEnemy);
                                    monoString *distances = U3DStrFormat(distance);
                                    AddTeammateHud(ui, nick, distances);
                                } else {
                                    monoString *nick = get_NickName(closestEnemy);
                                    monoString *distances = U3DStrFormat2(distance);
                                    AddTeammateHud(ui, nick, distances);
                                }
                            }
                        }

					
			       		if(espGranada) {
						                GrenadeLine_DrawLine(Grenade2, LocalPlayerPos, LocalPlayerPos,
                                                 Vector3(0, 1, 0) * 0.6);
                            ((void (*)(void *, Color)) getRealOffset(0x29141F4))(Render2,
                                                                                 Color::Green());
                            ((void (*)(void *, Color)) getRealOffset(0x2914298))(Render2,
                                                                                 Color::Blue());
					            if (Render2) {
                                LineRenderer_Set_PositionCount(Render2, 0x2);
                                LineRenderer_SetPosition(Render2, 0, LocalPlayerPos);
                                LineRenderer_SetPosition(Render2, 1, PlayerPos);
          }
					}
					
					if (aimAuto) {
						set_aim(LocalPlayer, PlayerLook);
					}
               
					if (scope && aimMirar) {
						set_aim(LocalPlayer, PlayerLook);
					}
					
					if (agachado && aimAgachar) {
						set_aim(LocalPlayer, PlayerLook);
					}
						
					if (firing && aimAtirar) {
						set_aim(LocalPlayer, PlayerLook);
					}
				}
			}
		}
	}
	}
    get_CanvasUpdate(player);
    LateUpdate(player);
}

static bool isEspReady() {
	return false;
}

void createDataList(Response& response) {
void *player = UpdateCanvas;
        if (player != NULL) {
        void *current_match = Curent_Match();

		if (current_match != NULL) {
            void *local_player = Current_Local_Player();

			if (local_player == NULL) {
                local_player = GetLocalPlayerOrObServer();
            }

			if (local_player != NULL) {
                void *fakeCamPlayer = get_MyFollowCamera(local_player);
                void *fakeCamEnemy = get_MyFollowCamera(player);

				if (fakeCamPlayer != NULL && fakeCamEnemy != NULL) {

					if (!isEspReady()) {

						monoDictionary<uint8_t *, void **> *players = *(monoDictionary<uint8_t*, void **> **)((long)current_match + Global.Dictionary);
                        void *camera = Camera_main();
						if (players != NULL && camera != NULL && players->getNumValues() >= 1) {

							for(int u = 0; u < players->getNumValues(); u++) {
                                void* closestEnemy = players->getValues()[u];

								if (closestEnemy != NULL && closestEnemy != fakeEnemy) {

									bool alive = get_isAlive(closestEnemy);

									bool visible = get_isVisible(closestEnemy);

									bool sameteam = get_isLocalTeam(closestEnemy);
								    
									float health = get_CurHP(closestEnemy);

									if (closestEnemy != local_player && alive && visible && !sameteam) {

                                        void *HeadTF = *(void **) ((uintptr_t) closestEnemy +
                                                                   Global.HeadTF);
                                        void *HipTF = *(void **) ((uintptr_t) closestEnemy +
                                                                  Global.HipTF);
                                        void *Dedo = *(void **) ((uintptr_t) closestEnemy +
                                                                 Global.HeadTF);
                                        void *PeD = *(void **) ((uintptr_t) closestEnemy +
                                                                Global.PeD);
                                        void *PeS = *(void **) ((uintptr_t) closestEnemy +
                                                                Global.PeS);
                                        void *RShoulder = *(void **) ((uintptr_t) closestEnemy +
                                                                      Global.RightShoulder);
                                        void *LShoulder = *(void **) ((uintptr_t) closestEnemy +
                                                                      Global.LeftShoulder);
                                        void *LeftHand = *(void **) ((uintptr_t) closestEnemy +
                                                                 Global.LeftHand);
                                        void *RightHand = *(void **) ((uintptr_t) closestEnemy +
                                                                     Global.RightHand);
                                        void *Toe = *(void **) ((uintptr_t) closestEnemy +
                                                                Global.ToeTF);
									    void *LeftLJ = *(void **) ((uintptr_t) closestEnemy +
                                                                 Global.LeftLJ);
                                        void *RightLJ = *(void **) ((uintptr_t) closestEnemy +
                                                                     Global.RightLJ);

                                         if (HeadTF != NULL && HipTF != NULL && Dedo != NULL &&
                                            PeD != NULL && PeS != NULL && RShoulder != NULL &&
                                            LShoulder != NULL && LeftHand != NULL  && RightHand != NULL && Toe != NULL) {

                                            Vector3 Head = Transform_INTERNAL_GetPosition(HeadTF);
                                            Vector3 Hip = Transform_INTERNAL_GetPosition(HipTF);
                                            Vector3 DedoTF = Transform_INTERNAL_GetPosition(Dedo);
                                            Vector3 Ped = Transform_INTERNAL_GetPosition(PeD);
                                            Vector3 Pes = Transform_INTERNAL_GetPosition(PeS);
                                            Vector3 RShoulderr = Transform_INTERNAL_GetPosition(
                                                    RShoulder);
                                            Vector3 LShoulderr = Transform_INTERNAL_GetPosition(
                                                    LShoulder);
                                            Vector3 RightHand1 =Transform_INTERNAL_GetPosition(RightHand);
                                            Vector3 LeftHand1 = Transform_INTERNAL_GetPosition(LeftHand);
                                            Vector3 ToeTF = Transform_INTERNAL_GetPosition(Toe);
											Vector3 RightLJT =Transform_INTERNAL_GetPosition(RightLJ);
                                            Vector3 LeftLJT = Transform_INTERNAL_GetPosition(LeftLJ);




                                            Vector3 PositionHead = WorldLocToScreenPoint(camera,
                                                                                         Head);
                                            if (PositionHead.Z < -1) continue;

                                            Vector3 PositionHip = WorldLocToScreenPoint(camera,
                                                                                        Hip);
                                            if (PositionHip.Z < -1) continue;

                                            Vector3 PositionDedoS = WorldLocToScreenPoint(camera,
                                                                                          DedoTF);
                                            if (PositionDedoS.Z < -1) continue;

                                            Vector3 PositionPeD = WorldLocToScreenPoint(camera,
                                                                                        Ped);
                                            if (PositionPeD.Z < -1) continue;

                                            Vector3 PositionPeS = WorldLocToScreenPoint(camera,
                                                                                        Pes);
                                            if (PositionPeS.Z < -1) continue;

                                            Vector3 PositionRShoulder = WorldLocToScreenPoint(
                                                    camera, RShoulderr);
                                            if (PositionRShoulder.Z < -1) continue;

                                            Vector3 PositionLShoulder = WorldLocToScreenPoint(
                                                    camera, LShoulderr);
                                            if (PositionLShoulder.Z < -1) continue;

                                            Vector3 PositionRightHand = WorldLocToScreenPoint(camera,
                                                                                             RightHand1);
                                            if (PositionRightHand.Z < -1) continue;

                                            Vector3 PositionLeftHand = WorldLocToScreenPoint(camera,
                                                                                              LeftHand1);
                                            if (PositionLeftHand.Z < -1) continue;

                                            Vector3 PositionToe = WorldLocToScreenPoint(camera,
                                                                                        ToeTF);
                                            if (PositionToe.Z < -1) continue;

											Vector3 PositionRJ = WorldLocToScreenPoint(camera,
                                                                                             LeftLJT);
                                            if (PositionRightHand.Z < -1) continue;

                                            Vector3 PositionLJ= WorldLocToScreenPoint(camera,
                                                                                              RightLJT);
                                            if (PositionLeftHand.Z < -1) continue;

											if (PositionToe.Z < -1) continue;
                              	
											
											Vector3 CenterWS = GetAttackableCenterWS(local_player);

											
											if(!get_IsDieing(closestEnemy)){
											
											        // ENVIA PARA A ESP AS INFO
                  PlayerData* data = &response.Players[response.PlayerCount];
                 data->HeadLocation = PositionHead;
              
				 data->PositionHip = PositionHip;
				 data->PositionDedoS = PositionDedoS;
				 data->PositionPeD = PositionPeD;
				 data->PositionPeS = PositionPeS;
				 data->PositionRShoulder = PositionRShoulder;
				 data->PositionLShoulder = PositionLShoulder;
				 data->PositionRightHand = PositionRightHand;
				 data->PositionLeftHand = PositionLeftHand;
				 data->PositionToe = PositionToe;
			     data->PositionRJ = PositionRJ;
				 data->PositionLJ = PositionLJ;
			     data->CenterWS = CenterWS;
				 data->HeadRaw = Head;
				 data->Health = health;
				 ++response.PlayerCount;

											
											
    }                                        
}
}
}
}
}
}
}
}

}

}



}



void (*DoUpdate)(void* Counter); // COW.FpsCounter

void _DoUpdate(void* Counter) {
    DoUpdate(Counter);
    if (Counter) {
        counterFPS =  *(int*)((uint64_t)Counter + 0x14);
    }
}



bool(*black)(void* _this);
bool _black(void* _this){
    return false;
}

void(*initializeRank)(void* _this);
void _InitializeRank(void* _this) {
    if (_this != NULL) {
        return;
    }
    return initializeRank(_this);
}


void(*entermatch)(void* _this);
void _entermatch(void* _this){
    if (entermatch != NULL) {
        return;
    }
    return entermatch(_this);
}

void(*entermatchrank)(void* _this);
void _entermatchrank(void* _this){
    if (entermatchrank != NULL) {
        return;
    }
    return entermatchrank(_this);
}
void(*anticheat)(void* _this);
void _anticheat(void* _this){
    if (anticheat != NULL) {
        return;
    }
    return anticheat(_this);
}

bool(*Ranked)(void* _this);
bool _Ranked(void* _this){
    if (Ranked != NULL) {
        return false;
    }
    return Ranked(_this);
}


bool(*Ranked2)(void* _this);
bool _Ranked2(void* _this){
    if (Ranked2 != NULL) {
        return true;
    }
    return Ranked2(_this);
}

bool(*askblack)(void* _this);
bool _askblack(void* _this){
    if (askblack != NULL) {
        return true;
    }
    return askblack(_this);
}




void(*entermatch2)(void* _this);
void _entermatch2(void* _this){
    if (entermatch2 != NULL) {
        return;
    }
    return entermatch2(_this);
}

void(*entermatch3)(void* _this);
void _entermatch3(void* _this){
    if (entermatch3 != NULL) {
        return;
    }
    return entermatch3(_this);
}
void(*noblack)(void* _this);
void _noblack(void* _this){
    if (noblack != NULL) {
        return;
    }
    return noblack(_this);
}

bool(*Noblack1)(void* _this);
bool _Noblack1(void* _this){
    if (Noblack1 != NULL) {
        return false;
    }
    return _Noblack1(_this);
}

void (*SendLogLeaveGame)(void *_thiz);
void _SendLogLeaveGame(void *_thiz){
    if (!_thiz){
        SendLogLeaveGame(_thiz);
        return;
    } else{
        return;
    }
}



bool(*acharpartida)(void* _this);
bool _acharpartida(void* _this){
    if (acharpartida != NULL) {
        return NULL;
    }
    return acharpartida(_this);
}

void(*acharpartida2)(void* _this);
void _acharpartida2(void* _this){
    if (acharpartida2 != NULL) {
        return;
    }
    return acharpartida2(_this);
}

void(*acharpartida3)(void* _this);
void _acharpartida3(void* _this){
    return;
}

void(*acharpartida0)(void* _this);
void _acharpartida0(void* _this){
    return;
}

void (*AntBan)(void *_thiz);
    void _AntBan(void *_thiz){
        if (_thiz) {
            return;
        }
        AntBan(_thiz);
    }
	
void (*SendCachedLogs)(void *_thiz);
void _SendCachedLogs(void *_thiz){
    if (!_thiz){
        SendCachedLogs(_thiz);
        return;
    } else{
        return;
    }
}
void (*Log)(void *_thiz);
void _Log(void *_thiz){
    if (_thiz) {
        return;
    }
    Log(_thiz);
}


bool (*ESP1)(void* _this);
bool _ESP1(void* _this) {
        return true;
}

bool (*ESP2)(void* _this);
bool _ESP2(void* _this) {
        return true;
}

bool (*ESP3)(void* _this);
bool _ESP3(void* _this) {
        return true;
}

bool (*ESP4)(void* _this);
bool _ESP4(void* _this) {
        return true;
}

bool (*ESP5)(void* _this);
bool _ESP5(void* _this) {
    return true;
}


int InitServer() {
    if (!server.Create()) {
        //LOGE("SE:1");
        return -1;
    }

    if (!server.Bind()) {
        //LOGE("SE:2");
        return -1;
    }

    if (!server.Listen()) {
        //LOGE("SE:3");
        return -1;
    }
    return 0;
}

void *CreateServer(void *) {
    if (InitServer() == 0) {
        if (server.Accept()) {
            Request request{};
            while (server.receive((void*)&request) > 0) {
                Response response{};
                if (request.Mode == Mode::InitMode) {
                    response.Success = true;
					
                } else if (request.Mode == Mode::StopMode) {
                    response.Success = true;
                    server.send((void *) &response, sizeof(response));
                    server.Close();
                    pthread_exit(nullptr);
					
                } else if (request.Mode == Mode::HackMode) {
					response.Success = true;
                } else if (request.Mode == Mode::ESPMode) {
                    SWidth = request.ScreenWidth;
                    SHeight = request.ScreenHeight;
                    response.PlayerCount = 1;
                    createDataList(response);
                    response.Success = true;

                } else if (request.Mode == m_Features::g_xxx) {
                    xxx = request.m_IsOn;
                    response.Success = true;
					
                }else if (request.Mode == m_Features::g_aimAuto) {
					LOGI("SUCESS");
                    aimAuto = request.m_IsOn;
                    response.Success = true;
					
                } else if (request.Mode == m_Features::g_aimAtirar) {
                    aimAtirar = request.m_IsOn;
                    response.Success = true;
					
                } else if (request.Mode == m_Features::g_aimMirar) {
                    aimMirar = request.m_IsOn;
                    response.Success = true;
					
                } else if (request.Mode == m_Features::g_aimAgachar) {
                    aimAgachar = request.m_IsOn;
                    response.Success = true;
					
                } else if (request.Mode == m_Features::g_aimMirar) {
                    aimMirar = request.m_IsOn;
                    response.Success = true;
					
                } else if (request.Mode == m_Features::g_espNames) {
                    espNames = request.m_IsOn;
                    response.Success = true;
					
                } else if (request.Mode == m_Features::g_espAlerta) {
                    espAlerta = request.m_IsOn;
                    response.Success = true;
					
                } else if (request.Mode == m_Features::g_espGranada) {
                    espGranada = request.m_IsOn;
                    response.Success = true;
					
                }else if (request.Mode == m_Features::g_telekill) {
                    telekill = request.m_IsOn;
			     	if(telekill){
		          	hexPatches.ghost.Modify();
                    } else {
                   hexPatches.ghost.Restore();
		             }
                    response.Success = true;
					
                } else if (request.Mode == m_Features::g_EspFire) {
                    EspFire = request.m_IsOn;
                    response.Success = true;
					
                } else if (request.Mode == m_Features::g_TelecarPro) {
                    TelecarPro = request.m_IsOn;
                    response.Success = true;
                }  else if (request.Mode == m_Features::g_nightmode) {
			      nightmode = request.m_IsOn;
					    if(nightmode){
		          	hexPatches.NightMod.Modify();
                     } else {
                       hexPatches.NightMod.Restore();
		             }
                    response.Success = true;
					
                }else if (request.Mode == m_Features::g_fly) {
		            fly = request.m_IsOn;
					    if(fly){
		          	hexPatches.FlyC.Modify();
                   } else {
                  hexPatches.FlyC.Restore();
		             }
                    response.Success = true;
					
                }else if (request.Mode == m_Features::g_under) {
					
					
                    under = request.m_IsOn;
					    if(under){
		            	hexPatches.UnderC.Modify();
                   } else {
                    hexPatches.UnderC.Restore();
		          }
                    response.Success = true;
                }else if (request.Mode == m_Features::g_medkitrun) {
					
					
                    medkitrun = request.m_IsOn;
					    if(medkitrun){
		            	hexPatches.MedKitRunning.Modify();
		          	hexPatches.MedKitRunning2.Modify();
                       } else {
                     hexPatches.MedKitRunning.Restore();
		         	hexPatches.MedKitRunning2.Restore();
		           }
                    response.Success = true;
                }else if(request.Mode == m_Features::g_speedhack){
                    
                  Speed = request.m_IsOn;
                 
                 if(Speed){
                   hexPatches.Speed4x.Modify();
				   hexPatches.antiSpeed.Modify();
                  } else {
                  hexPatches.Speed4x.Restore();
				  hexPatches.antiSpeed.Restore();
                  }
				  response.Success = true;
				  
				
				  } else if(request.Mode == m_Features::g_speedhack100x){
                    
                    iSpeed100x = request.m_IsOn;
                 
                 if(iSpeed100x){
                   hexPatches.Speed100x.Modify();
                  } else {
                  hexPatches.Speed100x.Restore();
				  
                  }
				  response.Success = true;
				  
				   } 
				
                server.send((void*)& response, sizeof(response));
            }
        }
    }
    return nullptr;
}




void *KLoad(void *) {
    while (true) {
        if (getRealOffset(0) != 0) {
			HOOK(0x1F5FB18, _DoUpdate,DoUpdate); // FPS counter
			HOOK(0x83CCFC, _LateUpdate,LateUpdate); // LateUpdate
			MSHookFunction((void *)getRealOffset(Global.GrenadeLine_Update), (void *)GrenadeLine_Update, (void **)&_GrenadeLine_Update);
       
			
			
	 
	
	


	hexPatches.MedKitRunning = MemoryPatch("libil2cpp.so", 0x14D3008, "\x01\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexPatches.MedKitRunning2 = MemoryPatch("libil2cpp.so", 0x83C5D4, "\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);

  



    hexPatches.NightMod = MemoryPatch(("libunity.so"), 0x2CB920, "\x00\x00\x80\xBF", 4);

    hexPatches.WallStone1 = MemoryPatch("libunity.so", (0xAD74A8), "\xC9\x3C\x8E\xBF", 4);
    hexPatches.WallStone2 = MemoryPatch("libunity.so", (0xAD74B8), "\xC9\x3C\x8E\xBF", 4);
    hexPatches.WallStone3 = MemoryPatch("libunity.so", (0xAD74E8), "\xC9\x3C\x8E\xBF", 4);


	
hexPatches.ghost = MemoryPatch("libil2cpp.so", 0xD23F34, "\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);

    hexPatches.Speed1000x = MemoryPatch("libunity.so", 0x33D074, "\xFF\xFF\x31\x3F", 4);
    hexPatches.Speed100x = MemoryPatch("libunity.so", 0x33D074, "\xE9\x26\x31\x3E", 4);
  
	hexPatches.Speed2x = MemoryPatch("libil2cpp.so", 0xC2EDFC, "\x82\x0F\x43\xE3\x1E\xFF\x2F\xE1", 8);
    hexPatches.Speed3x = MemoryPatch("libil2cpp.so", 0xC2EDFC, "\x83\x0F\x43\xE3\x1E\xFF\x2F\xE1", 8);
    hexPatches.Speed4x = MemoryPatch("libil2cpp.so", 0xC2EDFC, "\x84\x0F\x43\xE3\x1E\xFF\x2F\xE1", 8);
    hexPatches.Speed5x = MemoryPatch("libil2cpp.so", 0xC2EDFC, "\x85\x0F\x43\xE3\x1E\xFF\x2F\xE1", 8);
	
	hexPatches.antiSpeed = MemoryPatch("libil2cpp.so", 0x840AD0, "\x00\xF0\x20\xE3", 4);
 
 


    hexPatches.FlyC = MemoryPatch("libil2cpp.so", 0x2011F90, "\x00\x00\x41\x42", 4);
	hexPatches.UnderC = MemoryPatch("libil2cpp.so", 0x2011F90,"\x00\x00\x40\xC0", 4);

	
	
	
    HOOK(0x14F07F8,_black, black); // 15 //1.60 //public static void LogAndroidApplicationDetection(List`1<int> installedIDs);.  
    HOOK(0x14F1EC4,_black, black); // 16 //1.60  //public static CMOD_OPT LogEnterGame()  
    HOOK(0x14EE87C,_black, black); // 12 //1.60 //public static void LogScanIAPInventoryResult
  
	HOOK(0x5DAA30,_black, black); // 12 //1.60//public EAccount.BlacklistOpType get_ban_type() { } //BlacklistOpReq //ctor +109
 
	MSHookFunction((void*)getRealOffset(0x1EE268C), (void*)_entermatch, (void**)&entermatch); //public static bool IsPackageInstalled(string bundleIdentifier) { }
    MSHookFunction((void*)getRealOffset(0x1EE583C), (void*)_entermatch, (void**)&entermatch); //public static bool CheckFileExists(string fileName) { }
    	
	 HOOK(0x35F0A04, _anticheat, anticheat);
	  HOOK(0x66232C, _anticheat, anticheat);
	   HOOK(0x5E0D70, _anticheat, anticheat);
	    HOOK(0x35F0AA4, _anticheat, anticheat);
		 HOOK(0x12E7B64, _anticheat, anticheat);
		  
HOOK(0x2929338, _ESP1, ESP1);
    HOOK(0xD85BD8, _ESP2, ESP2);
    HOOK(0x29E6B8C, _ESP3, ESP3);
    HOOK(0x29E6AFC, _ESP5, ESP5);
    HOOK(0x808, _ESP4, ESP4);
		
// PRA NÃO CAIR
	pthread_exit(nullptr);
        }
    }
    return nullptr;
}

extern "C"
void __attribute__ ((constructor)) OnLoad() {
	pthread_t ptid;
	pthread_create(&ptid, nullptr, CreateServer, nullptr);
	
	pthread_t ptid2;
	pthread_create(&ptid2, nullptr, KLoad, nullptr);
	LOGI("pthread whiling sucess");
}
