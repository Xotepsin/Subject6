#include "RotatorCapsule.h"
#include "Components/CapsuleComponent.h"


ARotatorCapsule::ARotatorCapsule()
{
 	
	PrimaryActorTick.bCanEverTick = true;

    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
    Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    Collision->SetupAttachment(Scene);

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(Collision);

}


void ARotatorCapsule::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARotatorCapsule::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // ���Ͱ� ���� ��ǥ�迡�� Yaw ������ ������ ���ǵ常ŭ ȸ��
    FRotator RotationDelta(0.f, RotationSpeed, 0.f);
    AddActorLocalRotation(RotationDelta);

}

