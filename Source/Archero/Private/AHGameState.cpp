// Fill out your copyright notice in the Description page of Project Settings.


#include "AHGameState.h"
#include "AHPlayerCharacter.h"
#include "AHPlayWidget.h"
#include "AHJoyStickWidget.h"
#include "AHLevelUpWidget.h"
#include "Kismet/GameplayStatics.h"

AAHGameState::AAHGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	CurrentStage = 1;
	RemainingMonsters = 0;
	CurrentWave = 1;
	MaxWaves = 3;
}

void AAHGameState::BeginPlay()
{
	Super::BeginPlay();
	InitializeUI();
}

#pragma region Stage & Monster

void AAHGameState::NextStage()
{
	CurrentStage++;
	CurrentWave = 1;
	UE_LOG(LogTemp, Warning, TEXT("Current Stage: %d"), CurrentStage);

	// 여기에 다음 스테이지 문을 열거나, 다음 웨이브를 생성하는 로직을 트리거할 수 있습니다.
}

void AAHGameState::MonsterSpawned()
{
	RemainingMonsters++;
}

void AAHGameState::MonsterKilled()
{
	if (RemainingMonsters <= 0) return;

	RemainingMonsters--;

	if (RemainingMonsters == 0)
	{
		CurrentWave < MaxWaves ? StartNextWave() : MoveToNextLevel();
	}
}

void AAHGameState::StartNextWave()
{
	CurrentWave++;
	UE_LOG(LogTemp, Warning, TEXT("진행도 %d - %d "), CurrentStage, CurrentWave);
}

void AAHGameState::MoveToNextLevel()
{
	NextStage();

	FString NextMapName = FString::Printf(TEXT("Stage%d"), CurrentStage);

	// 화면에 로그를 띄우고 레벨 전환
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Loading %s..."), *NextMapName));

	// 실제로 언리얼 엔진에서 레벨을 열어주는 내장 함수
	UGameplayStatics::OpenLevel(GetWorld(), FName(*NextMapName));
}

#pragma endregion

void AAHGameState::LevelUpPause()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC) return;

	// 1. 게임 일시정지
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	// 2. 마우스 커서 표시
	PC->bShowMouseCursor = true;
	FInputModeUIOnly InputMode;
	PC->SetInputMode(InputMode);

	// 3. 위젯 생성
	if (LevelUpWidgetClass)
	{
		LevelUpWidgetInstance = CreateWidget<UUserWidget>(PC, LevelUpWidgetClass);
		if (LevelUpWidgetInstance)
		{
			LevelUpWidgetInstance->AddToViewport();

			// 스킬 카드 뽑기 시작
			if (UAHLevelUpWidget* LevelUpW = Cast<UAHLevelUpWidget>(LevelUpWidgetInstance))
			{
				LevelUpW->RollRandomSkills();
			}
		}
	}
}

void AAHGameState::ResumeGame()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC) return;

	// 위젯 제거
	if (LevelUpWidgetInstance)
	{
		LevelUpWidgetInstance->RemoveFromParent();
		LevelUpWidgetInstance = nullptr;
	}

	// 입력 모드 복구 (조이스틱 다시 작동)
	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	PC->SetInputMode(InputMode);
	//PC->bShowMouseCursor = false;
#if PLATFORM_ANDROID || PLATFORM_IOS
	PC->bShowMouseCursor = false;
#else
	PC->bShowMouseCursor = true;
#endif

	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void AAHGameState::InitializeUI()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC)
	{
		UE_LOG(LogTemp, Error, TEXT("[GameState] PlayerController 없음"));
		return;
	}

	// Play Widget
	if (PlayWidgetClass)
	{
		PlayWidgetInstance = CreateWidget<UAHPlayWidget>(PC, PlayWidgetClass);
		if (PlayWidgetInstance)
		{
			PlayWidgetInstance->AddToViewport(0);
			PlayWidgetInstance->currentCharacter =
				Cast<AAHPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		}
	}

	// Joystick Widget
	if (JoystickWidgetClass)
	{
		JoystickWidgetInstance = CreateWidget<UAHJoyStickWidget>(PC, JoystickWidgetClass);
		if (JoystickWidgetInstance)
		{
			JoystickWidgetInstance->AddToViewport(1);
		}
	}

	// 입력 모드: 조이스틱 터치 인식을 위해 GameAndUI 필수
	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	PC->SetInputMode(InputMode);
	//PC->bShowMouseCursor = false;
#if PLATFORM_ANDROID || PLATFORM_IOS
	// 모바일 빌드에서만 커서 숨김
	PC->bShowMouseCursor = false;
#else
	// 에디터/PC 테스트에서는 커서 유지
	PC->bShowMouseCursor = true;
#endif
}
