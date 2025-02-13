// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryPanel.generated.h"

class ATTCharacter;
class UInventoryComponent;
class UInventoryItemSlot;
class UWrapBox;
class UGridPanel;
class UTextBlock;

/**
 * 
 */
UCLASS()
class TEST_API UInventoryPanel : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//�κ��丮 UI�� ���ΰ�ħ�ϴ� �Լ�
	UFUNCTION()
	void RefreshInventory();

	//������ ������ ǥ���� ���� �ڽ�
	UPROPERTY(meta = (BindWidget))
	UWrapBox* InventoryPanel;

	//���� �κ��丮�� �� ���� ������ ǥ��
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeightInfo;

	//���� �κ��丮�� ��� ���� ����/�ִ� ���� ������ ǥ��
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CapacityInfo;

	UPROPERTY()
	ATTCharacter* PlayerCharacter;

	UPROPERTY()
	UInventoryComponent* InventoryRef;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryItemSlot> InventorySlotClass;



protected:
	//�κ��丮 ������ UI�� ǥ��(���� �� ���� �������� Update)
	void SetInfoText() const;
	virtual void NativeOnInitialized() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
