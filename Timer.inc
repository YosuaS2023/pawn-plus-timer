/*
	Credits:
	XCore/Zxuan
	Improve code from: 4sheed (part: PPTasks_(Start/Stop)PlayerTasks)

	English: (Translate)
	To be honest, I have made a timer for global/player, but it still uses a lot of native samples.
	So now I use 4sheed's code for the player part.

	NOTE: this doesn't work with arrays. just bool/int/float

	Indonesian: 
	Sejujurnya saya telah membuat timer untuk global/player, tapi masih mengunakan banyak native samp.
	Jadi sekarang saya mengunakan kode milik 4sheed untuk bagian player nya.

	CATATAN: ini belum bisa mengunakan array. hanya bool/int/float
*/
#include <PawnPlus>


#define @Yj:@Yk:##,,) "")
#define @Yk:##%2,%3) @Ya:@Yb:@Ye:##@@@%2@@@%3)
#define @Yab:#%0#%1@@@%2@@@%3,%4,%5) @Ya:@Yb:@Ye:#%0ai#%1,%2,%3@@@%4@@@%5)
#define @Yb:@Ye:#%0#%1@@@%2@@@%3,%4) @Yb1:@Yb2:#%0#%1@@@%2@@@%3,%4)
#define @Ys:%0) _:@Yj:@Yk:##%0,,)
#define @Yb1:@Yb2:#%0#%1@@@%6:%2@@@%3,%4) @Ya:@Yb:@Ye:#%0i#%1,_:%2@@@%3@@@%4)
#define @Yb2:#%0#%1@@@%2@@@%3,%4) @Ya:@Yb:@Ye:#%0i#%1,%2@@@%3@@@%4)
#define @Ye:#%0#%1@@@@@@%3) #%0#%1)
// -------------------------------------


native pawn_call_public_s(ConstAmxString:function, const format[], AnyTag:...) = pawn_call_public;
native SetTimer_s(ConstAmxString:fName, const interval, bool:repeating) = SetTimer;

#define TIMER__%0[%1](%2) forward %0(%2); public %0(%2)
#define TASK__%0[%1](%2) forward gtask@%0(%2); public gtask@%0(%2){ return SetTimer(#%0,%1,true); } forward %0(%2); public %0(%2)
#define PTASK__%0[%1](%2) forward ptask@%0(%2); public ptask@%0(%2){ return SetTimerEx(#%0,%1,true, "i", %2); } forward %0(%2); public %0(%2)
// #define STOP__%0; KillTimer(%0);

// repeats
#define REPEATS__%0[%1](%2) 	SetTimerEx(defera@%0,%1,true,@Ys:%2)
#define DEFER__%0[%1](%2) 	SetTimerEx(defera@%0,%1,false,@Ys:%2)

#define ptask@%0\32; ptask@
#define gtask@%0\32; gtask@
#define repeata@%0\32; #%0
#define defera@%0\32; #%0

#define ptask%0[%1](%2) PTASK__%0[%1](%2)
#define task%0[%1](%2) TASK__%0[%1](%2)
#define stop%0; 	KillTimer(%0);
#define repeat%0[%1](%2) REPEATS__%0[%1](%2)
#define defer%0[%1](%2) DEFER__%0[%1](%2)
#define timer%0[%1](%2) TIMER__%0[%1](%2)

new 
    Map:s_PlayerTimerID,
    Map:s_PlayerTaskFunc
;

static PPTasks_StartPlayerTasks(playerid)
{
	if (map_size(s_PlayerTaskFunc) == 0) 
		return;

	new List:list = list_new();
	map_add(s_PlayerTimerID, playerid, list);

	new Iter:ti = map_iter(s_PlayerTaskFunc);
	while (iter_inside(ti))
	{
		new timerid = pawn_call_public_s(iter_get_key_str_s(ti), "d", playerid);
		
		if (timerid)
			list_add(list, timerid);

		iter_move_next(ti);
	}
}

static PPTasks_StopPlayerTasks(playerid)
{
	if (!map_has_key(s_PlayerTimerID, playerid))
		return;
		
	new List:list;
	if (!map_get_safe(s_PlayerTimerID, playerid, list)) 
		return;

	new size = list_size(list);
	for (new i = 0; i < size; i++)
		KillTimer(list_get(list, i));

	list_delete(list);
	map_remove_deep(s_PlayerTimerID, playerid);
}

forward _pp@on_init@Tasks();
public _pp@on_init@Tasks()
{
    new count = amx_num_publics();
    for (new i = 0; i < count; i++)
    {
		new List:regex = str_extract(amx_public_name_s(i), "^(gtask@\\w+)");
        if (regex) {
			pawn_call_public_s(list_get_str_s(regex, 0), "");
			list_delete_deep(regex);
        }
    }
    return 1;
}

forward _pp@on_init@PP_PlayerTasks();
public _pp@on_init@PP_PlayerTasks()
{
	s_PlayerTaskFunc  = map_new();
	s_PlayerTimerID = map_new();

	new count = amx_num_publics();
	for (new i = 0; i < count; i++)
	{
		new List:regex = str_extract(amx_public_name_s(i), "^(ptask@\\w+)");

		if (!regex) continue;

		map_str_s_set(s_PlayerTaskFunc, list_get_str_s(regex, 0), i);
		list_delete_deep(regex);
	}

	for (new i = 0; i < MAX_PLAYERS; i++)
	{
		if (IsPlayerConnected(i) && !IsPlayerNPC(i))
			PPTasks_StartPlayerTasks(i);
	}

	return 1;
}
public OnPlayerConnect(playerid)
{
	if (!IsPlayerNPC(playerid)) 
		PPTasks_StartPlayerTasks(playerid);

	#if defined PPTasks_OnPlayerConnect
		return PPTasks_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect PPTasks_OnPlayerConnect
#if defined PPTasks_OnPlayerConnect
	forward PPTasks_OnPlayerConnect(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	if (!IsPlayerNPC(playerid)) 
		PPTasks_StopPlayerTasks(playerid);

	#if defined PPTasks_OnPlayerDisconnect
		return PPTasks_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect PPTasks_OnPlayerDisconnect
#if defined PPTasks_OnPlayerDisconnect
	forward PPTasks_OnPlayerDisconnect(playerid, reason);
#endif