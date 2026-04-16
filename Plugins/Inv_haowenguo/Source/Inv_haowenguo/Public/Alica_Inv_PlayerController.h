

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Alica_Inv_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UAlica_Inv_Widget;
class UInvManagerComponent;
/**
 * 
 */
UCLASS()
class INV_HAOWENGUO_API AAlica_Inv_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAlica_Inv_PlayerController();
	virtual void PostInitializeComponents()override;
	virtual void BeginPlay()override;
	virtual void Tick(float delta)override;
	virtual void SetupInputComponent()override;
	void PressE();
	void CreateHUD0();

	UFUNCTION(BlueprintCallable)
	UInvManagerComponent* GetInvManager() {
		return InvManager.Get();
	};

	UFUNCTION(BlueprintCallable)
	void OpenCloseInv();
	UFUNCTION(BlueprintCallable)
	void TraceItems();

	UPROPERTY(EditAnywhere, Category = "PickUp")
	float TraceLength=200.f;
protected:
	UPROPERTY(EditAnywhere, Category = "Inv")
	TObjectPtr<UInputMappingContext> inputmap;
	
	UPROPERTY(EditAnywhere, Category = "Inv")
	TObjectPtr<UInputAction> inputaction;
	


	UPROPERTY(EditAnywhere, Category = "Inv")
	TObjectPtr<UInputAction> InvOpenCloseaction;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UAlica_Inv_Widget> UAlica_Inv_Widget_class;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TObjectPtr<UAlica_Inv_Widget> Alica_Inv_widget0;

	UPROPERTY(EditAnywhere, Category = "Inv")
	TEnumAsByte< ECollisionChannel> collision_channel=ECollisionChannel::ECC_Visibility;

	TWeakObjectPtr<AActor> LastActor;
	TWeakObjectPtr<AActor> ThisActor;

	TWeakObjectPtr<UInvManagerComponent> InvManager;
};
