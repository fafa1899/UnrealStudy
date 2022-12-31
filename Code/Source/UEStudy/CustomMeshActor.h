// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "CustomMeshActor.generated.h"

UCLASS()
class UESTUDY_API ACustomMeshActor : public AActor {
  GENERATED_BODY()

 public:
  // Sets default values for this actor's properties
  ACustomMeshActor();

 protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  UStaticMesh* CreateMesh();
  void CreateGeometry(FStaticMeshRenderData* RenderData); 
  UMaterial* CreateMaterial();

 public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  UStaticMeshComponent* staticMeshComponent;
};
