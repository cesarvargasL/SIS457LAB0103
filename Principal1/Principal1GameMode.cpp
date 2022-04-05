// Copyright Epic Games, Inc. All Rights Reserved.

#include "Principal1GameMode.h"
#include "Principal1PlayerController.h"
#include "Principal1Pawn.h"

APrincipal1GameMode::APrincipal1GameMode()
{
	// no pawn by default
	DefaultPawnClass = APrincipal1Pawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = APrincipal1PlayerController::StaticClass();
}
