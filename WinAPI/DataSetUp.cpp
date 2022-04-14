#include "Stdafx.h"
#include "DataSetUp.h"

void DataSetUp::init(void)
{
	AnimationJsonDataSetup();
	ImageClassInit();
	AnimationClassInit();
	SoundInit();
}

void DataSetUp::release(void)
{
	while (!_qAniData.empty())
	{
		SAFE_DELETE( _qAniData.front());
	}
}

void DataSetUp::ImageClassInit()
{
#pragma region CharacterImg
	IMAGEMANAGER->addFrameImage("laharl", "Resource/Images/Disgaea/character/laharl_deploy.bmp", 700, 1860, 10, 31, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Etna", "Resource/Images/Disgaea/character/Etna_sheet.bmp", 600, 1380, 10, 23, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Archer", "Resource/Images/Disgaea/character/Archer_sheet.bmp", 320, 112, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Beast", "Resource/Images/Disgaea/character/beast_sheet.bmp", 462, 324, 6, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Cleric", "Resource/Images/Disgaea/character/Cleric_sheet.bmp", 320, 112, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Dragon", "Resource/Images/Disgaea/character/Dragon_sheet.bmp", 300, 300, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Flonne", "Resource/Images/Disgaea/character/Flonne_sheet.bmp", 600, 1080, 10, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Ghost", "Resource/Images/Disgaea/character/Ghost_sheet.bmp", 700, 840, 10, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Golem", "Resource/Images/Disgaea/character/Golem_sheet.bmp", 540, 280, 6, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Robin", "Resource/Images/Disgaea/character/Robin_sheet.bmp", 320, 112, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Warrior", "Resource/Images/Disgaea/character/warrior_sheet.bmp", 320, 112, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Vyers", "Resource/Images/Disgaea/character/Vyers_sheet.bmp", 700, 1400, 10, 20, true, RGB(255, 0, 255));

	
#pragma endregion

#pragma region UI
	IMAGEMANAGER->addFrameImage("GameState", "Resource/Images/Disgaea/UI/battleUI/GameState.bmp", 256, 320,1,10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("red", "Resource/Images/Disgaea/red.bmp", 134, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shadow", "Resource/Images/Disgaea/shadow.bmp", 20, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("black", "Resource/Images/Disgaea/black.bmp", 800, 800, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mapTile", "Resource/Images/Disgaea/Tile/tile5.bmp", 60, 44, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("mapTile", "Resource/Images/Disgaea/Tile/tile.bmp", 60, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("battleBack", "Resource/Images/Disgaea/UI/battleUI/battleBack.bmp", 600, 330, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("blueSign", "Resource/Images/Disgaea/UI/battleUI/1000_FILE_02.bmp", 20, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("redSign", "Resource/Images/Disgaea/UI/battleUI/1000_FILE_03.bmp", 36, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mapSign", "Resource/Images/Disgaea/UI/battleUI/selected.bmp", 60, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RedTile", "Resource/Images/Disgaea/UI/battleUI/RedTile.bmp", 60, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BlueTile", "Resource/Images/Disgaea/UI/battleUI/BlueTile.bmp", 60, 30, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("Dialog_back", "Resource/Images/Disgaea/UI/Dialog/DialogBack.bmp", 128, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("마계의 프린스", "Resource/Images/Disgaea/UI/BG051.bmp", 128, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CharacterIcon", "Resource/Images/Disgaea/UI/CharacterIcon.bmp", 400, 80,10,2, false, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("selectWindow_outline_LT", "Resource/Images/Disgaea/UI/window/leftTop.bmp", 3, 3, 1, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("selectWindow_outline_RT", "Resource/Images/Disgaea/UI/window/rightTop.bmp", 3, 3,1,1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("selectWindow_outline_LB", "Resource/Images/Disgaea/UI/window/leftBottom.bmp", 3, 3, 1, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("selectWindow_outline_RB", "Resource/Images/Disgaea/UI/window/rightBottom.bmp", 3, 3, 1, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("selectHand", "Resource/Images/Disgaea/UI/window/SYS1_55.bmp", 16, 14, 1, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("BattleHPBar", "Resource/Images/Disgaea/UI/battleUI/BattleHPBar.bmp", 37, 3, 1, 1, false);
	IMAGEMANAGER->addFrameImage("progress", "Resource/Images/Disgaea/UI/battleUI/progress.bmp", 60, 4, 1, 1, false);

	IMAGEMANAGER->addFrameImage("LevelUp", "Resource/Images/Disgaea/UI/1000_FILE_05.bmp", 60, 4, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GameState", "Resource/Images/Disgaea/UI/GameState.bmp", 60, 4, 1, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("nHP", "Resource/Images/Disgaea/UI/battleUI/nHP.bmp", 15, 9, 1, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("nJM", "Resource/Images/Disgaea/UI/battleUI/nJM.bmp", 15, 9, 1, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("nLV", "Resource/Images/Disgaea/UI/battleUI/nLV.bmp", 15, 9, 1, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("nMV", "Resource/Images/Disgaea/UI/battleUI/nMV.bmp", 15, 9, 1, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("nSP", "Resource/Images/Disgaea/UI/battleUI/nSP.bmp", 15, 9, 1, 1, true, RGB(0, 0, 0));

	IMAGEMANAGER->addFrameImage("DM", "Resource/Images/Disgaea/UI/battleUI/SYS04_04.bmp", 46, 30, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WIN", "Resource/Images/Disgaea/UI/battleUI/SYS04_07.bmp", 83, 31, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("DRAW", "Resource/Images/Disgaea/UI/battleUI/SYS04_08.bmp", 110, 31, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("trun", "Resource/Images/Disgaea/UI/battleUI/SYS04_09.bmp", 63, 31, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LOSE", "Resource/Images/Disgaea/UI/battleUI/SYS04_10.bmp", 93, 30, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("FIGHT", "Resource/Images/Disgaea/UI/battleUI/SYS04_11.bmp", 125, 30, 1, 1, true, RGB(255, 0, 255));

	
	IMAGEMANAGER->addFrameImage("BattleFaceS", "Resource/Images/Disgaea/UI/battleUI/BattleFaceS.bmp", 400, 256, 5, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NAME", "Resource/Images/Disgaea/UI/NAME.bmp", 128, 208, 1, 13, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Number", "Resource/Images/Disgaea/UI/Number.bmp", 120, 8, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Number2", "Resource/Images/Disgaea/UI/Number2.bmp", 250, 37, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Number3", "Resource/Images/Disgaea/UI/Number3.bmp", 200, 30, 10, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("bold_outline_LT", "Resource/Images/Disgaea/UI/window/WAKU02_01_01.bmp", 7, 7, 1, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bold_outline_T", "Resource/Images/Disgaea/UI/window/WAKU02_01_02.bmp", 10, 7, 1, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bold_outline_RT", "Resource/Images/Disgaea/UI/window/WAKU02_01_03.bmp", 7, 7, 1, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bold_outline_L", "Resource/Images/Disgaea/UI/window/WAKU02_01_04.bmp", 7, 10, 1, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bold_outline_R", "Resource/Images/Disgaea/UI/window/WAKU02_01_06.bmp", 7, 10, 1, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bold_outline_LB", "Resource/Images/Disgaea/UI/window/WAKU02_01_07.bmp", 7, 7, 1, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bold_outline_B", "Resource/Images/Disgaea/UI/window/WAKU02_01_08.bmp", 10, 7, 1, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bold_outline_RB", "Resource/Images/Disgaea/UI/window/WAKU02_01_09.bmp", 7, 7, 1, 1, false, RGB(255, 0, 255));

#pragma endregion

#pragma region background

	IMAGEMANAGER->addFrameImage("TitleScene", "Resource/Images/Disgaea/TitleScene/TitleScene.bmp", 600, 1076, 1, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TITLEBG", "Resource/Images/Disgaea/TitleScene/TITLEBG.bmp", 512, 256, 1, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Intro", "Resource/Images/Disgaea/TitleScene/BG003.bmp", 512, 256, 1, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("home", "Resource/Images/Disgaea/TitleScene/BG004.bmp", 640, 270, 1, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("stage1", "Resource/Images/Disgaea/TitleScene/BG007.bmp", 640, 270, 1, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("stage2", "Resource/Images/Disgaea/TitleScene/BG009.bmp", 640, 270, 1, 1, false, RGB(255, 0, 255));

#pragma endregion

#pragma region Map

#pragma endregion
	
}

void DataSetUp::AnimationClassInit()
{
	AniData* data = getAniData()->front();
	getAniData()->pop();
#pragma region Laharl
	ANIMATIONMANAGER->addAnimation("laharl_homeIdle_B", "laharl", 0, 0, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("laharl_homeIdle_LB", "laharl", 1, 1, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("laharl_homeIdle_L", "laharl", 2, 2, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("laharl_homeIdle_LT", "laharl", 3, 3, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("laharl_homeIdle_T", "laharl", 4, 4, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("laharl_homeIdle_RT", "laharl", 5, 5, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("laharl_homeIdle_R", "laharl", 6, 6, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("laharl_homeIdle_RB", "laharl", 7, 7, ANI_FPS, false, true);

	ANIMATIONMANAGER->addAnimation("laharl_beAttacked_LB", "laharl", 174, 174, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("laharl_beAttacked_LT", "laharl", 184, 184, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("laharl_beAttacked_RT", "laharl", 194, 194, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("laharl_beAttacked_RB", "laharl", 204, 204, ANI_FPS, false, false);

	ANIMATIONMANAGER->addAnimation("laharl_move_L", "laharl", 30, 35, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("laharl_move_T", "laharl", 50, 55, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("laharl_move_R", "laharl", 70, 75, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("laharl_move_B", "laharl", 10, 15, ANI_FPS, false, true);

	ANIMATIONMANAGER->addAnimation("laharl_jump_LB", "laharl", 26, 27, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("laharl_jump_LT", "laharl", 46, 47, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("laharl_jump_RT", "laharl", 66, 67, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("laharl_jump_RB", "laharl", 86, 87, ANI_FPS, false, false);

	ANIMATIONMANAGER->addAnimation("laharl_victory_LB", "laharl", 174, 174, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("laharl_victory_LT", "laharl", 184, 184, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("laharl_victory_RT", "laharl", 194, 194, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("laharl_victory_RB", "laharl", 204, 204, ANI_FPS, false, false);
	
	ANIMATIONMANAGER->addAnimation(data->getKeyStr(battle_idle_LT_Start), "laharl", data->getAniDataInt(battle_idle_LT_Start), data->getAniDataInt(battle_idle_LT_End), ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation(data->getKeyStr(battle_idle_LB_Start), "laharl", data->getAniDataInt(battle_idle_LB_Start), data->getAniDataInt(battle_idle_LB_End), ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation(data->getKeyStr(battle_idle_RT_Start), "laharl", data->getAniDataInt(battle_idle_RT_Start), data->getAniDataInt(battle_idle_RT_End), ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation(data->getKeyStr(battle_idle_RB_Start), "laharl", data->getAniDataInt(battle_idle_RB_Start), data->getAniDataInt(battle_idle_RB_End), ANI_FPS, false, true);

	ANIMATIONMANAGER->addAnimation(data->getKeyStr(move_LB_Start), "laharl", data->getAniDataInt(move_LB_Start), data->getAniDataInt(move_LB_End), ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation(data->getKeyStr(move_LT_Start), "laharl", data->getAniDataInt(move_LT_Start), data->getAniDataInt(move_LT_End), ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation(data->getKeyStr(move_RT_Start), "laharl", data->getAniDataInt(move_RT_Start), data->getAniDataInt(move_RT_End), ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation(data->getKeyStr(move_RB_Start), "laharl", data->getAniDataInt(move_RB_Start), data->getAniDataInt(move_RB_End), ANI_FPS, false, true);

	for (int i = 40; i < EJSON_ANIDATA_END; i+=2)
	{
		ANIMATIONMANAGER->addAnimation(data->getKeyStr(static_cast<EJSON_ANIDATA>(i)), "laharl", data->getAniDataInt(static_cast<EJSON_ANIDATA>(i)), data->getAniDataInt(static_cast<EJSON_ANIDATA>(i+1)), ANI_FPS, false, false);
	}

	SAFE_DELETE(data);
#pragma endregion

#pragma region Archer
	int arrNpcLBIdle[5] = { 1,10,11,1,1 };
	int arrNpcRBIdle[5] = { 7,12,13,7,7 };
	ANIMATIONMANAGER->addAnimation("Archer_idle_B", "Archer", 0, 0, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimationArray( "Archer_idle_LB", "Archer", arrNpcLBIdle, 5, ANI_FPS, true);
	ANIMATIONMANAGER->addAnimation( "Archer_idle_L", "Archer", 2, 2, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation( "Archer_idle_LT", "Archer", 3, 3, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation( "Archer_idle_T", "Archer", 4, 4, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation( "Archer_idle_RT", "Archer", 5, 5, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation( "Archer_idle_R", "Archer", 6, 6, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimationArray( "Archer_idle_RB", "Archer", arrNpcRBIdle, 5, ANI_FPS, true);
#pragma endregion

#pragma region Cleric

	ANIMATIONMANAGER->addAnimation( "Cleric_idle_B", "Cleric", 0, 0, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimationArray( "Cleric_idle_LB", "Cleric", arrNpcLBIdle, 5, ANI_FPS, true);
	ANIMATIONMANAGER->addAnimation( "Cleric_idle_L", "Cleric", 2, 2, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation( "Cleric_idle_LT", "Cleric", 3, 3, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation( "Cleric_idle_T", "Cleric", 4, 4, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation( "Cleric_idle_RT", "Cleric", 5, 5, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation( "Cleric_idle_R", "Cleric", 6, 6, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimationArray( "Cleric_idle_RB", "Cleric", arrNpcRBIdle, 5, ANI_FPS, true);
#pragma endregion

#pragma region Robin

	ANIMATIONMANAGER->addAnimation( "Robin_idle_B", "Robin", 0, 0, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimationArray( "Robin_idle_LB", "Robin", arrNpcLBIdle, 5, ANI_FPS, true);
	ANIMATIONMANAGER->addAnimation( "Robin_idle_L", "Robin", 2, 2, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation( "Robin_idle_LT", "Robin", 3, 3, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation( "Robin_idle_T", "Robin", 4, 4, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Robin_idle_RT", "Robin", 5, 5, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation( "Robin_idle_R", "Robin", 6, 6, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimationArray( "Robin_idle_RB", "Robin", arrNpcRBIdle, 5, ANI_FPS, true);
#pragma endregion

#pragma region Warrior

	ANIMATIONMANAGER->addAnimation( "Warrior_idle_B", "Warrior", 0, 0, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimationArray( "Warrior_idle_LB", "Warrior", arrNpcLBIdle, 5, ANI_FPS, true);
	ANIMATIONMANAGER->addAnimation("Warrior_idle_L", "Warrior", 2, 2, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation( "Warrior_idle_LT", "Warrior", 3, 3, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation( "Warrior_idle_T", "Warrior", 4, 4, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation( "Warrior_idle_RT", "Warrior", 5, 5, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation( "Warrior_idle_R", "Warrior", 6, 6, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimationArray( "Warrior_idle_RB", "Warrior", arrNpcRBIdle, 5, ANI_FPS, true);
#pragma endregion

#pragma region Beast

	ANIMATIONMANAGER->addAnimation( "Beast_idle_LB", "Beast", 0, 5, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation( "Beast_idle_LT", "Beast", 6, 11, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation( "Beast_idle_RT", "Beast", 12, 17, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation(" Beast_idle_RB", "Beast", 18, 23, ANI_FPS, false, true);
#pragma endregion

#pragma region Dragon

	ANIMATIONMANAGER->addAnimation( "Dragon_idle_LB", "Dragon", 0, 3, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation( "Dragon_idle_LT", "Dragon", 4, 7, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation( "Dragon_idle_RT", "Dragon", 8, 11, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation( "Dragon_idle_RB", "Dragon", 12, 15, ANI_FPS, false, true);
#pragma endregion

#pragma region Golem

	ANIMATIONMANAGER->addAnimation( "Golem_idle_LB", "Golem", 0, 5, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation( "Golem_idle_LT", "Golem", 6, 11, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation( "Golem_idle_RT", "Golem", 12, 17, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Golem_idle_RB", "Golem", 18, 23, ANI_FPS, false, true);
#pragma endregion
	
#pragma region Etna

	ANIMATIONMANAGER->addAnimation("Etna_homeIdle_B", "Etna", 0, 0, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Etna_homeIdle_LB", "Etna", 1, 1, ANI_FPS,false, true);
	ANIMATIONMANAGER->addAnimation("Etna_homeIdle_L", "Etna", 2, 2, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Etna_homeIdle_LT", "Etna", 3, 3, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Etna_homeIdle_T", "Etna", 4, 4, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Etna_homeIdle_RT", "Etna", 5, 5, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Etna_homeIdle_R", "Etna", 6, 6, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Etna_homeIdle_RB", "Etna", 7, 7, ANI_FPS,false, true);
	ANIMATIONMANAGER->addAnimation("Etna_move_LB", "Etna", 10, 15, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Etna_move_LT", "Etna", 20, 25, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Etna_move_RT", "Etna", 30, 35, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Etna_move_RB", "Etna", 40, 45, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Etna_jump_LB", "Etna", 16, 17, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_jump_LT", "Etna", 26, 27, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_jump_RT", "Etna", 36, 37, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_jump_RB", "Etna", 46, 47, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_Idle_LB", "Etna", 50, 53, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Etna_Idle_LT", "Etna", 54, 57, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Etna_Idle_RT", "Etna", 60, 63, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Etna_Idle_RB", "Etna", 64, 67, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Etna_run_LB", "Etna", 70, 71, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_run_LT", "Etna", 80, 81, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_run_RT", "Etna", 90, 91, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_run_RB", "Etna", 100, 101, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_beAttacked_LB", "Etna", 72, 72, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_beAttacked_LT", "Etna", 82, 82, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_beAttacked_RT", "Etna", 92, 92, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_beAttacked_RB", "Etna", 102, 102, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_victory_LB", "Etna", 73, 73, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_victory_LT", "Etna", 83, 83, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_victory_RT", "Etna", 93, 93, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_victory_RB", "Etna", 103, 103, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_kick_LB", "Etna", 74, 75, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_kick_LT", "Etna", 84, 85, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_kick_RT", "Etna", 94, 95, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_kick_RB", "Etna", 104, 105, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_gun_LB", "Etna", 110, 113, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_gun_LT", "Etna", 114, 117, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_gun_RT", "Etna", 120, 123, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_gun_RB", "Etna", 124, 127, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_punch_LB", "Etna", 130, 134, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_punch_LT", "Etna", 140, 144, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_punch_RT", "Etna", 150, 154, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_punch_RB", "Etna", 160, 164, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_pickUp_LB", "Etna", 135, 136, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_pickUp_LT", "Etna", 145, 146, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_pickUp_RT", "Etna", 155, 156, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_pickUp_RB", "Etna", 165, 166, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_animation1_L", "Etna", 170, 175, ANI_Dialog, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_animation1_R", "Etna", 180, 185, ANI_Dialog, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_animation2_L", "Etna", 190, 197, ANI_Dialog, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_animation2_R", "Etna", 200, 207, ANI_Dialog, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_animation2Reverce_L", "Etna", 190, 197, ANI_Dialog, true, false);
	ANIMATIONMANAGER->addAnimation("Etna_animation2Reverce_R", "Etna", 200, 207, ANI_Dialog, true, false);
	ANIMATIONMANAGER->addAnimation("Etna_animation3_L", "Etna", 210, 212, ANI_Dialog, false, false);
	ANIMATIONMANAGER->addAnimation("Etna_animation3_R", "Etna", 220, 222, ANI_Dialog, false, false);
	int arrEtnaCloseEyeLeft[] = { 215,215,214,214,215 };
	int arrEtnaCloseEyeRight[] = { 225,225,224,224,225 };
	ANIMATIONMANAGER->addAnimationArray("Etna_closeEye_L", "Etna", arrEtnaCloseEyeLeft, 5, ANI_Dialog, false);
	ANIMATIONMANAGER->addAnimationArray("Etna_closeEye_R", "Etna", arrEtnaCloseEyeRight, 5, ANI_Dialog, false);

#pragma endregion

#pragma region Flonne

	ANIMATIONMANAGER->addAnimation("Flonne_homeIdle_B", "Flonne", 0, 0, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Flonne_homeIdle_LB", "Flonne", 1, 1, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Flonne_homeIdle_L", "Flonne", 2, 2, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Flonne_homeIdle_LT", "Flonne", 3, 3, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Flonne_homeIdle_T", "Flonne", 4, 4, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Flonne_homeIdle_RT", "Flonne", 5, 5, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Flonne_homeIdle_R", "Flonne", 6, 6, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Flonne_homeIdle_RB", "Flonne", 7, 7, ANI_FPS, false, true);

	ANIMATIONMANAGER->addAnimation("Flonne_move_LB", "Flonne", 20, 25, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Flonne_move_LT", "Flonne", 30, 35, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Flonne_move_RT", "Flonne", 40, 45, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Flonne_move_RB", "Flonne", 50, 55, ANI_FPS, false, true);

	ANIMATIONMANAGER->addAnimation("Flonne_jump_LB", "Flonne", 26, 27, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_jump_LT", "Flonne", 36, 37, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_jump_RT", "Flonne", 46, 47, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_jump_RB", "Flonne", 56, 57, ANI_FPS, false, false);

	ANIMATIONMANAGER->addAnimation("Flonne_Idle_LB", "Flonne", 60, 63, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Flonne_Idle_LT", "Flonne", 64, 67, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Flonne_Idle_RT", "Flonne", 70, 73, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Flonne_Idle_RB", "Flonne", 74, 77, ANI_FPS, false, true);

	ANIMATIONMANAGER->addAnimation("Flonne_run_LB", "Flonne", 80, 81, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_run_LT", "Flonne", 90, 91, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_run_RT", "Flonne", 100, 101, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_run_RB", "Flonne", 110, 111, ANI_FPS, false, false);

	ANIMATIONMANAGER->addAnimation("Flonne_beAttacked_LB", "Flonne", 82, 82, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_beAttacked_LT", "Flonne", 92, 92, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_beAttacked_RT", "Flonne", 102, 102, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_beAttacked_RB", "Flonne", 112, 112, ANI_FPS, false, false);

	ANIMATIONMANAGER->addAnimation("Flonne_victory_LB", "Flonne", 83, 83, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_victory_LT", "Flonne", 93, 93, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_victory_RT", "Flonne", 103, 103, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_victory_RB", "Flonne", 113, 113, ANI_FPS, false, false);

	ANIMATIONMANAGER->addAnimation("Flonne_kick_LB", "Flonne", 84, 85, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_kick_LT", "Flonne", 94, 95, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_kick_RT", "Flonne", 104, 105, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_kick_RB", "Flonne", 114, 115, ANI_FPS, false, false);

	ANIMATIONMANAGER->addAnimation("Flonne_gun_LB", "Flonne", 120, 123, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_gun_LT", "Flonne", 124, 127, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_gun_RT", "Flonne", 130, 133, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_gun_RB", "Flonne", 134, 137, ANI_FPS, false, false);

	ANIMATIONMANAGER->addAnimation("Flonne_punch_LB", "Flonne", 140, 144, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_punch_LT", "Flonne", 150, 154, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_punch_RT", "Flonne", 160, 164, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_punch_RB", "Flonne", 170, 174, ANI_FPS, false, false);

	ANIMATIONMANAGER->addAnimation("Flonne_pickUp_LB", "Flonne", 145, 146, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_pickUp_LT", "Flonne", 155, 156, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_pickUp_RT", "Flonne", 165, 166, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Flonne_pickUp_RB", "Flonne", 175, 176, ANI_FPS, false, false);

	ANIMATIONMANAGER->addAnimation("Flonne_Skill_LB", "Flonne", 14, 14, ANI_Dialog, false, true);
	ANIMATIONMANAGER->addAnimation("Flonne_Skill_LT", "Flonne", 15, 15, ANI_Dialog, false, true);
	ANIMATIONMANAGER->addAnimation("Flonne_Skill_RT", "Flonne", 16, 16, ANI_Dialog, false, true);
	ANIMATIONMANAGER->addAnimation("Flonne_Skill_RB", "Flonne", 17, 17, ANI_Dialog, false, true);

	int arrFlonneCloseEyeLeft[] = { 10,10,11,11,10 };
	int arrFlonneCloseEyeRight[] = { 12,12,13,13,12 };
	ANIMATIONMANAGER->addAnimationArray("Flone_closeEye_L", "Flonne", arrFlonneCloseEyeLeft, 5, ANI_Dialog, false);
	ANIMATIONMANAGER->addAnimationArray("Flone_closeEye_R", "Flonne", arrFlonneCloseEyeRight, 5, ANI_Dialog, false);

#pragma endregion

#pragma region Ghost
	ANIMATIONMANAGER->addAnimation("Ghost_moveIdle_LB", "Ghost", 0,  4, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Ghost_moveIdle_LT", "Ghost", 10, 14, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Ghost_moveIdle_RT", "Ghost", 20, 24, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Ghost_moveIdle_RB", "Ghost", 30, 35, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Ghost_beAttacked_LB", "Ghost", 5, 5, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Ghost_beAttacked_LT", "Ghost", 15, 15, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Ghost_beAttacked_RT", "Ghost", 25, 25, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Ghost_beAttacked_RB", "Ghost", 35, 35, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Ghost_attack_LB", "Ghost", 40, 49, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Ghost_attack_LT", "Ghost", 50, 59, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Ghost_attack_RT", "Ghost", 60, 69, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Ghost_attack_RB", "Ghost", 70, 79, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Ghost_jumpAttack_LB", "Ghost", 80, 83, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Ghost_jumpAttack_LT", "Ghost", 90, 93, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Ghost_jumpAttack_RT", "Ghost", 100, 103, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Ghost_jumpAttack_RB", "Ghost", 110, 113, ANI_FPS, false, false);

	ANIMATIONMANAGER->addAnimation("Ghost_jump_LB", "Ghost", 84, 88, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Ghost_jump_LT", "Ghost", 94, 98, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Ghost_jump_RT", "Ghost", 104, 108, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Ghost_jump_RB", "Ghost", 114, 118, ANI_FPS, false, false);

#pragma endregion

#pragma region Vyers
	ANIMATIONMANAGER->addAnimation("Vyers_Idle_LB", "Vyers", 0, 4, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Vyers_Idle_LT", "Vyers", 10, 14, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Vyers_Idle_RB", "Vyers", 20, 24, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Vyers_Idle_RT", "Vyers", 30, 34, ANI_FPS, false, true);

	ANIMATIONMANAGER->addAnimation("Vyers_jump_LB", "Vyers", 6, 7, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Vyers_jump_LT", "Vyers", 16, 17, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Vyers_jump_RB", "Vyers", 26, 27, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Vyers_jump_RT", "Vyers", 36, 37, ANI_FPS, false, false);

	ANIMATIONMANAGER->addAnimation("Vyers_beAttacked_LB", "Vyers", 5, 5, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Vyers_beAttacked_LT", "Vyers", 15, 15, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Vyers_beAttacked_RB", "Vyers", 25, 25, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Vyers_beAttacked_RT", "Vyers", 35, 35, ANI_FPS, false, true);

	ANIMATIONMANAGER->addAnimation("Vyers_move_LB", "Vyers", 40, 45, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Vyers_move_LT", "Vyers", 50, 55, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Vyers_move_RB", "Vyers", 60, 65, ANI_FPS, false, true);
	ANIMATIONMANAGER->addAnimation("Vyers_move_RT", "Vyers", 70, 75, ANI_FPS, false, true);

	ANIMATIONMANAGER->addAnimation("Vyers_Attack_LB", "Vyers", 80, 90, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Vyers_Attack_LT", "Vyers", 91, 101, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Vyers_Attack_RT", "Vyers", 110, 120, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Vyers_Attack_RB", "Vyers", 121, 131, ANI_FPS, false, false);

	ANIMATIONMANAGER->addAnimation("Vyers_Skill1_LB", "Vyers", 140, 150, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Vyers_Skill1_LT", "Vyers", 151, 161, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Vyers_Skill1_RT", "Vyers", 170, 180, ANI_FPS, false, false);
	ANIMATIONMANAGER->addAnimation("Vyers_Skill1_RB", "Vyers", 181, 191, ANI_FPS, false, false);
#pragma endregion


}


void DataSetUp::AnimationJsonDataSetup()
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("Character.json");

	for (auto it = root["Animation"].begin(); it != root["Animation"].end(); it++)
	{
		AniData* aniData = new AniData;
		aniData->init();

		aniData->setName((*it)["name"].asString());

		for (int i = 0; i < EJSON_ANIDATA::EJSON_ANIDATA_END; i++)
		{
			aniData->setAniDataInt(static_cast<EJSON_ANIDATA>(i),
				(*it)[aniData->getKeyStr(static_cast<EJSON_ANIDATA>(i))].asInt());
		}
		_qAniData.push(aniData);
	}
}

void DataSetUp::SoundInit()
{
	SOUNDMANAGER->addSound("Title", "Resource/Sound/Disgaea/back/BGM001.OGG", true, true);
}
