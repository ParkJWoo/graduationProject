#pragma once

enum TEXTYPE { TEX_SINGLE, TEX_MULTI, TEX_END };

enum OBJID {
	OBJ_TERRAIN,
	OBJ_CAMERA,
	OBJ_BUTTON,
	OBJ_DIALOG, OBJ_DUST, OBJ_DIALOG_MATIKA, OBJ_DIALOG_IRONWINDOW, OBJ_DIALOG_LEO,
	OBJ_DIALOGBOX, OBJ_TUTORIALDIALOG,
	OBJ_BACKLAYER, OBJ_FIRSTLAYER, OBJ_CAGE, OBJ_CAGEDOOR, OBJ_SECONDLAYER, OBJ_MONSTER, OBJ_PLAYER, OBJ_DOOR, OBJ_STREETLIGHT, OBJ_FRONTLAYER, OBJ_LIGHT,
	OBJ_CUTTOON,
	OBJ_BULLET,OBJ_SPECIALATTACK,OBJ_ENEMYATTACK,
	OBJ_STAGEPLAYER,
	OBJ_EFFECT, OBJ_UI, OBJ_FADE, OBJ_MOUSE, OBJ_END
};

enum DATAID {
	PLAYER_DATA, PLAYER_MATRIX,
	STAGEPLAYER_DATA, STAGEPLAYER_MATRIX,
	CAMERA_DATA, CAMERA_MATRIX,
	ENEMY_DATA, ENEMY_MATRIX,
	STAGECAMERA_MATRIX,
	STAGEBOSSCAMERA_MATRIX,
	DATA_END
};

enum STATEID {
	IDLE = 1, ATTACK, DAMAGED, RUN, DIE, STATE_END
};