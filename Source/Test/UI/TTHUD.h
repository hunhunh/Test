// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TTHUD.generated.h"

class UMainMenu;
class UInteractionWidget;
struct FInteractableData;
/**
 * 
 */
UCLASS()
class TEST_API ATTHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ATTHUD();

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UMainMenu> MainMenuClass;
	
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UInteractionWidget>	InteractionWidgetClass;

	//true: 메뉴 표시 중, false: 숨김
	bool bIsMenuVisible;

	// ==============================
	// **메뉴 UI 관련 함수**
	// ==============================
	void DisplayMenu();
	void HideMenu();
	void ToggleMenu();

	// ==============================
	// **상호작용 UI 관련 함수**
	// ==============================

	void ShowInteractionWidget();
	void HideInteractionWidget();
	void UpdateInteractionWidget(const FInteractableData* InteractableData);

protected:
	UPROPERTY()
	UMainMenu* MainMenuWidget;

	UPROPERTY()
	UInteractionWidget* InteractionWidget;

	virtual void BeginPlay() override;
};
