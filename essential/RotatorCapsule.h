#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatorCapsule.generated.h"

class UCapsuleComponent;

UCLASS()
class SPARTAPROJECT_API ARotatorCapsule : public AActor
{
	GENERATED_BODY()
	
public:	
	ARotatorCapsule();

protected:
	void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Capsule|Component")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Capsule|Component")
	UCapsuleComponent* Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Capsule|Component")
	UStaticMeshComponent* StaticMesh;
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float RotationSpeed = 10.0f;


};
