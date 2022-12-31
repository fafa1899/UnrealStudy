// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomMeshActor.h"
#include "Output.h"

// Sets default values
ACustomMeshActor::ACustomMeshActor() {
  // Set this actor to call Tick() every frame.  You can turn this off to
  // improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACustomMeshActor::BeginPlay() {
  Super::BeginPlay();

  staticMeshComponent = NewObject<UStaticMeshComponent>(this);

  staticMeshComponent->SetMobility(EComponentMobility::Stationary);
  SetRootComponent(staticMeshComponent);
  staticMeshComponent->RegisterComponent();

  UStaticMesh* mesh = CreateMesh();
  if (mesh) {
    staticMeshComponent->SetStaticMesh(mesh);
  }  
}

UStaticMesh* ACustomMeshActor::CreateMesh() {
  UStaticMesh* mesh = NewObject<UStaticMesh>(staticMeshComponent);
  mesh->NeverStream = true;
  mesh->SetIsBuiltAtRuntime(true);

  TUniquePtr<FStaticMeshRenderData> RenderData =
      MakeUnique<FStaticMeshRenderData>();

  CreateGeometry(RenderData.Get());

  UMaterial* material = CreateMaterial();
  mesh->AddMaterial(material);

  mesh->SetRenderData(MoveTemp(RenderData));
  mesh->InitResources();
  mesh->CalculateExtendedBounds();  //设置包围盒之后调用这个函数起效，否则会被视锥体剔除
  return mesh;
}

UMaterial* ACustomMeshActor::CreateMaterial() {
  UMaterial* material = (UMaterial*)StaticLoadObject(
      UMaterial::StaticClass(), nullptr,
      TEXT("Material'/Game/Materials/RedColor.RedColor'"));
  
  return material;
}

void ACustomMeshActor::CreateGeometry(FStaticMeshRenderData* RenderData) {
  RenderData->AllocateLODResources(1);
  FStaticMeshLODResources& LODResources = RenderData->LODResources[0];

  int vertexNum = 4;

  TArray<FVector> xyzList;
  xyzList.Add(FVector(0, 0, 50));
  xyzList.Add(FVector(100, 0, 50));
  xyzList.Add(FVector(100, 100, 50));
  xyzList.Add(FVector(0, 100, 50));

  TArray<FVector2D> uvList;
  uvList.Add(FVector2D(0, 1));
  uvList.Add(FVector2D(0, 0));
  uvList.Add(FVector2D(1, 0));
  uvList.Add(FVector2D(1, 1));

  // 设置顶点数据
  TArray<FStaticMeshBuildVertex> StaticMeshBuildVertices;
  StaticMeshBuildVertices.SetNum(vertexNum);
  for (int m = 0; m < vertexNum; m++) {
    StaticMeshBuildVertices[m].Position = xyzList[m];
    StaticMeshBuildVertices[m].Color = FColor(255, 0, 0);
    StaticMeshBuildVertices[m].UVs[0] = uvList[m];
    StaticMeshBuildVertices[m].TangentX = FVector(0, 1, 0);  //切线
    StaticMeshBuildVertices[m].TangentY = FVector(1, 0, 0);  //副切线
    StaticMeshBuildVertices[m].TangentZ = FVector(0, 0, 1);  //法向量
  }

  LODResources.bHasColorVertexData = false;

  //顶点buffer
  LODResources.VertexBuffers.PositionVertexBuffer.Init(StaticMeshBuildVertices);

  //法线，切线，贴图坐标buffer
  LODResources.VertexBuffers.StaticMeshVertexBuffer.Init(
      StaticMeshBuildVertices, 1);

  //设置索引数组
  TArray<uint32> indices;
  int numTriangles = 2;
  int indiceNum = numTriangles * 3;
  indices.SetNum(indiceNum);
  indices[0] = 2;
  indices[1] = 1;
  indices[2] = 0;
  indices[3] = 3;
  indices[4] = 2;
  indices[5] = 0;

  LODResources.IndexBuffer.SetIndices(indices,
                                      EIndexBufferStride::Type::AutoDetect);

  LODResources.bHasDepthOnlyIndices = false;
  LODResources.bHasReversedIndices = false;
  LODResources.bHasReversedDepthOnlyIndices = false;
  // LODResources.bHasAdjacencyInfo = false;

  FStaticMeshLODResources::FStaticMeshSectionArray& Sections =
      LODResources.Sections;
  FStaticMeshSection& section = Sections.AddDefaulted_GetRef();
  section.bEnableCollision = false;

  section.MaterialIndex = 0;
  section.NumTriangles = numTriangles;
  section.FirstIndex = 0;
  section.MinVertexIndex = 0;
  section.MaxVertexIndex = vertexNum - 1;

  double boundArray[7] = {0, 0, 0, 200, 200, 200, 200};
  // ComputationalGeometry::BoundingVolumeFromPoints(xyzList, boundArray);

  // Output::PrintLogWarning("范围");
  // for (int i = 0; i < 7; i++)
  //{
  //	Output::PrintLogWarning("%lf",boundArray[i]);
  //}

  //设置包围盒
  FBoxSphereBounds BoundingBoxAndSphere;
  BoundingBoxAndSphere.Origin =
      FVector(boundArray[0], boundArray[1], boundArray[2]);
  BoundingBoxAndSphere.BoxExtent =
      FVector(boundArray[3], boundArray[4], boundArray[5]);
  BoundingBoxAndSphere.SphereRadius = boundArray[6];
  RenderData->Bounds = BoundingBoxAndSphere;
}

// Called every frame
void ACustomMeshActor::Tick(float DeltaTime) { Super::Tick(DeltaTime); }
