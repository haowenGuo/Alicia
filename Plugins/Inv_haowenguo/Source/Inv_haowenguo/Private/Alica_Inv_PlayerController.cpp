


#include "Alica_Inv_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include <EnhancedInputComponent.h>
#include "Components/WidgetComponent.h"
#include"Alica_Inv_Widget.h"
#include <Kismet/GameplayStatics.h>
#include"PickUp/HighLightface.h"
#include"InvManager/InvManagerComponent.h"
#include <PickUp/PickUpComponent.h>
AAlica_Inv_PlayerController::AAlica_Inv_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAlica_Inv_PlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	InvManager = FindComponentByClass<UInvManagerComponent>();
}

void AAlica_Inv_PlayerController::BeginPlay() {
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Display, TEXT("hello plugins"));
	UEnhancedInputLocalPlayerSubsystem* inputsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (inputsystem) {
		inputsystem->AddMappingContext(inputmap, 0);
	}
	CreateHUD0();

	
}

void AAlica_Inv_PlayerController::Tick(float delta)
{
	Super::Tick(delta);
	TraceItems();
}



void AAlica_Inv_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* eic = CastChecked<UEnhancedInputComponent>(InputComponent);
	eic->BindAction(inputaction, ETriggerEvent::Started, this, &AAlica_Inv_PlayerController::PressE);
	eic->BindAction(InvOpenCloseaction, ETriggerEvent::Started, this, & AAlica_Inv_PlayerController::OpenCloseInv);
}

void AAlica_Inv_PlayerController::PressE()
{
	UE_LOG(LogTemp, Display, TEXT("PressE"));

	if (!ThisActor.IsValid())return;

	if (IsValid(ThisActor->GetOwner()))return;
	UPickUpComponent* puc = ThisActor->FindComponentByClass<UPickUpComponent>();

	if (!IsValid(puc) || !InvManager.IsValid())return;

	InvManager->TryAddItem(puc);
	ThisActor->Destroy();

}

void AAlica_Inv_PlayerController::CreateHUD0()
{
	if (!IsLocalController())return;

	Alica_Inv_widget0 = CreateWidget<UAlica_Inv_Widget>(this, UAlica_Inv_Widget_class,FName("Alica_HUD0"));
	if (Alica_Inv_widget0) {
		Alica_Inv_widget0->AddToViewport();
	}
}

void AAlica_Inv_PlayerController::OpenCloseInv()
{
	if (InvManager.IsValid()) {
		InvManager->ChangeInvOpenClose();
	}
}

void AAlica_Inv_PlayerController::TraceItems()
{

	if (!GEngine)return;

	FVector2D screensize;
	GEngine->GameViewport->GetViewportSize(screensize);

	FVector TraceStart;
	FVector TraceDir;
	screensize = screensize / 2.0;
	
	UGameplayStatics::DeprojectScreenToWorld(this, screensize, TraceStart, TraceDir);
	float dis=(GetPawn()->GetActorLocation()- TraceStart).Dot(TraceDir);
	TraceStart += TraceDir * (dis-20.f);
	const FVector TraceEnd = TraceStart + TraceDir * TraceLength;
	FHitResult hitresult;
	GetWorld()->LineTraceSingleByChannel(hitresult, TraceStart, TraceEnd, collision_channel);
	LastActor = ThisActor;
	
	ThisActor = hitresult.GetActor();
	//Cast<ASword>(ThisActor);
	if (!ThisActor.IsValid()) {
		//UE_LOG(LogTemp, Display, TEXT("TraceA new Actor"));
		if (IsValid(Alica_Inv_widget0)) {
			Alica_Inv_widget0->HidePickUpMessage();
		}
	}
	if (ThisActor == LastActor)return;

	if (ThisActor.IsValid()) {
		
		if (!IsValid(ThisActor->GetOwner()))
		{
			//UE_LOG(LogTemp, Display, TEXT("TraceA new Actor"));
			UPickUpComponent* pickupcomponent = ThisActor->FindComponentByClass<UPickUpComponent>();
			if (!IsValid(pickupcomponent))return;

			if (IsValid(Alica_Inv_widget0)) {

				Alica_Inv_widget0->ShowPickUpMessage(pickupcomponent->GetPickUpMessage());

			}
			UActorComponent* uac = ThisActor->FindComponentByInterface(UHighLightface::StaticClass());
			if (IsValid(uac)) {
				IHighLightface::Execute_HightLight(uac);
			}
		}
	}
	if (LastActor.IsValid()) {
		UE_LOG(LogTemp, Display, TEXT("Stop Trace Last Actor"));
		UActorComponent* uac = LastActor->FindComponentByInterface(UHighLightface::StaticClass());
		if (IsValid(uac)) {
			IHighLightface::Execute_UnHightLight(uac);
		}
	}
}

