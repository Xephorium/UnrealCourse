#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Constructor
UWorldPosition::UWorldPosition() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UWorldPosition::BeginPlay() {
	Super::BeginPlay();
	
	PrintActorName();
	PrintActorTransform();
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWorldPosition::PrintActorName() const {

	/*--- Exercise #1: Create & Print a String Pointer ---*/

	// Note: The secret goal of this function is to play with & understand
	//       pointers. So we'll be doing a lot of toying around as we move
	//       toward printing the actual name. 

	FString LogOutput = TEXT("Hello");
	FString *Pointer = &LogOutput; // Creates pointer of type FString and
	                               // assigns it the address of LogOutput

	LogOutput.Len();  // Returns length of string.
	(*Pointer).Len(); // Same, but with a pointer!
	Pointer->Len();   // Same, but with a pointer & arrow operator!

	// Okay, so the line below actually won't work! 
    // ---> UE_LOG(LogTemp, Warning, TEXT("%s"), *Pointer);
	// Because the UE_LOG function is internally using the pure C++ printf()
	// to format, and (remember) printf() needs to be passed a string with an
	// asterisk for a normal FString variable, we need to first dereference the
	// pointer variable and then include the expected * for a string. 
	UE_LOG(LogTemp, Warning, TEXT("Output: %s"), **Pointer);
	// Apparently, the expected * for printf() isn't actually even dereferencing.
	// The printf() function overloads the * operator to check if the passed char
	// array has Len > 0 and return an empty char array if not. So there's a
	// dereference followed by an overloaded asterisk operator here. The earlier
	// lecture was a lie that was helpful for introducing pointers. :O


	/*--- Exercise #2: Print the Owning Actor's Name ---*/

	AActor *Owner = GetOwner(); // Stores a pointer to the owning Actor
    FString OwnerName = Owner->GetName(); // Accesses the name member of the dereferenced Actor
	OwnerName = (*Owner).GetName(); // Could also be done this way
	OwnerName = GetOwner()->GetName(); // Or this way
    UE_LOG(LogTemp, Warning, TEXT("Owner Name: %s"), *OwnerName); // Prints name! :)
}

void UWorldPosition::PrintActorTransform() const {

	/*--- Exercise #2: Print the Owning Actor's Transform (Location) ---*/

	// Gets Actor Location Directly
	FString OwnerTransformString = GetOwner()->GetActorLocation().ToString();
	
	// Gets Location Through Transform Class (Which Returns Loc, Rot, Sca)
	OwnerTransformString = GetOwner()->GetActorTransform().GetLocation().ToString();

	// Print Transform!
	UE_LOG(LogTemp, Warning, TEXT("Owner Location: %s"), *OwnerTransformString);
}