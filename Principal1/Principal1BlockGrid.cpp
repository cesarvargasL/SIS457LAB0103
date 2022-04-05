// Copyright Epic Games, Inc. All Rights Reserved.

#include "Principal1BlockGrid.h"
#include "Principal1Block.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

APrincipal1BlockGrid::APrincipal1BlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(200.f,0.f,0.f));
	ScoreText->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(0)));
	ScoreText->SetupAttachment(DummyRoot);

	// Create static mesh component
	biografia = CreateDefaultSubobject<UTextRenderComponent>(TEXT("mi_biografia0"));
	biografia->SetRelativeLocation(FVector(200.f, 0.f, 0.f));
	biografia->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	biografia->SetText(FText::Format(LOCTEXT("ScoreFmt", "biografia de cesar: {0}"), FText::AsNumber(0)));
	biografia->SetupAttachment(DummyRoot);

	// Set defaults
	Size = 3;
	BlockSpacing = 300.f;
}


void APrincipal1BlockGrid::BeginPlay()
{
	Super::BeginPlay();

	// Number of blocks
	const int32 NumBlocks = Size * Size;

	// Loop to spawn each block
	for(int32 BlockIndex=0; BlockIndex<NumBlocks; BlockIndex++)
	{
		const float XOffset = (BlockIndex/Size) * BlockSpacing; // Divide by dimension
		const float YOffset = (BlockIndex%Size) * BlockSpacing; // Modulo gives remainder

		// Make position vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		// Spawn a block
		APrincipal1Block* NewBlock = GetWorld()->SpawnActor<APrincipal1Block>(BlockLocation, FRotator(0,0,0));

		// Tell the block about its owner
		if (NewBlock != nullptr)
		{
			NewBlock->OwningGrid = this;
		}
	}
}


void APrincipal1BlockGrid::AddScore()
{
	// Increment score
	Score++;

	// Update text
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(Score)));

	// Update text
	biografia->SetText(FText::Format(LOCTEXT("ScoreFmt", "biografia_de_cesar: {0}"), FText::AsNumber(Score)));
}

#undef LOCTEXT_NAMESPACE
