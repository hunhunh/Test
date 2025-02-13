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

	//true: �޴� ǥ�� ��, false: ����
	bool bIsMenuVisible;

	// ==============================
	// **�޴� UI ���� �Լ�**
	// ==============================
	void DisplayMenu();
	void HideMenu();
	void ToggleMenu();

	// ==============================
	// **��ȣ�ۿ� UI ���� �Լ�**
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
