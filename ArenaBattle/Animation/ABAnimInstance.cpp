// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ABAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UABAnimInstance::UABAnimInstance()
{
	MovingThreshould = 3.f;
	JumpingThreshould = 100.f;
}

//처음 생성될 때 한번
void UABAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	//멤버변수 초기화

	Owner = Cast<ACharacter>(GetOwningActor()); //현재 가지고있는 액터타입 가져오기
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();//캐릭터 무브먼트 가져오기
	}
}

//매 프레임 호출
void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{

	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();//xy의 크기만 가져오기

		bIsIdle = GroundSpeed < MovingThreshould;
		bIsFalling = Movement->IsFalling(); //떨어지는지
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshould);//점프상태인지
	}
}
