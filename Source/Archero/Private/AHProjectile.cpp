// Fill out your copyright notice in the Description page of Project Settings.


#include "AHProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAHProjectile::AAHProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	RootComponent = SphereComp;
	SphereComp->InitSphereRadius(15.0f);

	//SphereComp->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = SphereComp;
	ProjectileMovement->InitialSpeed = 2000.f; // 초기 속도
	ProjectileMovement->MaxSpeed = 2000.f;     // 최대 속도
	ProjectileMovement->bRotationFollowsVelocity = true; // 날아가는 방향으로 회전
	ProjectileMovement->ProjectileGravityScale = 0.f;    // 중력 영향 0

	//SphereComp->OnComponentHit.AddDynamic(this, &AAHProjectile::OnHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AAHProjectile::OnProjectileOverlap);
}

// Called when the game starts or when spawned
void AAHProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAHProjectile::OnProjectileOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;


	bool IsSelf = (OtherActor == this);
	bool IsOwner = (OtherActor == GetOwner());
	bool IsProjectile = OtherActor->IsA(AAHProjectile::StaticClass());

	if (!IsSelf && !IsOwner && !IsProjectile)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, UDamageType::StaticClass());

		Destroy();
	}
}

// Called every frame
void AAHProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

