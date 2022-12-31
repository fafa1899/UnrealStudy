// Fill out your copyright notice in the Description page of Project Settings.


#include "StudyNote1MainActor.h"
#include "Output.h"

// Sets default values
AStudyNote1MainActor::AStudyNote1MainActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStudyNote1MainActor::BeginPlay()
{
	Super::BeginPlay();
	
	Output::PrintScreen("测试输出内容:%d,%s", 5, "ccc");
	Output::PrintLogWarning("测试输出内容:%d,%s", 5, "ccc");
    Output::PrintLogError("测试输出内容:%d,%s", 5, "ccc");
}

// Called every frame
void AStudyNote1MainActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

