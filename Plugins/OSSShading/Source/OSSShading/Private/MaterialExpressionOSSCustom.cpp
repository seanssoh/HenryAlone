#include "OSSShadingPrivatePCH.h"

#include "MaterialExpressionOSSCustom.h"
//#include "Private/Materials/HLSLMaterialTranslator.h"

#define LOCTEXT_NAMESPACE "OSSCustom"

UMaterialExpressionOSSCustom::UMaterialExpressionOSSCustom(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    // Structure to hold one-time initialization
    struct FConstructorStatics
    {
		FText NAME_OSS;
        FConstructorStatics()
			: NAME_OSS(LOCTEXT("OSS", "OSS"))
        {
        }
    };
    static FConstructorStatics ConstructorStatics;

    mConstX = 0.0f;
    mConstM = 1.0f;
    mConstN = 0.0f;

    MenuCategories.Add(ConstructorStatics.NAME_OSS);
}

int32 UMaterialExpressionOSSCustom::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex)
{
    TArray<int32> CompiledInputs;

//    int32 Arg1 = X.Expression ? X.Compile(Compiler) : Compiler->Constant(mConstX);
    //int32 Arg2 = M.Expression ? M.Compile(Compiler) : Compiler->Constant(mConstM);
    //int32 Arg3 = N.Expression ? N.Compile(Compiler) : Compiler->Constant(mConstN);
    CompiledInputs.Add(INDEX_NONE);
    return INDEX_NONE;

    //FHLSLMaterialTranslator *c = (FHLSLMaterialTranslator*)Compiler;
    //return c->AddCodeChunk(MCT_Float4, *CodeChunk);

    //return Compiler->CustomExpression(this, CompiledInputs);
}

void UMaterialExpressionOSSCustom::GetCaption(TArray<FString>& OutCaptions) const
{
    FString ret = TEXT("Custom");

    OutCaptions.Add(ret);
}




