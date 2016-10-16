#include "OSSShadingPrivatePCH.h"

#include "MaterialExpressionOSSUnprojectPoint.h"


#define LOCTEXT_NAMESPACE "UOSSUnprojectPoint"

UMaterialExpressionOSSUnprojectPoint::UMaterialExpressionOSSUnprojectPoint(const FObjectInitializer& ObjectInitializer)
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


int32 UMaterialExpressionOSSUnprojectPoint::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex)
{
    if (!X.Expression) return Compiler->Errorf(TEXT("Missing input X"));
    if (!PrjC.Expression) return Compiler->Errorf(TEXT("Missing input PrjC"));
    if (!PrjU.Expression) return Compiler->Errorf(TEXT("Missing input PrjU"));
    if (!PrjV.Expression) return Compiler->Errorf(TEXT("Missing input PrjV"));
    if (!PrjW.Expression) return Compiler->Errorf(TEXT("Missing input PrjW"));

    const int32 p = X.Compile(Compiler);
    const int32 c = PrjC.Compile(Compiler);
    const int32 u = PrjU.Compile(Compiler);
    const int32 v = PrjV.Compile(Compiler);
    const int32 w = PrjW.Compile(Compiler);

    const int32 x = Compiler->ComponentMask(p, true,  false, false, false);
    const int32 y = Compiler->ComponentMask(p, false, true,  false, false);
    const int32 z = Compiler->ComponentMask(p, false, false, true, false);

    return Compiler->Add( Compiler->Add(Compiler->Add(Compiler->Mul(x, u), Compiler->Mul(y, v)), Compiler->Mul(z, w)), c );
}

void UMaterialExpressionOSSUnprojectPoint::GetCaption(TArray<FString>& OutCaptions) const
{
    FString ret = TEXT("UnorojectPoint");

    OutCaptions.Add(ret);
}



