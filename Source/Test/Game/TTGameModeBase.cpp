// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/TTGameModeBase.h"
#include "GameFramework/HUD.h"

ATTGameModeBase::ATTGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> ChacterRef(TEXT("/Script/CoreUObject.Class'/Script/Test.TTCharacter'"));
	if (ChacterRef.Class)
	{
		DefaultPawnClass = ChacterRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/CoreUObject.Class'/Script/Test.TTPlayerController'"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<AHUD> HUDClassRef(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_TTHUD.BP_TTHUD_C'"));
	if (HUDClassRef.Succeeded())
	{
		HUDClass = HUDClassRef.Class;
	}

}
