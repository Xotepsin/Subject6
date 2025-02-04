# 6번 필수 과제
---
제가 강의를 4주차까지 듣고 과제를 하는걸로 착각을해서 과제를 좀 늦게시작해서 원래 강의를 들으면서 만든 프로젝트에다가 SubjectLevel이라는 맵을 만들어서 배치하여 진행하였습니다.

## 움직이는 발판

### 발판의 Component
	
저는 우선 움직이는 발판의 경우

```cpp
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scaffolding|Component")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scaffolding|Component")
	UBoxComponent* Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scaffolding|Component")
	UStaticMeshComponent* StaticMesh;
```
`MovingScaffolding.h`

```
    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
    Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    Collision->SetupAttachment(Scene);

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(Collision);
```
`MovingScaffolding.cpp`

`RootComponent` Scene을 달고 그아래에 Box모양의 `Collision`과 발판의 모양과 재질을 추가해주는 `StaticMesh` 도 달아주었습니다.


### 발판 움직이게 하기

```cpp
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
```
`MovingScaffolding.h`
그리고 필수기능에 있는 발판의 속도 `MoveSpeed`, `MaxRange`와 같은 변수를 public에 선언해주었습니다. 또한 UPROPERTY로 리플렉션을 해주었습니다.
그리고 private:에는 이 액터의 위치인 `StartLocation` 그리고 뒤에 로직에 사용하기위한 이 액터가 왔다갔다하기위해 정방향인지 역방향인지 구분하기 위한 `bool`타입의 `bMovingForward` 변수를 선언했습니다. 이 두 변수는 외부에 공개할 필요없이 로직 안에서만 필요하기때문에 private에 선언하였습니다.

```cpp
void AMovingScaffolding::BeginPlay()
{
    Super::BeginPlay();

    // 게임이 시작될 때 초기 위치를 설정
    StartLocation = GetActorLocation();  // 정확한 시작 위치로 설정
}
```
`MovingScaffolding.cpp`

그 후 이 액터의 위치를 가져오기 위해 `GetActorLocation()`함수를 사용하여 `StartLocation` 변수에 초기화하였습니다. 제가 원래 처음에는 이 부분을 생성자에 넣었더니 계속해서 제가 원하는 값이 안나오길래 로그를 찍어봤더니 제가 이 액터를 월드레벨에 추가하기 위해 대충 아무대나 드래그해서 집어넣은 곳이 이 StartLocation변수에 들어가서 제가 원하는대로 액터가 움직이지 않아주었습니다. 그래서 `BeginPlay()` 즉 게임이 시작되었을때를 초기위치로 설정해 주어야 로직이 제가 원하는대로 옳바르게 작동하는 것을 확인하고 수정하였습니다.

```cpp
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

```
그 후 생성자에 `bMovingForward`의 값을 true값을 저장하였습니다. 처음에는 정방향으로 움직여야 하기때문에...

```cpp
void AMovingScaffolding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FVector CurrentLocation = GetActorLocation();
    float DistanceTraveled = (CurrentLocation - StartLocation).X;
    
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
    FVector MoveDirection = bMovingForward ? FVector(1, 0, 0) : FVector(-1, 0, 0);
    FVector NewLocation = CurrentLocation + MoveDirection * MoveSpeed * DeltaTime;
    SetActorLocation(NewLocation);
}
```
그 후 Tick함수 로직입니다. `CurrentLocation`은 말 그대로 현재 액터의 위치이고 `GetActorLocation()`함수로 위치를 가져옵니다. `DistanceTraveled` 변수는 이 액터가 움직인 거리를 저장하는 변수입니다.

그후 `if`문으로 왕복 여부를 판단하고 정방향이면 `FVector(1,0,0)` 즉 X축으로 양방향으로 역방향이라면 X축의 음방향으로 움직이게 했습니다. 
![](https://velog.velcdn.com/images/xotepsin/post/7c5bc223-0f63-4cd5-a7ad-1f5defbced84/image.png)

제가 이렇게 움직이는 발판을 X,Y,Z를 만들었는데요 이건 그냥 `float DistanceTraveled = (CurrentLocation - StartLocation).X;`이 부분에서 X값만 Y,Z값으로 바꾸고 `FVector MoveDirection = bMovingForward ? FVector(1, 0, 0) : FVector(-1, 0, 0);` 여기서 1과,-1의 위치만 X,Y,Z축으로 바꾸었습니다.

## 회전하는 액터

### 회전하는 액터의 컴포넌트

```cpp
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
```
`RotatorCapsule.h`
```cpp
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
```
`RotatorCapsule.cpp`

회전하는 액터는 캡슐모양으로 만들고싶어서 `Component`또한 `CapsuleComponent`를 달았습니다. 그리고 액터가 회전해야하기때문에 회전할 스피드를 `RotationSpeed` 변수로 추가하고 `UPROPERTY`로 리플렉션 해주었습니다.

```cpp
void ARotatorCapsule::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // 액터가 로컬 좌표계에서 Yaw 축으로 지정한 스피드만큼 회전
    FRotator RotationDelta(0.f, RotationSpeed * DeltaTime, 0.f);
    AddActorLocalRotation(RotationDelta);

}
```
`RotatorCapsule.cpp`
그 후 간단하게 `RotationDelta`를 사용하여 `RotationSpeed`변수에 `DeltaTime`변수를 곱해서 프레임 독립적인 동작을 위해 사용하였습니다.
## 시연 영상
---
![](https://velog.velcdn.com/images/xotepsin/post/74841eb5-535c-4e1a-b6c4-f7b2e22ebecb/image.gif)
![업로드중..](blob:https://velog.io/71dd7369-2332-404f-99c2-0d91fa28b466)

