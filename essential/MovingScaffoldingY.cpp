#include "MovingScaffoldingY.h"
#include "Components/BoxComponent.h"

AMovingScaffoldingY::AMovingScaffoldingY()
{
	PrimaryActorTick.bCanEverTick = true;

    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
    Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    Collision->SetupAttachment(Scene);

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(Collision);

    bMovingForward = true;

}

void AMovingScaffoldingY::BeginPlay()
{
	Super::BeginPlay();
    StartLocation = GetActorLocation();
}

void AMovingScaffoldingY::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FVector CurrentLocation = GetActorLocation();
    float DistanceTraveled = (CurrentLocation - StartLocation).Y;

    // 왕복 여부를 판단하는 변수
    if (bMovingForward)
    {
        if (DistanceTraveled >= MaxRange)
        {
            // MaxRange에 도달하면 반대 방향으로 이동
            bMovingForward = false;
        }
    }
    else
    {
        if (DistanceTraveled <= 0.0f)
        {
            // StartLocation으로 돌아오면 다시 정방향으로 이동
            bMovingForward = true;
        }
    }
    // 정방향 또는 반대 방향으로 이동
    FVector MoveDirection = bMovingForward ? FVector(0, 1, 0) : FVector(0, -1, 0);
    FVector NewLocation = CurrentLocation + MoveDirection * MoveSpeed * DeltaTime;
    SetActorLocation(NewLocation);

}

