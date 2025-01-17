/* Teams scoped ddnet++ methods */
#include "score.h"
#include "teams.h"
#include "teehistorian.h"
#include <engine/shared/config.h>

#include "entities/character.h"
#include "player.h"

void CGameTeams::OnFinishDDPP(CPlayer *pPlayer, int mins, float secs)
{
	OnQuestFinish(pPlayer);
	if(mins > 0) // only give xp if race was at least 1 minute
	{
		if(!pPlayer->IsMaxLevel())
		{
			pPlayer->GiveXP(250);
			GameServer()->SendChatTarget(pPlayer->GetCID(), "+250 xp (finish race)");
			if(g_Config.m_SvFinishEvent == 1)
			{
				pPlayer->GiveXP(500);
				GameServer()->SendChatTarget(pPlayer->GetCID(), "+500 xp (Event-bonus)");
			}
		}
	}
}

void CGameTeams::OnQuestFinish(CPlayer *Player)
{
	//char aBuf[256];
	float time = (float)(Server()->Tick() - GetStartTime(Player)) / ((float)Server()->TickSpeed());
	if(time < 0.000001f)
		return;
	//str_format(aBuf, sizeof(aBuf),
	//	"'%s' [%d:%5.2f] total (int)[%d] (int) / 60[%d]",
	//	Server()->ClientName(Player->GetCID()), (int)time / 60,
	//	time - ((int)time / 60 * 60),
	//(int)time, //<---- seconds (total)
	//(int)time / 60); //<--- minutes (total)
	//GameServer()->SendChatTarget(Player->GetCID(), aBuf);

	if(Player->m_QuestState == CPlayer::QUEST_RACE)
	{
		if(Player->m_QuestStateLevel == 0)
		{
			GameServer()->QuestCompleted(Player->GetCID());
		}
		else if(Player->m_QuestStateLevel == 1)
		{
			if((int)time <= g_Config.m_SvQuestRaceTime1)
			{
				GameServer()->QuestCompleted(Player->GetCID());
			}
			else
			{
				GameServer()->QuestFailed(Player->GetCID());
			}
		}
		else if(Player->m_QuestStateLevel == 2)
		{
			if((int)time <= g_Config.m_SvQuestRaceTime2)
			{
				GameServer()->QuestCompleted(Player->GetCID());
			}
			else
			{
				GameServer()->QuestFailed(Player->GetCID());
			}
		}
		else if(Player->m_QuestStateLevel == 3)
		{
			GameServer()->QuestAddProgress(Player->GetCID(), 2, 1); //finish and go back to start
		}
		else if(Player->m_QuestStateLevel == 4)
		{
			if((int)time <= g_Config.m_SvQuestRaceTime3)
			{
				GameServer()->QuestCompleted(Player->GetCID());
			}
			else
			{
				GameServer()->QuestFailed(Player->GetCID());
			}
		}
	}
}
