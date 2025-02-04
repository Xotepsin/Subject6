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

    // 액터가 로컬 좌표계에서 Yaw 축으로 지정한 스피드만큼 회전
    FRotator RotationDelta(0.f, RotationSpeed * DealtaTime, 0.f);
    AddActorLocalRotation(RotationDelta);

}

