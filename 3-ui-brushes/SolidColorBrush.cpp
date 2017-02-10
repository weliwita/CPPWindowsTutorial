#include "Precompiled.h"

D2D1_COLOR_F const COLOR_BLUE = { 0.26f, 0.56f, 0.87f, 1.0f };
D2D1_COLOR_F const COLOR_YELLOW = { 0.99f, 0.85f, 0.0f, 1.0f };
D2D1_COLOR_F const COLOR_WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };
D2D1_COLOR_F const COLOR_BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };

struct SampleWindow : DesktopWindow<SampleWindow>
{
	ComPtr<ID2D1SolidColorBrush> m_brush;

	void CreateDeviceResources()
	{
		HR(m_target->CreateSolidColorBrush(COLOR_WHITE,
			m_brush.ReleaseAndGetAddressOf()));
	}

	void Draw()
	{
		m_target->Clear(COLOR_BLUE);

		auto size = m_target->GetSize();

		m_brush->SetOpacity(1.0f);

		m_brush->SetColor(COLOR_BLACK);
		auto br = RectF(100.0f, 100.0f, size.width - 100.0f, 200.0f);
		m_target->FillRectangle(br, m_brush.Get());

		m_brush->SetColor(COLOR_WHITE);
		auto br2 = RectF(100.0f, 300.0f, size.width - 100.0f, 200.0f);
		m_target->FillRectangle(br2, m_brush.Get());

		m_brush->SetOpacity(0.5f);
		m_brush->SetColor(COLOR_YELLOW);
		auto ry = RectF(150.0f, 150.0f, size.width - 150.0f, 350.0f);
		m_target->FillRectangle(ry, m_brush.Get());
	}
};

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    SampleWindow window;
    window.Run();

   
}
