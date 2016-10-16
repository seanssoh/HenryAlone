#include "OSSShadingPrivatePCH.h"

#include "MaterialExpressionOSSProjector.h"


#define LOCTEXT_NAMESPACE "UOSSProjector"

UMaterialExpressionOSSProjector::UMaterialExpressionOSSProjector(const FObjectInitializer& ObjectInitializer)
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

    ConstScale = 1.0f;

    MenuCategories.Add(ConstructorStatics.NAME_OSS);
}


int32 UMaterialExpressionOSSProjector::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex)
{
    if (!PrjC.Expression) return Compiler->Errorf(TEXT("Missing input PrjC"));
    if (!PrjU.Expression) return Compiler->Errorf(TEXT("Missing input PrjU"));
    if (!PrjV.Expression) return Compiler->Errorf(TEXT("Missing input PrjV"));

    const int32 ctp0d0 = Compiler->Constant( 0.0f);
    const int32 ctp0d5 = Compiler->Constant( 0.5f);
    const int32 ctp1d0 = Compiler->Constant( 1.0f);
    const int32 ctm1d0 = Compiler->Constant(-1.0f);
    

    const int32 s = Scale.Expression ? Scale.Compile(Compiler) : Compiler->Constant(ConstScale);

    const int32 c = PrjC.Compile(Compiler);
    const int32 u = PrjU.Compile(Compiler);
    const int32 v = PrjV.Compile(Compiler);

    const int32 p = Compiler->WorldPosition(WPT_Default);
    const int32 r = Compiler->Sub( p, c );

    const int32 z = Compiler->Div( Compiler->AppendVector( Compiler->Div( Compiler->Dot(r, u), Compiler->Dot(u,u)),
                                                           Compiler->Div( Compiler->Dot(r, v), Compiler->Dot(v,v))),
                                                           s);

    const int32 w = (Rotate180) ? Compiler->Mul(z, ctm1d0)  : z;

    if (RemapClampUnit)
    {
        return Compiler->Clamp( Compiler->Add( Compiler->Mul(w,ctp0d5), ctp0d5), ctp0d0, ctp1d0 );
    }

    return w;
}

void UMaterialExpressionOSSProjector::GetCaption(TArray<FString>& OutCaptions) const
{
    FString ret = TEXT("Projector");

    OutCaptions.Add(ret);
}



