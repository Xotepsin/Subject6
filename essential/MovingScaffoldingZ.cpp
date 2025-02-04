#include "MovingScaffoldingZ.h"
#include "Components/BoxComponent.h"

AMovingScaffoldingZ::AMovingScaffoldingZ()
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

void AMovingScaffoldingZ::BeginPlay()
{
	Super::BeginPlay();

    StartLocation = GetActorLocation();
	
}

void AMovingScaffoldingZ::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FVector CurrentLocation = GetActorLocation();
    float DistanceTraveled = (CurrentLocation - StartLocation).Z;

    // �պ� ���θ� �Ǵ��ϴ� ����
    if (bMovingForward)
    {
        if (DistanceTraveled >= MaxRange)
        {
            // MaxRange�� �����ϸ� �ݴ� �������� �̵�
            bMovingForward = false;
        }
    }
    else
    {
        if (DistanceTraveled <= 0.0f)
        {
            // StartLocation���� ���ƿ��� �ٽ� ���������� �̵�
            bMovingForward = true;
        }
    }
    // ������ �Ǵ� �ݴ� �������� �̵�
    FVector MoveDirection = bMovingForward ? FVector(0, 0, 1) : FVector(0, 0, -1);
    FVector NewLocation = CurrentLocation + MoveDirection * MoveSpeed * DeltaTime;
    SetActorLocation(NewLocation);
}

