#include "OSSShadingPrivatePCH.h"

#include "MaterialExpressionOSSProjectVector.h"


#define LOCTEXT_NAMESPACE "UOSSProjectVector"

UMaterialExpressionOSSProjectVector::UMaterialExpressionOSSProjectVector(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
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


int32 UMaterialExpressionOSSProjectVector::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex)
{
    if (!PrjU.Expression) return Compiler->Errorf(TEXT("Missing input PrjU"));
    if (!PrjV.Expression) return Compiler->Errorf(TEXT("Missing input PrjV"));
    if (!PrjW.Expression) return Compiler->Errorf(TEXT("Missing input PrjW"));
    if (!X.Expression) return Compiler->Errorf(TEXT("Missing input X"));

    const int32 u = PrjU.Compile(Compiler);
    const int32 v = PrjV.Compile(Compiler);
    const int32 w = PrjW.Compile(Compiler);
    const int32 x = X.Compile(Compiler);

    return Compiler->AppendVector( 
           Compiler->AppendVector( Compiler->Div(Compiler->Dot(x, u), Compiler->Dot(u,u)),
                                   Compiler->Div(Compiler->Dot(x, v), Compiler->Dot(v,v))),
                                   Compiler->Div(Compiler->Dot(x, w), Compiler->Dot(w,w)));

}

void UMaterialExpressionOSSProjectVector::GetCaption(TArray<FString>& OutCaptions) const
{
    FString ret = TEXT("ProjectVector");

    OutCaptions.Add(ret);
}



