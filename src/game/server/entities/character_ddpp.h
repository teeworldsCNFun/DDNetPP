#ifndef IN_CLASS_CHARACTER
#include <deque>
#include <engine/antibot.h>
#include <game/generated/protocol.h>
#include <game/generated/server_data.h>
#include <game/server/entities/stable_projectile.h>
#include <game/server/entity.h>
#include <game/server/save.h>

#include <game/gamecore.h>

#include "dummy/blmapchill_police.h"
#include <vector>

#include "drop_pickup.h"
#include "weapon.h"
class CCharacter : public CEntity
{
#endif

private:
	/*

		DDNet++

	*/

	void SnapCharacterDDPP();
	void HandleTilesDDPP(int Index);
	void DDPPDDRacePostCoreTick();

	// also: es gibt eine start- und endposition f�r die augen
	// ebenso wie eine startzeit und eine endzeit (bzw. eigentlich nur wie lange die animation geht)

	// z.B. startzeit waere jetzt, die zeit wie lange die animation geht w�re 1 sekunde
	// dann waere m_AngleTickStart = Server()->Tick() // = die jetzige zeit
	// und m_AngleTickTime = Server()->TickSpeed() // eine sekunde

	// m_AngleFrom ist die startposition, also z.B. 0(grad) (dann guckt er glaub ich nach rechts)
	// m_AngleTo dann z.B. 90(grad) (guckt nach unten)
	// d.h. er dreht sich von jetzt bis in einer sekunde um 90(grad)
	float m_AngleFrom; //
	float m_AngleTo;
	int m_AngleTickStart;
	int m_AngleTickTime;
	int m_AngleTickNext; // und das ist die zeit, wann die n�chste animation beginnen soll

	int m_EmoteTickNext;
	int m_EmoteTickNextFast;
	int m_HookTickNext;
	//int m_AimbotSwitchTick;
	bool m_AimbotMode; // wenn true, dann ist aimbot aktiviert, bei false halt nicht wozu? damit man weiss ob der bot den aimbot an hat oder halt random durch die gegend guckt? ne brauchts eig nich oder? lass erstmal ohne
	bool m_MoveMode;
	bool m_LeftMM;

	bool m_DummyShowRank;
	bool m_DummyFreezed;
	bool m_DummyHammer;

	bool m_getxp;

	int m_FreezeKillNext;
	int m_MoveTick;
	int m_LastMoveDirection;
	int m_StopMoveTick;
	bool m_IsFreeShopBot;
	void ClearFakeMotd();
	void SendShopMessage(const char *pMsg);
	int m_aWeaponsBackup[NUM_WEAPONS][2];
	bool m_WeaponsBackupped;

public:
	bool m_DummyFinished;
	int m_DummyFinishes;
	int m_LastIndexTile;
	int m_LastIndexFrontTile;
	vec2 MousePos() { return vec2(m_Core.m_Input.m_TargetX + m_Pos.x, m_Core.m_Input.m_TargetY + m_Pos.y); };
	int64_t m_AliveSince;
	bool m_IsSpecHF;
	vec2 GetPosition() { return m_Core.m_Pos; } //proudly mede by ChillerDragon
	void TakeHammerHit(CCharacter *pFrom); //ddpp implemented from fng2
	bool m_OnFire;
	bool m_WasInRoom;
	void DDPP_Tick();
	void DDPP_FlagTick();
	void CosmeticTick();
	void SpawnDDPP(CPlayer *pPlayer, vec2 Pos);
	void PostSpawnDDPP(CPlayer *pPlayer, vec2 Pos);
	void DDPPPostCoreTick();
	bool DDPPTakeDamage(vec2 Force, int Dmg, int From, int Weapon);
	int DDPP_DIE(int Killer, int Weapon, bool fngscore = false);
	void BlockTourna_Die(int Killer);
	void DummyTick();
	void PvPArenaTick();

	//usefull everywhere
	void DDPP_TakeDamageInstagib(int Dmg, int From, int Weapon);
	void MoveTee(int x, int y);
	void ChillTelePort(float X, float Y);
	void ChillTelePortTile(int X, int Y);
	void FreezeAll(int seconds);
	bool HasWeapon(int weapon);
	void KillSpeed();
	int GetAimDir();
	bool InputActive();

	//Chillintelligenz
	void CITick();
	void CIRestart();
	int CIGetDestDist();

	int m_ci_freezetime;

	//Block
	int BlockPointsMain(int Killer, bool fngscore = false);
	void XpOnKill(int Killer);
	void BlockSpawnProt(int Killer);
	void BlockQuestSubDieFuncBlockKill(int Killer);
	void BlockQuestSubDieFuncDeath(int Killer);

	/*
		QuestHammerHit

		gets called on hammer hit
	*/
	void QuestHammerHit(CCharacter *pTarget);
	void QuestShotgun();
	void QuestGrenade();
	void QuestRifle();
	void QuestNinja();
	void QuestFireWeapon();
	void DDPPFireWeapon();
	void PoliceHammerHit(CCharacter *pTarget);
	void DDPPHammerHit(CCharacter *pTarget);
	bool IsHammerBlocked();
	void DDPPGunFire(vec2 Direction);
	bool SpecialGunProjectile(vec2 Direction, vec2 ProjStartPos, int Lifetime);
	bool FreezeShotgun(vec2 Direction, vec2 ProjStartPos);

	/*
		KillingSpree

		was called BlockKillingSpree once
		but now handles all ddnet++ gametype sprees.
		So block and minigames (fng/vanilla).
		But not other gametypes as instagib or fng (sv_gametype or other server cfgs).
	*/
	void KillingSpree(int Killer);

	//block tourna

	int m_BlockTournaDeadTicks;

	//blockwave
	int BlockWaveFreezeTicks;

	//survival
	void SurvivalSubDieFunc(int Killer, int weapon);

	//instagib
	int m_SpreeTimerState; //0 = ready 1 = running (i know could be bool for now but maybe ill add different modes like count from spawn or count from first kill)
	void InstagibSubDieFunc(int Killer, int Weapon);
	void InstagibKillingSpree(int KillerID, int Weapon);
	bool m_UpdateInstaScoreBoard;
	void MoneyTile();
	void MoneyTilePolice();
	void MoneyTilePlus();
	void MoneyTileDouble();
	int m_survivexpvalue;
	bool m_hammerfight; //used for the rcon command has nothing todo with arenas yet
	//bool m_IsHammerarena; //used for chillerdragons hammerfight arena '/hammerfight'
	//bool m_Hammerarena_exit_request;
	//int m_Hammerarena_exit_request_time;
	bool m_IsPVParena;
	bool m_pvp_arena_exit_request;
	int m_pvp_arena_tele_request_time;
	bool m_isHeal;
	bool m_freezeShotgun;
	bool m_FreezeLaser;
	bool m_DestroyLaser;
	bool m_isDmg;
	int64_t m_FirstFreezeTick;
	bool m_fake_super;
	bool m_Godmode;
	bool m_Fire;
	bool m_DDPP_Finished;
	/*
		ForceFreeze

		mede by ChillerDragon too freeze no matter what used for freezing while freezed (for example for tournaments to have all same freeze time even if some wer freezed at tourna start)
		WARNING FORCE FREEZE ISNT ABLE TO OVERWRITE FREEZE AS IT SHOULD!!!
		it can still be used to bypass super but thats all i guess
	*/
	bool ForceFreeze(int Seconds);

	//trading stuff (stock market)
	//int m_StockMarket_item_Cucumbers; //player.h

	//weapons in kill messages

	int m_LastHitWeapon;
	int m_OldLastHookedPlayer;
	bool m_GotTasered;

	// drop pickups
	void DropHealth(int amount = 1);
	void DropArmor(int amount = 1);
	void DropWeapon(int WeaponID);
	bool m_aDecreaseAmmo[NUM_WEAPONS];

	void DropLoot();

	bool SetWeaponThatChrHas();

	//spawn weapons
	void SetSpawnWeapons();

	void BulletAmounts();
	int m_GunBullets;
	int m_ShotgunBullets;
	int m_GrenadeBullets;
	int m_RifleBullets;

	//spooky ghost
	void SetSpookyGhost();
	void UnsetSpookyGhost();
	void SaveRealInfos();
	bool m_CountSpookyGhostInputs;

	int m_TimesShot;

	int m_aSpookyGhostWeaponsBackup[NUM_WEAPONS][2];
	bool m_SpookyGhostWeaponsBackupped;
	int m_aSpookyGhostWeaponsBackupGot[NUM_WEAPONS][2];

	//room by supermoderator invited
	bool m_HasRoomKeyBySuperModerator;
	bool DDPP_Respawn();

	//harvest plant
	bool m_CanHarvestPlant;
	bool m_HarvestPlant;

	// shop
	bool m_EnteredShop; // TODO: move to CShop ?

	//bank
	bool m_InBank;

	//jail
	bool m_InJailOpenArea;

	//bomb
	bool m_IsBombing;
	bool m_IsBomb;
	bool m_IsBombReady;
	int m_BombPosX;
	int m_BombPosY;

	//battlegores
	void KillFreeze(bool unfreeze);

	bool HandleConfigTile(int Type);

	// finite cosmetics
	bool m_Rainbow;
	bool m_Bloody;
	bool m_StrongBloody;
	bool m_WaveBloody;
	bool m_WaveBloodyGrow;
	int m_WaveBloodyStrength;
	bool m_Atom;
	bool m_Trail;
	bool m_autospreadgun;
	bool m_ninjasteam;
	bool m_RandomCosmetics; // admin only cosmetic doesn't have to be backupped or anything. Because it won't check if u have these cosmetics unlocked.

	bool m_HomingMissile;

	// atom vars (not to be confused with atom wars) <--- made chillidreghuhn giggle xd
	std::vector<CStableProjectile *> m_AtomProjs;
	int m_AtomPosition;

	// trail vars
	std::vector<CStableProjectile *> m_TrailProjs;
	struct HistoryPoint
	{
		vec2 m_Pos;
		float m_Dist;

		HistoryPoint(vec2 Pos, float Dist) :
			m_Pos(Pos), m_Dist(Dist) {}
	};
	std::deque<HistoryPoint> m_TrailHistory;
	float m_TrailHistoryLength;

	enum
	{
		DUMMYMODE_DEFAULT = 0,
		DUMMYMODE_ADVENTURE = -7,
		DUMMYMODE_QUEST = 36,
	};

	//dummymode public vars (used by survival 34)
	int m_DummyDir;

	//dummymode 25 FNN vars
	bool m_Dummy_nn_ready;
	bool m_Dummy_nn_touched_by_humans;
	bool m_Dummy_nn_stop;
	int m_Dummy_nn_ready_time;
	int m_FNN_CurrentMoveIndex;
	int m_aRecMove[FNN_MOVE_LEN];
	int m_FNN_ticks_loaded_run;
	int m_FNN_start_servertick;
	int m_FNN_stop_servertick;
	vec2 m_StartPos;
	// void TestPrintTiles(int Index);

	//dummymode 105 vars
	bool m_Dummy105_move_left;

	//dummymode 104 vars
	bool m_Dummy104_panic_hook;
	int m_Dummy104_angry;
	bool m_Dummy104_rj_failed;

	//dummymode 27 vars (BlmapChill police guard)
	bool m_Dummy27_IsReadyToEnterPolice;
	int m_Dummy27_loved_x;
	int m_Dummy27_loved_y;
	int m_Dummy27_lower_panic;
	int m_Dummy27_speed;
	int m_Dummy27_help_mode; //0=off 1=right side 2=right_side_extreme
	bool m_Dummy27_help_hook;

	//dummymode 31 vars (ChillBlock5 police guard)
	bool m_Dummy_SpawnAnimation;
	int m_Dummy_SpawnAnimation_delay;
	bool m_Dummy_GetSpeed;
	bool m_Dummy_GotStuck;
	bool m_Dummy_ClosestPolice;
	int m_Dummy_dmm31;
	int m_Dummy_AttackMode;

	//dummymode 32 (Blampchill police racer)
	int m_DummyGrenadeJump;
	bool m_DummyTouchedGround;
	bool m_DummyAlreadyBeenHere;
	bool m_DummyStartGrenade;
	bool m_DummyUsedDJ;
	int m_DummySpawnTeleporter; // 1 = left, 2 = middle, 3 = right (the totele 9 at spawn)s

	//dummy 29 vars !!!!! also use 18 vars in 29 xD

	CDummyBlmapChillPolice *m_pDummyBlmapChillPolice;

	CNetObj_PlayerInput *Input() { return &m_SavedInput; };
	CNetObj_PlayerInput *LatestInput() { return &m_LatestInput; };
	void Fire(bool Fire = true);
	int GetReloadTimer() { return m_ReloadTimer; }

	//dummymode 29 vars (ChillBlock5 blocker)
	int m_DummyFreezeBlockTrick;
	int m_Dummy_trick_panic_check_delay;
	bool m_Dummy_start_hook;
	bool m_Dummy_speedright; //used to go right from the left side of the freeze if there is enoigh speed
	bool m_Dummy_trick3_panic_check;
	bool m_Dummy_trick3_panic;
	bool m_Dummy_trick3_start_count;
	bool m_Dummy_trick3_panic_left;
	bool m_Dummy_trick4_hasstartpos;
	bool m_Dummy_lock_bored; //tricky way to keep the bored bool activatet
	bool m_Dummy_doBalance;
	bool m_Dummy_AttackedOnSpawn;
	bool m_Dummy_bored_shootin;
	bool m_Dummy_bored_cuz_nothing_happens;
	bool m_Dummy_movement_to_block_area_style_window; //yep dis is too long
	bool m_Dummy_planned_movment; // belongs to:   m_Dummy_movement_to_block_area_style_window

	//dummy 19 vars
	int m_DummyDriveDuration;

	//dummymode 23 vars

	int m_Dummy_help_m8_before_hf_hook; //yep a bool int timer
	bool m_Dummy_help_emergency; //activate if boot falls of platform while helping
	bool m_Dummy_help_no_emergency; //this is just used to check if the bot planned to be in this situation. this bool is just used for not activating m_Dummy_help_emergency
	bool m_Dummy_hook_mate_after_hammer; //after unfreezing a mate with hammer hold him with hook
	bool m_Dummy_help_before_fly; //to help at the mate if he gets freeze before the hammerfly started
	bool m_Dummy_2p_panic_while_helping; //if the bot falls of the platform while helping at the 2p part
	bool m_Dummy_panic_balance; //hammerhit part struggle -> balance
	bool m_Dummy_mate_failed; //a �var which toggles the dummy_2p_state value -2
	bool m_Dummy_hh_hook; //check for hook in hammerhit at end
	bool m_Dummy_collected_weapons; //ob er nochmal zu den waffen hochfliegen muss
	bool m_Dummy_mate_collected_weapons; //ob auch der race mate waffen hat
	bool m_Dummy_rjumped2; //ob der dummy grad den rj2 hinter sich hat
	bool m_Dummy_dd_hook; //hier hookt er im 2p part                          nvm i renamed in 2p not dd      ignore -> [CARE USED OLD VAR FROM OLD SYSTEM FOR NEW SYSTEM CHECK THIS STUFF IF USE OLD SYSTEM AGIAN!!!!]
	bool m_Dummy_dd_helphook; //just a helphook bool ... used for start and stoop hooking while helping at the dummydrag part
	bool m_Dummy_2p_hook; //same as m_Dummy_dd_hook but in new sys
	bool m_Dummy_2p_hook_grabbed; // for better resetting if part failed
	int m_Dummy_2p_state; //Maybe cool stuff comign with it
	int m_Dummy_mode23; //yes dummymode23 has his own modes o.O
	int m_Dummy_nothing_happens_counter; // counts all the nonaction lol
	int m_Dummy_panic_weapon; // if the bot has panic (nothing happens -> panic mate coudl get bored)  change the wepaon to this var value
	int m_Dummy_sent_chat_msg; // 0 == noMsgDisTick 1 == MsgDisTick              [to send a chat message just 1 time]
	int m_Dummy_mate_help_mode; //how the bot shoudl help
	int m_Dummy_movement_mode23; //a movement mode for mode23
	//int m_Dummy_rj_fails_counter;		//the hammerfly and weapon check sometimes causes fails and the dummy tries to rocketjump but is not abel to do it. this counter is used to detect this problem and kill the bot is detected

	//bool m_Dummy_2p_hammer1;			//Check if he did the first hammer

	//bool m_Dummy_rj_ready;				//check if the bot has the perfect position to make the rocketjump

	//notstand vars fuer mode 18 (also used in 29)
	bool m_Dummy_jumped; //gesprungen wenn der notstand ausgetufen wird
	bool m_Dummy_hooked; //gehookt wenn der notstand ausgerufen wird
	bool m_Dummy_moved_left; //nach links gelaufen wenn der notstand ausgerufen wird
	bool m_Dummy_hook_delay; //hook delay wenn der notstand ausgerufen wurde
	bool m_Dummy_ruled; //ob der dummy in diesem leben schonmal am ruler spot war
	bool m_Dummy_pushing; //ob er jemand grad beim wayblocken aus seinem wb spot schiebt
	bool m_Dummy_emergency; // Notsand
	bool m_Dummy_wb_hooked; //ob er grad vom wayblockspot wen wayblockig hookt
	bool m_Dummy_left_freeze_full; //wenn jemand schon in die linke freeze wand geblockt wurde
	bool m_Dummy_happy; //wenn er sich auf seinem lieblings wb spot befindet
	bool m_Dummy_get_speed; //im tunnel anlauf holen wenn ausgebremst                     WARNING THIS VAR IS ALSO USED IN DUMMYMODE == 26
	bool m_Dummy_bored; //wenn dem bot langweilig wird wechselt er die wayblock taktik
	bool m_Dummy_special_defend; //dummy_mode18 mode bool
	bool m_Dummy_special_defend_attack; //sub var f�r m_Dummy_special_defend die abfr�gt ob der bot schon angreifen soll

	int m_Dummy_bored_counter; //z�hl hoch bis dem dummy lw wird

	int m_Dummy_mode18; //yes dummymode18 has his own modes o.O
	//bool mode18_main_init;              //yep one of the randomesteztes booleans in ze world
private:
#ifndef IN_CLASS_CHARACTER
}
#endif
