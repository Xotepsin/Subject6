#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingScaffoldingY.generated.h"

class UBoxComponent;

UCLASS()
class SPARTAPROJECT_API AMovingScaffoldingY : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovingScaffoldingY();

protected:
	void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scaffolding|Component")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scaffolding|Component")
	UBoxComponent* Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scaffolding|Component")
	UStaticMeshComponent* StaticMesh;

	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float MoveSpeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float MaxRange = 1000.0f;

private:
	FVector StartLocation;
	bool bMovingForward;

};
