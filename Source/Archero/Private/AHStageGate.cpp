// Fill out your copyright notice in the Description page of Project Settings.


#include "AHStageGate.h"
#include "AHGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
AAHStageGate::AAHStageGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox")); RootComponent = TriggerBox;
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	TriggerBox->SetGenerateOverlapEvents(true);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AAHStageGate::OnOverlapBegin);

	bIsOpen = false;

}

// Called when the game starts or when spawned
void AAHStageGate::BeginPlay()
{
	Super::BeginPlay();
	
	GateClose();
}

void AAHStageGate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Gate In"));

		if (bIsOpen)
		{
			GateClose();
			UAHGameInstance* GI = GetGameInstance<UAHGameInstance>();

			FString LevelName = FString::Printf(TEXT("Stage%d"), GI->CurrentStage);
			UGameplayStatics::OpenLevel(this, FName(*LevelName));
			UE_LOG(LogTemp, Warning, TEXT("Move to Stage %d"), GI->CurrentStage);
		}
	}
}

// Called every frame
//void AAHStageGate::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

