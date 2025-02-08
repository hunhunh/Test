// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemDataStructs.h"
#include "Character/TTCharacter.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API UItemBase : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category = "Item")
	int32 Quantity;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FName ID; //데이터 테이블의 검색 필드 역할을 하는 항목


	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemType ItemType;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemQuality ItemQuality;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemStatistics ItemStatistics;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemTextData TextData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemNumericData NumericData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemAssetData AssetData;


	//================================================
	//FUNCTIONS
	//================================================
	UItemBase();

	UFUNCTION(Category = "Item")
	UItemBase* CreateItemCopy();

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemStackWeight() const { return Quantity * NumericData.Weight; };
	
	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemSinleWeight() const { return NumericData.Weight; };
	
	UFUNCTION(Category = "Item")
	FORCEINLINE bool IsFullItemStack() const { return Quantity == NumericData.MaxStackSize; };

	UFUNCTION(Category = "Item")
	void SetQuantity(const int32 NewQuantity);

	UFUNCTION(Category = "Item")
	virtual void Use(ATTCharacter* Character);

protected:
	bool operator==(const FName& OtherID) const
	{
		return this->ID == OtherID;
	}
};
