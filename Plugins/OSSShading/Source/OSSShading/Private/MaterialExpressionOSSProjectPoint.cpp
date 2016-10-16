#include "OSSShadingPrivatePCH.h"

#include "MaterialExpressionOSSProjectPoint.h"


#define LOCTEXT_NAMESPACE "UOSSProjectPoint"

UMaterialExpressionOSSProjectPoint::UMaterialExpressionOSSProjectPoint(const FObjectInitializer& ObjectInitializer)
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


int32 UMaterialExpressionOSSProjectPoint::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex)
{
    if (!PrjC.Expression) return Compiler->Errorf(TEXT("Missing input PrjC"));
    if (!PrjU.Expression) return Compiler->Errorf(TEXT("Missing input PrjU"));
    if (!PrjV.Expression) return Compiler->Errorf(TEXT("Missing input PrjV"));
    if (!PrjW.Expression) return Compiler->Errorf(TEXT("Missing input PrjW"));
    if (!X.Expression) return Compiler->Errorf(TEXT("Missing input X"));

    const int32 c = PrjC.Compile(Compiler);
    const int32 u = PrjU.Compile(Compiler);
    const int32 v = PrjV.Compile(Compiler);
    const int32 w = PrjW.Compile(Compiler);
    const int32 p = X.Compile(Compiler);

    const int32 r = Compiler->Sub( p, c );

    return Compiler->AppendVector( 
           Compiler->AppendVector( Compiler->Div(Compiler->Dot(r, u), Compiler->Dot(u,u)),
                                   Compiler->Div(Compiler->Dot(r, v), Compiler->Dot(v,v))),
                                   Compiler->Div(Compiler->Dot(r, w), Compiler->Dot(w,w)));

}

void UMaterialExpressionOSSProjectPoint::GetCaption(TArray<FString>& OutCaptions) const
{
    FString ret = TEXT("ProjectPoint");

    OutCaptions.Add(ret);
}



