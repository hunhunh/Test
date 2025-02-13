// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryPanel.h"
#include "Character/TTCharacter.h"
#include "Components/InventoryComponent.h"
#include "Components/TextBlock.h"
#include "UI/InventoryItemSlot.h"
#include "Components/WrapBox.h"
#include <Interfaces/ItemDragDropOperation.h>

void UInventoryPanel::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerCharacter = Cast<ATTCharacter>(GetOwningPlayerPawn());

	if (PlayerCharacter)
	{
		InventoryRef = PlayerCharacter->GetInventory();

		if (InventoryRef)
		{
			InventoryRef->OnInventoryUpdated.AddUObject(this, &UInventoryPanel::RefreshInventory);
			SetInfoText();
		}
	}
}

void UInventoryPanel::RefreshInventory()
{
	if (InventoryRef && InventorySlotClass)
	{
		InventoryPanel->ClearChildren();

		for (UItemBase* const& InventoryItem : InventoryRef->GetInventoryContents())
		{
			UInventoryItemSlot* ItemSlot = CreateWidget<UInventoryItemSlot>(this, InventorySlotClass);
			ItemSlot->SetItemRef(InventoryItem);
			InventoryPanel->AddChildToWrapBox(ItemSlot);
		}

		SetInfoText();
	}
}

void UInventoryPanel::SetInfoText() const
{
	const FString WeightInfoValue{
		FString::SanitizeFloat(InventoryRef->GetInventoryTotalWeight()) + "/" +
		FString::SanitizeFloat(InventoryRef->GetWeightCapacity())
	};

	const FString CapacityInfoValue{
		FString::FromInt(InventoryRef->GetInventoryContents().Num()) + "/" +
		FString::FromInt(InventoryRef->GetSlotsCapacity())
	};

	WeightInfo->SetText(FText::FromString(WeightInfoValue));
	CapacityInfo->SetText(FText::FromString(CapacityInfoValue));
}

bool UInventoryPanel::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	const UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>(InOperation);

	// ��ȿ�� ������ �����Ͱ� �ְ�, �κ��丮 ������ �����ϴ��� Ȯ��
	if (ItemDragDrop->SourceItem && InventoryRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Detected an item drop on InventoryPanel."))

		return true;
	}

	return false;
}
