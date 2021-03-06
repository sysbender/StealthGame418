// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
//#include "GameFramework/PlayerController.h"

#include "Kismet/GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn)
{
	if (InstigatorPawn) {
		InstigatorPawn->DisableInput(nullptr);

		if (SpectatingViewpointClass) {

			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);
			// change view target if any valid actor found
			if (ReturnedActors.Num() > 0) {
				AActor*  AANewViewTarget = ReturnedActors[0];

				APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
				if (PC) {
					PC->SetViewTargetWithBlend(AANewViewTarget, 1.0f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is nullptr, please update GameMode class iwth valid subclass. Cannot change view target"));
			}


		}


	}

	OnMissionCompleted(InstigatorPawn);


}
