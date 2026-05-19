#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AHDefaultGameState.generated.h"


enum GameClearState
{
	Play,
	Lose,
	Win
};
/**
 *
 */
UCLASS()
class ARCHERO_API AAHDefaultGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	class AAHDefaultCharacter* playerCharacter = nullptr;

	GameClearState currentState = GameClearState::Play;

	UPROPERTY(EditAnywhere, Category = "Play", meta = (AllowPrivateAccess = "true"))
	float ClearTime = 300.f;
	float LeftTime;
public:
	AAHDefaultGameState();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	//virtual FString GetTimeString();
};