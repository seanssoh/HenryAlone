#include "OSSShadingPrivatePCH.h"

#include "MaterialExpressionOSSUnprojectVector.h"


#define LOCTEXT_NAMESPACE "UOSSUnprojectVector"

UMaterialExpressionOSSUnprojectVector::UMaterialExpressionOSSUnprojectVector(const FObjectInitializer& ObjectInitializer)
:	Super(ObjectInitializer)
{
    // Structure to hold one-time initialization
    struct FConstructorStatics
    {
		FText NAME_Math;
		FText NAME_OSS;
        FConstructorStatics()
			: NAME_OSS(LOCTEXT("OSS", "OSS"))
        {
        }
    };
    static FConstructorStatics ConstructorStatics;

    MenuCategories.Add(ConstructorStatics.NAME_OSS);
}


int32 UMaterialExpressionOSSUnprojectVector::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex)
{
    if (!X.Expression) return Compiler->Errorf(TEXT("Missing input X"));
    if (!PrjU.Expression) return Compiler->Errorf(TEXT("Missing input PrjU"));
    if (!PrjV.Expression) return Compiler->Errorf(TEXT("Missing input PrjV"));
    if (!PrjW.Expression) return Compiler->Errorf(TEXT("Missing input PrjW"));

    const int32 p = X.Compile(Compiler);
    const int32 u = PrjU.Compile(Compiler);
    const int32 v = PrjV.Compile(Compiler);
    const int32 w = PrjW.Compile(Compiler);

    const int32 x = Compiler->ComponentMask(p, true,  false, false, false);
    const int32 y = Compiler->ComponentMask(p, false, true,  false, false);
    const int32 z = Compiler->ComponentMask(p, false, false, true,  false);

    return Compiler->Add(Compiler->Add(Compiler->Mul(x, u), Compiler->Mul(y, v)), Compiler->Mul(z, w));
}

void UMaterialExpressionOSSUnprojectVector::GetCaption(TArray<FString>& OutCaptions) const
{
    FString ret = TEXT("UnorojectVector");

    OutCaptions.Add(ret);
}



