// Fill out your copyright notice in the Description page of Project Settings.


#include "AHGameState.h"
#include "AHPlayerCharacter.h"
#include "AHPlayWidget.h"
#include "Kismet/GameplayStatics.h"

AAHGameState::AAHGameState()
{
	currentStage = 1;
	remainingMonsters = 0;
	currentWave = 1;
	maxWaves = 3;
}

void AAHGameState::BeginPlay()
{
	Super::BeginPlay();

	if (!PlayWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayWidgetClass 미설정 -> BP에서 설정하기"));
		return;
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		UUserWidget* Created = CreateWidget<UUserWidget>(PC, PlayWidgetClass);
		if (Created)
		{
			Created->AddToViewport();

			if (UAHPlayWidget* AsGameMain = Cast<UAHPlayWidget>(Created))
			{
				AsGameMain->currentCharacter = Cast<AAHPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			}
		}
	}
}

void AAHGameState::NextStage()
{
	currentStage++;
	currentWave = 1;
	UE_LOG(LogTemp, Warning, TEXT("Current Stage: %d"), currentStage);

	// 여기에 다음 스테이지 문을 열거나, 다음 웨이브를 생성하는 로직을 트리거할 수 있습니다.
}

void AAHGameState::MonsterSpawned()
{
	remainingMonsters++;
	UE_LOG(LogTemp, Log, TEXT("남은 적: %d"), remainingMonsters);
}

void AAHGameState::MonsterKilled()
{
	if (remainingMonsters <= 0) return;

	remainingMonsters--;
	UE_LOG(LogTemp, Warning, TEXT("처치! 남은 적: %d"), remainingMonsters);

	// 스테이지의 모든 몬스터를 다 잡았다면!
	if (remainingMonsters == 0)
	{
		if (currentWave < maxWaves)
		{
			StartNextWave();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("다음 레벨로 이동"), currentStage);
			MoveToNextLevel();
		}
	}
}

void AAHGameState::StartNextWave()
{
	currentWave++;
	UE_LOG(LogTemp, Warning, TEXT("진행도 %d - %d "), currentStage, currentWave);
}

void AAHGameState::MoveToNextLevel()
{
	NextStage();

	// 맵 이름을 규칙성 있게 세팅합니다. (예: Map_Stage1, Map_Stage2, Map_Stage3 ...)
	FString NextMapName = FString::Printf(TEXT("Stage%d"), currentStage);

	// 화면에 로그를 띄우고 레벨 전환
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Loading %s..."), *NextMapName));

	// 실제로 언리얼 엔진에서 레벨을 열어주는 내장 함수
	UGameplayStatics::OpenLevel(GetWorld(), FName(*NextMapName));
}
