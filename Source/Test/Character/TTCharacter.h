// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Interfaces/InteractionInterface.h"
#include "TTCharacter.generated.h"

class ATTHUD;
class UInventoryComponent;

USTRUCT()
struct FInteractionData
{
	GENERATED_USTRUCT_BODY()

	FInteractionData() : CurrentInteractable(nullptr), LastInteractionCheckTime(0.0f)
	{

	};

	UPROPERTY()
	AActor* CurrentInteractable;

	UPROPERTY()
	float LastInteractionCheckTime;
};


UCLASS()
class TEST_API ATTCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATTCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Camera Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

	// Input Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	//Pickup ��ȣ�ۿ�
protected:
	UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")
	TScriptInterface<IInteractionInterface> TargetInteractable;

	//��ȣ�ۿ� Ű
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> InteractAction;

	//��ȣ�ۿ� Ȯ�� ��
	float InteractionCheckFrequency;

	//��ȣ�ۿ� Ȯ�� �Ÿ�
	float InteractionCheckDistance;

	FTimerHandle TimerHandle_Interaction;

	FInteractionData InteractionData;

	//�÷��̾� �ֺ��� ��ȣ�ۿ� ������ ������Ʈ Ž��
	void PerformInteractionCheck();
	//���ο� ��ȣ�ۿ� ������ ������Ʈ�� �����ϰ� ����
	void FoundInteractable(AActor* NewInteractable);
	//��ȣ�ۿ� ������ ������Ʈ�� ���� �� ó��
	void NoInteractableFound();
	//�÷��̾ ��ȣ�ۿ��� �õ��� �� ����
	void BeginInteract();
	//�÷��̾��� ��ȣ�ۿ� �ߴ�
	void EndInteract();
	//�÷��̾ ��ȣ�ۿ��� �Ϸ����� �� ����
	void Interact();

public:
	FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction); };


	//Widget

protected:
	UPROPERTY()
	TObjectPtr<ATTHUD> HUD;

	//Inventory
protected:
	UPROPERTY(VisibleAnywhere, Category = "Character | Inventory")
	TObjectPtr<UInventoryComponent> PlayerInventory;

public:
	FORCEINLINE UInventoryComponent* GetInventory() const { return PlayerInventory; };

	//InventoryWidget
public:
	void UpdateInteractionWidget() const;

	//Input Inventory toggle menu
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ToggleMenuAction;

	void ToggleMenu();
};
