// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryPanel.h"
#include "Character/TTCharacter.h"
#include "Components/InventoryComponent.h"
#include "Components/TextBlock.h"
#include "UI/InventoryItemSlot.h"
#include "Components/WrapBox.h"

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
	WeightInfo->SetText(FText::Format(FText::FromString("{0}/{1}"),
		InventoryRef->GetInventoryTotalWeight(),
		InventoryRef->GetWeightCapacity()));

	CapacityInfo->SetText(FText::Format(FText::FromString("{0}/{1}"),
		InventoryRef->GetInventoryContents().Num(),
		InventoryRef->GetSlotsCapacity()));
}

bool UInventoryPanel::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
