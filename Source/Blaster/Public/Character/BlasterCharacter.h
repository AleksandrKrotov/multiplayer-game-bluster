// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BlasterTypes/TurningInPlace.h"
#include "BlasterCharacter.generated.h"

UCLASS()
class BLASTER_API ABlasterCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ABlasterCharacter();

#pragma region Actor Interface

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void PostInitializeComponents() override;

#pragma endregion  Actor Interface

#pragma region Setter/Getter

    void SetOverlappingWeapon(AWeapon* InWeapon);
    bool IsWeaponEquipped() const;
    bool IsAiming() const;
    float GetSpeed() const;
    FORCEINLINE float GetAO_Yaw() const { return AO_Yaw; }
    FORCEINLINE float GetAO_Pitch() const { return AO_Pitch; }
    AWeapon* GetEquippedWeapon() const;
    FORCEINLINE ETurningInPlace GetTurningInPlace() const { return TurningInPlace; }

#pragma endregion  Setter/Getter

protected:
    virtual void BeginPlay() override;

    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);
    void EquipButtonPressed();
    void CrouchButtonPressed();
    void AimButtonPressed();
    void AimButtonReleased();
    void AimOffset(float DeltaTime);
    void TurnInPlace(float DeltaTime);

private:
    UPROPERTY(EditAnywhere, Category = Camera)
    class USpringArmComponent* CameraBoom;

    UPROPERTY(EditAnywhere, Category = Camera)
    class UCameraComponent* FollowCamera;

    UPROPERTY(EditAnywhere, Category = Camera)
    float InterpolationSpeed = 10.0f;

    UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
    class AWeapon* OverlappingWeapon;

    UPROPERTY(VisibleAnywhere)
    class UCombatComponent* CombatComponent;

    float AO_Yaw;
    float InterpAO_Yaw;
    float AO_Pitch;
    FRotator StartingAimRotation;

    ETurningInPlace TurningInPlace;

private:

    UFUNCTION(Server, Reliable)
    void ServerEquipButtonPressed();

#pragma region RepNotifyRegion
    UFUNCTION()
    void OnRep_OverlappingWeapon(AWeapon* InLastWeapon);
#pragma endregion RepNotifyRegion

};