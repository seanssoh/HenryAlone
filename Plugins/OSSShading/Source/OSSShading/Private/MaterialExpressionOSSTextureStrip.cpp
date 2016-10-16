#include "OSSShadingPrivatePCH.h"

#include "MaterialExpressionOSSTextureStrip.h"


#define LOCTEXT_NAMESPACE "UOSSTextureStrip"

UMaterialExpressionOSSTextureStrip::UMaterialExpressionOSSTextureStrip(const FObjectInitializer& ObjectInitializer)
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

    ConstID = 0.0f;
    ConstNum = 1.0f;
    ConstTileOffset = 0;

    MenuCategories.Add(ConstructorStatics.NAME_OSS);
}


int32 UMaterialExpressionOSSTextureStrip::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex)
{
    if (!UV.Expression) return Compiler->Errorf(TEXT("Missing input UV"));

    const int32 uvs = UV.Compile(Compiler);
    const int32 rid = ID.Expression  ? ID.Compile(Compiler)  : Compiler->Constant(ConstID);
    const int32 num = Num.Expression ? Num.Compile(Compiler) : Compiler->Constant(ConstNum);

    const int32 ctp0d5 = Compiler->Constant( 0.5f);
    const int32 tof = Compiler->Constant((float)ConstTileOffset);
    const int32 iid = Compiler->Floor(Compiler->Add(Compiler->Add(rid, tof), ctp0d5 ) );

    const int32 u = Compiler->ComponentMask( uvs, true,  false, false, false );
    const int32 v = Compiler->ComponentMask( uvs, false, true,  false, false );

    //return Compiler->AppendVector( Compiler->Div( Compiler->Add( u, iid ), num ), v );
    return Compiler->AppendVector(u, Compiler->Div(Compiler->Add(v, iid), num));
}

void UMaterialExpressionOSSTextureStrip::GetCaption(TArray<FString>& OutCaptions) const
{
    FString ret = TEXT("Texture Strip");

    OutCaptions.Add(ret);
}



