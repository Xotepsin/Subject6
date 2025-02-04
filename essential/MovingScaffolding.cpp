#include "MovingScaffolding.h"
#include "Components/BoxComponent.h"


AMovingScaffolding::AMovingScaffolding()
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

void AMovingScaffolding::BeginPlay()
{
    Super::BeginPlay();

    // ������ ���۵� �� �ʱ� ��ġ�� ����
    StartLocation = GetActorLocation();  // ��Ȯ�� ���� ��ġ�� ����
}


void AMovingScaffolding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FVector CurrentLocation = GetActorLocation();
    float DistanceTraveled = (CurrentLocation - StartLocation).X;
    
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
    FVector MoveDirection = bMovingForward ? FVector(1, 0, 0) : FVector(-1, 0, 0);
    FVector NewLocation = CurrentLocation + MoveDirection * MoveSpeed * DeltaTime;
    SetActorLocation(NewLocation);
}

