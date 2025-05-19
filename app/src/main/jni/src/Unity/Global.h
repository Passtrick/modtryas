#ifndef ANDROID_MOD_MENU_GLOBAL_H
#define ANDROID_MOD_MENU_GLOBAL_H

struct {

    uintptr_t MainCameraTransform = 0x5C;  // public Transform MainCameraTransform; // 0x54  (1.60.2)
    uintptr_t Dictionary = 0x44; // protected Dictionary<byte, Player> NgEZJDq; // 0x44  (1.60.2)
     uintptr_t GetWeaponType = 0x858C18;
        ////////////////////////////////////////////////////////
    uintptr_t GrenadeLine_isVisible = 0xC;
    uintptr_t GrenadeLine_m_GrenadeLine = 0x10; // protected LineRenderer m_GrenadeLine
    uintptr_t LineRenderer_Set_PositionCount = 0x29143D4; // public void set_positionCount(int value) { }
    uintptr_t LineRenderer_SetPosition = 0x2914480; // public void SetPosition(int index, Vector3 position) { }
    uintptr_t GrenadeLine_DrawLine = 0xDF1CC8; // private void DrawLine(Vector3 throwPos, Vector3 throwVel, Vector3 gravity) { }
    uintptr_t GrenadeLine_Update = 0xDF1978; // private void Update() { }


    uintptr_t HeadTF = 0x1C8; // protected Transform JoqBDUR; // 0x1B4  (1.60.2)
    uintptr_t HipTF = 0x1CC;  // protected Transform gBb{jci; // 0x1B8 (1.60.2)
    uintptr_t HandTF = 0x1C4; // protected Transform yFayxSS; // 0x1B0 (1.60.2)
    uintptr_t EyeTF = 0x1F4; // protected Transform yvZ[NRv; // 0x1DC  (1.60.2)
    uintptr_t ToeTF = 0x1DC; // 	protected Transform `}Klj; // 0x1C4  (1.60.2)
    uintptr_t PeS = 0x1E4;  //protected Transform oporBaB; // 0x1D4 1.59
    uintptr_t PeD = 0x1E8; //protected Transform lpF[hWQ; // 0x1D81.59
    uintptr_t RightShoulder = 0x1FC; //protected Transform IcoOWF; // 0x1E4 (1.60.2)
    uintptr_t LeftShoulder = 0x1F8; // protected Transform iuhFwSC; // 0x1E0 (1.60.2)
    uintptr_t RightHand =0x1C4; // protected Transform yFayxSS; // 0x1B0 (1.60.2)
    uintptr_t LeftHand = 0x1F4; // pprotected Transform yvZ[NRv; // 0x1DC  (1.60.2)
    uintptr_t RightLJ =0x1E4; // protected Transform yFayxSS; // 0x1B0 (1.60.2)
    uintptr_t LeftLJ = 0x1E8; // pprotected Transform yvZ[NRv; // 0x1DC  (1.60.2)
/////////////////////////////////////////////////////////////////////////////////////
    
    uintptr_t IsClientBot = 0xDC; // public bool IsClientBot; // 0xC8  [v1.60.2]
    uintptr_t get_isAlive = 0x8606A4; // public bool IsCameraTrackableEntityAlive [v1.60.2]
    uintptr_t get_IsSighting = 0x871B30; // public bool get_IsSighting [v1.60.2]
	uintptr_t get_isLocalTeam = 0x819958; // public virtual bool IsLocalTeammate [v1.60.2]
	uintptr_t get_isVisible = 0x812BFC; // public override bool IsVisible [v1.60.2]
		
	uintptr_t get_IsDieing = 0x7FFAE8; // public bool get_IsDieing() { } [v1.60.2]
	uintptr_t GetAttackableCenterWS = 0x80FB18; // public override Vector3 GetAttackableCenterWS [v1.60.2]
	uintptr_t get_NickName = 0x810084; // public string get_NickName [v1.60.2]
	
	uintptr_t get_CurHP = 0x847738; // public int get_CurHP() { } [v1.60.2]
	uintptr_t get_MaxHP = 0x8477B0; // public int get_MaxHP() { } 1.57
		
	uintptr_t Current_Local_Player = 0x11CCED4; // public static Player CurrentLocalPlayer [v1.60.2]
	uintptr_t GetLocalPlayerOrObServer = 0x11CD708; // public static Player GetLocalPlayerOrObServer [v1.60.2]
	
	uintptr_t get_IsFiring = 0x7F8CC0;; // public bool IsFiring [v1.60.2]
	uintptr_t GetLocalPlayer = 0x1341F24; // private static Player GetLocalPlayer() { } [v1.60.2]
	
	uintptr_t Curent_Match = 0x11CCBB0; // public static  CurrentMatch() { } [v1.60.2]
	uintptr_t get_imo = 0x815E30; // public ytMNhlw GetActiveWeapon() { } [v1.60.2]
	uintptr_t set_esp = 0x15FDD24; // public void utKBmvc(Vector3 RvOJF{, Vector3 bQiMI) { } [v1.60.2]
	uintptr_t set_aim = 0x810F18; // public void SetAimRotation(Quaternion laYChSW) { } [v1.60.2]
    uintptr_t Camera_main = 0x27F8680; // public static Camera get_main [v1.60.2]

	uintptr_t WorldToScreenPoint = 0x27F7F90; // public Vector3 WorldToScreenPoint(Vector3 position) { } [v1.60.2]
	uintptr_t Transform_INTERNAL_GetPosition = 0x29F20D4; // private void INTERNAL_get_position [v1.60.2]
	uintptr_t Transform_INTERNAL_SetPosition = 0x29F2174; // private void INTERNAL_get_position [v1.60.2]
	

	
	uintptr_t U3DStr = 0x27A4238; // private string CreateString(sbyte* value) { } [v1.60.2]
	uintptr_t CurrentUIScene = 0x11B46DC; // public static UICOWBaseScene CurrentUIScene [v1.60.2]
	
	uintptr_t get_IsCrouching = 0x81B374; // public bool IsCrouching() { } [v1.60.2]
	uintptr_t ShowDynamicPopupMessage = 0x923BC8; // public void ShowDynamicPopupMessage(string message, float duration = 5) { } [v1.60.2]
	uintptr_t ShowPopupMessage = 0x923D08; //	public void ShowPopupMessage(string message, float duration = 2) { } [v1.60.2]
	uintptr_t AddTeammateHud = 0x93A984; // public void ShowAssistantText(string playerName, string line) { } [v1.60.2]
	uintptr_t U3DStrConcat = 0x27A2B60; // public static string Concat(string str0, string str1, string str2, string str3) { } [v1.60.2]
	uintptr_t Component_GetTransform = 0x27FA17C; // public Transform get_transform() [v1.60.2]
	uintptr_t GetForward = 0x29F2C34; // public Vector3 get_forward [v1.60.2]
    uintptr_t get_MyFollowCamera = 0x81099C; // public FollowCamera get_MyFollowCamera() [v1.60.2]
	uintptr_t WallS1 = 0xAD74A8; // UNITY BLIB
  uintptr_t WallS2 = 0xAD74B8; // UNITY BLIB
  uintptr_t WallS3 = 0xAD74E8; // UNITY BLIB
    uintptr_t GetPlayerDead = 0x811368; // public virtual bool IsLocalTeammate() { } 1.60.2

} Global;

#endif


