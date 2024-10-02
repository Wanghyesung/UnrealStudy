// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ABAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UABAnimInstance::UABAnimInstance()
{
	MovingThreshould = 3.f;
	JumpingThreshould = 100.f;
}

//ó�� ������ �� �ѹ�
void UABAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	//������� �ʱ�ȭ

	Owner = Cast<ACharacter>(GetOwningActor()); //���� �������ִ� ����Ÿ�� ��������
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();//ĳ���� �����Ʈ ��������
	}
}

//�� ������ ȣ��
void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{

	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();//xy�� ũ�⸸ ��������

		bIsIdle = GroundSpeed < MovingThreshould;
		bIsFalling = Movement->IsFalling(); //����������
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshould);//������������
	}
}
