#include "ColorPicker.h"
#include "ColorSwatchButton.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/SizeBox.h"
#include "Components/WrapBoxSlot.h"

void UColorPicker::NativeConstruct()
{
	Super::NativeConstruct();

	if (!ColorGrid)
	{
		UE_LOG(LogTemp, Warning, TEXT("UColorPicker: ColorGrid is not bound."));
		return;
	}

	ColorGrid->ClearChildren();

	for (const FLinearColor& SwatchColor : Palette)
	{
		UColorSwatchButton* SwatchButton = WidgetTree
			? WidgetTree->ConstructWidget<UColorSwatchButton>(UColorSwatchButton::StaticClass())
			: NewObject<UColorSwatchButton>(this);

		if (!SwatchButton)
		{
			continue;
		}

		USizeBox* SwatchSize = WidgetTree
			? WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass())
			: NewObject<USizeBox>(this);
		UBorder* SwatchFill = WidgetTree
			? WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass())
			: NewObject<UBorder>(this);

		if (!SwatchSize || !SwatchFill)
		{
			continue;
		}

		SwatchSize->SetWidthOverride(28.0f);
		SwatchSize->SetHeightOverride(28.0f);
		SwatchFill->SetBrushColor(SwatchColor);
		SwatchSize->SetContent(SwatchFill);
		SwatchButton->SetContent(SwatchSize);
		SwatchButton->SwatchColor = SwatchColor;

		SwatchButton->OnSwatchColorClicked.RemoveDynamic(this, &UColorPicker::OnSwatchColorClicked);
		SwatchButton->OnSwatchColorClicked.AddDynamic(this, &UColorPicker::OnSwatchColorClicked);
		ColorGrid->AddChildToWrapBox(SwatchButton);

		if (UWrapBoxSlot* WrapSlot = Cast<UWrapBoxSlot>(SwatchButton->Slot))
		{
			WrapSlot->SetPadding(FMargin(2.0f));
		}
	}
}

void UColorPicker::OnColorButtonClicked(FLinearColor Color)
{
	if (HexText)
	{
		HexText->SetText(FText::FromString(ToHex(Color)));
	}

	OnColorSelected.Broadcast(Color);
}

FLinearColor UColorPicker::ParseHexColor(const FString& HexString)
{
	FString Sanitized = HexString.TrimStartAndEnd();
	if (Sanitized.StartsWith(TEXT("#")))
	{
		Sanitized.RightChopInline(1);
	}

	if (Sanitized.Len() == 6)
	{
		Sanitized.Append(TEXT("FF"));
	}

	if (Sanitized.Len() != 8)
	{
		return FLinearColor::White;
	}

	return FLinearColor::FromSRGBColor(FColor::FromHex(Sanitized));
}

FString UColorPicker::ToHex(const FLinearColor& Color)
{
	const FColor SRGB = Color.ToFColorSRGB();
	return FString::Printf(TEXT("#%02X%02X%02X%02X"), SRGB.R, SRGB.G, SRGB.B, SRGB.A);
}

void UColorPicker::OnSwatchColorClicked(FLinearColor SelectedColor)
{
	OnColorButtonClicked(SelectedColor);
}
