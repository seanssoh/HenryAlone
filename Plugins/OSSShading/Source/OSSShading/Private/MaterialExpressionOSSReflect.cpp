#include "OSSShadingPrivatePCH.h"

#include "MaterialExpressionOSSReflect.h"

#define LOCTEXT_NAMESPACE "UMaterialExpressionOSSReflect"

UMaterialExpressionOSSReflect::UMaterialExpressionOSSReflect(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    // Structure to hold one-time initialization
    struct FConstructorStatics
    {
		FText NAME_Math;
		FText NAME_OSS;
        FConstructorStatics()
            : NAME_Math(LOCTEXT("Math", "Math"))
            , NAME_OSS(LOCTEXT("OSS", "OSS"))
        {
        }
    };
    static FConstructorStatics ConstructorStatics;

    MenuCategories.Add(ConstructorStatics.NAME_Math);
    MenuCategories.Add(ConstructorStatics.NAME_OSS);
}

int32 UMaterialExpressionOSSReflect::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex)
{
    if( !I.Expression ) return Compiler->Errorf(TEXT("Missing input I"));
    if( !N.Expression ) return Compiler->Errorf(TEXT("Missing input N"));

    const int32 n = N.Compile(Compiler);
    const int32 i = I.Compile(Compiler);
    const int32 cte2 = Compiler->Constant(2.0f);

    //return I - 2.0*dot(N, I)*N;
    return Compiler->Sub(i, Compiler->Mul(cte2, Compiler->Mul(n, Compiler->Dot(n, i))));
}

void UMaterialExpressionOSSReflect::GetCaption(TArray<FString>& OutCaptions) const
{
    FString ret = TEXT("Reflect");
    OutCaptions.Add(ret);
}






