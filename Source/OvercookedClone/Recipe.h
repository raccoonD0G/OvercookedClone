#pragma once

#include "CoreMinimal.h"
#include "Recipe.generated.h"

UENUM(BlueprintType)
enum class EIngredientType : uint8
{
    None        UMETA(DisplayName = "None"),

    // 기본 채소
    Lettuce     UMETA(DisplayName = "Lettuce"),
    Tomato      UMETA(DisplayName = "Tomato"),
    Cucumber    UMETA(DisplayName = "Cucumber"),
    Onion       UMETA(DisplayName = "Onion"),
    Carrot      UMETA(DisplayName = "Carrot"),
    Mushroom    UMETA(DisplayName = "Mushroom"),
    Potato      UMETA(DisplayName = "Potato"),

    // 고기 & 해산물
    Beef        UMETA(DisplayName = "Beef"),
    Chicken     UMETA(DisplayName = "Chicken"),
    Fish        UMETA(DisplayName = "Fish"),
    Shrimp      UMETA(DisplayName = "Shrimp"),

    // 탄수화물 / 베이스
    Rice        UMETA(DisplayName = "Rice"),
    Dough       UMETA(DisplayName = "Dough"),
    Bread       UMETA(DisplayName = "Bread"),
    BurgerBun   UMETA(DisplayName = "Burger Bun"),
    Tortilla    UMETA(DisplayName = "Tortilla"),
    Seaweed     UMETA(DisplayName = "Seaweed"),

    // 기타
    Cheese      UMETA(DisplayName = "Cheese"),
    Egg         UMETA(DisplayName = "Egg"),
    Flour       UMETA(DisplayName = "Flour"),
    TomatoSauce UMETA(DisplayName = "Tomato Sauce")
};

UENUM(BlueprintType)
enum class EIngredientState : uint8
{
    Raw         UMETA(DisplayName = "Raw"),
    Chopped     UMETA(DisplayName = "Chopped"),
    Cooked      UMETA(DisplayName = "Cooked"),
    Fried       UMETA(DisplayName = "Fried"),
    Boiled      UMETA(DisplayName = "Boiled"),
    Baked       UMETA(DisplayName = "Baked"),
    Burned      UMETA(DisplayName = "Burned")
};

UENUM(BlueprintType)
enum class ERecipeType : uint8
{
    None        UMETA(DisplayName = "None"),

    Salad       UMETA(DisplayName = "Salad"),
    Soup        UMETA(DisplayName = "Soup"),
    Sushi       UMETA(DisplayName = "Sushi"),
    Hamburger   UMETA(DisplayName = "Hamburger"),
    Pizza       UMETA(DisplayName = "Pizza"),
    Burrito     UMETA(DisplayName = "Burrito"),
    FriedDish   UMETA(DisplayName = "Fried Dish"),
    Cake        UMETA(DisplayName = "Cake")
};

USTRUCT(BlueprintType)
struct FIngredientInfo
{
    GENERATED_BODY()
    
    FIngredientInfo() : Ingredient(EIngredientType::None), RequiredState(EIngredientState::Raw) { }
    FIngredientInfo(EIngredientType NewIngredient, EIngredientState NewRequiredState) : Ingredient(NewIngredient), RequiredState(NewRequiredState) { }

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EIngredientType Ingredient;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EIngredientState RequiredState;

    bool operator==(const FIngredientInfo& Other) const
    {
        return Ingredient == Other.Ingredient && RequiredState == Other.RequiredState;
    }
};

FORCEINLINE uint32 GetTypeHash(const FIngredientInfo& Info)
{
    return HashCombine(::GetTypeHash(Info.Ingredient), ::GetTypeHash(Info.RequiredState));
}

USTRUCT(BlueprintType)
struct FRecipeData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ERecipeType RecipeType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FIngredientInfo> RequiredIngredients;
};
