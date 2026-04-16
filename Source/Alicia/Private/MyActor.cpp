// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collsion = CreateDefaultSubobject<UCapsuleComponent>(TEXT("collsion"));
    staticmesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticmesh"));
    spherecollision = CreateDefaultSubobject<USphereComponent>(TEXT("spherecollision"));
	SetRootComponent(collsion);
	staticmesh->SetupAttachment(GetRootComponent());
    spherecollision->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("Hello C++ and UE5!"));
	//GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, TEXT("Hello c++ and UE5"));

    spherecollision->OnComponentBeginOverlap.AddDynamic(this, &AMyActor::OnBeginOverlap);
    spherecollision->OnComponentEndOverlap.AddDynamic(this, &AMyActor::OnEndOverlap);

}
void AMyActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*
	FString s = OtherActor->GetName();
	FString s0 = FString("begin overlap:") + s;
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, s0);
	}*/

}
void AMyActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*
	FString s = OtherActor->GetName();
	FString s0 = FString("end overlap:") + s;
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, s0);
	}*/
}
float AMyActor::dowork()
{
    FVector location = GetActorLocation();
    DrawDebugLine(GetWorld(), location, location + FVector(0.f, 0.f, 100.f), FColor::Blue, false, -1, 0, 2.0f);
    DrawDebugPoint(GetWorld(), location + FVector(0.f, 0.f, 100.f), 10.f, FColor::Red, false, -1, 0);
    // 绘制球体、盒子等其他形状
    DrawDebugSphere(GetWorld(), location, 50.f, 12, FColor::Blue, false, -1, 0, 2.0f);
    return 1.f;
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FVector location = GetActorLocation();
	//DrawDebugLine(GetWorld(), location, location + FVector(0.f, 0.f, 100.f), FColor::Blue, false, -1, 0, 2.0f);
    //AddActorWorldOffset(FVector(0.f, 0.f, 50.f)*DeltaTime);
    //dowork();
}

