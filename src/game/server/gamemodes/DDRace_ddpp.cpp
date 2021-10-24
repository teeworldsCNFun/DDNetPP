/* DDRace scoped ddnet++ methods */
#include "DDRace.h"
#include "gamemode.h"
#include <engine/server.h>
#include <engine/shared/config.h>
#include <game/mapitems.h>
#include <game/server/entities/character.h>
#include <game/server/entities/flag.h>
#include <game/server/gamecontext.h>
#include <game/server/player.h>

void CGameControllerDDRace::HandleCharacterTilesDDPP(class CCharacter *pChr, int Tile1, int Tile2, int Tile3, int Tile4, int FTile1, int FTile2, int FTile3, int FTile4)
{
	// finish tile
	if(((m_TileIndex == TILE_FINISH) || (m_TileFIndex == TILE_FINISH) || FTile1 == TILE_FINISH || FTile2 == TILE_FINISH || FTile3 == TILE_FINISH || FTile4 == TILE_FINISH || Tile1 == TILE_FINISH || Tile2 == TILE_FINISH || Tile3 == TILE_FINISH || Tile4 == TILE_FINISH) && m_DDRaceState == DDRACE_STARTED)
	{
        #pragma message "Look into this teams quest finish mess"
		// m_Teams.OnCharacterFinish(pChr->GetPlayer()->GetCID()); // Quest 3 lvl 0-4 is handled in here teams.cpp
		if(pChr->GetPlayer()->m_QuestState == CPlayer::QUEST_RACE)
		{
			if(pChr->GetPlayer()->m_QuestStateLevel == 5)
			{
				if(HasFlag(pChr) != -1) //has flag
				{
					GameServer()->QuestCompleted(pChr->GetPlayer()->GetCID());
				}
				else
				{
					GameServer()->QuestFailed(pChr->GetPlayer()->GetCID());
				}
			}
			else if(pChr->GetPlayer()->m_QuestStateLevel == 9)
			{
				if(!pChr->GetPlayer()->m_QuestFailed)
				{
					GameServer()->QuestCompleted(pChr->GetPlayer()->GetCID());
				}
			}
		}

		pChr->m_DummyFinished = true;
		pChr->m_DummyFinishes++;

		/*
		char aBuf[128];
		str_format(aBuf, sizeof(aBuf), "xp [%d/1000]", pChr->GetPlayer()->GetXP());
		GameServer()->SendBroadcast(aBuf, pChr->GetPlayer()->GetCID(), 0);
		*/
	}
	// start (override)
	if(((m_TileIndex == TILE_START) || (m_TileFIndex == TILE_START) || FTile1 == TILE_START || FTile2 == TILE_START || FTile3 == TILE_START || FTile4 == TILE_START || Tile1 == TILE_START || Tile2 == TILE_START || Tile3 == TILE_START || Tile4 == TILE_START) && (m_DDRaceState == DDRACE_NONE || m_DDRaceState == DDRACE_FINISHED || (m_DDRaceState == DDRACE_STARTED && !Team() && g_Config.m_SvTeam != 3)))
	{
		pChr->GetPlayer()->m_MoneyTilePlus = true;
		if(pChr->GetPlayer()->m_QuestState == CPlayer::QUEST_RACE)
		{
			if((pChr->GetPlayer()->m_QuestStateLevel == 3 || pChr->GetPlayer()->m_QuestStateLevel == 8) && pChr->GetPlayer()->m_QuestProgressValue)
			{
				GameServer()->QuestAddProgress(pChr->GetPlayer()->GetCID(), 2);
			}
			else if(pChr->GetPlayer()->m_QuestStateLevel == 9 && pChr->GetPlayer()->m_QuestFailed)
			{
				// GameServer()->SendChatTarget(pChr->GetPlayer()->GetCID(), "[QUEST] running agian.");
				pChr->GetPlayer()->m_QuestFailed = false;
			}
		}
		pChr->m_DDPP_Finished = false;
	}
}
